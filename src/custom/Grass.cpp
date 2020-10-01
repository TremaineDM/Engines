#include "Grass.h"

Grass::Grass()
{

}

Grass::Grass(const char* name, MATH::Vec3 position, unsigned int amount_) : MeshRenderer("resources/models/LowPolyGrass.obj")
{
	this->name = name;
	transform.setPos(position);
	MeshRenderer::Init(this);
	MeshRenderer::CreateShader("src/graphics/shaders/GrassVert.glsl", "src/graphics/shaders/GrassFrag.glsl");
	MeshRenderer::SetInstanceID(1);
	Instancer::Init(amount_, gameobject);
	MeshRenderer::SetInstanceAmount(amount_);
}

Grass::~Grass()
{
}

void Grass::Update(const float deltaTime)
{
	transform.Update(deltaTime);
	MeshRenderer::Update(deltaTime);
}

void Grass::Render() const
{
	MeshRenderer::Render();

	
}

void Grass::HandleEvents(const SDL_Event& event)
{
	MeshRenderer::HandleEvents(event);
}


