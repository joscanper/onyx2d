/*

    cTextureShader - Class that contain the basic code for a shader with texture

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


#include "ctextureshader.h"

namespace onyx2d
{

cTextureShader::cTextureShader()
{

    string vc = "";
           vc+= "void main() {";
           vc+= "  gl_TexCoord[0]=gl_MultiTexCoord0;";
           vc+= "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; ";
           vc+= "}";

    string fc = "uniform sampler2D tex;";
           fc+= "uniform float alpha;";
           fc+= "void main(){";
           fc+= "  vec4 color = texture2D(tex,gl_TexCoord[0].st);";
           fc+= "  color.a *= alpha;";
           fc+= "  gl_FragColor = color;";
           fc+= "}";

    VertexCode(vc.c_str());
    FragmentCode(fc.c_str());

    Compile();

    Alpha = 1.0f;

}

cTextureShader::~cTextureShader()
{
    //dtor
}

void cTextureShader::Update()
{
    SetUniform1("tex",0);
    SetUniform1("alpha",Alpha);

}

}
