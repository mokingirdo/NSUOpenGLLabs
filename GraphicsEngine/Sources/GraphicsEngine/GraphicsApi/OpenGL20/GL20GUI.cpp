#include "GL20GUI.h"
#include <string.h>
#include <stdio.h>
#include <string>

void GL20GUI::Label(int x, int y, int w, int h,  const char * pText)
{
	// http://stackoverflow.com/questions/9430852/glutbitmapcharacter-positions-text-wrong


	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // save
	glLoadIdentity();// and clear
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top

	glRasterPos2f(-0.9, 0.9); // center of screen. (-1,0) is center left.
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	char buf[300];

	sprintf(buf, "FPS = ");
	sprintf(buf + 6, pText);
	const char * p = buf;
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p); while (*(++p));

	glEnable(GL_DEPTH_TEST); // Turn depth testing back on

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // revert back to the matrix I had before.
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// TODO: Task03
}
