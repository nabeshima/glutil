varying vec3 position;
varying vec3 normal;

void main( void ) {
  position = vec3( gl_ModelViewMatrix * gl_Vertex );
  normal = normalize( gl_NormalMatrix * gl_Normal );
  
  gl_Position = ftransform();

  // 頂点座標を元に, テクスチャ座標に割り当てる
  gl_TexCoord[ 0 ].s = ( gl_Vertex[ 0 ] + gl_Vertex[ 1 ] + 1.0 ) / 3.0;
  gl_TexCoord[ 0 ].t = ( 0.817 * gl_Vertex[ 0 ] - 0.817 * gl_Vertex[ 1 ] + 0.817 * gl_Vertex[ 2 ] + 1.0 ) / ( 1.817 );
}
