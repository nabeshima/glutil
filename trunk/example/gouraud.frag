uniform sampler2D texture;

void main( void ) {
  vec4 color = texture2D( texture, gl_TexCoord[ 0 ].st * 5.0 );  
  
  gl_FragColor = color * gl_Color;
}
