/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	World.cpp

	See World.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\data_loader\GameDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\graphics\RenderList.h"
#include "sssf\graphics\TextureManager.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gui\Viewport.h"

/*
	World - Default Constructor, it constructs the layers
	vector, allowing new layers to be added.
*/
World::World()	
{
	layers = new vector<WorldLayer*>();
	worldWidth = 0;
	worldHeight = 0;
}

/*
	~World - This destructor will remove the memory allocated
	for the layer vector.
*/
World::~World()	
{
	delete layers;
}

/*
	addLayer - This method is how layers are added to the World.
	These layers might be TiledLayers, SparseLayers, or 
	IsometricLayers, all of which are child classes of WorldLayer.
*/
void World::addLayer(WorldLayer *layerToAdd)
{
	layers->push_back(layerToAdd);
}

/*
	addWorldRenderItemsToRenderList - This method sends the render
	list and viewport to each of the layers such that they
	may fill it with RenderItems to draw.
*/
void World::addWorldRenderItemsToRenderList(Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();
		for (unsigned int i = 0; i < layers->size(); i++)
		{
			layers->at(i)->addRenderItemsToRenderList(	renderList,
				viewport);
		}
	}
}

void World::initBox2DTiles()
{
	//Don't have any gravity, because we're top-down
	b2Vec2 gravity(0.0f, 0.0f);
	boxWorld = new b2World(gravity);

	for(unsigned int i = 0; i < layers->size(); i++)
	{
		if(layers->at(i)->hasCollidableTiles() == true)
		{
			TiledLayer* layer = (TiledLayer*)layers->at(i);
			int columns = layer->getColumns();
			int rows = layer->getRows();

			for(int j = 0; j < rows; j++)
			{
				for(int z = 0; z < columns; z++)
				{
					Tile* tile = layer->getTile(j,z);
					if(tile->collidable == true)
					{
						b2BodyDef tileBodyDef;
						float tileWidth = (layer->getTileWidth() * 1.0f)/5.0f;
						float tileHeight = (layer->getTileHeight() * 1.0f)/5.0f;
						float pX = (z)*tileWidth + tileWidth/2.0f;
						float pY = -1.0f*(j)*tileHeight - (tileHeight/2.0f);

						tileBodyDef.position.Set(pX, pY);
						b2Body* tileBody = boxWorld->CreateBody(&tileBodyDef);
						b2PolygonShape tileBox;
						tileBox.SetAsBox(tileWidth/2.0f, tileHeight/2.0f);
						tileBody->CreateFixture(&tileBox, 0.0f);
					}
				}
			}
		}
	}
}

/*
	clear - This method removes all data from the World. It should
	be called first when a level is unloaded or changed. If it
	is not called, an application runs the risk of having lots
	of extra data sitting around that may slow the progam down.
	Or, if the world thinks a level is still active, it might add
	items to the render list using image ids that have already been
	cleared from the GameGraphics' texture manager for the world.
	That would likely result in an exception.
*/
void World::unloadWorld()
{
	layers->clear();
	worldWidth = 0;
	worldHeight = 0;
}

/*
	update - This method should be called once per frame. Note that
	the World is for static objects, so we don't have anything
	to update as/is. But, should the need arise, one could add non-
	collidable layers to a game world and update them here. For
	example, particle systems.
*/
void World::update(Game *game)
{
	// NOTE THAT THIS METHOD IS NOT IMPLEMENTED BUT COULD BE
	// SHOULD YOU WISH TO ADD ANY NON-COLLIDABLE LAYERS WITH
	// DYNAMIC CONTENT OR PARTICLE SYSTEMS
}

int	World::getCollidableGridColumns()
{
	int maxColumns = 0;
	vector<WorldLayer*>::iterator it = layers->begin();
	while (it != layers->end())
	{
		WorldLayer *layer = (*it);
		if (layer->hasCollidableTiles())
		{
			int numColumns = layer->getColumns();
			if (numColumns > maxColumns)
				maxColumns = numColumns;
		}
		it++;
	}
	return maxColumns;
}

int World::getCollidableGridRows()
{
	int maxRows = 0;
	vector<WorldLayer*>::iterator it = layers->begin();
	while (it != layers->end())
	{
		WorldLayer *layer = (*it);
		if (layer->hasCollidableTiles())
		{
			int numRows = layer->getRows();
			if (numRows > maxRows)
				maxRows = numRows;
		}
		it++;
	}
	return maxRows;
}

bool World::isInsideCollidableTile(int centerX, int centerY)
{
	vector<WorldLayer*>::iterator it = layers->begin();
	while (it != layers->end())
	{
		WorldLayer *layer = (*it);
		if (layer->hasCollidableTiles())
		{
			if (layer->isInsideCollidableTile(centerX, centerY))
				return true;
		}
		it++;
	}
	return false;}

bool World::overlapsCollidableTiles(int centerX, int centerY, int nodeWidth, int nodeHeight)
{
	vector<WorldLayer*>::iterator it = layers->begin();
	while (it != layers->end())
	{
		WorldLayer *layer = (*it);
		if (layer->hasCollidableTiles())
		{
			AABB aabb;
			aabb.setCenterX((float)centerX);
			aabb.setCenterY((float)centerY);
			aabb.setWidth((float)nodeWidth);
			aabb.setHeight((float)nodeHeight);
			bool overlaps = layer->overlapsCollidableTile(aabb);
			if (overlaps)
				return true;
		}
		it++;
	}
	return false;
}