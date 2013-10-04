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

#ifndef EXPORTS_HPP_INCLUDED
#define EXPORTS_HPP_INCLUDED

#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>
#include "Platform.hpp"
#include "Render.hpp"


extern Library* OriginalGL;
extern "C" bool __stdcall Initialize(void);
extern "C" bool __stdcall DeInitialize(void);

extern void (__stdcall *ptr_glAccum) (GLenum op, GLfloat value);
extern void (__stdcall *ptr_glActiveTextureARB) (GLenum texture);
extern void (__stdcall *ptr_glAlphaFunc) (GLenum func, GLclampf ref);
extern GLboolean (__stdcall *ptr_glAreTexturesResident) (GLsizei n, const GLuint *textures, GLboolean *residences);
extern void (__stdcall *ptr_glArrayElement) (GLint index);
extern void (__stdcall *ptr_glBegin) (GLenum mode);
extern void (__stdcall *ptr_glBindBufferARB) (GLenum target, GLuint buffer);
extern void (__stdcall *ptr_glBindTexture) (GLenum target, GLuint texture);
extern void (__stdcall *ptr_glBitmap) (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
extern void (__stdcall *ptr_glBlendFunc) (GLenum sfactor, GLenum dfactor);
extern void (__stdcall *ptr_glBufferDataARB) (GLenum target, GLsizeiptrARB size, const GLvoid *data, GLenum usage);
extern void (__stdcall *ptr_glBufferSubDataARB) (GLenum target, GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data);
extern void (__stdcall *ptr_glCallList) (GLuint list);
extern void (__stdcall *ptr_glCallLists) (GLsizei n, GLenum type, const GLvoid *lists);
extern void (__stdcall *ptr_glClear) (GLbitfield mask);
extern void (__stdcall *ptr_glClearAccum) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void (__stdcall *ptr_glClearColor) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern void (__stdcall *ptr_glClearDepth) (GLclampd depth);
extern void (__stdcall *ptr_glClearIndex) (GLfloat c);
extern void (__stdcall *ptr_glClearStencil) (GLint s);
extern void (__stdcall *ptr_glClipPlane) (GLenum plane, const GLdouble *equation);


                                    /**         TYPEDEFS: Colour Functions         **/

extern void (__stdcall *ptr_glColor3b) (GLbyte red, GLbyte green, GLbyte blue);
extern void (__stdcall *ptr_glColor3bv) (const GLbyte *v);
extern void (__stdcall *ptr_glColor3d) (GLdouble red, GLdouble green, GLdouble blue);
extern void (__stdcall *ptr_glColor3dv) (const GLdouble *v);
extern void (__stdcall *ptr_glColor3f) (GLfloat red, GLfloat green, GLfloat blue);
extern void (__stdcall *ptr_glColor3fv) (const GLfloat *v);
extern void (__stdcall *ptr_glColor3i) (GLint red, GLint green, GLint blue);
extern void (__stdcall *ptr_glColor3iv) (const GLint *v);
extern void (__stdcall *ptr_glColor3s) (GLshort red, GLshort green, GLshort blue);
extern void (__stdcall *ptr_glColor3sv) (const GLshort *v);
extern void (__stdcall *ptr_glColor3ub) (GLubyte red, GLubyte green, GLubyte blue);
extern void (__stdcall *ptr_glColor3ubv) (const GLubyte *v);
extern void (__stdcall *ptr_glColor3ui) (GLuint red, GLuint green, GLuint blue);
extern void (__stdcall *ptr_glColor3uiv) (const GLuint *v);
extern void (__stdcall *ptr_glColor3us) (GLushort red, GLushort green, GLushort blue);
extern void (__stdcall *ptr_glColor3usv) (const GLushort *v);

extern void (__stdcall *ptr_glColor4b) (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
extern void (__stdcall *ptr_glColor4bv) (const GLbyte *v);
extern void (__stdcall *ptr_glColor4d) (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
extern void (__stdcall *ptr_glColor4dv) (const GLdouble *v);
extern void (__stdcall *ptr_glColor4f) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern void (__stdcall *ptr_glColor4fv) (const GLfloat *v);
extern void (__stdcall *ptr_glColor4i) (GLint red, GLint green, GLint blue, GLint alpha);
extern void (__stdcall *ptr_glColor4iv) (const GLint *v);
extern void (__stdcall *ptr_glColor4s) (GLshort red, GLshort green, GLshort blue, GLshort alpha);
extern void (__stdcall *ptr_glColor4sv) (const GLshort *v);
extern void (__stdcall *ptr_glColor4ub) (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern void (__stdcall *ptr_glColor4ubv) (const GLubyte *v);
extern void (__stdcall *ptr_glColor4ui) (GLuint red, GLuint green, GLuint blue, GLuint alpha);
extern void (__stdcall *ptr_glColor4uiv) (const GLuint *v);
extern void (__stdcall *ptr_glColor4us) (GLushort red, GLushort green, GLushort blue, GLushort alpha);
extern void (__stdcall *ptr_glColor4usv) (const GLushort *v);
extern void (__stdcall *ptr_glColorMask) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern void (__stdcall *ptr_glColorMaterial) (GLenum face, GLenum mode);
extern void (__stdcall *ptr_glColorPointer) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);


                                    /**         TYPEDEFS: Continued         **/


extern void (__stdcall *ptr_glCopyPixels) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
extern void (__stdcall *ptr_glCopyTexImage1D) (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
extern void (__stdcall *ptr_glCopyTexImage2D) (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern void (__stdcall *ptr_glCopyTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern void (__stdcall *ptr_glCopyTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern void (__stdcall *ptr_glCullFace) (GLenum mode);
extern void (__stdcall *ptr_glDeleteBuffers) (GLsizei n,  const GLuint* buffers);
extern void (__stdcall *ptr_glDeleteLists) (GLuint list, GLsizei range);
extern void (__stdcall *ptr_glDeleteTextures) (GLsizei n, const GLuint *textures);
extern void (__stdcall *ptr_glDepthFunc) (GLenum func);
extern void (__stdcall *ptr_glDepthMask) (GLboolean flag);
extern void (__stdcall *ptr_glDepthRange) (GLclampd zNear, GLclampd zFar);
extern void (__stdcall *ptr_glDisable) (GLenum cap);
extern void (__stdcall *ptr_glDisableClientState) (GLenum array);
extern void (__stdcall *ptr_glDrawArrays) (GLenum mode, GLint first, GLsizei count);
extern void (__stdcall *ptr_glDrawBuffer) (GLenum mode);
extern void (__stdcall *ptr_glDrawElements) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
extern void (__stdcall *ptr_glDrawPixels) (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern void (__stdcall *ptr_glDebugEntry) (DWORD dwArg1, DWORD dwArg2);

                                    /**         TYPEDEFS: EdgeFlag Functions         **/

extern void (__stdcall *ptr_glEdgeFlag) (GLboolean flag);
extern void (__stdcall *ptr_glEdgeFlagv) (const GLboolean *flag);
extern void (__stdcall *ptr_glEdgeFlagPointer) (GLsizei stride, const GLvoid *pointer);


                                    /**         TYPEDEFS: Continued         **/

extern void (__stdcall *ptr_glEnable) (GLenum cap);
extern void (__stdcall *ptr_glEnableClientState) (GLenum array);
extern void (__stdcall *ptr_glEnd) (void);
extern void (__stdcall *ptr_glEndList) (void);


                                    /**         TYPEDEFS: Eval Coordinate Functions         **/

extern void (__stdcall *ptr_glEvalCoord1d) (GLdouble u);
extern void (__stdcall *ptr_glEvalCoord1dv) (const GLdouble *u);
extern void (__stdcall *ptr_glEvalCoord1f) (GLfloat u);
extern void (__stdcall *ptr_glEvalCoord1fv) (const GLfloat *u);
extern void (__stdcall *ptr_glEvalCoord2d) (GLdouble u, GLdouble v);
extern void (__stdcall *ptr_glEvalCoord2dv) (const GLdouble *u);
extern void (__stdcall *ptr_glEvalCoord2f) (GLfloat u, GLfloat v);
extern void (__stdcall *ptr_glEvalCoord2fv) (const GLfloat *u);


                                    /**         TYPEDEFS: Eval Mesh Functions         **/

extern void (__stdcall *ptr_glEvalMesh1) (GLenum mode, GLint i1, GLint i2);
extern void (__stdcall *ptr_glEvalMesh2) (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);


                                    /**         TYPEDEFS: Eval Point Functions         **/

extern void (__stdcall *ptr_glEvalPoint1) (GLint i);
extern void (__stdcall *ptr_glEvalPoint2) (GLint i, GLint j);


                                    /**         TYPEDEFS: Continued         **/

extern void (__stdcall *ptr_glFeedbackBuffer) (GLsizei size, GLenum type, GLfloat *buffer);
extern void (__stdcall *ptr_glFinish) (void);
extern void (__stdcall *ptr_glFlush) (void);


                                    /**         TYPEDEFS: Fog Functions         **/

extern void (__stdcall *ptr_glFogf) (GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glFogfv) (GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glFogi) (GLenum pname, GLint param);
extern void (__stdcall *ptr_glFogiv) (GLenum pname, const GLint *params);


                                    /**         TYPEDEFS: Continued         **/

extern void (__stdcall *ptr_glFrontFace) (GLenum mode);
extern void (__stdcall *ptr_glFrustum) (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void (__stdcall *ptr_glGenBuffersARB) (GLsizei n, GLuint *buffers);
extern GLuint (__stdcall *ptr_glGenLists) (GLsizei range);
extern void (__stdcall *ptr_glGenTextures) (GLsizei n, GLuint *textures);


                                    /**         TYPEDEFS: Get Functions        **/

extern void (__stdcall *ptr_glGetBooleanv) (GLenum pname, GLboolean *params);
extern void (__stdcall *ptr_glGetDoublev) (GLenum pname, GLboolean *params);
extern void (__stdcall *ptr_glGetFloatv) (GLenum pname, GLboolean *params);
extern void (__stdcall *ptr_glGetIntegerv) (GLenum pname, GLboolean *params);


                                    /**         TYPEDEFS: Get Functions        **/

extern void (__stdcall *ptr_glGetClipPlane) (GLenum plane, GLdouble *equation);
extern GLenum (__stdcall *ptr_glGetError) (void);


                                    /**         TYPEDEFS: Get Light Functions        **/

extern void (__stdcall *ptr_glGetLightfv) (GLenum light, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetLightiv) (GLenum light, GLenum pname, GLint *params);


                                    /**         TYPEDEFS: Get Map Functions        **/

extern void (__stdcall *ptr_glGetMapdv) (GLenum target, GLenum query, GLdouble *v);
extern void (__stdcall *ptr_glGetMapfv) (GLenum target, GLenum query, GLfloat *v);
extern void (__stdcall *ptr_glGetMapiv) (GLenum target, GLenum query, GLint *v);


                                    /**         TYPEDEFS: Get Material Functions        **/

extern void (__stdcall *ptr_glGetMaterialfv) (GLenum face, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetMaterialiv) (GLenum face, GLenum pname, GLint *params);


                                    /**         TYPEDEFS: Get PixelMap Functions        **/

extern void (__stdcall *ptr_glGetPixelMapfv) (GLenum map, GLfloat *values);
extern void (__stdcall *ptr_glGetPixelMapuiv) (GLenum map, GLuint *values);
extern void (__stdcall *ptr_glGetPixelMapusv) (GLenum map, GLushort *values);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glGetPointerv) (GLenum pname, GLvoid **params);
extern void (__stdcall *ptr_glGetPolygonStipple) (GLubyte *mask);
extern const GLubyte* (__stdcall *ptr_glGetString) (GLenum name);


                                    /**         TYPEDEFS: GetTexENV/GetTexGEN Functions        **/

extern void (__stdcall *ptr_glGetTexEnvfv) (GLenum target, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetTexEnviv) (GLenum target, GLenum pname, GLint *params);
extern void (__stdcall *ptr_glGetTexGendv) (GLenum coord, GLenum pname, GLdouble *params);
extern void (__stdcall *ptr_glGetTexGenfv) (GLenum coord, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetTexGeniv) (GLenum coord, GLenum pname, GLint *params);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glGetTexImage) (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
extern void (__stdcall *ptr_glGetTexLevelParameterfv) (GLenum target, GLint level, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetTexLevelParameteriv) (GLenum target, GLint level, GLenum pname, GLint *params);
extern void (__stdcall *ptr_glGetTexParameterfv) (GLenum target, GLenum pname, GLfloat *params);
extern void (__stdcall *ptr_glGetTexParameteriv) (GLenum target, GLenum pname, GLint *params);
extern void (__stdcall *ptr_glHint) (GLenum target, GLenum mode);


                                    /**         TYPEDEFS: Index Functions        **/

extern void (__stdcall *ptr_glIndexd) (GLdouble c);
extern void (__stdcall *ptr_glIndexdv) (const GLdouble *c);
extern void (__stdcall *ptr_glIndexf) (GLfloat c);
extern void (__stdcall *ptr_glIndexfv) (const GLfloat *c);
extern void (__stdcall *ptr_glIndexi) (GLint c);
extern void (__stdcall *ptr_glIndexiv) (const GLint *c);
extern void (__stdcall *ptr_glIndexs) (GLshort c);
extern void (__stdcall *ptr_glIndexsv) (const GLshort *c);
extern void (__stdcall *ptr_glIndexub) (GLubyte c);
extern void (__stdcall *ptr_glIndexubv) (const GLubyte *c);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glIndexMask) (GLuint mask);
extern void (__stdcall *ptr_glIndexPointer) (GLenum type, GLsizei stride, const GLvoid *pointer);
extern void (__stdcall *ptr_glInitNames) (void);
extern void (__stdcall *ptr_glInterleavedArrays) (GLenum format, GLsizei stride, const GLvoid *pointer);
extern GLboolean (__stdcall *ptr_glIsEnabled) (GLenum cap);
extern GLboolean (__stdcall *ptr_glIsList) (GLuint list);
extern GLboolean (__stdcall *ptr_glIsTexture) (GLuint texture);


                                    /**         TYPEDEFS: Light Functions        **/

extern void (__stdcall *ptr_glLightf) (GLenum light, GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glLightfv) (GLenum light, GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glLighti) (GLenum light, GLenum pname, GLint param);
extern void (__stdcall *ptr_glLightiv) (GLenum light, GLenum pname, const GLint *params);
extern void (__stdcall *ptr_glLightModelf) (GLenum pname, GLfloat *param);
extern void (__stdcall *ptr_glLightModelfv) (GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glLightModeli) (GLenum pname, GLint param);
extern void (__stdcall *ptr_glLightModeliv) (GLenum pname, const GLint *params);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glLineStipple) (GLint factor, GLushort pattern);
extern void (__stdcall *ptr_glLineWidth) (GLfloat width);
extern void (__stdcall *ptr_glListBase) (GLuint base);
extern void (__stdcall *ptr_glLoadIdentity) (void);
extern void (__stdcall *ptr_glLoadMatrixd) (const GLdouble *m);
extern void (__stdcall *ptr_glLoadMatrixf) (const GLfloat *m);
extern void (__stdcall *ptr_glLoadName) (GLuint name);
extern void (__stdcall *ptr_glLogicOp) (GLenum opcode);


                                    /**         TYPEDEFS: Map#/Material Functions        **/

extern void (__stdcall *ptr_glMap1d) (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
extern void (__stdcall *ptr_glMap1f) (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
extern void (__stdcall *ptr_glMap2d) (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
extern void (__stdcall *ptr_glMap2f) (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
extern void (__stdcall *ptr_glMapGrid1d) (GLint un, GLdouble u1, GLdouble u2);
extern void (__stdcall *ptr_glMapGrid1f) (GLint un, GLfloat u1, GLfloat u2);
extern void (__stdcall *ptr_glMapGrid2d) (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
extern void (__stdcall *ptr_glMapGrid2f) (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern void (__stdcall *ptr_glMaterialf) (GLenum face, GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glMaterialfv) (GLenum face, GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glMateriali) (GLenum face, GLenum pname, GLint param);
extern void (__stdcall *ptr_glMaterialiv) (GLenum face, GLenum pname, const GLint *params);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glMatrixMode) (GLenum mode);
extern void (__stdcall *ptr_glMultiTexCoord2fARB) (GLenum target, GLfloat s, GLfloat t);
extern void (__stdcall *ptr_glMultMatrixd) (const GLdouble *m);
extern void (__stdcall *ptr_glMultMatrixf) (const GLdouble *m);
extern void (__stdcall *ptr_glNewList) (GLuint list, GLenum mode);


                                    /**         TYPEDEFS: Normal/Coordinate Functions        **/

extern void (__stdcall *ptr_glNormal3b) (GLbyte nx, GLbyte ny, GLbyte nz);
extern void (__stdcall *ptr_glNormal3bv) (const GLbyte *v);
extern void (__stdcall *ptr_glNormal3d) (GLdouble nx, GLdouble ny, GLdouble nz);
extern void (__stdcall *ptr_glNormal3dv) (const GLdouble *v);
extern void (__stdcall *ptr_glNormal3f) (GLfloat nx, GLfloat ny, GLfloat nz);
extern void (__stdcall *ptr_glNormal3fv) (const GLfloat *v);
extern void (__stdcall *ptr_glNormal3i) (GLint nx, GLint ny, GLint nz);
extern void (__stdcall *ptr_glNormal3iv) (const GLint *v);
extern void (__stdcall *ptr_glNormal3s) (GLshort nx, GLshort ny, GLshort nz);
extern void (__stdcall *ptr_glNormal3sv) (const GLshort *v);
extern void (__stdcall *ptr_glNormalPointer) (GLenum type, GLsizei stride, const GLvoid *pointer);

extern void (__stdcall *ptr_glOrtho) (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern void (__stdcall *ptr_glPassThrough) (GLfloat token);


                                    /**         TYPEDEFS: Pixel Functions        **/

extern void (__stdcall *ptr_glPixelMapfv) (GLenum map, GLsizei mapsize, const GLfloat *values);
extern void (__stdcall *ptr_glPixelMapuiv) (GLenum map, GLsizei mapsize, const GLuint *values);
extern void (__stdcall *ptr_glPixelMapusv) (GLenum map, GLsizei mapsize, const GLushort *values);
extern void (__stdcall *ptr_glPixelStoref) (GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glPixelStorei) (GLenum pname, GLint para);
extern void (__stdcall *ptr_glPixelTransferf) (GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glPixelTransferi) (GLenum pname, GLint param);
extern void (__stdcall *ptr_glPixelZoom) (GLfloat xfactor, GLfloat yfactor);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glPointSize) (GLfloat size);
extern void (__stdcall *ptr_glPolygonMode) (GLenum face, GLenum mode);
extern void (__stdcall *ptr_glPolygonOffset) (GLfloat factor, GLfloat units);
extern void (__stdcall *ptr_glPolygonStipple) (const GLubyte *mask);
extern void (__stdcall *ptr_glPopAttrib) (void);
extern void (__stdcall *ptr_glPopClientAttrib) (void);
extern void (__stdcall *ptr_glPopMatrix) (void);
extern void (__stdcall *ptr_glPopName) (void);
extern void (__stdcall *ptr_glPrioritizeTextures) (GLsizei n, const GLuint *textures, const GLclampf *priorities);
extern void (__stdcall *ptr_glPushAttrib) (GLbitfield mask);
extern void (__stdcall *ptr_glPushClientAttrib) (GLbitfield mask);
extern void (__stdcall *ptr_glPushMatrix) (void);
extern void (__stdcall *ptr_glPushName) (GLuint name);


                                    /**         TYPEDEFS: Raster Functions        **/

extern void (__stdcall *ptr_glRasterPos2d) (GLdouble x, GLdouble y);
extern void (__stdcall *ptr_glRasterPos2dv) (const GLdouble *v);
extern void (__stdcall *ptr_glRasterPos2f) (GLfloat x, GLfloat y);
extern void (__stdcall *ptr_glRasterPos2fv) (const GLfloat *v);
extern void (__stdcall *ptr_glRasterPos2i) (GLint x, GLint y);
extern void (__stdcall *ptr_glRasterPos2iv) (const GLint *v);
extern void (__stdcall *ptr_glRasterPos2s) (GLshort x, GLshort y);
extern void (__stdcall *ptr_glRasterPos2sv) (const GLshort *v);
extern void (__stdcall *ptr_glRasterPos3d) (GLdouble x, GLdouble y, GLdouble z);
extern void (__stdcall *ptr_glRasterPos3dv) (const GLdouble *v);
extern void (__stdcall *ptr_glRasterPos3f) (GLfloat x, GLfloat y, GLfloat z);
extern void (__stdcall *ptr_glRasterPos3fv) (const GLfloat *v);
extern void (__stdcall *ptr_glRasterPos3i) (GLint x, GLint y, GLint z);
extern void (__stdcall *ptr_glRasterPos3iv) (const GLint *v);
extern void (__stdcall *ptr_glRasterPos3s) (GLshort x, GLshort y, GLshort z);
extern void (__stdcall *ptr_glRasterPos3sv) (const GLshort *v);
extern void (__stdcall *ptr_glRasterPos4d) (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void (__stdcall *ptr_glRasterPos4dv) (const GLdouble *v);
extern void (__stdcall *ptr_glRasterPos4f) (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void (__stdcall *ptr_glRasterPos4fv) (const GLfloat *v);
extern void (__stdcall *ptr_glRasterPos4i) (GLint x, GLint y, GLint z, GLint w);
extern void (__stdcall *ptr_glRasterPos4iv) (const GLint *v);
extern void (__stdcall *ptr_glRasterPos4s) (GLshort x, GLshort y, GLshort z, GLshort w);
extern void (__stdcall *ptr_glRasterPos4sv) (const GLshort *v);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glReadBuffer) (GLenum mode);
extern void (__stdcall *ptr_glReadPixels) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);


                                    /**         TYPEDEFS: Rect/Render/Rotate/Scale Functions        **/

extern void (__stdcall *ptr_glRectd) (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
extern void (__stdcall *ptr_glRectdv) (const GLdouble *v1, const GLdouble *v2);
extern void (__stdcall *ptr_glRectf) (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern void (__stdcall *ptr_glRectfv) (const GLfloat *v1, const GLfloat *v2);
extern void (__stdcall *ptr_glRecti) (GLint x1, GLint y1, GLint x2, GLint y2);
extern void (__stdcall *ptr_glRectiv) (const GLint *v1, const GLint *v2);
extern void (__stdcall *ptr_glRects) (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
extern void (__stdcall *ptr_glRectsv) (const GLshort *v1, const GLshort *v2);
extern GLint (__stdcall *ptr_glRenderMode) (GLenum mode);
extern void (__stdcall *ptr_glRotated) (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern void (__stdcall *ptr_glRotatef) (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void (__stdcall *ptr_glScaled) (GLdouble x, GLdouble y, GLdouble z);
extern void (__stdcall *ptr_glScalef) (GLfloat x, GLfloat y, GLfloat z);


                                    /**         TYPEDEFS: Continued        **/

extern void (__stdcall *ptr_glScissor) (GLint x, GLint y, GLsizei width, GLsizei height);
extern void (__stdcall *ptr_glSelectBuffer) (GLsizei size, GLuint *buffer);
extern void (__stdcall *ptr_glShadeModel) (GLenum mode);
extern void (__stdcall *ptr_glStencilFunc) (GLenum func, GLint ref, GLuint mask);
extern void (__stdcall *ptr_glStencilMask) (GLuint mask);
extern void (__stdcall *ptr_glStencilOp) (GLenum fail, GLenum zfail, GLenum zpass);


                                    /**         TYPEDEFS: Tex Functions        **/

extern void (__stdcall *ptr_glTexCoord1d) (GLdouble s);
extern void (__stdcall *ptr_glTexCoord1dv) (const GLdouble *v);
extern void (__stdcall *ptr_glTexCoord1f) (GLfloat s);
extern void (__stdcall *ptr_glTexCoord1fv) (const GLfloat *v);
extern void (__stdcall *ptr_glTexCoord1i) (GLint s);
extern void (__stdcall *ptr_glTexCoord1iv) (const GLint *v);
extern void (__stdcall *ptr_glTexCoord1s) (GLshort s);
extern void (__stdcall *ptr_glTexCoord1sv) (const GLshort *v);
extern void (__stdcall *ptr_glTexCoord2d) (GLdouble s, GLdouble t);
extern void (__stdcall *ptr_glTexCoord2dv) (const GLdouble *v);
extern void (__stdcall *ptr_glTexCoord2f) (GLfloat s,  GLfloat t);
extern void (__stdcall *ptr_glTexCoord2fv) (const GLfloat *v);
extern void (__stdcall *ptr_glTexCoord2i) (GLint s, GLint t);
extern void (__stdcall *ptr_glTexCoord2iv) (const GLint *v);
extern void (__stdcall *ptr_glTexCoord2s) (GLshort s, GLshort t);
extern void (__stdcall *ptr_glTexCoord2sv) (const GLshort *v);
extern void (__stdcall *ptr_glTexCoord3d) (GLdouble s, GLdouble t, GLdouble r);
extern void (__stdcall *ptr_glTexCoord3dv) (const GLdouble *v);
extern void (__stdcall *ptr_glTexCoord3f) (GLfloat s, GLfloat t, GLfloat r);
extern void (__stdcall *ptr_glTexCoord3fv) (const GLfloat *v);
extern void (__stdcall *ptr_glTexCoord3i) (GLint s, GLint t, GLint r);
extern void (__stdcall *ptr_glTexCoord3iv) (const GLint *v);
extern void (__stdcall *ptr_glTexCoord3s) (GLshort s, GLshort t, GLshort r);
extern void (__stdcall *ptr_glTexCoord3sv) (const GLshort *v);
extern void (__stdcall *ptr_glTexCoord4d) (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern void (__stdcall *ptr_glTexCoord4dv) (const GLdouble *v);
extern void (__stdcall *ptr_glTexCoord4f) (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern void (__stdcall *ptr_glTexCoord4fv) (const GLfloat *v);
extern void (__stdcall *ptr_glTexCoord4i) (GLint s, GLint t, GLint r, GLint q);
extern void (__stdcall *ptr_glTexCoord4iv) (const GLint *v);
extern void (__stdcall *ptr_glTexCoord4s) (GLshort s, GLshort t, GLshort r, GLshort q);
extern void (__stdcall *ptr_glTexCoord4sv) (const GLshort *v);
extern void (__stdcall *ptr_glTexCoordPointer) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void (__stdcall *ptr_glTexEnvf) (GLenum target, GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glTexEnvfv) (GLenum target, GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glTexEnvi) (GLenum target, GLenum pname, GLint param);
extern void (__stdcall *ptr_glTexEnviv) (GLenum target, GLenum pname, const GLint *params);
extern void (__stdcall *ptr_glTexGend) (GLenum coord, GLenum pname, GLdouble param);
extern void (__stdcall *ptr_glTexGendv) (GLenum coord, GLenum pname, const GLdouble *params);
extern void (__stdcall *ptr_glTexGenf) (GLenum coord, GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glTexGenfv) (GLenum coord, GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glTexGeni) (GLenum coord, GLenum pname, GLint param);
extern void (__stdcall *ptr_glTexGeniv) (GLenum coord, GLenum pname, const GLint *params);
extern void (__stdcall *ptr_glTexImage1D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLint format, GLenum type, const GLvoid *pixels);
extern void (__stdcall *ptr_glTexImage2D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid *pixels);
extern void (__stdcall *ptr_glTexParameterf) (GLenum target, GLenum pname, GLfloat param);
extern void (__stdcall *ptr_glTexParameterfv) (GLenum target, GLenum pname, const GLfloat *params);
extern void (__stdcall *ptr_glTexParameteri) (GLenum target, GLenum pname, GLint param);
extern void (__stdcall *ptr_glTexParameteriv) (GLenum target, GLenum pname, const GLint *params);
extern void (__stdcall *ptr_glTexSubImage1D) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
extern void (__stdcall *ptr_glTexSubImage2D) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type,const GLvoid *pixels);


                                    /**         TYPEDEFS: Translate/Vertex Functions       **/

extern void (__stdcall *ptr_glTranslated) (GLdouble x, GLdouble y, GLdouble z);
extern void (__stdcall *ptr_glTranslatef) (GLfloat x, GLfloat y, GLfloat z);
extern void (__stdcall *ptr_glVertex2d) (GLdouble x, GLdouble y);
extern void (__stdcall *ptr_glVertex2dv) (const GLdouble *v);
extern void (__stdcall *ptr_glVertex2f) (GLfloat x, GLfloat y);
extern void (__stdcall *ptr_glVertex2fv) (const GLfloat *v);
extern void (__stdcall *ptr_glVertex2i) (GLint x, GLint y);
extern void (__stdcall *ptr_glVertex2iv) (const GLint *v);
extern void (__stdcall *ptr_glVertex2s) (GLshort x, GLshort y);
extern void (__stdcall *ptr_glVertex2sv) (const GLshort *v);
extern void (__stdcall *ptr_glVertex3d) (GLdouble x, GLdouble y, GLdouble z);
extern void (__stdcall *ptr_glVertex3dv) (const GLdouble *v);
extern void (__stdcall *ptr_glVertex3f) (GLfloat x, GLfloat y, GLfloat z);
extern void (__stdcall *ptr_glVertex3fv) (const GLfloat *v);
extern void (__stdcall *ptr_glVertex3i) (GLint x, GLint y, GLint z);
extern void (__stdcall *ptr_glVertex3iv) (const GLint *v);
extern void (__stdcall *ptr_glVertex3s) (GLshort x, GLshort y, GLshort z);
extern void (__stdcall *ptr_glVertex3sv) (const GLshort *v);
extern void (__stdcall *ptr_glVertex4d) (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void (__stdcall *ptr_glVertex4dv) (const GLdouble *v);
extern void (__stdcall *ptr_glVertex4f) (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void (__stdcall *ptr_glVertex4fv) (const GLfloat *v);
extern void (__stdcall *ptr_glVertex4i) (GLint x, GLint y, GLint z, GLint w);
extern void (__stdcall *ptr_glVertex4iv) (const GLint *v);
extern void (__stdcall *ptr_glVertex4s) (GLshort x, GLshort y, GLshort z, GLshort w);
extern void (__stdcall *ptr_glVertex4sv) (const GLshort *v);
extern void (__stdcall *ptr_glVertexPointer) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void (__stdcall *ptr_glViewport) (GLint x, GLint y, GLsizei width, GLsizei height);

#if defined _WIN32 || defined _WIN64
extern int (__stdcall *ptr_wglChoosePixelFormat) (HDC hdc, const PIXELFORMATDESCRIPTOR *ppfd);
extern HGLRC (__stdcall *ptr_wglCreateContext) (HDC hdc);
extern HGLRC (__stdcall *ptr_wglCreateLayerContext) (HDC hdc, int iLayerPlane);
extern BOOL (__stdcall *ptr_wglCopyContext) (HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask);
extern BOOL (__stdcall *ptr_wglDeleteContext) (HGLRC hglrc);
extern BOOL (__stdcall *ptr_wglDescribeLayerPlane) (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nBytes, LPLAYERPLANEDESCRIPTOR plpd);
extern int (__stdcall *ptr_wglDescribePixelFormat) (HDC hdc, int iPixelFormat, UINT nBytes, LPPIXELFORMATDESCRIPTOR ppfd);
extern HGLRC (__stdcall *ptr_wglGetCurrentContext) (void);
extern HDC (__stdcall *ptr_wglGetCurrentDC) (void);
extern PROC (__stdcall *ptr_wglGetDefaultProcAddress) (LPCSTR lpszProc);
extern int (__stdcall *ptr_wglGetLayerPaletteEntries) (HDC hdc, int iLayerPlane, int iStart, int cEntries, COLORREF *pcr);
extern int (__stdcall *ptr_wglGetPixelFormat) (HDC hdc);
extern PROC (__stdcall *ptr_wglGetProcAddress) (LPCSTR lpszProc);
extern BOOL (__stdcall *ptr_wglMakeCurrent) (HDC hdc, HGLRC hglrc);
extern BOOL (__stdcall *ptr_wglRealizeLayerPalette) (HDC hdc, int iLayerPlane, BOOL bRealize);
extern int (__stdcall *ptr_wglSetLayerPaletteEntries) (HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF *pcr);
extern BOOL (__stdcall *ptr_wglSetPixelFormat) (HDC hdc, int iPixelFormat, const PIXELFORMATDESCRIPTOR *ppfd);
extern BOOL (__stdcall *ptr_wglShareLists) (HGLRC hglrc1, HGLRC hglrc2);
extern BOOL (__stdcall *ptr_wglSwapBuffers) (HDC hdc);
extern BOOL (__stdcall *ptr_wglSwapLayerBuffers) (HDC hdc, UINT fuPlanes);
extern void (__stdcall *ptr_wglSwapMultipleBuffers) (DWORD dwArg1, DWORD dwArg2);
extern BOOL (__stdcall *ptr_wglUseFontBitmapsW) (HDC hdc, DWORD first, DWORD count, DWORD listBase);
extern BOOL (__stdcall *ptr_wglUseFontBitmapsA) (HDC hdc, DWORD first, DWORD count, DWORD listBase);
extern BOOL (__stdcall *ptr_wglUseFontOutlinesW) (HDC hdc, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);
extern BOOL (__stdcall *ptr_wglUseFontOutlinesA) (HDC hdc, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);
#endif


#endif // EXPORTS_HPP_INCLUDED
