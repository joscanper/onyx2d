/*

    cConsole - Class that controls graphic console, text console and logging

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

#ifndef CCONSOLE_H_
#define CCONSOLE_H_

#define CONSOLE_DEFAULT_HEIGHT 200

#include <vector>

#include "csingleton.h"
#include "cdate.h"
#include "../graphic/cdrawable.h"
#include "../graphic/cimage.h"

#include "../onyx2d_defs.h"


namespace onyx2d
{
    namespace RecordType
    {
        enum{
        None = 0,
        Info,
        Error,
        Warning,
        };
    };

	class cConsole: public cSingleton<cConsole>, public cDrawable
	{
		private:

			class cConsoleRecord
			{
				public:
					std::string Text;
					uint8       Type;
					cDate		Date;
			};

			/*cImage *m_pWarning;
			cImage *m_pError;
			cImage *m_pInfo;

			cImage *m_pArrowUp;
			cImage *m_pArrowDown;*/

			std::vector<cConsoleRecord>	m_vRegistry;

		public:

			/**
			* Function that add a record to console registry
			* @param text Text that going to be added to the registry
			* @param type Type of the record (view namespace RecordType)
			*/
			bool AddRecord(std::string text,uint8 type);

			/**
			* Function that shows the graphic console
			*/
			void Update(){};

			/**
			* Function that shows the graphic console
			*/
			void Draw();

			/**
			* Function that release all class object
			*/
			void Release();


			/**
			* Function that setup the initial graphic configuration
            * @param width Width of the console
            * @param height Height of the console
			*/
			void Init(uint32 width, uint32 height);

	};

	inline cConsole* Console()
	{
		return cConsole::GetSingletonPtr();
	};


};

#endif
