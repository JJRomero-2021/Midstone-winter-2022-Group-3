#include "Particles.h"
#include "Randomizer.h"

Particles::Particles(int numberOfParticles):vao(0),vbo(0){
	Randomizer r;

	for(int i =0; i< numberOfParticles; ++i){
		pos.push_back(Vec3(0.0f,0.0f,0.0f));
		vel.push_back(Vec3(r.box_muller(0.0f,10.0f), r.box_muller(0.0f,10.0f), r.box_muller(0.0f, 2.0f)));
		color.push_back(Vec4(r.rand(0.5f, 1.0f), r.rand(0.0f, 1.0f), r.rand(0.0f, 1.0f),1.0));
	}
	setupParticles();
	printf("Done loading\n");
}

Particles::~Particles(){
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}


#define POS_LENGTH 	(pos.size() * (sizeof(Vec3)))
#define VEL_LENGTH 	(vel.size() * (sizeof(Vec3)))
#define COLOR_LENGTH (color.size() * (sizeof(Vec4)))

void Particles::setupParticles(){

	const int posID = 0;
	const int velID = 1;
	const int colorID = 2;

	/// create and bind the VOA
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	/// Create and initialize vertex buffer object VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, POS_LENGTH + VEL_LENGTH + COLOR_LENGTH, NULL, GL_STATIC_DRAW);

	/// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
	glBufferSubData(GL_ARRAY_BUFFER, 0, POS_LENGTH, &pos[0]);
	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
	glBufferSubData(GL_ARRAY_BUFFER, POS_LENGTH, VEL_LENGTH, &vel[0]);
	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
	glBufferSubData(GL_ARRAY_BUFFER, POS_LENGTH + VEL_LENGTH, COLOR_LENGTH, &color[0]);

	glEnableVertexAttribArray(posID);
	glVertexAttribPointer(posID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(velID);
	glVertexAttribPointer(velID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(POS_LENGTH));
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(POS_LENGTH + VEL_LENGTH));
	glBindVertexArray(0);
}
#undef POS_LENGTH
#undef VEL_LENGTH
#undef COLOR_LENGTH

void Particles::Render() const {
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, pos.size());
	glBindVertexArray(0); // Disable the VAO
	glDisable(GL_PROGRAM_POINT_SIZE);
}