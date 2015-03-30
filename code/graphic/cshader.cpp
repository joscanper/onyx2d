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


#include "cshader.h"
#include "..\core\cconsole.h"

namespace onyx2d
{

cShader::cShader()
{
    program = 0;
}

cShader::cShader(cShader* sh)
{
    vs = sh->vs;
    fs = sh->fs;
    program = sh->program;
}

cShader::cShader(char* vert_file, char* frag_file)
{
    program = 0;
    FromFile(vert_file, frag_file);
}


void cShader::FromFile(char* vert_file, char* frag_file)
{
    VertexFile(vert_file);
    FragmentFile(frag_file);
}

cShader::~cShader()
{

    glDetachObjectARB(program, vs);
    glDetachObjectARB(program, fs);

    glDeleteObjectARB(vs);
    glDeleteObjectARB(fs);
    glDeleteObjectARB(program);

}

void cShader::VertexFile(char* vert_file)
{
    char* vertSrc = ReadShaderFile(vert_file);
    if (vertSrc != NULL)
        VertexCode(vertSrc);
}

void cShader::FragmentFile(char* frag_file)
{
    char* fragSrc = ReadShaderFile(frag_file);
    if (fragSrc != NULL)
        FragmentCode(fragSrc);
}

void cShader::VertexCode(const char* vert_code)
{
    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
    glShaderSourceARB(vs, 1, (const char**)&vert_code, NULL);
}

void cShader::FragmentCode(const char* frag_code)
{
    fs = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    glShaderSourceARB(fs, 1, (const char**)&frag_code, NULL);
}

bool cShader::Compile()
{

    glCompileShaderARB(vs);
    GLint vertCompiled;
    glGetShaderiv(vs, GL_COMPILE_STATUS,&vertCompiled);
    if (!vertCompiled)
    {
        string log_str = "cShader : Error while compile vertex shader";
        Console()->AddRecord(log_str, RecordType::Error);
       // PrintInfoLog(vs);
        return false;
    }

    glCompileShader(fs);
    GLint fragCompiled;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fragCompiled);
        if (!vertCompiled)
    {
        string log_str = "cShader : Error while compile fragment shader";
        Console()->AddRecord(log_str, RecordType::Error);
       // PrintInfoLog(fs);
        return false;
    }



    // Create a program object and attach the two compiled shaders
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Link the program object and print out the info log
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    PrintInfoLog(program);

    if (!linked)
    {
        string log_str = "cShader : Error while linking shaders";
        Console()->AddRecord(log_str, RecordType::Error);
        return false;
    }

    GLenum wasError = glGetError();
    if(wasError){
        string log_str = "cShader : Error compiling shader";
        Console()->AddRecord(log_str, RecordType::Error);
        return false;
    }

    return true;
}

void cShader::PrintInfoLog(GLhandleARB obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
                     &infologLength);

    if (infologLength > 0)
    {
    infoLog = (char *)malloc(infologLength);
    glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
        cout << infoLog;
    free(infoLog);
    }
}

void cShader::Begin()
{
    glUseProgramObjectARB(program);

    Update();
}

void cShader::End()
{
    glUseProgramObjectARB(0);
}

char* cShader::ReadShaderFile(char *fn)
{
    FILE *fp;
    char *content = NULL;

    int count=0;

    if (fn != NULL) {

        fp = fopen(fn,"rt");

        if (fp != NULL) {

                    fseek(fp, 0, SEEK_END);
                count = ftell(fp);
                rewind(fp);
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
            if (content == NULL)
            {
                string log_str = "cShader : The file was empty : ";
                log_str += fn;
                Console()->AddRecord(log_str, RecordType::Warning);
            }
        }else{
            string log_str = "cShader : File not found : ";
            log_str += fn;
            Console()->AddRecord(log_str, RecordType::Error);
        }
    }



    return content;
}

//---------------------------------


