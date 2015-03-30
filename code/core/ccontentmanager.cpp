#include "ccontentmanager.h"
#include "cconsole.h"

namespace onyx2d
{

    cContentManager::cContentManager()
    {
        m_sXMLPath = "";
    }

    cContentManager::~cContentManager()
    {
        //dtor
    }


    bool cContentManager::SetXMLPath(string file_path)
    {
        if (FileExist(file_path))
        {
            m_sXMLPath = file_path;
            return true;
        }else{
            string msg = "cContentManager : File not found : ";
            msg += file_path;
            Console()->AddRecord(msg, RecordType::Error);
            return false;
        }
    }

    cImage* cContentManager::GetImage(string asset_n)
    {
        return new cImage(GetString("images",asset_n));
    }

    cSound* cContentManager::GetSound(string asset_n)
    {
        return new cSound(GetString("sounds",asset_n));
    }

    string  cContentManager::GetText(string asset_n)
    {
        return GetString("texts",asset_n);
    }

    string cContentManager::GetString(string category, string asset_n)
    {
        string value = "";
        cXMLDocument doc(m_sXMLPath.c_str());
        if(!doc.LoadFile()){
            string err = "cContentManager : File not found : ";
            err += m_sXMLPath;
            Console()->AddRecord(err,RecordType::Error);
            return value;
        }

        cXMLElement *pElem;	  // current element
        cXMLElement *pRoot = doc.RootElement();
        cXMLElement* asset_s;

        bool found = false;

        pElem = pRoot->FirstChildElement( category );
        if (pElem)
        {
            asset_s =  pElem->FirstChildElement( asset_n );
            if ( asset_s )
                found = true;
        }

        if (!found)
        {
            string err = "cContentManager : Asset not found : ";
            err += asset_n;
            Console()->AddRecord(err,RecordType::Error);

        }
        else
        {
            value = asset_s->FirstChild()->Value();

        }

        return value;
    }
}
