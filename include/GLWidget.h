/**
 * $Id$
 * Copyright (c) 2013 Cota Nabeshima <cota@upard.org>
 * This file is subject to the MIT license available at,
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef _GLUTIL_GLWIDGET_H_
#define _GLUTIL_GLWIDGET_H_

#include <cutil/XWidget.h>

extern "C" {
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
}


namespace glutil {


/*! \class GLWdiget
  カメラに使うための最小のプログラム.
  非Qt. GLXとXlibを使ったウィンドウクラス.
  Windowsで使う場合は作り替える必要有.
*/

class GLWidget
  : public cutil::XWidget {
  
private:
  //! 次の動作: -1ならinitializeGLを呼ぶ. 0なら何もしない. 1ならfinalizeGLを呼んでからinitializeGLを呼ぶ.
  enum NextOp {
    INIT,
    RESET,
    NONE
  };
  NextOp nextop;
  
  
  //! repaintコマンドが発行されているか,排他制御.
  bool rpFlag;
  bool resizeFlag;
  cutil::Mutex rpMutex;
  cutil::WaitCondition rpCond;
  
  //! End用
  bool endFlag;
  cutil::Mutex endMutex;
  cutil::Thread thr;
  
  //! 保存関連  
  cutil::Mutex imgMutex;
  int imageByteSize;

  unsigned char *imagebuf;
  bool keepImageFlag;
  
  float *depthbuf;
  bool keepDepthFlag;

protected:
  virtual XVisualInfo chooseVisual();

public:
  void operator()();

protected:
  virtual void initializeGL(){};
  virtual void finalizeGL(){};
  
  virtual void paintGL(){};
  virtual void resizeGL( int width, int height ) {};
  
public:
  GLWidget();
  virtual ~GLWidget();
  
  //! open時にもう一度openしても何もおこらない.
  void open( int width, int height, const std::string &title = "" );
  void close();
  
  /*! 
    waitFlag が true ならば repaint終了までブロック.
    シミュレーションでカメラを使うときに.
    waitFlag が falseでも,
    keepImageMode が true ならばブロックされる.
  */
  void repaint( bool waitFlag = true );
  
  
  //! 次のrepaintで最初にinitializeGL()を呼ぶようにする.
  void refresh();

  //! if keepImageFlag is true, this function force the widget not to be resized.
  void keepImageMode( bool keepImageFlag );

  /*! 
    keepImageMode( true )した場合に取得できる.
    \param imagebuf
    imagebufは, width * height * 4 byteのuchar配列を渡すこと.
    
    メモリにコピーできたらtrueを返す.
  */
  bool getImage( unsigned char *imagebuf );
  
  //! getImage()で得られたファイルをPPMで書き出す.
  bool writePPM( const std::string &filename );
  
  //! depth画像をを保存する.
  void keepDepthMode( bool keepDepthFlag );
    
  /*! 
    keepDepthMode( true )した場合に取得できる.
    \param depthbuf
    depthbufは, width * height の 4 byte float配列を渡すこと.
    
    メモリにコピーできたらtrueを返す.
  */
  bool getDepth( float *depthbuf );

  // ( 0, 1 ) の float を, RGBAに変換. XWidgetに描画できるように.
  static void convertDepthToImage( const float *depthbuf, unsigned char *buf32, int width, int height );
  
protected:
  virtual void showEvent();
  virtual void exposeEvent();
  virtual void resizeEvent( int width, int height );
  
};

}

#endif