bool cShader::SetUniform1(GLcharARB* varname, GLfloat v0, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index


    glUniform1f(loc, v0);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform2(GLcharARB* varname, GLfloat v0, GLfloat v1, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2f(loc, v0, v1);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform3(GLcharARB* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3f(loc, v0, v1, v2);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform4(GLcharARB* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4f(loc, v0, v1, v2, v3);

    return true;
}


bool cShader::SetUniform1(GLcharARB* varname, GLint v0, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform1i(loc, v0);

    return true;
}

bool cShader::SetUniform2(GLcharARB* varname, GLint v0, GLint v1, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2i(loc, v0, v1);


    return true;
}


bool cShader::SetUniform3(GLcharARB* varname, GLint v0, GLint v1, GLint v2, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3i(loc, v0, v1, v2);

    return true;
}


bool cShader::SetUniform4(GLcharARB* varname, GLint v0, GLint v1, GLint v2, GLint v3, GLint index)
{
    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4i(loc, v0, v1, v2, v3);

    return true;
}

bool cShader::SetUniform1(GLcharARB* varname, GLuint v0, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform1uiEXT(loc, v0);

    return true;
}

bool cShader::SetUniform2(GLcharARB* varname, GLuint v0, GLuint v1, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2uiEXT(loc, v0, v1);


    return true;
}

bool cShader::SetUniform3(GLcharARB* varname, GLuint v0, GLuint v1, GLuint v2, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3uiEXT(loc, v0, v1, v2);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform4(GLcharARB* varname, GLuint v0, GLuint v1, GLuint v2, GLuint v3, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4uiEXT(loc, v0, v1, v2, v3);

    return true;
}
//-----------------------------------------------------------------------------

bool cShader::SetUniform1fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform1fv(loc, count, value);

    return true;
}
bool cShader::SetUniform2fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2fv(loc, count, value);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform3fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index)
{


    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3fv(loc, count, value);

    return true;
}


bool cShader::SetUniform4fv(GLcharARB* varname, GLsizei count, GLfloat *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4fv(loc, count, value);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform1iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform1iv(loc, count, value);

    return true;
}


bool cShader::SetUniform2iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index)
{


    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2iv(loc, count, value);

    return true;
}


bool cShader::SetUniform3iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3iv(loc, count, value);

    return true;
}

bool cShader::SetUniform4iv(GLcharARB* varname, GLsizei count, GLint *value, GLint index)
{
    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4iv(loc, count, value);

    return true;
}


bool cShader::SetUniform1uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform1uivEXT(loc, count, value);

    return true;
}

bool cShader::SetUniform2uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform2uivEXT(loc, count, value);

    return true;
}


bool cShader::SetUniform3uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index)
{


    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform3uivEXT(loc, count, value);

    return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetUniform4uiv(GLcharARB* varname, GLsizei count, GLuint *value, GLint index)
{

    GLint loc;
    if (varname)
      loc =  GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniform4uivEXT(loc, count, value);

    return true;
}


bool cShader::SetUniformMatrix2v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index)
{

    GLint loc;
    if (varname)
      loc =  GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniformMatrix2fv(loc, count, transpose, value);

    return true;
}


bool cShader::SetUniformMatrix3v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniformMatrix3fv(loc, count, transpose, value);

    return true;
}


bool cShader::SetUniformMatrix4v(GLcharARB* varname, GLsizei count, GLboolean transpose, GLfloat *value, GLint index)
{
    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return false;  // can't find variable / invalid index

    glUniformMatrix4fv(loc, count, transpose, value);

    return true;
}

void cShader::GetUniformv(GLcharARB* varname, GLfloat* values, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return;  // can't find variable / invalid index

	glGetUniformfv(program, loc, values);

}

void cShader::GetUniformv(GLcharARB* varname, GLint* values, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return;  // can't find variable / invalid index

	glGetUniformiv(program, loc, values);

}

void cShader::GetUniformv(GLcharARB* varname, GLuint* values, GLint index)
{

    GLint loc;
    if (varname)
       loc = GetUniformLocation(varname);
    else
       loc = index;

    if (loc==-1)
       return;  // can't find variable / invalid index

	glGetUniformuivEXT(program, loc, values);

}

