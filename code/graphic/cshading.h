#ifndef CSHADING_H
#define CSHADING_H

#include "cdrawable.h"
#include "cshader.h"
#include <vector>

using namespace std;

namespace onyx2d
{

class cShading : public cDrawable
{

    public:
        cShading();

        /**
            Copy Constructor
            @param sh Other shading object
        */
        cShading(cShading* sh);

        virtual ~cShading();

        void InsertShader(cShader *shader, uint16 pos);

        uint16 PushShader(cShader *shader);

        void   RemoveShader(int index);

        void   RemoveShader(cShader *shader);

        void   ClearShaderList();

    protected:
        vector<cShader*> m_vShaders;
        cShader* m_pAlpha;
    private:

        void Update();
};

}

#endif // CSHADING_H
