/*

    cContentManager - Manager that allow xml file based content loading

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


#ifndef CCONTENTMANAGER_H
#define CCONTENTMANAGER_H

#include "../onyx2d_defs.h"

#include "csingleton.h"
#include "utils/gen_func.h"
#include "xml/xml.h"
#include "../graphic/cimage.h"
#include "../sound/csound.h"

#include <iostream>

using namespace std;

namespace onyx2d
{

/*
namespace ContentType
{
    enum
    {
        Image = 0,
        Sound,
        Text,
    };
};
*/
class cContentManager : public cSingleton<cContentManager>
{


    public:
        cContentManager();
        virtual ~cContentManager();

        /**
        * Function that sets the path of content XML
        * @param file_p Path of the file
        * @return <i>true</i> if the file is founded, <i>false</i> in other cases
        */
        bool SetXMLPath(string file_p);

        /**
        * Function that gets the path of content XML
        * @return Path of the file
        */
        string GetXMLPath(){ return m_sXMLPath; };


        cImage* GetImage(string asset_n);
        cSound* GetSound(string asset_n);
        string  GetText (string asset_n);

        string  GetString(string category, string asset_n);

    protected:
    private:
        string m_sXMLPath;

};

inline cContentManager* ContentMngr()
{
        return cContentManager::GetSingletonPtr();
};

}
#endif // CCONTENTMANAGER_H
