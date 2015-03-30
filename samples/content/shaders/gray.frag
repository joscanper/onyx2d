uniform sampler2D tex;
uniform float alpha;
void main()
{	
	vec4 color = texture2D(tex, gl_TexCoord[0].st);	
	color.a *= alpha;
	float gray = dot(color.rgb, vec3(0.3,0.59,0.11));	
	gl_FragColor = vec4(gray, gray, gray, color.a);
	
}
