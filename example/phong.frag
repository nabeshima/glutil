uniform sampler2D texture;

varying vec3 position;
varying vec3 normal;

void main( void ) {
  vec4 color = texture2D( texture, gl_TexCoord[ 0 ].st * 5.0 );  

  vec3 fnormal = normalize( normal );
  vec3 light = normalize( gl_LightSource[ 0 ].position.xyz - position );
  float diffuse = dot( light, fnormal );
  
  gl_FragColor = color * gl_FrontLightProduct[ 0 ].ambient;

  if ( diffuse > 0.0 ) {
    
    vec3 view = normalize( position );
    vec3 halfway = normalize( light - view );
    float specular = pow( max( dot( fnormal, halfway ), 0.0 ), gl_FrontMaterial.shininess );
    
    gl_FragColor += 
      color * gl_FrontLightProduct[ 0 ].diffuse * diffuse
      + gl_FrontLightProduct[ 0 ].specular * specular;
  }
}
