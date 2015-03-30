/*

    cRenderManager - Class that controls all the graphics elements

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


#include "crendermanager.h"
#include "../input/cinputmanager.h"
#include "../core/cconsole.h"

namespace onyx2d
{


cRenderManager::cRenderManager()
{
    //ctor
}

cRenderManager::~cRenderManager()
{
    for (int i=0; i<m_vDrawables.size(); i++)
        SAFE_RELEASE(m_vDrawables[i]);

    m_vDrawables.clear();

}

bool cRenderManager::DeviceStart(int width, int height, bool fullscreen, char* title, int argc, char**argv)
{

    //Starts freeGLUT
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize(width,height);
    glutCreateWindow(title);

    if (fullscreen)
    {
        stringstream mode;
        mode << width << "x" << height << ":32@60";
        //cout << mode.str() << endl;
        glutGameModeString(mode.str().c_str());
        glutEnterGameMode();
    }


    glutDisplayFunc(renderGlut);
    glutReshapeFunc(reshapeGlut);
    glutKeyboardFunc(keysGlut);
    glutKeyboardUpFunc(keysUpGlut);
    glutSpecialFunc(specialKeysGlut);
    glutSpecialUpFunc(specialKeysUpGlut);
    //glutJoystickFunc(joystickGlut);
	glutMouseFunc(mouseGlut);
	glutPassiveMotionFunc(motionGlut);
	glutIdleFunc(idleGlut);

    m_vSize.x = width;
    m_vSize.y = height;

    //m_vDrawables.push_back( (cDrawable*)rect );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Set the viewport
    glViewport(0, 0, width,height);

    //SetUp ortho camera
    glOrtho(0,width,0,height,-1.0,1.0);

    //Sets the clear screen color
    ClearColor.Set(0.5f,0.5f,0.5f);

    //Sets graphical options of the console
    Console()->Size.Set(width, CONSOLE_DEFAULT_HEIGHT);
    m_vDrawables.push_back(Console());
    Console()->Position.y = height - CONSOLE_DEFAULT_HEIGHT;
    Console()->Position.z = 1000;

    //Generate FrameBuffer, RenderBuffer and RenderTexture
    glGenFramebuffersEXT(1, &m_uFrameBufferID);
    glGenRenderbuffersEXT(1, &m_uRenderBufferID);
    glGenTextures(1, &m_uRenderTextureID);

    //Starts the framebuffer, renderbuffer, and render texture of the camera
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uFrameBufferID);

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_uRenderBufferID);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height); //It stores depth component
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    glBindTexture(GL_TEXTURE_2D, m_uRenderTextureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_uRenderBufferID);//Attach RenderBuffer to the FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_uRenderTextureID, 0); //Attach Texture to the FBO

    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
        Console()->AddRecord("cRenderManager : Error setting up frame buffer",RecordType::Error);
        return false;
    }

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    return true;
}


bool cRenderManager::DeviceEnd()
{
    if (glutGetWindow())
        glutDestroyWindow(glutGetWindow());
  	//exit(0);
	return true;
}

void cRenderManager::Cls()
{
    glClearColor(ClearColor.r,ClearColor.g,ClearColor.b, ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
}

void cRenderManager::Render()
{
    if (glutGetWindow())
    {

        //Sorts all the drawable elements by depth variable
        DrawablesDepthQuickSort(0, m_vDrawables.size());

        Cls();

        //Set the viewport
        //glViewport(0, 0, m_vSize.x,m_vSize.y);

        //SetUp ortho camera
        //glOrtho(0, m_vSize.x, 0, m_vSize.y,-1.0,1.0); // set to orthogonal projection

        for (int i=0; i<m_vDrawables.size(); i++)
        {
            //cout << i << endl;
            if (m_vDrawables[i]->Active)
                m_vDrawables[i]->Draw();
        }

        glutSwapBuffers();
    }
}

void cRenderManager::Update()
{
    if (glutGetWindow())
    {

        Render();
        glutMainLoopEvent();

        for (int i=0; i<m_vDrawables.size(); i++)
        {
            if (m_vDrawables[i]->Active)
                m_vDrawables[i]->Update();
        }
    }
}

void cRenderManager::Idle()
{
    if (glutGetWindow())
        glutPostRedisplay();
}

void cRenderManager::Reshape(int x, int y)
{
    if (glutGetWindow())
    {
        /*if (x != m_vSize.x || y != m_vSize.y)
        {
            glutReshapeWindow( m_vSize.x, m_vSize.y);
            cout << "Rehacemos" < < endl;
        }*/

        //cout << x << " " << y;

          //cout << "Reshape" << endl;
          /*float aspect = (float)x / (float)y;
          float halfy = (float)tan(1.0 / 2.0);
          float halfx = halfy * aspect;*/

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //Set the viewport
        glViewport(0, 0, m_vSize.x - (m_vSize.x - x), m_vSize.y - (m_vSize.y - y));

        m_vSize.x = x;
        m_vSize.y = y;

        //SetUp ortho camera
        glOrtho(0,x,0,y,-1.0,1.0);


    }
}

