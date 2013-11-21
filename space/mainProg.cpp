#include "glut.h"
#include "SOIL.h"
#include <math.h>

#define PI 3.14159265;

#define GL_CLAMP_TO_EDGE 0x812F //get rid of annoying line in textur
//source: http://www.opengl.org/registry/api/glext.hhttp://www.opengl.org/registry/api/glext.h


//Feeling naughty?
//
//#define PI 3
//

//----------------
//rotation for camera direction
float angle=0.0;
// vector representing camera direction
float lx=0.0f,ly =1.0f,lz=-1.0f;
// XYZ pos of the camera
float x=0.0f,y=1.0f,z=70.0f;
float y2 = 1.0f;
//---------------

int KeyDown[256];
GLUquadricObj *Planet;
GLfloat radius[] = {108.968, 0.383, 0.945, 1.0, 0.561, 11.209, 9.449, 4.007, 3.883, 0.180, 0.273};
GLfloat speed[9] = {4.15, 1.625, 1.0, 0.53, 0.08, 0.03, 0.01, 0.006, 0.004};
GLfloat dist[10] = {0.0, 18.6, 21.7, 24.3, 29.2, 63.4, 103.8, 193.4, 294.8, 382};
// Data aquired from: http://nineplanets.org/data1.html

GLfloat LightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };  
GLfloat LightAmbient[] = { 0.0, 0.0, 0.0, 0.0 }; 


GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
GLuint  texture[11];  
bool pause = false;
bool showGrid = false;
bool showOrbit = false;
bool orth = false;
char* imgLocation[11] = {"img/sun.jpg", "img/mercury.jpg", "img/venus.jpg", "img/earth.jpg", "img/mars.jpg", "img/jupiter.jpg", "img/saturn.jpg", "img/uranus.jpg", "img/neptune.jpg", "img/pluto.jpg", "img/moon.jpg"};
char* skyboximg[6] = {"img/11.png", "img/12.png", "img/13.png", "img/14.png", "img/15.png", "img/16.png"};
GLuint _skybox[6];

GLfloat zoom = 2.65f;


float rot[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};



int loadSkyboxImg(){
	for(int x = 0; x < 6; x++){

		_skybox[x] = SOIL_load_OGL_texture
        (
        skyboximg[x],
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
        );

	 if(texture[x] == 0)
        return false;
	}
 return true;
}
void orthog(){

	orth = true; //in orth view

    int max = 400;
	int min = -400;
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION); 

	glLoadIdentity();
	
	glOrtho(-w/zoom, w/zoom, h/zoom, -h/zoom, max ,min);

	
	glMatrixMode(GL_MODELVIEW);
	glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);	
    glTexCoord2f(1.0f, 0.0f); glVertex2f(-w/2, h/2 );
    glTexCoord2f(1.0f, 1.0f); glVertex2f(-w/2, -h/2); 
    glTexCoord2f(0.0f, 1.0f); glVertex2f(w/2, -h/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(w/2, h/2); 
    glEnd();
	
	/*left -screen width/2
		right screen width/2
		bottom screen height/2
		top -screen height/2*/

}




