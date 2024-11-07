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



#include <stdint.h> // uint64_t

#ifndef CALLBACK_H
#define CALLBACK_H

namespace DRAMSim
{

template <typename ReturnT, typename Param1T, typename Param2T,
typename Param3T, typename Param4T, typename Param5T, typename Param6T, typename Param7T, typename Param8T>
class CallbackBase
{
public:
	virtual ~CallbackBase() = 0;
	virtual ReturnT operator()(Param1T, Param2T, Param3T, Param4T, Param5T, Param6T, Param7T, Param8T) = 0;
};

template <typename Return, typename Param1T, typename Param2T, typename Param3T, typename Param4T, typename Param5T, typename Param6T, typename Param7T, typename Param8T>
DRAMSim::CallbackBase<Return,Param1T,Param2T,Param3T,Param4T,Param5T,Param6T,Param7T, Param8T>::~CallbackBase() {}

template <typename ConsumerT, typename ReturnT,
typename Param1T, typename Param2T, typename Param3T, typename Param4T, typename Param5T, typename Param6T, typename Param7T, typename Param8T >
class Callback: public CallbackBase<ReturnT,Param1T,Param2T,Param3T,Param4T,Param5T,Param6T,Param7T,Param8T>
{
private:
	typedef ReturnT (ConsumerT::*PtrMember)(Param1T,Param2T,Param3T,Param4T,Param5T,Param6T,Param7T,Param8T);

public:
	Callback( ConsumerT* const object, PtrMember member) :
			object(object), member(member)
	{
	}

	Callback( const Callback<ConsumerT,ReturnT,Param1T,Param2T,Param3T,Param4T,Param5T,Param6T,Param7T,Param8T>& e ) :
			object(e.object), member(e.member)
	{
	}

	ReturnT operator()(Param1T param1, Param2T param2, Param3T param3, Param4T param4, Param5T param5, Param6T param6, Param7T param7, Param8T param8)
	{
		return (const_cast<ConsumerT*>(object)->*member)
		       (param1,param2,param3,param4,param5,param6,param7,param8);
	}

private:

	ConsumerT* const object;
	const PtrMember  member;
};

typedef CallbackBase <void, int, uint64_t, uint64_t, uint64_t, int, unsigned, uint64_t, uint64_t> TransactionCompleteCB;
} // namespace DRAMSim

#endif
