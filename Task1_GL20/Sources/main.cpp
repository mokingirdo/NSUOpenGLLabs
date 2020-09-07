// vs2010.cpp : Defines the entry point for the console application.
//

//https://www.opengl.org/sdk/docs/man/
#include "stdafx.h"
#include "glew.h" // Include the GLEW header file
#include "glut.h" // Include the GLUT header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


float width;
float height;

GLuint vertexShader;
GLuint fragmentShader;
GLuint program;

GLuint bufferPosition;
GLuint bufferColor;

GLuint attrConstColor;


void InitGeometry()
{
	GLfloat vertices[] = {
		-0.5f,  0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,

		 0.5f, -0.5f, 0.5f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f,
		 -0.5f,  0.5f, -0.5f, 1.0f,

		 -0.5f,  0.5f, 0.5f, 1.0f,
		 -0.5f,  -0.5f, -0.5f, 1.0f,
		 -0.5f,  -0.5f, 0.5f, 1.0f,
		 0.5f,  -0.5f, 0.5f, 1.0f,

		 -0.5f, 0.5f, 0.5f, 1.0f,
		  0.5f, 0.5f, 0.5f, 1.0f,
//Earth
		-0.5f,  0.5f, -0.5f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f,

		0.5f, -0.5f, 0.5f, 1.0f,
		0.5f,  0.5f, -0.5f, 1.0f,
		0.5f,  0.5f, 0.5f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,

		-0.5f,  0.5f, 0.5f, 1.0f,
		-0.5f,  -0.5f, -0.5f, 1.0f,
		-0.5f,  -0.5f, 0.5f, 1.0f,
		0.5f,  -0.5f, 0.5f, 1.0f,

		-0.5f, 0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f,
//
		  /*-6.0f,  0.5f, -0.5f, 2.0f,
		  -5.0f,  0.5f, -0.5f, 2.0f,
		  -6.0f, -0.5f, -0.5f, 2.0f,
		  -5.0f, -0.5f, -0.5f, 2.0f,

		  -5.0f, -0.5f, 0.5f, 2.0f,
		  -5.0f,  0.5f, -0.5f, 2.0f,
		  -5.0f,  0.5f, 0.5f, 2.0f,
		  -6.0f,  0.5f, -0.5f, 2.0f,

		  -6.0f,  0.5f, 0.5f, 2.0f,
		  -6.0f,  -0.5f, -0.5f, 2.0f,
		  -6.0f,  -0.5f, 0.5f, 2.0f,
		  -5.0f,  -0.5f, 0.5f, 2.0f,

		  -6.0f, 0.5f, 0.5f, 2.0f,
		  -5.0f, 0.5f, 0.5f, 2.0f,*/
 //Moon

			-0.5f,  0.5f, -0.5f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,
			 -0.5f, -0.5f, -0.5f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f,

			 0.5f, -0.5f, 0.5f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f,
			 0.5f,  0.5f, 0.5f, 1.0f,
			-0.5f,  0.5f, -0.5f, 1.0f,

			 -0.5f,  0.5f, 0.5f, 1.0f,
			-0.5f,  -0.5f, -0.5f, 1.0f,
			-0.5f,  -0.5f, 0.5f, 1.0f,
			0.5f,  -0.5f, 0.5f, 1.0f,

			-0.5f, 0.5f, 0.5f, 1.0f,
			 0.5f, 0.5f, 0.5f, 1.0f,
		 /* -11.0f,  0.5f, -0.5f, 3.0f,
		  -10.0f,  0.5f, -0.5f, 3.0f,
		  -11.0f, -0.5f, -0.5f, 3.0f,
		  -10.0f, -0.5f, -0.5f, 3.0f,

		  -10.0f, -0.5f, 0.5f, 3.0f,
		  -10.0f,  0.5f, -0.5f, 3.0f,
		  -10.0f,  0.5f, 0.5f, 3.0f,
		  -11.0f,  0.5f, -0.5f, 3.0f,

		  -11.0f,  0.5f, 0.5f, 3.0f,
		  -11.0f,  -0.5f, -0.5f, 3.0f,
		  -11.0f,  -0.5f, 0.5f, 3.0f,
		  -10.0f,  -0.5f, 0.5f, 3.0f,

		  -11.0f, 0.5f, 0.5f, 3.0f,
		  -10.0f, 0.5f, 0.5f, 3.0f*/
	};

	glGenBuffers(1, &bufferPosition);
	glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLfloat colors[] = {
		1.0, 1.0, 0.0, 1.0f,
		1.0, 0.0, 0.0, 1.0f,
		1.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,

		1.0, 0.0, 0.0, 1.0f,
		1.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,

		1.0, 0.0, 0.0, 1.0f,
		1.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,
		1.0, 0.0, 0.0, 1.0f,

		1.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 0.0, 1.0f,

		//Earth

		0.0, 1.0, 0.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,

		0.0, 0.0, 1.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,

		0.0, 0.0, 1.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,

		0.0, 0.0, 1.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,
		//Moon
		1.0, 1.0, 1.0, 1.0f,
		0.0, 0.0, 0.0, 1.0f,
		0.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 1.0, 1.0f,

		0.0, 0.0, 0.0, 1.0f,
		0.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 1.0, 1.0f,
		1.0, 1.0, 1.0, 1.0f,

		0.0, 0.0, 0.0, 1.0f,
		0.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 1.0, 1.0f,
		0.0, 0.0, 0.0, 1.0f,

		0.0, 0.0, 0.0, 1.0f,
		1.0, 1.0, 1.0, 1.0f
		
	};

	glGenBuffers(1, &bufferColor);
	glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

void DeinitGeometry()
{
	
}

void Render (void)
{
	
	
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f); // Clear the background of our window to red  
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

	glUseProgram(program);

	// Matrix Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;
	
	// Matrix View
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 3.0f, 5.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f);

	double t = (double)clock() / 700;

	glm::mat4x4 matWorld = glm::mat4x4();
	glm::mat4x4 matView  = glm::lookAt(glm::vec3(0, 3, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	matWorld = glm::rotate(matWorld, (float)t, glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4x4 rot = glm::lookAt(glm::vec3(cos(t), 0., -sin(t)), glm::vec3(sin(t), 0, cos(t)), glm::vec3(0,1,0));
		
	glm::mat4x4 matWorldViewSun = matView * matWorld;
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&matWorldViewSun[0][0]);
	{
		glUniform4f(attrConstColor, 3, 3, 3, 1);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		
		glBindBuffer(GL_ARRAY_BUFFER, bufferPosition);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, bufferColor);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);


		glm::mat4x4 matWorldViewEarth = glm::mat4x4();

		matWorldViewEarth = glm::translate(matWorldViewEarth, glm::vec3(2.0f, 0.0f, 0.0f));
		matWorldViewEarth = glm::scale(matWorldViewEarth, glm::vec3(0.5f, 0.5f, 0.5f));
		matWorldViewEarth = glm::rotate(matWorldViewEarth, (float)t, glm::vec3(0.0f, 1.0f, 0.0f));

		matWorldViewSun = matWorldViewSun * matWorldViewEarth;
		glLoadMatrixf(&matWorldViewSun[0][0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 14, 14);

		glm::mat4x4 matWorldViewMoon = glm::mat4x4();

		matWorldViewMoon = glm::translate(matWorldViewMoon, glm::vec3(2.0f, 0.0f, 0.0f));
		matWorldViewMoon = glm::scale(matWorldViewMoon, glm::vec3(0.5f, 0.5f, 0.5f));
		matWorldViewMoon = glm::rotate(matWorldViewMoon, (float)t, glm::vec3(0.0f, 1.0f, 0.0f));

		matWorldViewSun = matWorldViewSun * matWorldViewMoon;
		glLoadMatrixf(&matWorldViewSun[0][0]);

		glDrawArrays(GL_TRIANGLE_STRIP, 28, 14);

		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(0);
	}

	glUseProgram(0);

	
	glFlush(); // Flush the OpenGL buffers to the window  
}