void drawGrid(bool draw, int rows, int columns){

	if(draw){
	 glBegin(GL_LINES);
	 glColor3f(1.0, 0.0, 0.0);
    /* Horizontal lines. */
    for (int i=0; i<=rows; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(columns, i, 0);
    }
    /* Vertical lines. */
    for (int i=0; i<=columns; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, rows, 0);
    }


	 for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(columns, i, 0);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, -rows, 0);
    }

	//----

	for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(-columns, i, 0);
    }
    /* Vertical lines. */
    for (int i=(-columns); i<=0; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, (-rows), 0);
    }


	 for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(columns, i, 0);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, -rows, 0);
    }

	//---
	for (int i=0; i<=(rows); i++) {
      glVertex3f(0, i, 0);
      glVertex3f(-columns, i, 0);
    }
    /* Vertical lines. */
    for (int i=(-columns); i<=0; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, (rows), 0);
    }


	 for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(columns, i, 0);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i, -rows, 0);
    }

	 glColor3f(0.0, 1.0, 0.0);
    /* Horizontal lines. */
    for (int i=0; i<=rows; i++) {
      glVertex3f(0, 0, i);
      glVertex3f(0, columns, i);
    }
    /* Vertical lines. */
    for (int i=0; i<=columns; i++) {
     glVertex3f(0, i, 0);
      glVertex3f(0, i, rows);
    }


	 for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, 0, i);
      glVertex3f(0, columns, i);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
    glVertex3f(0, i, 0);
      glVertex3f(0,i, -rows);
    }

	//----

	for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, 0, i);
      glVertex3f(0,-columns, i);
    }
    /* Vertical lines. */
    for (int i=(-columns); i<=0; i++) {
      glVertex3f(0, i, 0);
      glVertex3f(0,i, (-rows));
    }


	 for (int i=(-rows); i<=0; i++) {
      glVertex3f(0, 0, i);
      glVertex3f(0,columns, i);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
     glVertex3f(0, i, 0);
      glVertex3f(0,i, -rows);
    }

	//---
	for (int i=0; i<=(rows); i++) {
      glVertex3f(0, 0, i);
      glVertex3f(0,-columns, i);
    }
    /* Vertical lines. */
    for (int i=(-columns); i<=0; i++) {
     glVertex3f(0, i, 0);
      glVertex3f(0,i, (rows));
    }


	 for (int i=(-rows); i<=0; i++) {
    glVertex3f(0, 0, i);
      glVertex3f(0,columns, i);
    }
    /* Vertical lines. */
  
	for (int i=0; i<=columns; i++) {
     glVertex3f(0, i, 0);
      glVertex3f(0,i, -rows);
    }


	//finallll
	 glColor3f(0.0, 0.0, 1.0);
  
    for (int i=0; i<=rows; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i,0, rows);
    }
   
    for (int i=0; i<=columns; i++) {
glVertex3f(0, 0, i);
      glVertex3f(rows, 0, i);
    }

	//----

	for (int i=(-rows); i<=0; i++) {
     glVertex3f(i, 0, 0);
      glVertex3f(i,0, rows);
    }

	  for (int i=0; i<=columns; i++) {
glVertex3f(0, 0, i);
      glVertex3f(-rows, 0, i);
    }

	

	   for (int i=0; i<=rows; i++) {
      glVertex3f(i, 0, 0);
      glVertex3f(i,0, -rows);
    }
   

	    for (int i=(-columns); i<=0; i++) {
      glVertex3f(0, 0, i);
      glVertex3f(rows, 0, i);
    }
  
  
    //last
		for (int i=(-rows); i<=0; i++) {
     glVertex3f(i, 0, 0);
      glVertex3f(i,0, -rows);
    }

	for (int i=(-rows); i<=0; i++) {
		glVertex3f(0, 0, i);
      glVertex3f(-rows,0, i);
    }
   glColor3f(1.0, 1.0, 1.0);
  glEnd();
	}

}


int loadImg(){
 for(int x = 0; x < 11; x++){

    texture[x] = SOIL_load_OGL_texture
        (
        imgLocation[x],
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
        );

	 if(texture[x] == 0)
        return false;
	}
 return true;
}

void TextureUp(GLuint tex)                                    
{ 
 
 
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                                         
}


void createSkyBox(float x, float y, float z, float width, float height, float length)
{
	
	
	x = x - width  / 2;
    y = y - height / 2;
    z = z - length / 2;

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);		
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,	y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	y, z);    
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);	
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	y, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);		
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	y, z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);		
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height,	z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,	y + height,	z);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);		
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,	y + height,	z);	
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x,	y + height,	z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	y, z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);		
        
    glEnd();

    glBindTexture(GL_TEXTURE_2D, _skybox[0]);
    glBegin(GL_QUADS);	
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height,	z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height,	z);
    glEnd();

	 

	}


