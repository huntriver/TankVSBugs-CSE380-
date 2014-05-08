#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\AABB.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "Box2D\Box2D.h"

// THESE ARE THE SWEEP AND PRUNE ORDERINGS
const unsigned int LEFT_EDGE = 0;
const unsigned int RIGHT_EDGE = 1;
const unsigned int TOP_EDGE = 2;
const unsigned int BOTTOM_EDGE = 3;

class CollidableObject
{
protected:
	AABB boundingVolume;
	bool currentlyCollidable;
	AABB sweptShape;
	unsigned int sweepAndPruneIndices[4];
	PhysicalProperties pp;
	bool onTileThisFrame;
	bool onTileLastFrame;
	unsigned int collisionEdge;
	b2Body* body;
	// Collision Counter
	int leftEdgeCC;
	int rightEdgeCC;
	int upEdgeCC;
	int downEdgeCC;

public:
	CollidableObject()	
	{
		leftEdgeCC = 0;
		rightEdgeCC = 0;
		upEdgeCC = 0;
		downEdgeCC = 0;
	}
	~CollidableObject()	{}

	// CollidableObject.cpp METHODS
	void updateSweptShape(float percentageOfFrameTimeRemaining);

	// INLINED METHODS
	int getLeftEdgeCC() { return leftEdgeCC;}
	int getRightEdgeCC() { return rightEdgeCC;}
	int getUpEdgeCC() { return upEdgeCC;}
	int getDownEdgeCC() { return downEdgeCC;}
	bool				isCurrentlyCollidable()		{ return currentlyCollidable;	}
	bool				isOnTileThisFrame()			{ return onTileThisFrame;		}
	bool				wasOnTileLastFrame()		{ return onTileLastFrame;		}
	AABB*				getBoundingVolume()			{ return &boundingVolume;		}
	AABB*				getSweptShape()				{ return &sweptShape;			}
	PhysicalProperties* getPhysicalProperties()		{ return &pp;					}
	b2Body*				getB2Body()					{ return body;                  }
	unsigned int		getCollisionEdge()			{ return collisionEdge;			}

	void				setCollisionEdge(unsigned int initCollisionEdge)
	{	collisionEdge = initCollisionEdge; }
	unsigned int		getSweepAndPruneIndex(unsigned int sweepAndPruneOrdering)		
	{ return sweepAndPruneIndices[sweepAndPruneOrdering];	}
	void				setSweepAndPruneIndex(unsigned int sweepAndPruneOrdering, unsigned int index)
	{ sweepAndPruneIndices[sweepAndPruneOrdering] = index;  }

	void setCurrentlyCollidable(bool initCurrentlyCollidable)
	{	currentlyCollidable = initCurrentlyCollidable; }
	void setOnTileThisFrame(bool initOnTileThisFrame)
	{	onTileThisFrame = initOnTileThisFrame; }
	void setOnTileLastFrame(bool initOnTileLastFrame)
	{	onTileLastFrame = initOnTileLastFrame; }
	void setB2Body(b2Body* initBody)
	{
		body = initBody;
	}

	void advanceOnTileStatus()
	{
		onTileLastFrame = onTileThisFrame;
		onTileThisFrame = false;
	}

	void setLeftEdgeCC(int initLeftEdgeCC)
	{
		leftEdgeCC = initLeftEdgeCC;
	}

	void setRightEdgeCC(int initRightEdgeCC)
	{
		rightEdgeCC = initRightEdgeCC;
	}

	void setUpEdgeCC(bool initUpEdgeCC)
	{
		upEdgeCC = initUpEdgeCC;
	}

	void setDownEdgeCC(bool initDownEdgeCC)
	{
		downEdgeCC = initDownEdgeCC;
	}
};