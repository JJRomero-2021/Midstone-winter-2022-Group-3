#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "Sphere.h"
#include <SDL_image.h>

using namespace MATH;

class PhysicsObject {
	friend class Physics;
protected:
	Vec3 pos, vel, accel;
	float mass;
	Sphere boundingSphere;
	float angle, angularVel, angularAccel, rotationalI;
	SDL_Surface* image;
	SDL_Texture* texture;
public:
	PhysicsObject();
	virtual ~PhysicsObject();
	

public:
	/// Untility functions so small they cane be inlined
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void setAngularVel(const float angularVel_) { angularVel = angularVel_; }
	inline void applyForce(const Vec3 force) { accel = force / mass;  }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	SDL_Texture* getTexture() { return texture; }


};
#endif

