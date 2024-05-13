#include "spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

ncSpring_t* ncSprings = NULL;

ncSpring_t* CreateSpring(struct ncBody* body1, struct ncBody* body2, float restLength, float k)
{
	ncSpring_t* spring = (ncSpring_t*)malloc(sizeof(ncSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(ncSpring_t));

	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}

void AddSpring(ncSpring_t* spring)
{
	assert(spring);

	//add element to linked list
	spring->prev = NULL;
	spring->next = ncSprings;

	if (ncSprings) ncSprings->prev = spring;

	//set head of element to new element
	ncSprings = spring;
}

void DestroySpring(ncSpring_t* spring)
{
	if (!spring) return;

	if (spring->prev) spring->prev->next = spring->next;
	if (spring->next) spring->next->prev = spring->prev;

	if (spring == ncSprings) ncSprings = spring->next;

	free(spring);
}

void DestoryAllSprings()
{

}

void ApplySpringForce(ncSpring_t* springs) 
{

}