void createPlanets(float distance, GLfloat P_radius, float speed){

	glPushMatrix();
	//planet rotation round sun
	glRotatef(speed, 0.0, 1.0, 0.0);

	//distance from centre
	glTranslatef(distance,0.0,0.0);

	//makes planet rightway up
	glRotatef(90.0,-1.0,0.0,0.0);

	//create planet
	gluSphere(Planet, P_radius, 32, 32);

	//rotation of planet
	glRotatef(speed, 0.0, 0.0, 1.0);
	glPopMatrix();

}


void genOrbit(GLfloat x, GLfloat z, GLfloat radius){
	int triangles = 100; //triangles used to draw circle
	
	GLfloat twoPi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i <= triangles; i++) { 
			glVertex3f(
			   x + (radius* sin(i * twoPi / triangles)), 0.0,
			    z + (radius * cos(i *  twoPi / triangles))
			);
		}
	glEnd();
}

void drawOrbit(){
	if(showOrbit){
	
	 for(int i = 0; i < 9; i++){ 

     if(i == 3){ //earth
		 glColor3f(0.0, 1.0, 0.0);
	 }else{
		  glColor3f(1.0, 0.0, 0.0);
	 }

	 genOrbit(0.0,0.0,dist[i]);
	 }

	 glColor3f(1.0, 1.0, 1.0);
	}
}

void drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if(orth){
		int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	   glBindTexture(GL_TEXTURE_2D, _skybox[0]);
glBegin(GL_QUADS);	
glTexCoord2f(1.0f, 0.0f); glVertex2f(-w/2, h/2 );
glTexCoord2f(1.0f, 1.0f); glVertex2f(w/2, h/2); 
glTexCoord2f(0.0f, 1.0f); glVertex2f(w/2, -h/2);
glTexCoord2f(0.0f, 0.0f); glVertex2f(-w/2, -h/2); 
glEnd();
		glRotated(90,1,0,0);
	
	}else{
	gluLookAt(	x, y, z,
			x+lx, y2,  z+lz,
			0.0f, 1.0f,  0.0f); //y2 =1.0


	 glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);

	 glDisable(GL_DEPTH_TEST);
	createSkyBox(x,y,z,100,100,100);
	
	glEnable(GL_DEPTH_TEST);
	//dont change
	glTranslatef(0.0,0.0,-100.0); //60.0
	}
	

	//Sun
	GLfloat SunCol[] = { 0.8, 0.6, 0.0, 0.0};
	 
	TextureUp(texture[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, SunCol);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
	
	createPlanets(dist[0], radius[0]/9, 0); //scale sun down by 1/9!
	GLfloat SunColNull[] = { 0.0, 0.0, 0.0, 0.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, SunColNull);
	//Mercury
	TextureUp(texture[1]);
	createPlanets(dist[1], radius[1], rot[0]);

	//Venus
	TextureUp(texture[2]);
	createPlanets(dist[2], radius[2], rot[1]);
	
	//Earth0
	TextureUp(texture[3]);
	createPlanets(dist[3], radius[3], rot[2]);
	
	//Mars
	TextureUp(texture[4]);
	createPlanets(dist[4], radius[4], rot[3]);

	//Jupitar
	TextureUp(texture[5]);
	createPlanets(dist[5], radius[5], rot[4]);

	//Saturn
	TextureUp(texture[6]);
	createPlanets(dist[6], radius[6], rot[5]);

	//Uranus
	TextureUp(texture[7]);
	createPlanets(dist[7], radius[7], rot[6]);

	//Neptune
	TextureUp(texture[8]);
	createPlanets(dist[8], radius[8], rot[7]);

	//Pluto
	TextureUp(texture[9]);
	createPlanets(dist[9], radius[9], rot[8]);

	//added from speshKey make the cam move yo!

float fraction = 0.01f;
		if(!orth){
			if(KeyDown[GLUT_KEY_LEFT] == 1){
			x -= 0.05;
			
					
			}else if(KeyDown[GLUT_KEY_RIGHT] == 1){
            x += 0.05;
				
			}else if(KeyDown[GLUT_KEY_UP] == 1){
		
			y2 += 0.02;
			y += 0.02;
			
			}else if(KeyDown[GLUT_KEY_DOWN] == 1){
			y2 -= 0.02;
			y -= 0.02;
			
			}else if(KeyDown[GLUT_KEY_PAGE_DOWN]){
			y += 0.001;
			
			}else if(KeyDown[GLUT_KEY_PAGE_UP]){
			y -= 0.001;
			}
			else if(KeyDown[GLUT_KEY_HOME]){
				z -= 0.1;
			}else if(KeyDown[GLUT_KEY_END]){
				z += 0.1;
			}
		}

		drawGrid(showGrid, 30, 30);
		drawOrbit();


        glutSwapBuffers();
		if(pause == false){
		

         for(int i = 9; i >= 0; i--){

			 rot[i] += speed[i]; //rotate round the sun

		 }




		
		}

		//GLfloat emit2[] = {0.0f, 0.0f, 0.0f, 0.0f}; 
		//glMaterialfv(GL_FRONT, GL_EMISSION, emit2);
	
		glutPostRedisplay();
}





