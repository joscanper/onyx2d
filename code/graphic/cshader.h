/*

    cShader - Class that allows the compilation and use of shaders

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


#ifndef CSHADER_H
#define CSHADER_H

#include "../onyx2d_defs.h"
#include "../core/cobject.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace onyx2d
{

class cShader : cObject
{
    public:
        cShader();

        cShader(char* vert_file, char* frag_file);

        /**
            Copy Constructor
            @param sh Other Shader
        */
        cShader(cShader* sh);

        virtual ~cShader();

        void FromFile(char* vert_file, char* frag_file);
        void VertexFile(char* vert_file);
        void FragmentFile(char* frag_file);
        void VertexCode(const char* vert_code);
        void FragmentCode(const char* frag_code);
        bool Compile();
        void Begin();
        void End();

        // Submitting Uniform Variables. You can set varname to 0 and specifiy index retrieved with GetUniformLocation (best performance)
        bool       SetUniform1(GLcharARB* varname, GLfloat v0, GLint index = -1);  //!< Specify value of uniform variable. \param varname The name of the uniform variable.
        bool       SetUniform2(GLcharARB* varname, GLfloat v0, GLfloat v1, GLint index = -1);  //!< Specify value of uniform variable. \param varname The name of the uniform variable.
        bool       SetUniform3(GLcharARB* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLint index = -1);  //!< Specify value of uniform variable. \param varname The name of the uniform variable.
        bool       SetUniform4(GLcharARB* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLint index = -1);  //!< Specify value of uniform variable. \param varname The name of the uniform variable.

        bool       SetUniform1(GLcharARB* varname, GLint v0, GLint index = -1);  //!< Specify value of uniform integer variable. \param varname The name of the uniform variable.
        bool       SetUniform2(GLcharARB* varname, GLint v0, GLint v1, GLint index = -1); //!< Specify value of uniform integer variable. \param varname The name of the uniform variable.
        bool       SetUniform3(GLcharARB* varname, GLint v0, GLint v1, GLint v2, GLint index = -1); //!< Specify value of uniform integer variable. \param varname The name of the uniform variable.
        bool       SetUniform4(GLcharARB* varname, GLint v0, GLint v1, GLint v2, GLint v3, GLint index = -1); //!< Specify value of uniform integer variable. \param varname The name of the uniform variable.

        // Note: unsigned integers require GL_EXT_gpu_shader4 (for example GeForce 8800)
        bool       SetUniform1(GLcharARB* varname, GLuint v0, GLint index = -1); //!< Specify value of uniform unsigned integer variable. Only works if GL_EXT_gpu_shader4 is available. \param varname The name of the uniform variable.
        bool       SetUniform2(GLcharARB* varname, GLuint v0, GLuint v1, GLint index = -1); //!< Specify value of uniform unsigned integer variable. Only works if GL_EXT_gpu_shader4 is available. \param varname The name of the uniform variable.
        bool       SetUniform3(GLcharARB* varname, GLuint v0, GLuint v1, GLuint v2, GLint index = -1); //!< Specify value of uniform unsigned integer variable. Only works if GL_EXT_gpu_shader4 is available. \param varname The name of the uniform variable.
        bool       SetUniform4(GLcharARB* varname, GLuint v0, GLuint v1, GLuint v2, GLuint v3, GLint index = -1); //!< Specify value of uniform unsigned integer variable. Only works if GL_EXT_gpu_shader4 is available. \param varname The name of the uniform variable.

        // Arrays
        bool       SetUniform1fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform2fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform3fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform4fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.

        bool       SetUniform1iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform2iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform3iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.
        bool       SetUniform4iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index = -1); //!< Specify values of uniform array. \param varname The name of the uniform variable.

        bool       SetUniform1uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index = -1); //!< Specify values of uniform array. Requires GL_EXT_gpu_shader4. \param varname The name of the uniform variable.
        bool       SetUniform2uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index = -1); //!< Specify values of uniform array. Requires GL_EXT_gpu_shader4. \param varname The name of the uniform variable.
        bool       SetUniform3uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index = -1); //!< Specify values of uniform array. Requires GL_EXT_gpu_shader4. \param varname The name of the uniform variable.
        bool       SetUniform4uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index = -1); //!< Specify values of uniform array. Requires GL_EXT_gpu_shader4. \param varname The name of the uniform variable.

        bool       SetUniformMatrix2v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index = -1); //!< Specify values of uniform 2x2 matrix. \param varname The name of the uniform variable.
        bool       SetUniformMatrix3v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index = -1); //!< Specify values of uniform 3x3 matrix. \param varname The name of the uniform variable.
        bool       SetUniformMatrix4v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index = -1); //!< Specify values of uniform 4x4 matrix. \param varname The name of the uniform variable.

        // Receive Uniform variables:
        void       GetUniformv(GLcharARB* varname, GLfloat* values, GLint index = -1); //!< Receive value of uniform variable. \param varname The name of the uniform variable.
        void       GetUniformv(GLcharARB* varname, GLint*   values, GLint index = -1); //!< Receive value of uniform variable. \param varname The name of the uniform variable.
        void       GetUniformv(GLcharARB* varname, GLuint*  values, GLint index = -1); //!< Receive value of uniform variable. Requires GL_EXT_gpu_shader4 \param varname The name of the uniform variable.

        //GLfloat
        bool        SetVertexAttrib1(GLuint index, GLfloat v0); //!< Specify value of attribute.
        bool        SetVertexAttrib2(GLuint index, GLfloat v0, GLfloat v1); //!< Specify value of attribute.
        bool        SetVertexAttrib3(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2); //!< Specify value of attribute.
        bool        SetVertexAttrib4(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3); //!< Specify value of attribute.

        //GLdouble
        bool        SetVertexAttrib1(GLuint index, GLdouble v0); //!< Specify value of attribute.
        bool        SetVertexAttrib2(GLuint index, GLdouble v0, GLdouble v1); //!< Specify value of attribute.
        bool        SetVertexAttrib3(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2); //!< Specify value of attribute.
        bool        SetVertexAttrib4(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3); //!< Specify value of attribute.

        //GLshort
        bool        SetVertexAttrib1(GLuint index, GLshort v0); //!< Specify value of attribute.
        bool        SetVertexAttrib2(GLuint index, GLshort v0, GLshort v1); //!< Specify value of attribute.
        bool        SetVertexAttrib3(GLuint index, GLshort v0, GLshort v1, GLshort v2); //!< Specify value of attribute.
        bool        SetVertexAttrib4(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3); //!< Specify value of attribute.

        // Normalized Byte (for example for RGBA colors)
        bool        SetVertexAttribNormalizedByte(GLuint index, GLbyte v0, GLbyte v1, GLbyte v2, GLbyte v3); //!< Specify value of attribute. Values will be normalized.

        //GLint (Requires GL_EXT_gpu_shader4)
        bool        SetVertexAttrib1(GLuint index, GLint v0); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.
        bool        SetVertexAttrib2(GLuint index, GLint v0, GLint v1); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.
        bool        SetVertexAttrib3(GLuint index, GLint v0, GLint v1, GLint v2); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.
        bool        SetVertexAttrib4(GLuint index, GLint v0, GLint v1, GLint v2, GLint v3); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.

        //GLuint (Requires GL_EXT_gpu_shader4)
        bool        SetVertexAttrib1(GLuint index, GLuint v0); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4. \param v0 value of the first component
        bool        SetVertexAttrib2(GLuint index, GLuint v0, GLuint v1); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.
        bool        SetVertexAttrib3(GLuint index, GLuint v0, GLuint v1, GLuint v2); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.
        bool        SetVertexAttrib4(GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3); //!< Specify value of attribute. Requires GL_EXT_gpu_shader4.


    protected:
        GLhandleARB vs,fs;
        GLhandleARB program;

    private:
        GLint GetUniformLocation(const GLcharARB *name); //!< Retrieve Location (index) of a Uniform Variable
        void PrintInfoLog(GLhandleARB obj);
        char *ReadShaderFile(char* file);
};

}
#endif // CSHADER_H
