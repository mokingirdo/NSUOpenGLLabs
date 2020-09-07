#include "GL20TextureSampler.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"


GL20TextureSampler::GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	m_useAniso = false;
	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

GL20TextureSampler::~GL20TextureSampler()
{

}

void GL20TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
	// https://www.opengl.org/wiki/Sampler_Object
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
	// http://opengl-master.ru/view_post.php?id=78
	// http://www.araku.ac.ir/~d_comp_engineering/88892/1323108/OpenGL%20Game%20Development.pdf

	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		m_filterMode = GL_NEAREST;
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		m_filterMode = GL_LINEAR_MIPMAP_NEAREST;
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		m_filterMode = GL_LINEAR_MIPMAP_LINEAR;
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		m_useAniso = true;
		m_filterMode = GL_LINEAR_MIPMAP_LINEAR;
		// TODO: Task05_01
	}
}

void GL20TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	// http://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do

	m_wrapMode = wrapMode;

	if (wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		m_wrapMode = GL_CLAMP;
		// TODO: Task05_01
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		m_wrapMode = GL_REPEAT;
		// TODO: Task05_01
	}
}

void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	// TODO: Task05_01

	// Set wrap mode (Clamp, Repeat).

	//ПОВТОРЯТЬ ПО ОСИ Х И У
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
	// TODO: Task05_01
	//устанавливаем фильтрацию
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
		
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic).
	// TODO: Task05_01
	
	// Enable/disable anisotropic filter.
	if (m_useAniso)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 25);
		// TODO: Task05_01
	}
	else
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		// TODO: Task05_01
	}
}
