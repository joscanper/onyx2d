#include "cshading.h"
#include "../core/cconsole.h"

namespace onyx2d
{

cShading::cShading()
{

}

cShading::cShading(cShading* sh)
{
    m_vShaders = sh->m_vShaders;
    m_pAlpha = sh->m_pAlpha;
}

cShading::~cShading()
{

}

void cShading::InsertShader(cShader *shader, uint16 pos)
{
    vector<cShader*>::iterator it;
    it = m_vShaders.begin();
    it = it+pos;
    m_vShaders.insert(it, shader);
}

uint16 cShading::PushShader(cShader *shader)
{
    m_vShaders.push_back(shader);
    return m_vShaders.size()-1;
}

void cShading::RemoveShader(int index)
{
    if (index>=m_vShaders.size())
    {
        Console()->AddRecord("cShading : Out of index deleting the shader", RecordType::Warning);
        return;
    }
    m_vShaders.erase (m_vShaders.begin()+index);
}

void cShading::RemoveShader(cShader *shader)
{
   for(uint16 n = 0; n < m_vShaders.size(); n++)
    if (m_vShaders[n]== shader)
        m_vShaders.erase (m_vShaders.begin()+n);

}

void cShading::Update()
{


}

void cShading::ClearShaderList()
{
    m_vShaders.clear();
}



}
