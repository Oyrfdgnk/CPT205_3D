#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector"
#include <corecrt_math_defines.h>
#include <cmath>
#define GL_MULTISAMPLE 32925

using namespace std;
static GLubyte* pixeldata;
vector<GLubyte*>p;
GLuint texture[20];

static GLint imagewidth0, imageheight0, pixellength0;
static GLint imagewidth1, imageheight1, pixellength1;
static GLint imagewidth2, imageheight2, pixellength2;
static GLint imagewidth3, imageheight3, pixellength3;
static GLint imagewidth4, imageheight4, pixellength4;
static GLint imagewidth5, imageheight5, pixellength5;
static GLint imagewidth6, imageheight6, pixellength6;
static GLint imagewidth7, imageheight7, pixellength7;
static GLint imagewidth8, imageheight8, pixellength8;
static GLint imagewidth9, imageheight9, pixellength9;
static GLint imagewidth10, imageheight10, pixellength10;
static GLint imagewidth11, imageheight11, pixellength11;
static GLint imagewidth12, imageheight12, pixellength12;
static GLint imagewidth13, imageheight13, pixellength13;
static GLint imagewidth14, imageheight14, pixellength14;
static GLint imagewidth15, imageheight15, pixellength15;
static GLint imagewidth16, imageheight16, pixellength16;
const int cloudNum = 10;
const int snowNum = 250;

int w = 1000, h = 600;
int scale = 1;
int i = 0;
int flag = 0;
int winter = 1;
int mainMenu;

float X0 = 0.0, Y0 = 0.0, Z0 = -1000.0;
float XRef = 0.0, YRef = 0.0, ZRef = 3000.0;
float XUp = 0.0, YUp = 1.0, ZUp = 0.0;
float angle = 0.0f;
float angle2 = 0.0f;
float moveSpeed = 30.0f;


struct cloudPos {
    float x;
    float y;
    float z;
};
struct snowPos {
    float x;
    float y;
    float z;
};
cloudPos cloudpos[cloudNum];
snowPos snowpos[snowNum];


