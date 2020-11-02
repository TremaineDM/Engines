#ifndef SCENE1_H
#define SCENE1_H

#include "Scene.h"
#include "custom/Camera.h"
#include "custom/TestModel.h"
#include "custom/Plane.h"
#include "graphics/Shader.h"
#include "custom/Grass.h"
#include "imgui/imgui.h"
#include "custom/LightObject.h"

/**< Forward declaring classes that we will use  */
class MouseRay;
class Player;
class Tilemap;

//! Scene 1 class
/*!  This class inherits from Scene and controls all events and object's in the first scene */
class Scene1 : public Scene
{
private:
	//! Player Pointer
	/*! Used for movement and interacting with the world  */
	Player* player; 
	
	//! Grass Pointer
	/*! Is a gameobject that we can spawn into the world  */
	Grass* grass;

	//! TestModel Pointer
	/*! Is a gameobject that we can spawn into the world  */
	TestModel* fog;

	//! Plane Pointer
	/*! Is a gameobject that we can spawn into the world  */
	Plane* plane;

	//! MouseRay Pointer
	/*! Converts mouse position on screen to world space to allow us to do mouse picking  */
	MouseRay* mouseRay;

	//! Debug Pointer
	/*! Used for all of our debug functions */
	Debug debug;

	LightObject* light;

private:
	//! GameObject Pointer
	/*! Stores our object that was most recently selected using our mouseRay */
	GameObject* selectedObject;	 

	//! Const Char* Pointer
	/*! Stores our objects that can be spawned */
	const char* objClasses[2] = { "Plane", "Test Object" };

	//! Create object with object ID function
	/*! Used when we want to runtime spawn objects depending on the given ID */
	void CreateObjWithID(Vec3 pos_,  Vec3 rot_,  Vec3 scale_, const char* name_, const int& ID) const;

public:
	//! Scene 1 Constructor
	Scene1();
	//! Scene 1 Destructor 
	~Scene1();

	//! Virtual overridden OnCreate Function
	/*! Gets called at the beginning of the loop */
	virtual bool OnCreate() override;

	//! Virtual overridden OnDestroy Function
	/*! Gets called at the end of the loop */
	virtual void OnDestroy() override;

	//! Virtual overridden Update Function
	/*! Updates all of the gameobjects throughout the loop */
	virtual void Update(const float deltaTime) override;

	//! Virtual overridden Render Function
	/*! Renders all of the gameobjects throughout the loop */
	virtual void Render() const override;

	//! Virtual overridden HandleEvents Function
	/*! Checks for keyboard/mouse events throughout the loop */
	virtual void HandleEvents(const SDL_Event &event) override;

	//! Virtual overridden Reset Function
	/*! When called resets the scene back to its original state */
	virtual void Reset() override;

	//! Virtual overridden SaveMapData Function
	/*! Saves objects and object transforms in the scene */
	virtual void SaveMapData() const override;

	//! Virtual overridden LoadMapData Function
	/*! Loads objects and object transforms in the scene */
	virtual void LoadMapData() override;
	
	//! Check Intersection function
	/*! Checks if the MouseRay has intersected with a object */
	bool CheckIntersection(MouseRay *ray, const Vec3& origin, GameObject* obj);
};
#endif