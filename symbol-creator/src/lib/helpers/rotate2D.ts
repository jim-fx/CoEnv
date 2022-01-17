export function rotate2D(vec, angleInDegree){
	const angle = angleInDegree * (Math.PI/180);	
	const x = vec[0] * Math.cos(angle) - vec[1] * Math.sin(angle)
	const y = vec[0] * Math.sin(angle) + vec[1] * Math.cos(angle)
	return [x,y];
}