// ========Initialization========
void when_in_mainloop()
{
    if (scale == 0)
        scale = 1;
    glViewport(0, 0, w / scale, h / scale);
    glutPostRedisplay(); // force OpenGL to redraw the current window
}
void ReadFig(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
    GLubyte* pixeldata;
    FILE* pfile;
    fopen_s(&pfile, path, "rb");
    if (pfile == 0) exit(0);
    fseek(pfile, 0x0012, SEEK_SET);
    fread(&imagewidth, sizeof(imagewidth), 1, pfile);
    fread(&imageheight, sizeof(imageheight), 1, pfile);
    pixellength = imagewidth * 3;
    while (pixellength % 4 != 0)pixellength++;
    pixellength *= imageheight;
    pixeldata = (GLubyte*)malloc(pixellength);
    if (pixeldata == 0) exit(0);
    fseek(pfile, 54, SEEK_SET);
    fread(pixeldata, pixellength, 1, pfile);
    p.push_back(pixeldata);
    fclose(pfile);
}
void reshapeWindow(GLint w, GLint h) {
    glViewport(0, 0, w, h);
}
void myTexture(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		// set texture environment parameters
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Choose the most correct or highest quality option
    glGenTextures(20, &texture[0]);

    //Bind the picture
    ReadFig("fig/lake.bmp", imagewidth0, imageheight0, pixellength0);
    ReadFig("fig/wall1.bmp", imagewidth1, imageheight1, pixellength1);
    ReadFig("fig/wall2.bmp", imagewidth2, imageheight2, pixellength2);
    ReadFig("fig/wall3.bmp", imagewidth3, imageheight3, pixellength3);
    ReadFig("fig/wall4.bmp", imagewidth4, imageheight4, pixellength4);
    ReadFig("fig/wall5.bmp", imagewidth5, imageheight5, pixellength5);
    ReadFig("fig/stone_1.bmp", imagewidth6, imageheight6, pixellength6);
    ReadFig("fig/sand.bmp", imagewidth7, imageheight7, pixellength7);
    ReadFig("fig/wood_1.bmp", imagewidth8, imageheight8, pixellength8);
    ReadFig("fig/wood_2.bmp", imagewidth9, imageheight9, pixellength9);
    ReadFig("fig/grass.bmp", imagewidth10, imageheight10, pixellength10);
    ReadFig("fig/stone_2.bmp", imagewidth11, imageheight11, pixellength11);
    ReadFig("fig/stone_3.bmp", imagewidth12, imageheight12, pixellength12);
    ReadFig("fig/door1.bmp", imagewidth13, imageheight13, pixellength13);
    ReadFig("fig/snow.bmp", imagewidth14, imageheight14, pixellength14);
    ReadFig("fig/wall6.bmp", imagewidth15, imageheight15, pixellength15);
    ReadFig("fig/glass.bmp", imagewidth16, imageheight16, pixellength16);

    // Water
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Wall 
    for (int i = 1; i <= 5; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[i]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    // Stone_1
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[6]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Sand
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[7]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Wood
    for (int i = 8; i <= 9; i++) {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[i]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    // Grass
    glBindTexture(GL_TEXTURE_2D, texture[10]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[10]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Stone_2
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[11]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Stone_3
    glBindTexture(GL_TEXTURE_2D, texture[12]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[12]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    // Door
    glBindTexture(GL_TEXTURE_2D, texture[13]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 458, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[13]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Snow
    glBindTexture(GL_TEXTURE_2D, texture[14]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[14]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Ice
    glBindTexture(GL_TEXTURE_2D, texture[15]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[15]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Glass
    glBindTexture(GL_TEXTURE_2D, texture[16]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, p[16]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


}
void myLight() {

    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // ========Environment Light========
    GLfloat Light_morning[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat Light_afternoon[] = { 0.4, 0.3, 0.4, 1.0 };
    GLfloat Light_night[] = { 0.3, 0.3, 0.4, 1.0 };
    if (flag % 3 == 0) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_morning);
    else if (flag % 3 == 1) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_afternoon);
    else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_night);


    // ========SPOT Light========
    GLfloat light_position0[] = { -2999.0, 2999.0 / 2, 2999.0, 1.0 };
    GLfloat light_direction0[] = { 1.0, -1.0, -1.0, 0.0 };
    GLfloat light_ambient0[] = { 1.0, 1.0, 0.1, 1.0 };
    GLfloat light_diffuse0[] = { 1.0, 1.0, 0.4, 1.0 };
    GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position1[] = { 2999.0, 2999.0 / 2, 2999.0, 1.0 };
    GLfloat light_direction1[] = { -1.0, -1.0, 1.0, 0.0 };
    GLfloat light_ambient1[] = { 0.9, 0.5, 0.4, 1.0 };
    GLfloat light_diffuse1[] = { 0.9, 0.2, 0.2, 1.0 };
    GLfloat light_specular1[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 30);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.7);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);

    // ========Parallel light=======
    GLfloat light_ambient2[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse2[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_specular2[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_direction2[] = { 1.0, -1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_direction2);

    if (flag % 3 == 0) {
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
    }
    else if (flag % 3 == 1) {
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
}

// ========Interaction========
void Keyboard(unsigned char key, int x, int y) {
    // Move forward
    if ((key == 'w' || key == 'W')) {
        X0 += 20.0f * sin(angle * M_PI / 180.0f);
        Z0 += 20.0f * cos(angle * M_PI / 180.0f);
        XRef += 20.0f * sin(angle * M_PI / 180.0f);
        ZRef += 20.0f * cos(angle * M_PI / 180.0f);
    }
    // Move backward
    else if ((key == 's' || key == 'S')) {
        X0 -= 20.0f * sin(angle * M_PI / 180.0f);
        Z0 -= 20.0f * cos(angle * M_PI / 180.0f);
        XRef -= 20.0f * sin(angle * M_PI / 180.0f);
        ZRef -= 20.0f * cos(angle * M_PI / 180.0f);
    }
    // Move left
    else if ((key == 'a' || key == 'A')) {
        X0 += 20.0f * cos(angle * M_PI / 180.0f);
        Z0 -= 20.0f * sin(angle * M_PI / 180.0f);
        XRef += 20.0f * cos(angle * M_PI / 180.0f);
        ZRef -= 20.0f * sin(angle * M_PI / 180.0f);
    }
    // Move right
    else if ((key == 'd' || key == 'D')) {
        X0 -= 20.0f * cos(angle * M_PI / 180.0f);
        Z0 += 20.0f * sin(angle * M_PI / 180.0f);
        XRef -= 20.0f * cos(angle * M_PI / 180.0f);
        ZRef += 20.0f * sin(angle * M_PI / 180.0f);
    }
    // Head turn left
    else if (key == 'j' || key == 'J') {
        angle += 10.0f;
    }
    // Head turn right
    else if (key == 'l' || key == 'L') {
        angle -= 10.0f;
    }
    // Head turn up
    else if (key == 'i' || key == 'I') {
        if (angle2 < 80.0f) {
            angle2 += 10.0f;
        }
    }
    // Head turn down
    else if (key == 'k' || key == 'K') {
        if (angle2 > -80.0f) {
            angle2 -= 10.0f;
        }
    }
    // Change color
    if ((key == 'c' || key == 'C')) {
        flag = (flag + 1) % 3;
        myLight();
    }

    XRef = 4000 * sin(angle * M_PI / 180) + X0;
    YRef = 4000 * tan(angle2 * M_PI / 180) + Y0;
    ZRef = 4000 * cos(angle * M_PI / 180) + Z0;
    glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y) {
    // Change season
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        winter = (winter + 1) % 2;
    }
    // Move up
    if (state == GLUT_UP && button == 3 && (Y0 + 30 <= 2500) && (YRef + 30 <= 2500)) {
        Y0 += 20; YRef += 20.0f;
    }
    // Move down
    if (state == GLUT_DOWN && button == 4 && (Y0 - 30 >= -200) && (YRef - 30 >= -200)) {
        Y0 -= 20; YRef -= 20.0f;
    }
}
void menuCallback(int value) {
    switch (value) {
    case 'w':
    case 'W':
        X0 += 20.0f * sin(angle * M_PI / 180.0f);
        Z0 += 20.0f * cos(angle * M_PI / 180.0f);
        XRef += 20.0f * sin(angle * M_PI / 180.0f);
        ZRef += 20.0f * cos(angle * M_PI / 180.0f);
        break;
    case 's':
    case 'S':
        X0 -= 20.0f * sin(angle * M_PI / 180.0f);
        Z0 -= 20.0f * cos(angle * M_PI / 180.0f);
        XRef -= 20.0f * sin(angle * M_PI / 180.0f);
        ZRef -= 20.0f * cos(angle * M_PI / 180.0f);
        break;
    case 'a':
    case 'A':
        X0 += 20.0f * cos(angle * M_PI / 180.0f);
        Z0 -= 20.0f * sin(angle * M_PI / 180.0f);
        XRef += 20.0f * cos(angle * M_PI / 180.0f);
        ZRef -= 20.0f * sin(angle * M_PI / 180.0f);
        break;
    case 'd':
    case 'D':
        X0 -= 20.0f * cos(angle * M_PI / 180.0f);
        Z0 += 20.0f * sin(angle * M_PI / 180.0f);
        XRef -= 20.0f * cos(angle * M_PI / 180.0f);
        ZRef += 20.0f * sin(angle * M_PI / 180.0f);
        break;
    case 'j':
    case 'J':
        angle += 10.0f;
        break;
    case 'l':
    case 'L':
        angle -= 10.0f;
        break;
    case 'i':
    case 'I':
        if (angle2 < 90.0f) {
            angle2 += 10.0f;
        }
        break;
    case 'k':
    case 'K':
        if (angle2 > -90.0f) {
            angle2 -= 10.0f;
        }
        break;
    case 'c':
    case 'C':
        flag = (flag + 1) % 3;
        myLight();
        break;
    case 3: // Mouse Wheel Up
        if (Y0 + 30 <= 2500 && YRef + 30 <= 2500) {
            Y0 += 20;
            YRef += 20.0f;
        }
        break;
    case 4: // Mouse Wheel Down
        if (Y0 - 30 >= -200 && YRef - 30 >= -200) {
            Y0 -= 20;
            YRef -= 20.0f;
        }
        break;
    case GLUT_LEFT_BUTTON:
        winter = (winter + 1) % 2;  // Toggle Winter
        break;
    default:
        break;
    }
    XRef = 4000 * sin(angle * M_PI / 180) + X0;
    YRef = 4000 * tan(angle2 * M_PI / 180) + Y0;
    ZRef = 4000 * cos(angle * M_PI / 180) + Z0;
    glutPostRedisplay();
}
void Menu() {
    mainMenu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Turn Head Left (J/j)", 'j');
    glutAddMenuEntry("Turn Head Right (L/l)", 'l');
    glutAddMenuEntry("Turn Head Up (I/i)", 'i');
    glutAddMenuEntry("Turn Head Down (K/k)", 'k');
    glutAddMenuEntry("Move Forward (W/w)", 'w');
    glutAddMenuEntry("Move Backward (S/s)", 's');
    glutAddMenuEntry("Move Left (A/a)", 'a');
    glutAddMenuEntry("Move Right (D/d)", 'd');
    glutAddMenuEntry("Change Color (C/c)", 'c');
    glutAddMenuEntry("Move Up (Mouse Wheel Up)", 3);  // 3 represents Mouse Wheel Up
    glutAddMenuEntry("Move Down (Mouse Wheel Down)", 4);  // 4 represents Mouse Wheel Down
    glutAddMenuEntry("Toggle Winter (Left Click)", GLUT_LEFT_BUTTON);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// ========Animation=======
void makeSnowPos() {
    for (int i = 0; i < snowNum; i++) {
        snowpos[i].x = float(-3500 + rand() % 7001);
        snowpos[i].y = 3500 + float(rand() % 500);
        snowpos[i].z = float(-3500 + rand() % 7001);
    }
}
void makeCloudPos() {
    for (int i = 0; i < cloudNum; i++) {
        cloudpos[i].x = float(3500 + rand() % 1000);
        cloudpos[i].y = 2000 + float(rand() % 500);
        cloudpos[i].z = float(-3500 + rand() % 7000);
    }
}

// ========Cylinder=======
void drawCylinder(float ru, float rd, float height, int i, float x, float y, float z) {
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    GLUquadricObj* objCylinder = gluNewQuadric();
    gluQuadricTexture(objCylinder, GL_TRUE);	// bind texture

    glPushMatrix();
    glTranslatef(x, y + height, z);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(objCylinder, ru, rd, height, 100, 300);
    glPopMatrix();
}
void drawCylinder2(float ru, float rd, float height, int i) {
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    GLUquadricObj* objCylinder = gluNewQuadric();
    gluQuadricTexture(objCylinder, GL_TRUE);	// bind texture

    glPushMatrix();
    glTranslatef(0, height, 0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluCylinder(objCylinder, ru, rd, height, 100, 300);
    glPopMatrix();
}
// ========Cube=======
void drawCube(float x, float y, float z, int t, float j, float k, float l) {

    glPushMatrix();
    glTranslatef(j, k, l);
    glScalef(x, y, z);
    glBindTexture(GL_TEXTURE_2D, texture[t]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0), glVertex3f(1.0, 0.0, -1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(1.0, 0.0, 1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-1.0, 0.0, 1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-1.0, 0.0, -1.0);

    glTexCoord2f(0.0, 0.0), glVertex3f(-1.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-1.0, 0.0, -1.0);

    glTexCoord2f(0.0, 0.0), glVertex3f(1.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-1.0, 0.0, 1.0);

    glTexCoord2f(0.0, 0.0), glVertex3f(1.0, 0.0, -1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(1.0, 0.0, 1.0);

    glTexCoord2f(0.0, 0.0), glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-1.0, 1.0, -1.0);

    glTexCoord2f(0.0, 0.0), glVertex3f(1.0, 0.0, -1.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-1.0, 0.0, -1.0);
    glEnd();
    glPopMatrix();

    glEnable(GL_LIGHTING);
}
// ========Ball=======
void drawBall(float r) {

    GLfloat bright_emission[] = { 0.0, 1.0, 0.0 }; // Adjusted for a light emission
    GLfloat no_emission[] = { 0.0, 0.0, 0.0 }; // Adjusted for a no emission
    glMaterialfv(GL_FRONT, GL_EMISSION, bright_emission); // Set emission for the light source
    glPushAttrib(GL_TEXTURE_BIT);
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glPushMatrix();
    GLUquadric* quadricObj = gluNewQuadric();
    gluQuadricTexture(quadricObj, GL_TRUE);
    gluSphere(quadricObj, r, 80, 80);
    gluDeleteQuadric(quadricObj);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission); // Set emission for the light source

    glPopMatrix();
    glPopAttrib();
    glLoadIdentity();
    glFlush();


}
// ========Island========
void drawIsland() {
    glColor4f(1.0, 1.0, 1.0, 1.0);
    drawCube(3000.0, 299.0, 1500, 6, 0, -500, -1500);
    //上
    if (winter % 2 == 0) {
        glBindTexture(GL_TEXTURE_2D, texture[10]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texture[14]);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0), glVertex3f(3000, -200.0, -3000.0);
    glTexCoord2f(0.0, 10.0), glVertex3f(3000, -200.0, 0);
    glTexCoord2f(10.0, 10.0), glVertex3f(-3000, -200.0, 0.0);
    glTexCoord2f(10.0, 0.0), glVertex3f(-3000, -200.0, -3000.0);
    glEnd();
}
// ========Water========
void drawWater()
{
    GLfloat diffuse_water[] = { 80.0 / 255.0, 120.0 / 255.0, 150.0 / 255.0 };
    GLfloat specular_water[] = { 80.0 / 255.0, 120.0 / 255.0, 150.0 / 255.0 };
    GLfloat shiness_water = 0.02;
    glMaterialfv(GL_FRONT, GL_SHININESS, &shiness_water);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_water);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_water);
    if (winter % 2 == 1)     glBindTexture(GL_TEXTURE_2D, texture[16]);
    else glBindTexture(GL_TEXTURE_2D, texture[0]);

    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 0.6);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(3000.0, -350, 0.0);
    glTexCoord2f(0.0, 50.0); glVertex3f(3000.0, -350, 3000.0);
    glTexCoord2f(50.0, 50.0); glVertex3f(-3000.0, -350, 3000.0);
    glTexCoord2f(50.0, 0.0); glVertex3f(-3000.0, -350, 0.0);
    glEnd();
    glPopMatrix();
}
// ========Sand=======
void drawSand() {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0), glVertex3f(3000.0, -300.0, 0.0);
    glTexCoord2f(0.0, 0.5), glVertex3f(3000.0, -499.0, 1000.0);
    glTexCoord2f(1.0, 0.5), glVertex3f(-3000.0, -499.0, 1000.0);
    glTexCoord2f(1.0, 0.0), glVertex3f(-3000.0, -300.0, 0.0);

    glTexCoord2f(0.0, 0.5), glVertex3f(3000.0, -499.0, 1000.0);
    glTexCoord2f(0.0, 1.0), glVertex3f(3000.0, -499.0, 3000.0);
    glTexCoord2f(1.0, 1.0), glVertex3f(-3000.0, -499.0, 3000.0);
    glTexCoord2f(1.0, 0.5), glVertex3f(-3000.0, -499.0, 1000.0);

    glEnd();
    glPopMatrix();

}
// ========Wall========
void drawWall() {

    GLfloat ratio = 40.0 / 512.0;
    glPushMatrix();
    glColor3f(1, 1, 1);

    if (winter % 2 == 0) glBindTexture(GL_TEXTURE_2D, texture[3]);
    else glBindTexture(GL_TEXTURE_2D, texture[1]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, ratio); glVertex3f(3000.0, -500, -3000.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(3000.0, 3000.0, -3000.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(3000.0, 3000.0, 3000.0);
    glTexCoord2f(1.0, ratio); glVertex3f(3000.0, -500.0, 3000.0);
    glEnd();


    if (winter % 2 == 0) glBindTexture(GL_TEXTURE_2D, texture[4]);
    else glBindTexture(GL_TEXTURE_2D, texture[2]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, ratio); glVertex3f(3000.0, -500, 3000.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(3000.0, 3000.0, 3000.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-3000.0, 3000.0, 3000.0);
    glTexCoord2f(1.0, ratio); glVertex3f(-3000.0, -500, 3000.0);
    glEnd();

    if (winter % 2 == 0) glBindTexture(GL_TEXTURE_2D, texture[4]);
    else glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, ratio); glVertex3f(-3000.0, -500, 3000.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-3000.0, 3000.0, 3000.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-3000.0, 3000.0, -3000.0);
    glTexCoord2f(0.0, ratio); glVertex3f(-3000.0, -500.0, -3000.0);
    glEnd();


    if (winter % 2 == 0) glBindTexture(GL_TEXTURE_2D, texture[3]);
    else glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, ratio); glVertex3f(-3000.0, -500, -3000.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-3000.0, 3000.0, -3000.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(3000.0, 3000.0, -3000.0);
    glTexCoord2f(0.0, ratio); glVertex3f(3000.0, -500, -3000.0);
    glEnd();

    if (winter % 2 == 0) glBindTexture(GL_TEXTURE_2D, texture[15]);
    else glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);  glVertex3f(3000.0, 3000.0, 3000.0);
    glTexCoord2f(1.0, 0.0);  glVertex3f(-3000.0, 3000.0, 3000.0);
    glTexCoord2f(1.0, 1.0);  glVertex3f(-3000.0, 3000.0, -3000.0);
    glTexCoord2f(0.0, 1.0);  glVertex3f(3000.0, 3000.0, -3000.0);
    glEnd();
    glPopMatrix();

}
// ========Cloud========
void drawCloud() {
    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < cloudNum; i++) {
        glPushMatrix();
        glTranslatef(cloudpos[i].x, cloudpos[i].y, cloudpos[i].z);
        for (int i = 0; i < 10; i++) {
            glPushMatrix();
            glTranslatef(-i * 60, 0.0, 0.0 + i % 2 * (60 * sqrt(3.0)));
            glColor4f(0.8, 1.0, 1.0, 0.5);
            glutSolidSphere(60, 80, 80);
            glPopMatrix();
        }
        for (int i = 0; i < 7; i++) {
            glPushMatrix();
            glTranslatef(-60 - i * 60, 60, 10.0 + i % 2 * (20 * sqrt(3.0)));
            glColor4f(0.8, 1.0, 1.0, 0.5);
            glutSolidSphere(60, 80, 80);
            glPopMatrix();
        }
        glPopMatrix();
    }
    glEnable(GL_TEXTURE_2D);

}
// ========Barrier========
void drawBarrier(float x, float y, float z) {
    glPushMatrix();
    drawCube(5.0, 60.0, 5.0, 6, x, y, z);
    glPushMatrix();
    glTranslatef(x, y + 65.0, z);
    drawBall(5.0);
    glPopMatrix();

    drawCube(5.0, 6.0, 5.0, 6, x, y + 70.0, z);
    glPopMatrix();
}
void drawBarriers() {
    for (int i = 0; i < 2; i++) {
        drawBarrier(1240, -200.0, 380 + i * 400);
    }
    for (int i = 0; i < 1; i++)
    {
        drawBarrier(1060, -200.0, 380 + i * 400);
    }
    for (int i = 0; i < 2; i++)
    {
        drawBarrier(-1240, -200.0, 380 + i * 400);
    }
    for (int i = 0; i < 1; i++)
    {
        drawBarrier(-1060, -200.0, 380 + i * 400);
    }
    for (int i = 0; i < 2; i++)
    {
        drawBarrier(-670 + i * 400, -200.0, 620);
    }
    for (int i = 0; i < 2; i++)
    {
        drawBarrier(670 - i * 400, -200.0, 620);
    }
    for (int i = 0; i < 2; i++)
    {
        drawBarrier(670 - i * 400, -200.0, 380 + 2 * 200);
    }
    for (int i = 0; i < 2; i++)
    {
        drawBarrier(-670 + i * 400, -200.0, 380 + 2 * 200);
    }


    drawBarrier(1060, -200.0, 620);
    drawBarrier(-1060, -200.0, 620);

    drawBarrier(1060, -200.0, 10);
    drawBarrier(1240, -200.0, 10);
    drawBarrier(-1060, -200.0, 10);
    drawBarrier(-1240, -200.0, 10);

    glPushMatrix();
    glTranslatef(1060, -150.0, 620);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 1060 * 2, 8);
    glPopMatrix();
    drawCube(1060, 30.0, 4.0, 8, 0.0, -200.0, 620);

    glPushMatrix();
    glTranslatef(1240, -150.0, 780);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 1240 * 2, 8);
    glPopMatrix();
    drawCube(1240, 30.0, 4.0, 8, 0.0, -200.0, 780);

    glPushMatrix();
    glTranslatef(1060, -150.0, 620);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 610, 8);
    glPopMatrix();
    drawCube(4.0, 30.0, 300, 8, 1060, -200.0, 315);

    glPushMatrix();
    glTranslatef(-1060, -150.0, 620);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 610, 8);
    glPopMatrix();
    drawCube(4.0, 30.0, 300, 8, -1060, -200.0, 315);

    glPushMatrix();
    glTranslatef(-1240, -150.0, 375);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 370, 8);
    glPopMatrix();
    drawCube(4.0, 30.0, 185, 8, -1240, -200.0, 191);

    glPushMatrix();
    glTranslatef(1240, -150.0, 375);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    drawCylinder2(4.0, 4.0, 370, 8);
    glPopMatrix();
    drawCube(4.0, 30.0, 185, 8, 1240, -200.0, 191);



}
// ========Stair=======
void drawStairs() {
    for (int i = 0; i < 5; i++)
    {
        drawCube(15.0, 300.0 - 30 * i, 210.0, 8, 1265 + 30 * i, -500.0, 370 + 210);
    }
    for (int i = 0; i < 5; i++)
    {
        drawCube(15.0, 300.0 - 30 * i, 210.0, 8, -1265 - 30 * i, -500.0, 370 + 210);
    }
    drawCube(100.0, 1, 210.0, 8, -1500, -349, 370 + 210);
    drawBarrier(1410, -349, 380);
    drawBarrier(1410, -349, 780);
    drawBarrier(1590, -349, 380);
    drawBarrier(1590, -349, 780);

    drawCube(100.0, 1, 210.0, 8, 1500, -349, 370 + 210);
    drawBarrier(-1410, -349, 380);
    drawBarrier(-1410, -349, 780);
    drawBarrier(-1590, -349, 380);
    drawBarrier(-1590, -349, 780);


}
// ========Platform=======
void drawPlatform() {
    float lenghthZ = 300.0;
    float widthX = 100.0;
    float heightY = 50.0;
    glPushMatrix();
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    drawCube(widthX, heightY, lenghthZ, 9, -1150, -250, lenghthZ);
    drawCube(widthX, heightY, lenghthZ, 9, 1150, -250, lenghthZ);
    drawCube(1250, heightY, 100, 9, 0.0, -250, 600 + 100);
    glPopMatrix();
    for (int i = 0; i < 2; i++) {
        drawCylinder(10, 10, 250, 9, 1230, -450, 370 + i * 400);
    }
    for (int i = 0; i < 1; i++)
    {
        drawCylinder(10, 10, 250, 9, 1070, -450, 370 + i * 400);
    }
    for (int i = 0; i < 2; i++)
    {
        drawCylinder(10, 10, 250, 9, -1230, -450, 370 + i * 400);
    }
    for (int i = 0; i < 1; i++)
    {
        drawCylinder(10, 10, 250, 9, -1070, -450, 370 + i * 400);
    }
    for (int i = 0; i < 2; i++)
    {
        drawCylinder(10, 10, 250, 9, -670 + i * 400, -450, 630);
    }
    for (int i = 0; i < 2; i++)
    {
        drawCylinder(10, 10, 250, 9, 670 - i * 400, -450, 630);
    }
    for (int i = 0; i < 2; i++)
    {
        drawCylinder(10, 10, 250, 9, 670 - i * 400, -450, 370 + 2 * 200);
    }
    for (int i = 0; i < 2; i++)
    {
        drawCylinder(10, 10, 250, 9, -670 + i * 400, -450, 370 + 2 * 200);
    }
    glPopMatrix();
}
// ========Boat========
void drawBoat(float x, float y, float z) {

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(3, 3, 4.5);
    for (int i = 0; i < 2; i++) {

        glBindTexture(GL_TEXTURE_2D, texture[9]);
        glPushMatrix();
        glTranslatef(0, i * 2 * sqrt(3), 0);
        glScalef(1 - i * 0.2, 1 - i * 0.2, 1 - i * 0.2);

        glBindTexture(GL_TEXTURE_2D, texture[8]);
        glBegin(GL_POLYGON);
        glTexCoord2f(0.5, 1.0); glVertex3f(0.0, 0.0, 20 + 5 * sqrt(3));
        glTexCoord2f(0.0, 0.8); glVertex3f(-20.0, 0.0, 20);
        glTexCoord2f(0.0, 0.2); glVertex3f(-20.0, 0.0, -20);
        glTexCoord2f(0.5, 0.0); glVertex3f(0.0, 0.0, -20 - 5 * sqrt(3));
        glTexCoord2f(1.0, 0.2); glVertex3f(20.0, 0.0, -20);
        glTexCoord2f(1.0, 0.8); glVertex3f(20.0, 0.0, 20);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texture[9]);


        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, 20);
        glTexCoord2f(0.0, 1.0); glVertex3f(-20.0, 0.0, -20);
        glTexCoord2f(1.0, 1.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), -20);
        glTexCoord2f(1.0, 0.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), 20);

        glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 0.0, 20);
        glTexCoord2f(0.0, 1.0); glVertex3f(20.0, 0.0, -20);
        glTexCoord2f(1.0, 1.0); glVertex3f(20.0 + 10, 10 * sqrt(3), -20);
        glTexCoord2f(1.0, 0.0); glVertex3f(20.0 + 10, 10 * sqrt(3), 20);

        glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, 20);
        glTexCoord2f(0.0, 1.0);  glVertex3f(-20.0 - 10, 10 * sqrt(3), 20);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3) + 10);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, 20 + 5 * sqrt(3));

        glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 0.0, 20);
        glTexCoord2f(0.0, 1.0); glVertex3f(20.0 + 10, 10 * sqrt(3), 20);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3) + 10);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, 20 + 5 * sqrt(3));

        glTexCoord2f(0.0, 0.0); glVertex3f(-20.0, 0.0, -20);
        glTexCoord2f(0.0, 1.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), -20);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3) - 10);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, -20 - 5 * sqrt(3));

        glTexCoord2f(0.0, 0.0); glVertex3f(20.0, 0.0, -20);
        glTexCoord2f(0.0, 1.0); glVertex3f(20.0 + 10, 10 * sqrt(3), -20);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3) - 10);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, -20 - 5 * sqrt(3));
        glEnd();
        glPopMatrix();

    }

    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(20.0 + 10, 10 * sqrt(3), 20);
    glTexCoord2f(0.0, 1.0); glVertex3f(20.0 + 10, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 1.0); glVertex3f(20.0, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 0.0); glVertex3f(20.0, 10 * sqrt(3), 20);

    glTexCoord2f(0.0, 0.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), 20);
    glTexCoord2f(0.0, 1.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 0.0); glVertex3f(-20.0, 10 * sqrt(3), 20);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3) + 10);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3));
    glTexCoord2f(1.0, 1.0); glVertex3f(20.0, 10 * sqrt(3), 20);
    glTexCoord2f(1.0, 0.0); glVertex3f(20.0 + 10, 10 * sqrt(3), 20);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3) + 10);
    glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 10 * sqrt(3), 20 + 5 * sqrt(3));
    glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 10 * sqrt(3), 20);
    glTexCoord2f(1.0, 0.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), 20);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3) - 10);
    glTexCoord2f(0.0, 1.0);   glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3));
    glTexCoord2f(1.0, 1.0); glVertex3f(-20.0, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 0.0); glVertex3f(-20.0 - 10, 10 * sqrt(3), -20);

    glTexCoord2f(0.0, 0.0);  glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3) - 10);
    glTexCoord2f(0.0, 1.0);  glVertex3f(0.0, 10 * sqrt(3), -20 - 5 * sqrt(3));
    glTexCoord2f(1.0, 1.0);  glVertex3f(20.0, 10 * sqrt(3), -20);
    glTexCoord2f(1.0, 0.0);  glVertex3f(20.0 + 10, 10 * sqrt(3), -20);
    glEnd();


    glPushMatrix();
    glTranslatef(-30.0, 10 * sqrt(3), 0.0);
    glRotatef(60.0, 0.0, 0.0, 1.0);
    drawCube(40.0, 5.0, 2.5, 8, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.0, 10 * sqrt(3), 0.0);
    glRotatef(-60.0, 0.0, 0.0, 1.0);
    drawCube(40.0, 5.0, 2.5, 8, 0, 0, 0);
    glPopMatrix();

    glPopMatrix();



}
// ========Lamp========
void drawLamp(float x, float y, float z) {
    GLfloat bright_emission[] = { 1.0, 1.0, 1.0 }; // Adjusted for  emission
    GLfloat no_emission[] = { 0.0, 0.0, 0.0 };
    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, bright_emission); // Set light emission
    glColor4f(1.0, 1.0, 1.0, 1.0);
    drawCube(11.0, 50, 1.0, 6, 0, 20, 11.0);
    drawCube(11.0, 50, 1.0, 6, 0, 20, -11.0);
    drawCube(1.0, 50, 11.0, 6, 11, 20, 0.0);
    drawCube(1.0, 50, 11.0, 6, -11, 20, 0.0);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission); // Set no emission 
    glColor4f(1.0, 1.0, 1.0, 1.0);
    drawCube(15, 20, 15, 11, x, y, z);
    drawCube(15, 20, 15, 11, x, y + 60.0, z);
    drawCube(2.0, 60, 1.5, 11, x + 13, y, z + 13.5);
    drawCube(2.0, 60, 1.5, 11, x - 13, y, z + 13.5);
    drawCube(2.0, 60, 1.5, 11, x - 13, y, z - 13.5);
    drawCube(2.0, 60, 1.5, 11, x + 13, y, z - 13.5);
    glPopMatrix();
}
// ========Road========
void drawRoad() {
    for (int i = 0; i < 34; i++)
    {
        glPushMatrix();
        glTranslatef(0.0, -200.0, -50 - 45 * i);
        glScalef(1.25, 1.0, 0.5);
        drawCube(19.0, 1.0, 20.0, 6, -20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 0.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, -31.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, 31.0, 0.0, -16.0);
        glPopMatrix();
    }
    for (int i = 0; i < 25; i++)//1125
    {
        glPushMatrix();
        glTranslatef(-1150.0, -200.0, -50 - 45 * i);
        glScalef(1.25, 1.0, 0.5);
        drawCube(19.0, 1.0, 20.0, 6, -20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 0.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, -31.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, 31.0, 0.0, -16.0);
        glPopMatrix();
    }
    for (int i = 0; i < 25; i++)
    {
        glPushMatrix();
        glTranslatef(1150.0, -200.0, -50 - 45 * i);
        glScalef(1.25, 1.0, 0.5);
        drawCube(19.0, 1.0, 20.0, 6, -20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 0.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, -31.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, 31.0, 0.0, -16.0);
        glPopMatrix();
    }
    for (int i = 0; i < 26; i++)
    {
        glPushMatrix();
        glTranslatef(1195 - 45 * i, -200.0, -1225.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glScalef(1.25, 1.0, 0.5);
        drawCube(19.0, 1.0, 20.0, 6, -20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 0.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, -31.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, 31.0, 0.0, -16.0);
        glPopMatrix();
    }
    for (int i = 0; i < 26; i++)
    {
        glPushMatrix();
        glTranslatef(-1195 + 45 * i, -200.0, -1225.0);
        glRotatef(90.0, 0.0, -1.0, 0.0);
        glScalef(1.25, 1.0, 0.5);
        drawCube(19.0, 1.0, 20.0, 6, -20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 20.0, 0.0, -60.0);
        drawCube(19.0, 1.0, 20.0, 6, 0.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, -31.0, 0.0, -16.0);
        drawCube(9.0, 1.0, 20.0, 6, 31.0, 0.0, -16.0);
        glPopMatrix();
    }
}
// ========House========
void drawHouse() {
    glPushMatrix();
    glTranslatef(0, -200.0, 0.0);
    glScalef(1.5, 1.5, 1.0);
    glTranslatef(0, 200.0, 0.0);
    // Piles and Pillars
    drawCube(15.0, 20.0, 15.0, 6, -325.0, -200.0, -1630.0);
    drawCube(15.0, 20.0, 15.0, 6, 325.0, -200.0, -1630.0);
    drawCube(100.0, 20.0, 40.0, 6, 0.0, -200.0, -1655.0);
    drawCylinder(10.0, 10.0, 500, 12, 325.0, -200.0, -1630.0);
    drawCylinder(10.0, 10.0, 500, 12, -325.0, -200.0, -1630.0);

    // Door
    drawCube(50.0, 250.0, 1.0, 13, 0.0, -180.0, -1640.0);
    drawCube(25.0, 250.0, 40.0, 6, -75.0, -180.0, -1655.0);
    drawCube(25.0, 250.0, 40.0, 6, 75.0, -180.0, -1655.0);
    drawCube(100.0, 50.0, 40.0, 6, 0.0, 70.0, -1655.0);

    // Front
    drawCube(25.0, 400.0, 25.0, 6, -75.0, -200.0, -1715.0);
    drawCube(25.0, 400.0, 25.0, 6, 75.0, -200.0, -1715.0);
    drawCube(100.0, 80.0, 25.0, 6, 0.0, 120.0, -1715.0);

    // Glass frame
    drawCube(50.0, 400.0, 10.0, 6, -350.0, -200.0, -1745.0);
    drawCube(50.0, 400.0, 10.0, 6, 350.0, -200.0, -1745.0);
    drawCube(300.0, 50.0, 10.0, 6, 0.0, -200.0, -1745.0);
    drawCube(300.0, 50.0, 10.0, 6, 0.0, 150.0, -1745.0);
    drawCube(300.0, 5.0, 2.5, 11, 0.0, 150.0 - 5, -1745.0);
    drawCube(300.0, 5.0, 2.5, 11, 0.0, -150.0 + 5, -1745.0);
    drawCube(300.0, 5.0, 2.5, 11, 0.0, 0, -1745.0);
    for (int i = 0; i < 5; i++)
    {
        drawCube(2.5, 300, 2.5, 11, 350 - i * 50, -150.0 + 5, -1745.0);
    }
    for (int i = 0; i < 5; i++)
    {
        drawCube(2.5, 300, 2.5, 11, -350 + i * 50, -150.0 + 5, -1745.0);

    }

    // Wall
    glColor4f(1.0, 1.0, 1.0, 1.0);
    drawCube(10.0, 400.0, 227.5, 6, 390.0, -200.0, -1982.5);
    drawCube(10.0, 400.0, 227.5, 6, -390.0, -200.0, -1982.5);
    drawCube(400.0, 400.0, 11.0, 6, 0.0, -200.0, -2221.0);
    drawCube(400.0, 10.0, 227.5, 6, 0.0, 199.0, -1982.5);

    // Roof
    drawCube(50.0, 25.0, 350.0, 12, 0.0, 650, -1930.0);
    for (int i = 0; i < 10; i++) {
        drawCube(25.0, 50.0, 350.0, 12, 25.0 + i * 50, 600.0 - i * 50, -1930.0);
        drawCube(25.0, 50.0, 350.0, 12, 25.0 + i * 50, 550.0 - i * 50, -1930.0);
    }
    for (int i = 0; i < 10; i++) {
        drawCube(25.0, 50.0, 350.0, 12, -25.0 - i * 50, 600.0 - i * 50, -1930.0);
        drawCube(25.0, 50.0, 350.0, 12, -25.0 - i * 50, 550.0 - i * 50, -1930.0);
    }
    for (int i = 0; i < 6; i++) {
        drawCube(25.0, i * 50, 200.0, 6, 375.0 - i * 50, 200.0, -1930.0);
    }
    for (int i = 0; i < 6; i++) {
        drawCube(25.0, i * 50, 200.0, 6, -375.0 + i * 50, 200.0, -1930.0);
    }
    for (int i = 0; i < 5; i++) {
        drawCube(25.0, i * 50, 200.0, 6, -225.0 + i * 50, 350.0, -1930.0);
    }
    for (int i = 0; i < 5; i++) {
        drawCube(25.0, i * 50, 200.0, 6, 225.0 - i * 50, 350.0, -1930.0);
    }
    drawCube(175.0, 200, 100.0, 6, 0.0, 150, -2130.0);

    // Glass frame
    drawCube(200.0, 5.0, 2.5, 11, 0.0, 200.0, -1745.0);
    drawCube(200.0, 5.0, 2.5, 11, 0.0, 350.0 - 5, -1745.0);
    drawCube(2.5, 150.0, 2.5, 11, -97.5, 200, -1745.0);
    drawCube(2.5, 150.0, 2.5, 11, 97.5, 200, -1745.0);
    for (int i = 0; i < 4; i++) {
        drawCube(2.5, 150.0, 2.5, 11, 117.5 - 80 * i, 200, -1745.0);
    }
    drawCube(200.0, 5.0, 2.5, 11, 0.0, 275.0, -1745.0);

    // Glass
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 0.6);
    drawCube(300.0, 300.0, 10.0, 16, 0.0, -150.0, -1755.0);
    drawCube(150.0, 150, 10.0, 16, 0.0, 200.0, -1755.0);
    glPopMatrix();

    glPopMatrix();
}
// ========Tree========
void drawTree(float x, float y, float z, float size) {


    GLfloat diffuse_tree[] = { 80.0 / 255.0, 220.0 / 255.0, 150.0 / 255.0 };
    GLfloat specular_tree[] = { 80.0 / 255.0, 220.0 / 255.0, 150.0 / 255.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_tree);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_tree);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    GLUquadricObj* objCylinder = gluNewQuadric();
    GLUquadricObj* objCylinder2 = gluNewQuadric();
    glPushMatrix();
    glScalef(1.0, size, 1.0);
    drawCylinder(25, 25, 800, 9, x, y, z);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y + 300, z);
    glScalef(1.0, size, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    if (winter % 2 == 0) {
        glColor3f(0.0, 0.2, 0.0);
        gluCylinder(objCylinder, 200, 0.1, 650, 80, 80);
        gluCylinder(objCylinder, 200, 0.1, 1, 80, 80);
        glColor3f(1, 1, 1);
        glPopMatrix();

    }
    else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.35, 0.7, 0.7);
        gluCylinder(objCylinder2, 200, 0.1, 650, 80, 80);
        glColor3f(0.0, 0.1, 0.0);
        gluCylinder(objCylinder, 200, 0.1, 1, 80, 80);
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glPopMatrix();
    }
}
// ========Snow========
void drawSnows() {
    glDisable(GL_TEXTURE_2D);

    GLfloat diffuse_snow[] = { 0.8, 1.0, 1.0 }; // Adjusted for material
    GLfloat specular_snow[] = { 0.8, 1.0, 1.0 }; // Adjusted for material
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_snow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_snow);
    if (winter % 2 == 1)
    {
        for (int i = 0; i < snowNum; i++) {
            glPushMatrix();
            glTranslatef(snowpos[i].x, snowpos[i].y, snowpos[i].z);
            glutSolidSphere(20.0, 80, 80);
            glPopMatrix();
        }

    }
    glEnable(GL_TEXTURE_2D);

}

