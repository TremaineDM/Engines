#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(const char* name, MATH::Vec3 position) : MeshRenderer("Plane.fbx")
{
	this->name = name;
	transform.setPos(position);

	transform.scale =  Vec3(1.0f, 1.0f, 1.0f);
	transform.rotation = Vec3(90.0f, 0.0f, 0.0f);
	transform.rotation.print();

	RigidBody3D::Init(this);
	MeshRenderer::Init(this);

	MeshRenderer::CreateShader("src/graphics/shaders/DefaultVert.glsl", "src/graphics/shaders/DefaultFrag.glsl");

}

Plane::~Plane()
{
}

void Plane::Update(const float deltaTime)
{
	//transform.rotation.y += deltaTime;
	transform.Update(deltaTime);
	MeshRenderer::Update(deltaTime);
	RigidBody3D::Update(deltaTime);
}

void Plane::Render() const
{
	MeshRenderer::Render();
}

void Plane::HandleEvents(const SDL_Event& event)
{
	MeshRenderer::HandleEvents(event);
}

void Plane::OnCollisionEnter(RigidBody3D& otherBody)
{
	
}