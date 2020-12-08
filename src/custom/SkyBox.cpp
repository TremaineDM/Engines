#include "SkyBox.h"
#include "core/ModelManager.h"
SkyBox::SkyBox()
{
#pragma region MyRegion
		float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
#pragma endregion

	bool result = LoadSkyBox("resources/skybox/right.jpg", "resources/skybox/left.jpg", "resources/skybox/top.jpg", "resources/skybox/bottom.jpg", "resources/skybox/front.jpg", "resources/skybox/back.jpg");
	if (!result) { std::cout << "sky box failed to load textures" << std::endl; }
	
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	shader = new Shader();
	shader->CreateShader("src/graphics/shaders/SkyBoxVert.glsl", "src/graphics/shaders/SkyBoxFrag.glsl");
	shader->RunShader();
	
}
SkyBox::~SkyBox()
{
	glDeleteTextures(1, &skyboxTextureID);
}
bool SkyBox::LoadSkyBox(const char* posx, const char* negx, const char* posy, const char* negy, const char* posz, const char* negz)
{
	
	glGenTextures(1, &skyboxTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	SDL_Surface* texSurface = IMG_Load(posx);
	if (texSurface == nullptr) { return false; }
	int mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);

	
	texSurface = IMG_Load(negx);
	if (texSurface == nullptr) { return false; }
    mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);

	
	texSurface = IMG_Load(posy);
	if (texSurface == nullptr) { return false; }
	mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);

	
	texSurface = IMG_Load(negy);
	if (texSurface == nullptr) { return false; }
	mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);

	
	texSurface = IMG_Load(posz);
	if (texSurface == nullptr) { return false; }
	mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);


	texSurface = IMG_Load(negz);
	if (texSurface == nullptr) { return false; }
	mode = (texSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, texSurface->w, texSurface->h, 0, mode, GL_UNSIGNED_BYTE, texSurface->pixels);
	SDL_FreeSurface(texSurface);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}


void SkyBox::Update(const float deltaTime)
{
	
}

void SkyBox::Render() const
{
	
	
	glDepthFunc(GL_LEQUAL);
	//glDisable(GL_CULL_FACE);
	shader->RunShader();
	shader->TakeInUniformMat4("viewMatrix", Camera::getInstance()->getRotationMatrix());
	shader->TakeInUniformMat4("projectionMatrix", Camera::getInstance()->getProjectionMatrix());
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	//glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	
}

void SkyBox::HandleEvents(const SDL_Event& event)
{
}
