/*

    cDate - Class that contain a specific date (month, year and day)

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

#pragma once

#ifndef CDATE_H_
#define CDATE_H_

#include "../onyx2d_defs.h"
#include <string>

namespace onyx2d
{

	class cDate
	{
	private:
		uint8	 m_uDay;
		uint8  m_uMonth;
		uint16 m_uYear;

	public:

		void setDay(uint8 day){ m_uDay = day; };
		void setMonth(uint8 month){ m_uMonth = month; };
		void setYear(uint16 year){ m_uYear = year; };

		uint8 getDay(){ return m_uDay; };
		uint8 getMonth(){ return m_uMonth; };
		uint16 getYear(){ return m_uYear; };
/*
		std::string getDate(std::string format)
		{
				//TODO
		};
*/
		bool setDate(uint8 day, uint8 month, uint16 year)
		{
			setDay(day);
			setMonth(month);
			setYear(year);
		}


	};

};


#endif
