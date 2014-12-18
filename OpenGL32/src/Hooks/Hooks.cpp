/**  © 2013, Brandon T. All Rights Reserved.
  *
  *  This file is part of the GLX Library.
  *  GLX is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  GLX is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with GLX.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "Hooks.hpp"

void GLHook_glActiveTextureARB(GLenum texture)
{
    InfoLogger.texture.LogActiveTexture(texture);
	ptr_glActiveTextureARB(texture);
}

void GLHook_glBindBufferARB(GLenum target, GLuint buffer)
{
    InfoLogger.model.LogBindBuffer(target, buffer);
	ptr_glBindBufferARB(target, buffer);
}

void GLHook_glBindTexture(GLenum target, GLuint texture)
{
    InfoLogger.map.LogBindTexture(target, texture);
    InfoLogger.texture.LogBindTexture(target, texture);
    InfoLogger.font.LogBindTexture(texture);
	ptr_glBindTexture(target, texture);
}

void GLHook_glBufferDataARB(GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage)
{
    InfoLogger.model.LogBufferData(target, size, data, usage);
	ptr_glBufferDataARB(target, size, data, usage);
}

void GLHook_glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data)
{
    InfoLogger.model.LogBufferSubData(target, offset, size, data);
	ptr_glBufferSubDataARB(target, offset, size, data);
}

void GLHook_glCallList(GLuint list)
{
    if (FontsEnabled)
    {
        InfoLogger.font.LogCallList(list);
    }
	ptr_glCallList(list);
}

void GLHook_glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
    InfoLogger.font.LogColour(red, green, blue, alpha);
	ptr_glColor4ub(red, green, blue, alpha);
}

void GLHook_glDeleteBuffersARB(GLsizei n,  const GLuint* buffers)
{
    for (int I = 0; I < n; ++I)
    {
        auto it = std::find_if(ModelBuffer::Buffers.begin(), ModelBuffer::Buffers.end(), [&](const ModelBuffer &B) {return B.ID == buffers[I];});
        if (it != ModelBuffer::Buffers.end())
        {
            ModelBuffer::Buffers.erase(it);
        }
    }
    ModelBuffer::Buffers.shrink_to_fit();
    ptr_glDeleteBuffers(n, buffers);
}

void GLHook_glDeleteLists(GLuint list, GLsizei range)
{
    for (std::size_t I = list; I < list + range; ++I)
    {
        auto it = std::find_if(Font::Fonts.begin(), Font::Fonts.end(), [&](const Font &F) {return F.ID == I;});
        if (it != Font::Fonts.end())
        {
            Font::Fonts.erase(it);
        }
    }
    Font::Fonts.shrink_to_fit();
	ptr_glDeleteLists(list, range);
}

void GLHook_glDeleteTextures(GLsizei n, const GLuint *textures)
{
    for (int I = 0; I < n; ++I)
    {
        auto it = Texture::IDMap.find(textures[I]);
        if (it != Texture::IDMap.end())
        {
            Texture::IDMap.erase(it);
        }

        auto jt = std::remove_if(Texture::Textures.begin(), Texture::Textures.end(), [&](const Texture &T) {return T.ID == textures[I];});
        if (jt != Texture::Textures.end())
        {
            Texture::Textures.erase(jt);
        }
    }
    Texture::Textures.shrink_to_fit();
	ptr_glDeleteTextures(n, textures);
}

void GLHook_glDisable(GLenum cap)
{
	ptr_glDisable(cap);
}

void GLHook_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    InfoLogger.model.LogDrawElements(mode, count, type, indices);
	ptr_glDrawElements(mode, count, type, indices);
}

void GLHook_glEnable(GLenum cap)
{
	ptr_glEnable(cap);
}

void GLHook_glEnd(void)
{
    ptr_glEnd();
}

void GLHook_glEndList(void)
{
    InfoLogger.font.LogEndList();
	ptr_glEndList();
}

GLuint GLHook_glGenLists(GLsizei range)
{
    InfoLogger.font.LogGenList(range);
    return ptr_glGenLists(range);
}

void GLHook_glGenTextures(GLsizei n, GLuint *textures)
{
    InfoLogger.font.LogGenTextures(n, textures);
	ptr_glGenTextures(n, textures);
}

void GLHook_glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t)
{
	ptr_glMultiTexCoord2fARB(target, s, t);
}

void GLHook_glNewList(GLuint list, GLenum mode)
{
    InfoLogger.font.LogNewList(list, mode);
	ptr_glNewList(list, mode);
}

void GLHook_glPixelStorei(GLenum pname, GLint para)
{
    InfoLogger.map.LogPixelStore(pname, para);
	ptr_glPixelStorei(pname, para);
}

void GLHook_glPopMatrix(void)
{
    InfoLogger.model.LogPopMatrix();
	ptr_glPopMatrix();
	InfoLogger.matrices.LogMatrix();
}

void GLHook_glTexCoord2f(GLfloat s,  GLfloat t)
{
	ptr_glTexCoord2f(s,  t);
}

void GLHook_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid *pixels)
{
    InfoLogger.map.Log2DImageTexture(target, width, height, pixels);
    InfoLogger.texture.Log2DImageTexture(target, pixels, width, height);
	ptr_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void GLHook_glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    InfoLogger.font.LogTranslate(x, y, z);
	ptr_glTranslatef(x, y, z);
}

void GLHook_glVertex2f(GLfloat x, GLfloat y)
{
    InfoLogger.map.LogVertices(x, y);
    InfoLogger.texture.LogVerticesF(x, y); //ADDED 2014-12-17 10:40PM to hook compass and special animated textures.
	ptr_glVertex2f(x, y);
}

void GLHook_glVertex2i(GLint x, GLint y)
{
    InfoLogger.font.LogVertices(x, y);
    InfoLogger.texture.LogVerticesI(x, y);
	ptr_glVertex2i(x, y);
}

void GLHook_glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
    InfoLogger.model.LogVertexPointer(size, type, stride, pointer);
	ptr_glVertexPointer(size, type, stride, pointer);
}

PROC GLHook_wglGetProcAddress(LPCSTR lpszProc)
{
    std::string FunctionCalled(lpszProc);
    if (FunctionCalled == "glActiveTextureARB")
    {
        xDetour(ptr_glActiveTextureARB, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glActiveTextureARB);
    }
    else if (FunctionCalled == "glBindBufferARB")
    {
        xDetour(ptr_glBindBufferARB, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glBindBufferARB);
    }
    else if (FunctionCalled == "glBufferDataARB")
    {
        xDetour(ptr_glBufferDataARB, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glBufferDataARB);
    }
    else if (FunctionCalled == "glBufferSubDataARB")
    {
        xDetour(ptr_glBufferSubDataARB, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glBufferSubDataARB);
    }
    else if (FunctionCalled == "glDeleteBuffersARB")
    {
        xDetour(ptr_glDeleteBuffers, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glDeleteBuffersARB);
    }
    else if (FunctionCalled == "glDeleteLists")
    {
        xDetour(ptr_glDeleteLists, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glDeleteLists);
    }
    else if (FunctionCalled == "glDeleteTextures")
    {
        xDetour(ptr_glDeleteTextures, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glDeleteTextures);
    }
    else if (FunctionCalled == "glMultiTexCoord2fARB")
    {
        xDetour(ptr_glMultiTexCoord2fARB, ptr_wglGetProcAddress(lpszProc));
        return reinterpret_cast<int (__stdcall *)()>(GLHook_glMultiTexCoord2fARB);
    }

	return ptr_wglGetProcAddress(lpszProc);
}

BOOL GLHook_wglSwapBuffers(HDC hdc)
{
    ProcessRequests();
    GLint ViewPort[4] = {0};
    bool Drawing[3] = {0};
    static std::vector<std::uint8_t> Buffer;
    static Render R(hdc, 8);
    Debugger.SetRenderer(&R);

    if (ColourBufferEnabled)
    {
        glGetIntegerv(GL_VIEWPORT, ViewPort);
        glPixelStorei(GL_PACK_ALIGNMENT, 4);
        Buffer.resize(ViewPort[2] * ViewPort[3] * 4);
        glReadPixels(0, 0, ViewPort[2], ViewPort[3], GL_BGRA, GL_UNSIGNED_BYTE, Buffer.data());
    }

    if (SmartGlobal && SmartGlobal->version)
    {
        if (SmartOpenGLEnabled)
        {
            if (ColourBufferEnabled)
            {
                FlipImageBytes(Buffer.data(), SmartGlobal->img, ViewPort[2], ViewPort[3]);
            }

            if (!IsIconic(WindowFromDC(hdc)))
            {
                int X = 0, Y = 0;
                EnableDrawing(Drawing[0], Drawing[1], Drawing[2]);
                if (SmartDebugEnabled)
                {
                    BltSmartBuffer();
                    Debugger.Draw();
                }

                SmartGlobal->getMousePos(X, Y);
                if (X != -1 && Y != -1)
                {
                    glPointSize(3);
                    glRasterPos2i(X, Y);
                    glColor3ub(0xFF, 0, 0);
                    glBegin(GL_POINTS);
                        glVertex3f(X, Y, 0);
                    glEnd();
                }
                DisableDrawing(Drawing[0], Drawing[1], Drawing[2]);
            }
        }
    }
    else
    {
        if (!SharedImageData || !SharedImageData->GetDataPointer())
        {
            CreateSharedMemory(getpid()) || OpenSharedMemory(getpid());
        }

        void* ImgPtr = SharedImageData->GetDataPointer();
        if (ColourBufferEnabled)
        {
            FlipImageBytes(Buffer.data(), ImgPtr, ViewPort[2], ViewPort[3]);
        }

        if (!IsIconic(WindowFromDC(hdc)))
        {
            EnableDrawing(Drawing[0], Drawing[1], Drawing[2]);
            void* DbgPtr = reinterpret_cast<std::uint8_t*>(SharedImageData->GetDataPointer()) + SharedImageSize;
            BltMappedBuffer(DbgPtr, ViewPort[2], ViewPort[3]);
            Debugger.Draw();
            DisableDrawing(Drawing[0], Drawing[1], Drawing[2]);
        }
    }

    InfoLogger.Reset();
    return ptr_wglSwapBuffers(hdc);
}