// Calls in loop
void Cycle() 
{
	// ������� ����������� ������ (������� Render)
	glutPostRedisplay();
}

// Reshapes the window appropriately
void Reshape(int w, int h)
{
	width  = w;
	height = h;

	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width/(GLdouble)height, 0.01, 100.0) ;


}

void InitShaders()
{
	//! �������� ��� ��������
	const char* vsSource = 
		//"attribute vec3 coord;\n"
		//"out vec3 fragmentColor;\n"
		"attribute vec4 position;"
		"attribute vec4 color;"
		"uniform vec4 constColor;"
		"void main() {\n"
		//"  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
		//"  gl_FrontColor = gl_Color;\n"
		"  gl_Position =  gl_ModelViewProjectionMatrix * position;\n"
		"  gl_FrontColor = color * constColor;\n"
		"}\n";
	const char* fsSource = 
		//"uniform vec4 color;\n"
		//"in vec3 fragmentColor;\n"
		"void main() {\n"
		//"  gl_FragColor = color;\n"
		"  gl_FragColor = gl_Color;\n"
		//"  gl_FragColor = vec4(fragmentColor, 1.0);\n"
		"}\n";
	int success = 0;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (vertexShader, 1, &vsSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv  (vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(vertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource (fragmentShader, 1, &fsSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv  (fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(fragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in vertex shader compilation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");

	glLinkProgram (program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program linkage!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetProgramInfoLog(program, MAX_INFO_LOG_SIZE, NULL, infoLog);
		fprintf(stderr, "Error in program validation!\n");
		fprintf(stderr, "Info log: %s\n", infoLog);
	}

	attrConstColor = glGetUniformLocation(program, "constColor");
}

void DeinitShaders()
{
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteProgram(program);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}

//int _tmain(int argc, _TCHAR* argv[])
int _tmain(int argc, char* argv[])
{
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitDisplayMode(GLUT_RGBA /*| GLUT_DEPTH | GLUT_DOUBLE*/); // Set up a basic display buffer (only single buffered for now)
	//glEnable(GL_DEPTH_TEST);
	// Create the application's window
	{
		glutInitWindowPosition(100, 100);			// Set the position of the window
		glutInitWindowSize(512, 512);				// Set the width and height of the window
		glutCreateWindow("OpenGL First Window");	// Set the title for the window
	}

	GLenum err = glewInit(); 
	if (GLEW_OK != err) 
	{ 
		return 0;
	}

	glutDisplayFunc(Render); // Tell GLUT to use the method "display" for rendering  
	glutReshapeFunc(Reshape);
	glutIdleFunc(Cycle);
	
	InitGeometry();
	InitShaders();

	glutMainLoop(); // Enter GLUT's main loop

	// TODO: ������� ������� �������� ���� � ���������� �������
	DeinitShaders();

	int i = 0;

	return 0;
}
