#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody() 
{
	Body* newBody = (Body*)malloc(sizeof(Body));
	assert(newBody);

	newBody->prev = NULL;
	newBody->next = bodies;

	if (bodies) 
	{
		bodies->prev = newBody;
	}

	bodies = newBody;
	bodyCount++;

	return newBody;
}

void DestroyBody(Body* body)
{
	if (!body) return;

	if (body->prev) 
	{
		body->prev->next = body->next;
	}

	if (body->next)
	{
		body->next->prev = body->prev;
	}

	if (bodies == body) 
	{
		bodies = body->next;
	}

	bodyCount--;

	free(body);
}