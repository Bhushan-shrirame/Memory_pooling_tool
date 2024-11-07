/*********************************************************************************
*  Copyright (c) 2010-2011, Elliott Cooper-Balis
*                             Paul Rosenfeld
*                             Bruce Jacob
*                             University of Maryland 
*                             dramninjas [at] gmail [dot] com
*  All rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*  
*     * Redistributions of source code must retain the above copyright notice,
*        this list of conditions and the following disclaimer.
*  
*     * Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
*  
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************************/




#include <stdio.h>
#include "dramsim_test.h"

using namespace DRAMSim;

int x=0;

/* callback functors */
void some_object::read_complete(int nid, uint64_t tid, uint64_t sc, int mem_id, unsigned id, uint64_t address, uint64_t clock_cycle)
{
	x++;
	uint64_t diff=clock_cycle-sc;
	printf("Mem_id: %d Trans_id: %ld node_id: %d [Callback] write complete: %d 0x%lx  diff=%ld \n", mem_id, tid, nid, id, address,diff);
}

void some_object::write_complete(int nid, uint64_t tid, uint64_t sc, int mem_id, unsigned id, uint64_t address, uint64_t clock_cycle)
{
	x++;
	uint64_t diff=clock_cycle-sc;
	printf("Mem_id: %d Trans_id: %ld node_id: %d [Callback] write complete: %d 0x%lx  diff=%ld \n", mem_id, tid, nid, id, address,diff);
}

/* FIXME: this may be broken, currently */
void power_callback(double a, double b, double c, double d)
{
//	printf("power callback: %0.3f, %0.3f, %0.3f, %0.3f\n",a,b,c,d);
}


int some_object::add_one_and_run(MultiChannelMemorySystem *mem, uint64_t addr, uint64_t tid, uint64_t sc, int nid)
{
//	int t=(tid-1)*4;

	//create a transaction and add it 
	bool isWrite = false; 
	mem->addTransaction(isWrite, addr, nid, tid,sc);

/*	mem->addTransaction(isWrite, addr, nid, t+2,sc);

	// send a read to channel 1 on the same cycle 
	addr = 1LL<<33 | addr; 


	for (int i=0; i<100; i++)
	{
		mem->update();
	}

	// add another some time in the future 

	// send a write to channel 0 
	addr = 0x9000c0; 
	isWrite = true; 
	mem->addTransaction(isWrite, addr, nid, t+3,sc);

	mem->addTransaction(isWrite, addr, nid, t+4,sc);


	for(int i=0;i<85;i++)
	{
		mem->update();
	}
	int cycle=-20;
	 //do a bunch of updates (i.e. clocks) -- at some point the callback will fire 
	for (int i=0; i<cycle; i++)
	{
		mem->update();
	}

	get a nice summary of this epoch
	mem->printStats(true);*/

	return 0;
}

some_object obj;

TransactionCompleteCB *read_cb= new Callback<some_object, void, int, uint64_t, uint64_t, uint64_t, int, unsigned, uint64_t, uint64_t>(&obj, &some_object::read_complete);
TransactionCompleteCB *write_cb= new Callback<some_object, void, int, uint64_t, uint64_t, uint64_t, int, unsigned, uint64_t, uint64_t>(&obj, &some_object::write_complete);
MultiChannelMemorySystem *local_mem[3];

int main()
{
	//some_object obj;
	//TransactionCompleteCB *read_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::read_complete);
	//TransactionCompleteCB *write_cb = new Callback<some_object, void, unsigned, uint64_t, uint64_t>(&obj, &some_object::write_complete);

	/* pick a DRAM part to simulate */
	/*MultiChannelMemorySystem *mem = getMemorySystemInstance("ini/DDR3_micron_8M_8B_x16_sg15.ini", "system.ini", "..", "example_app", 16384); 


	mem->RegisterCallbacks(read_cb, write_cb, power_callback);
	MultiChannelMemorySystem *mem2 = getMemorySystemInstance("ini/DDR2_micron_16M_8b_x8_sg3E.ini", "system.ini", "..", "example_app", 16384); 

	mem2->RegisterCallbacks(read_cb, write_cb, power_callback);

	MultiChannelMemorySystem *mem3 = getMemorySystemInstance("ini/DDR2_micron_16M_8b_x8_sg3E.ini", "system.ini", "..", "example_app", 16384); 

	mem3->RegisterCallbacks(read_cb, write_cb, power_callback);*/

for(int i=0;i<3;i++)
	{
		local_mem[i]= getMemorySystemInstance(i,"ini/DDR4_x16_2400.ini", "system.ini", "..", "example_app", 1024);
		local_mem[i]->RegisterCallbacks(read_cb,write_cb,power_callback);	//DRAM simulator function
	}	

	//local_mem[0]->setCPUClockSpeed(2500000000);

	printf("dramsim_test main()\n");
	printf("-----MEM1------\n");
	
//	for(int i=0;i<10000000;i++)
	
	for(int i=0;i<10;i++)
		obj.add_one_and_run(local_mem[0], 0x200040UL, 1,1,1,1);
	for(int i=0;i<500;i++)
	{
		local_mem[0]->update();
	}	

//	obj.add_one_and_run(local_mem[1], 0x200040UL, 2,2,2);
	//obj.add_one_and_run(local_mem[2], 0x200040UL, 1);

	//printf("-----MEM2------\n");
	//obj.add_one_and_run(local_mem[0], 0x2ffc0UL, 2);
	//obj.add_one_and_run(local_mem[1], 0x2ffc0UL, 2);
	//obj.add_one_and_run(local_mem[2], 0x2ffc0UL, 2);
	
	for(int i=0;i<10000;i++)
	{
		local_mem[0]->update();
	}

	printf("\ntotal mem access: %d", x);

	return 0; 
}