void cRenderManager::DebugText( float x, float y, std::string string) {
    glRasterPos2f(x, y);
    for (uint16 i=0; i<string.size(); i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
}



void cRenderManager::DrawablesDepthQuickSort(int ini, int end) {

         if(ini < end){
                //----Merge
                int i;
                int pivote, valor_pivote;
                cDrawable* temp;

                pivote = ini;
                valor_pivote = m_vDrawables[pivote]->Position.z;
                for (i=ini; i<end; i++){
                    if (m_vDrawables[i]->Position.z < valor_pivote){
                                        pivote++;
                                        temp=m_vDrawables[i];
                                        m_vDrawables[i]=m_vDrawables[pivote];
                                        m_vDrawables[pivote]=temp;

                        }
                }
                temp=m_vDrawables[ini];
                m_vDrawables[ini]=m_vDrawables[pivote];
                m_vDrawables[pivote]=temp;
                //-----

                DrawablesDepthQuickSort( ini, pivote-1);
                DrawablesDepthQuickSort(pivote+1, end);
         }

}

void cRenderManager::DeleteDrawable(cDrawable *dra)
{
    m_vDrawables.erase( find(m_vDrawables.begin(), m_vDrawables.end(), dra) );
    SAFE_RELEASE(dra);
}

Vector2<float> cRenderManager::RotateCoordinates(Vector2<float> coors, float angle, Vector2<float> rot_ref)
{
    Vector2<float> tmp;
    tmp.x = rot_ref.x+(coors.x-rot_ref.x)*cos(ToRads(angle))+(coors.y-rot_ref.y)*sin(ToRads(angle));
    tmp.y = rot_ref.y-(coors.x-rot_ref.x)*sin(ToRads(angle))+(coors.y-rot_ref.y)*cos(ToRads(angle));
    coors.Set(tmp.x,tmp.y);

    return coors;
}


void renderGlut(void){ RenderMngr()->Update();};
void reshapeGlut(int x, int y){ RenderMngr()->Reshape(x,y); };
void idleGlut(void){ RenderMngr()->Idle(); };
void keysGlut(unsigned char key, int x, int y){ InputMngr()->UpdateKeys(key, x ,y); }
void keysUpGlut(unsigned char key, int x, int y){ InputMngr()->UpdateKeysUp(key, x ,y); }
void specialKeysGlut(int key, int x, int y){ InputMngr()->UpdateSpecialKeys(key, x ,y); }
void specialKeysUpGlut(int key, int x, int y){ InputMngr()->UpdateSpecialKeysUp(key, x ,y); }
void mouseGlut(int button, int state, int x, int y){ InputMngr()->UpdateMouse(button, state, x, y); }
void motionGlut(int x, int y){ InputMngr()->UpdateMouseMotion(x,y); }


}//namespace onyx2d