// ========Timer=======
void cloudTimer(int value) {
    for (int i = 0; i < cloudNum; i++) {
        cloudpos[i].x -= 5;
        if (cloudpos[i].x < -3500) {
            cloudpos[i].x = float(3500 + rand() % 1000);
            cloudpos[i].y = 2000 + float(rand() % 501);
            cloudpos[i].z = float(-3500 + rand() % 7001);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, cloudTimer, 0);
}
void snowTimer(int value) {
    for (int i = 0; i < snowNum; i++) {
        snowpos[i].y -= 5;
        if (snowpos[i].y < -200) {
            snowpos[i].x = float(-3500 + rand() % 7001);
            snowpos[i].y = 3500 + float(rand() % 3000);
            snowpos[i].z = float(-3500 + rand() % 7001);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, snowTimer, 0);
}


void displayObject() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-150, 150, -150, 150, 100, 8000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(X0, Y0, Z0, XRef, YRef, ZRef, XUp, YUp, ZUp);
    glEnable(GL_DEPTH_TEST);


    GLfloat ambient[4] = { 1.0, 1.0, 1.0, 1.0 }, diffuse[4] = { 1.0, 1.0, 1.0, 1.0 }, specular[] = { 1, 1, 1, 1.0 };
    GLfloat shininess = 8.0, emission[] = { 0.0, 0.0, 0.0, 1.0 };
    //----------Set material parameters-----------
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);

    //----------Draw object-----------
    drawWall();
    drawCloud();
    drawSnows();
    drawIsland();
    drawRoad();
    drawHouse();
    drawSand();
    drawBarriers();
    drawPlatform();
    drawStairs();
    drawBoat(1800, -350, 600);
    drawBoat(-1800, -350, 600);
    drawLamp(-150.0, -200.0, -1400);
    drawLamp(150.0, -200.0, -1400);
    for (int i = 0; i < 3; i++)
    {
        drawLamp(-150.0, -200.0, -100 - 500 * i);
        drawLamp(150.0, -200.0, -100 - 500 * i);
        drawLamp(1300.0, -200.0, -100 - 500 * i);
        drawLamp(1000.0, -200.0, -100 - 500 * i);
        drawLamp(-1300.0, -200.0, -100 - 500 * i);
        drawLamp(-1000.0, -200.0, -100 - 500 * i);
    }
    for (int i = 0; i < 5; i++)
    {
        drawTree(-2600 + i * 1300, -200, -2700.0, 2.5);
    }
    for (int i = 0; i < 2; i++)
    {
        drawTree(-2600, -200, -1400.0 + i * 1300, 1.5);
        drawTree(2600, -200, -1400.0 + i * 1300, 1.5);

        drawTree(-1600, -200, -1400.0 + i * 1300, 1.5);
        drawTree(1600, -200, -1400.0 + i * 1300, 1.5);

        drawTree(-600, -200, -1400.0 + i * 1300, 1.5);
        drawTree(600, -200, -1400.0 + i * 1300, 1.5);
    }
    drawWater();

    glFlush();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Penghao.Ouyang_2141736");
    glEnable(GL_MULTISAMPLE); // MSAA
    myTexture();
    myLight();
    glutReshapeFunc(reshapeWindow);
    glutDisplayFunc(displayObject);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    makeCloudPos();
    makeSnowPos();
    glutTimerFunc(16, cloudTimer, 0);
    glutTimerFunc(16, snowTimer, 0);
    Menu();

    glutMainLoop();
}
