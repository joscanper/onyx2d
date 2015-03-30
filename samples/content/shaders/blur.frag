uniform sampler2D tex; 
uniform float alpha;

void main()
{
  vec4 tc;

  tc = texture2D(tex, gl_TexCoord[0].xy);
  tc += texture2D(tex, gl_TexCoord[0].xy + (0.01));
  tc += texture2D(tex, gl_TexCoord[0].xy - (0.01));
  
  tc.a *= alpha;
  
  gl_FragColor = tc/3.0;
}