void changeSize(int w, int h) {

	if (w == 0 || h == 0) return;   

	float ratio =  w * 1.0 / h;

	
	glMatrixMode(GL_PROJECTION);

	// Reset Le Matrix
	glLoadIdentity();

		// Set perspective
	gluPerspective(45,ratio,1,1000);
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	


	
}


void speshKey(int key, int x, int y){
	
	KeyDown[key] = 1;
	
}



void keyPress (unsigned char key, int x, int y) {
   
	switch(key){
		
		case 'l':
	  
       glEnable(GL_LIGHTING); 
       glutPostRedisplay();
        break;

		case 'p':
			if(pause){
				pause = false;
				glutPostRedisplay();
			}else{
				pause = true;
				glutPostRedisplay();
			}
			
			break;

     case 'k':
       glDisable(GL_LIGHTING);  
       glutPostRedisplay();
        break;

	 case 'g':
		 if(showGrid){
			 showGrid = false;}
		 else{
		 showGrid = true;
		 }
		 break;

		  case 'o':
		 if(showOrbit){
			 showOrbit = false;}
		 else{
		 showOrbit = true;
		 }
		 break;

	case 'q':
	case 27: //escape
    glutLeaveGameMode(); 
    exit(1337); //All your 1337 are belong to us
	break;

	case 'n':
		if(orth){
		orth = false;
		drawScene();
		changeSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
		}else{
		orth = true;
		showOrbit = true;
		orthog();
		}
		break;
	
	}
}



void initRender(){

	glClearDepth(1.0);
	
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_DIFFUSE , LightDiffuse); 
	glLightfv(GL_LIGHT0,GL_AMBIENT , LightAmbient);
    

	Planet = gluNewQuadric();
	gluQuadricDrawStyle(Planet, GLU_FILL);
    gluQuadricTexture(Planet, GL_TRUE);
	gluQuadricNormals(Planet, GLU_SMOOTH);

	
}

void keyUp(int key, int x, int y)
{
    KeyDown[key] = 0;
}



void main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutGameModeString( "1600x900:32@60");
	glutEnterGameMode();
	 
	
	initRender();
	glutIgnoreKeyRepeat(true);
	loadSkyboxImg();
	loadImg();
	
	glutDisplayFunc(drawScene);
	glutReshapeFunc(changeSize);

	
	glutKeyboardFunc(keyPress); 
	glutSpecialUpFunc(keyUp);
	glutSpecialFunc(speshKey);
	
	// enter GLUT event processing cycle
	glutMainLoop();
}

