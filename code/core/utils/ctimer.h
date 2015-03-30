/**

    cTimer Class

    High Resolution cTimer.
    This cTimer is able to measure the elapsed time with 1 micro-second accuracy
    in both Windows, Linux and Unix system

    Copyright (C) 2010-2011 Josue Candela Perdomo (josuecp.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

**/

#ifndef CTIMER_H_
#define CTIMER_H_

#include "../../onyx2d_defs.h"

#if defined(_WIN32) || defined(__WIN32__)// Windows system specific
    #include <windows.h>
#else// Unix based system specific
	#include <sys/time.h>
#endif


//namespace onyx2d
//{

	class cTimer
	{
	public:
            cTimer();                                   //! Default constructor
            ~cTimer();                                  //! Default destructor

			void   Start();                             //! Start timer
			void   Stop();                              //! Stop the timer
			double GetElapsedTime();                    //! Get elapsed time in second
			double GetElapsedTimeInSec();               //! Get elapsed time in second (same as getElapsedTime)
			double GetElapsedTimeInMilliSec();          //! Get elapsed time in milli-second
			double GetElapsedTimeInMicroSec();          //! Get elapsed time in micro-second


	protected:


	private:
			double startTimeInMicroSec;                 //! Starting time in micro-second
			double endTimeInMicroSec;                   //! Ending time in micro-second
			int    stopped;                             //! Stop flag
	#if defined(_WIN32) || defined(__WIN32__)// Windows system specific
			LARGE_INTEGER frequency;                    //! Ticks per second
			LARGE_INTEGER startCount;
			LARGE_INTEGER endCount;
	#else
			timeval startCount;
			timeval endCount;
	#endif
	};

//}
#endif // CTIMER_H_