bool cShader::SetVertexAttrib1(GLuint index, GLfloat v0)
{

   glVertexAttrib1f(index, v0);

   return true;
}

bool cShader::SetVertexAttrib2(GLuint index, GLfloat v0, GLfloat v1)
{

   glVertexAttrib2f(index, v0, v1);

   return true;
}

bool cShader::SetVertexAttrib3(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2)
{

    glVertexAttrib3f(index, v0, v1, v2);

    return true;
}

bool cShader::SetVertexAttrib4(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{

   glVertexAttrib4f(index, v0, v1, v2, v3);

   return true;
}


bool cShader::SetVertexAttrib1(GLuint index, GLdouble v0)
{

   glVertexAttrib1d(index, v0);

   return true;
}

bool cShader::SetVertexAttrib2(GLuint index, GLdouble v0, GLdouble v1)
{

   glVertexAttrib2d(index, v0, v1);

   return true;
}

bool cShader::SetVertexAttrib3(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2)
{

   glVertexAttrib3d(index, v0, v1, v2);

   return true;
}

bool cShader::SetVertexAttrib4(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{

   glVertexAttrib4d(index, v0, v1, v2, v3);

   return true;
}

bool cShader::SetVertexAttrib1(GLuint index, GLshort v0)
{


   glVertexAttrib1s(index, v0);

   return true;
}

bool cShader::SetVertexAttrib2(GLuint index, GLshort v0, GLshort v1)
{

   glVertexAttrib2s(index, v0, v1);

   return true;
}


bool cShader::SetVertexAttrib3(GLuint index, GLshort v0, GLshort v1, GLshort v2)
{

   glVertexAttrib3s(index, v0, v1, v2);

   return true;
}

bool cShader::SetVertexAttrib4(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3)
{

   glVertexAttrib4s(index, v0, v1, v2, v3);

   return true;
}

//----------------------------------------------------------------------------

bool cShader::SetVertexAttribNormalizedByte(GLuint index, GLbyte v0, GLbyte v1, GLbyte v2, GLbyte v3)
{

   glVertexAttrib4Nub(index, v0, v1, v2, v3);

   return true;
}

//-----------------------------------------------------------------------------

bool cShader::SetVertexAttrib1(GLuint index, GLint v0)
{
   glVertexAttribI1i(index, v0);
   return true;
}


bool cShader::SetVertexAttrib2(GLuint index, GLint v0, GLint v1)
{

   glVertexAttribI2iEXT(index, v0, v1);

   return true;
}


bool cShader::SetVertexAttrib3(GLuint index, GLint v0, GLint v1, GLint v2)
{

   glVertexAttribI3iEXT(index, v0, v1, v2);

   return true;
}

bool cShader::SetVertexAttrib4(GLuint index, GLint v0, GLint v1, GLint v2, GLint v3)
{
   glVertexAttribI4iEXT(index, v0, v1, v2, v3);

   return true;
}

bool cShader::SetVertexAttrib1(GLuint index, GLuint v0)
{
   glVertexAttribI1uiEXT(index, v0);

   return true;
}


bool cShader::SetVertexAttrib2(GLuint index, GLuint v0, GLuint v1)
{

   glVertexAttribI2uiEXT(index, v0, v1);

   return true;
}


bool cShader::SetVertexAttrib3(GLuint index, GLuint v0, GLuint v1, GLuint v2)
{

   glVertexAttribI3uiEXT(index, v0, v1, v2);

   return true;
}

bool cShader::SetVertexAttrib4(GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{

   glVertexAttribI4uiEXT(index, v0, v1, v2, v3);

   return true;
}


//---------------------------------

GLint cShader::GetUniformLocation(const GLcharARB *name)
{
	GLint loc;

	loc = glGetUniformLocationARB(program, name);
	/*if (loc == -1)
	{
        string log_str = "cShader : Can't find uniform variable : ";
         log_str +=  name;
        Console()->AddRecord(log_str, RecordType::Error);
	}*/

    //CHECK_GL_ERROR();
	return loc;
}

}
