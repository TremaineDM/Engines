#include "Water.h"
#include "core/Timer.h"

Water::Water(const char* name, MATH::Vec3 pos, SkyBox* _skybox):MeshRenderer("Plane.fbx"){
	this->name = name;
	this->transform.pos = pos;
	//reflectTex = new Texture("resources/textures/water_dudv.png");
	//reflectTex->LoadImage();
	MeshRenderer::Init(this);
	MeshRenderer::renderFlags = RenderProperties::OVERRIDE_RENDERER;
	MeshRenderer::CreateShader("src/graphics/shaders/WaterVert.glsl", "src/graphics/shaders/WaterFrag.glsl");
	MeshRenderer::SetInstanceID(0);
	//initRefractionFB();
	//initReflectionFB();
	
}

Water::~Water()
{
	glDeleteFramebuffers(1, &refractionFrameBuffer);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteFramebuffers(1, &reflectionFrameBuffer);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteTextures(1, &refractionTexture);
	glDeleteTextures(1, &refractionDepthTexture);
	skyBox = nullptr;
	
}

//Pass the skybox in scene from renderer
const void Water::GetSkyBoxInfo()
{
	if (skyBox == nullptr) { skyBox = Renderer::GetSkyBox(); }
	skyboxID = skyBox->GetSkyBoxTexture();
	skyBoxVAO = skyBox->GetVAO();
}


void Water::BindReflectionFrameBuffer() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
	glViewport(0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
}

void Water::BindRefractionFrameBuffer() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
	glViewport(0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
}

void Water::CreateReflectionFrameBuffer()
{
	glGenFramebuffers(1, &reflectionFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, reflectionFrameBuffer);
	glDrawBuffer(reflectionFrameBuffer);
}

void Water::CreateRefractionFrameBuffer()
{
	glGenFramebuffers(1, &refractionFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, refractionFrameBuffer);
	glDrawBuffer(refractionFrameBuffer);
}

void Water::CreateTextureAttachment(unsigned int texture, int width, int height)
{
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
}

void Water::CreateDepthBufferAttachment()
{
	glGenRenderbuffers(1, &reflectionDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);
}

void Water::CreateDepthTextureAttachment()
{

	glGenTextures(1, &refractionDepthTexture);
	glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, refractionDepthTexture, 0);

}

void Water::initReflectionFB()
{
	CreateReflectionFrameBuffer();
	CreateTextureAttachment(reflectionTexture, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	CreateDepthBufferAttachment();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	UnbindCurrentFB();

}

void Water::initRefractionFB()
{
	CreateRefractionFrameBuffer();
	CreateTextureAttachment(refractionTexture, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	CreateDepthTextureAttachment();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	UnbindCurrentFB();
}

void Water::UnbindCurrentFB() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0,Globals::SCREEN_WIDTH ,Globals::SCREEN_HEIGHT);
}


void Water::Update(const float deltaTime)
{
	time += Timer::GetScaledDeltaTime();
}

void Water::Render() const
{
	glEnable(GL_DEPTH_TEST);
	
	//BindReflectionFrameBuffer();
	//BindRefractionFrameBuffer();
	MeshRenderer::shader.RunShader();
	glBindVertexArray(skyBoxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, reflectTex->getTextureID());
	MeshRenderer::shader.TakeInUniformMat4("cube", Camera::getInstance()->getViewMatrix());
	MeshRenderer::shader.TakeInUniformVec3("cameraPos", Camera::getInstance()->getPosition());
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDrawBuffer(reflectionDepthBuffer);
	//texture.DrawTextureToScreen(refractionTexture, 1.0f, 0.5f, 0.0f, 0.5f);
	MeshRenderer::Render();
	//UnbindCurrentFB();
}
void Water::HandleEvents(const SDL_Event& event)
{
}