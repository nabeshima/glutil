/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#if defined(__APPLE__) && !defined(__FreeBSD__)
#include <OpenGL/gl.h>
#else
#define GL_GLEXT_PROTOTYPES 
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include "GLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace glutil;

namespace {

void printProgramInfoLog( GLuint program ) {

  GLsizei bufSize;
  glGetProgramiv( program, GL_INFO_LOG_LENGTH , &bufSize );
  
  // linuxで,メッセージが無いのに1が返る場合があった.
  if ( bufSize > 1 ) { 
    GLchar infoLog[ bufSize ];
    GLsizei length;
      
    glGetProgramInfoLog( program, bufSize, &length, infoLog );
    cerr << "GLShader programinfo: " << endl << infoLog << endl << endl;
  }
}

void printShaderInfoLog( GLuint shader ) {
  GLsizei bufSize;
  glGetShaderiv( shader, GL_INFO_LOG_LENGTH , &bufSize );
  
  // linuxで,メッセージが無いのに1が返る場合があった.
  if ( bufSize > 1 ) {
    GLchar infoLog[ bufSize ];
    GLsizei length;

    glGetShaderInfoLog( shader, bufSize, &length, infoLog );
    cerr << "GLShader shaderinfo: " << endl << infoLog << endl << endl;
  }
}

}

bool GLShader::load( const string &vert_filename,
                     const string &frag_filename ) {
  {
    ifstream fin( vert_filename.c_str(), ios::binary );
    if ( fin ) {
      ostringstream out;
      out << fin.rdbuf();
      vert_src = out.str();
      fin.close();
    }
  }

  {
    ifstream fin( frag_filename.c_str(), ios::binary );
    if ( fin ) {
      ostringstream out;
      out << fin.rdbuf();
      frag_src = out.str();
      fin.close();
    }
  }
  
  if ( vert_src == "" ||
       frag_src == "" ) {
    
    vert_src = "";
    frag_src = "";

    return false;
  }
  else {
    return true; 
  }
}

bool GLShader::initialize() const {

  if ( vert_src == "" ||
       frag_src == "" ) {
    return false;
  }
  
  /* シェーダオブジェクトの作成 */
  GLuint
    vertShader = glCreateShader( GL_VERTEX_SHADER ),
    fragShader = glCreateShader( GL_FRAGMENT_SHADER );

  if ( vertShader == 0 ||
       fragShader == 0 ) {
    return false;
  }

  /* シェーダのソースプログラムの読み込み */
  {
    const char* svert = vert_src.c_str();
    glShaderSource( vertShader, 1, &svert, NULL );
    printShaderInfoLog( vertShader );
    
    const char* sfrag = frag_src.c_str();;
    glShaderSource( fragShader, 1, &sfrag, NULL );
    printShaderInfoLog( fragShader );
  }
  
  // コンパイル
  {
    GLint compiled;
    
    /* バーテックスシェーダのソースプログラムのコンパイル */
    glCompileShader( vertShader );
    glGetShaderiv( vertShader, GL_COMPILE_STATUS, &compiled );
    printShaderInfoLog( vertShader );    
    
    if ( compiled == GL_FALSE ) {
      
      glDeleteShader( vertShader );
      glDeleteShader( fragShader );
      
      return false;
    }
    
    /* フラグメントシェーダのソースプログラムのコンパイル */
    glCompileShader( fragShader );
    glGetShaderiv( fragShader, GL_COMPILE_STATUS, &compiled );
    printShaderInfoLog( fragShader );
    
    if ( compiled == GL_FALSE ) {

      glDeleteShader( vertShader );
      glDeleteShader( fragShader );
      
      return false;
    }
  }
  
  /* プログラムオブジェクトの作成 */
  program = glCreateProgram();
  
  /* シェーダオブジェクトのシェーダプログラムへの登録 */
  glAttachShader( program, vertShader );
  glAttachShader( program, fragShader );
  
  /* シェーダオブジェクトの削除 */
  glDeleteShader( vertShader );
  glDeleteShader( fragShader );
  
  // リンク結果
  GLint linked;
  
  /* シェーダプログラムのリンク */
  glLinkProgram( program );
  glGetProgramiv( program, GL_LINK_STATUS, &linked );
  printProgramInfoLog( program );
  
  if ( linked == GL_FALSE ) {

    glDeleteProgram( program );
    program = 0;

    return false;
  }

  return true;
}

void GLShader::finalize() const {
  if ( program != 0 ) {
    glDeleteProgram( program );
  }
}
