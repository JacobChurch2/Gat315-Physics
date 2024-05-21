#pragma once
#include "raylib.h"

typedef struct ncBody ncBody;

typedef struct ncSpring
{
	struct ncBody* body1;
	struct ncBody* body2;
	float restLength;
	float k; // stiffness

	struct ncSpring* next;
	struct ncSpring* prev;
}ncSpring_t;

extern ncSpring_t* ncSprings;

ncSpring_t* CreateSpring(struct ncBody* body1, struct ncBody* body2, float restLength, float k);
void ApplySpringForcePosition(Vector2 position, ncBody* body, float restLength, float k, float damping);
//void ApplySpringForcePosition(Vector2 position, ncBody* body, float restLength, float k, float damping);
void AddSpring(ncSpring_t* spring);
void DestroySpring(ncSpring_t* spring);
void DestoryAllSprings();

void ApplySpringForce(ncSpring_t* springs);