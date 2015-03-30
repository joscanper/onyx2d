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

#include "cconsole.h"
#include "../graphic/crendermanager.h"

namespace onyx2d
{


bool cConsole::AddRecord(std::string text, uint8 type)
	{
		std::string sign;

		switch (type)
		{
			case(RecordType::Error):
				{
					sign = "[!] : ";
				}
					break;
			case(RecordType::Info):
				{
					sign = "(i) : ";
				}
					break;
			case(RecordType::Warning):
				{
					sign = "[?] : ";
				}
					break;
		}

		std::string text2 = sign + text + "\n";
		printf(text2.c_str());

		cConsoleRecord record;

		record.Text = text;
		record.Type = type;

		m_vRegistry.push_back(record);

		return true;
	}

	void cConsole::Init(uint32 width, uint32 height)
	{
		//Setup the position
		Console()->Position.Set(0,height,0);

		//Setup the size
		Size.Set(width, height-20);

        std::string str = "Onyx Illusion 2D Engine v";
        str += ONYX2D_VERSION;
        AddRecord(str.c_str(),0);
        AddRecord("Copyright (C) 2010-2011 Josue Candela Perdomo",0);
        AddRecord("---------------------------------------------",0);

		//Load the images
		//m_pWarning = new cImage("data/images/console/warning.png");
		//m_pError   = new cImage("data/images/console/error.png");
		//m_pInfo    = new cImage("data/images/console/info.png");

		//m_pArrowUp    = new cImage("data/images/console/arrow_up.png");
		//m_pArrowDown  = new cImage("data/images/console/arrow_down.png");

		Active = false;
	}

	void cConsole::Draw()
	{
		if (Active)
		{

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();


			//m_pWarning->Active(false);
			//m_pError->Active(false);
			//m_pInfo->Active(false);

			//m_pArrowUp->setRelativePosition(getSize().x-18,-18);
			//m_pArrowDown->setRelativePosition(getSize().x-18,-getSize().y+2);


			// Enable alpha blending in the object
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			glColor4f(0,0,0,0.3f);

            glTranslated(Position.x, Position.y,0);

			// Dark background
			glBegin(GL_QUADS);
				glVertex2d(0,0);
				glVertex2d(Size.x,0);
				glVertex2d(Size.x,Size.y);
				glVertex2d(0,Size.y);
			glEnd();

			// Left bar
			glBegin(GL_QUADS);
				glVertex2d(0,0);
				glVertex2d(20,0);
				glVertex2d(20,Size.y+20);
				glVertex2d(0,Size.y+20);
			glEnd();

			// Right bar
			/*glBegin(GL_QUADS);
				glVertex2d(getPosition().x+getSize().x,getPosition().y);
				glVertex2d(getPosition().x+getSize().x-20,getPosition().y);
				glVertex2d(getPosition().x+getSize().x-20,getPosition().y-getSize().y);
				glVertex2d(getPosition().x+getSize().x,getPosition().y-getSize().y);
			glEnd();*/

			//Outlines
			/*glColor4f(0.7f,0.7f,0.7f,1.0f);

			glBegin(GL_LINES);
				glVertex2d(getPosition().x,getPosition().y);
				glVertex2d(getPosition().x+getSize().x,getPosition().y);
				glVertex2d(getPosition().x+getSize().x,getPosition().y-getSize().y);
				glVertex2d(getPosition().x,getPosition().y-getSize().y);
			glEnd();

			glBegin(GL_LINES);
				glVertex2d(getPosition().x+getSize().x,getPosition().y-getSize().y-20);
				glVertex2d(getPosition().x,getPosition().y-getSize().y-20);
			glEnd();*/

			glColor4f(1.0f,1.0f,1.0f,1.0f);

			//uint32 rely = getPosition()
			float y    = Position.y-(Size.y*2)+5;
			float x    = Position.x+22;

			//Write prompt
			RenderMngr()->DebugText(x-18,y,">>");

            y=y+20;

			//Write register (from bottom to top)
			for ( uint32 i=m_vRegistry.size(); i>0; i--)
			{
				if (y<Position.y)
				{
				    if (m_vRegistry.at(i-1).Type != RecordType::None)
					{
                        //Background color
                        switch(m_vRegistry[i-1].Type)
                        {
                            case(RecordType::Error):
                                    glColor4f(1.0f,0.0f,0.0f,0.5f);
                                    break;
                            case(RecordType::Info):
                                    glColor4f(0.0f,0.0f,1.0f,0.5f);
                                    break;
                            case(RecordType::Warning):
                                    glColor4f(1.0f,0.7f,0.0f,0.5f);
                                    break;
                        }

                        glBegin(GL_QUADS);
                            glVertex2d(0,y+15);
                            glVertex2d(Size.x,y+15);
                            glVertex2d(Size.x,y-5);
                            glVertex2d(0,y-5);
                        glEnd();
					}

					//Registry text line
					glColor4f(1.0f,1.0f,1.0f,1.0f);
					RenderMngr()->DebugText(x+2,y, m_vRegistry.at(i-1).Text);

					y=y+20;
				}else{
					break;
				}
			}

			glDisable(GL_BLEND);

		}
	}

	void cConsole::Release()
	{

	}

}
