void main( void ) {
  vec3 position = vec3( gl_ModelViewMatrix * gl_Vertex );
  vec3 normal = normalize( gl_NormalMatrix * gl_Normal );
  vec3 light = normalize( gl_LightSource[ 0 ].position.xyz - position );
  float diffuse = dot( light, normal );
	
  gl_FrontColor = gl_FrontLightProduct[ 0 ].ambient;
  if ( diffuse > 0.0 ) {
    vec3 view = normalize( position );
    vec3 halfway = normalize( light - view );
    float specular = pow( max( dot( normal, halfway ), 0.0 ), gl_FrontMaterial.shininess );
    gl_FrontColor += 
      gl_FrontLightProduct[ 0 ].diffuse * diffuse
      + gl_FrontLightProduct[ 0 ].specular * specular;
  }

  gl_Position = ftransform();

  // 頂点座標を元に, テクスチャ座標に割り当てる
  gl_TexCoord[ 0 ].s = ( gl_Vertex[ 0 ] + gl_Vertex[ 1 ] + 1.0 ) / 3.0;
  gl_TexCoord[ 0 ].t = ( 0.817 * gl_Vertex[ 0 ] - 0.817 * gl_Vertex[ 1 ] + 0.817 * gl_Vertex[ 2 ] + 1.0 ) / ( 1.817 );
}
