#include <unistd.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define pi (22.0/7)
#define k_circSize 50
#define k_charSizeX 50
#define k_charSizeY 100

GLFWwindow *window;

int numObjs;

/*
 *void drawChar(char c, int *x, int *y){
 *    //glBegin(GL_LINE_LOOP);
 *        //glVertex2f((GLfloat) *x, (GLfloat) *y);
 *        //glVertex2f((GLfloat) *x, (GLfloat) *y+k_charSizeY);
 *        //glVertex2f((GLfloat) *x+k_charSizeX, (GLfloat) *y+k_charSizeY);
 *        //glVertex2f((GLfloat) *x+k_charSizeX, (GLfloat) *y);
 *    //glEnd();
 *    switch(c){
 *        case '0':
 *            printf("0");
 *            glBegin(GL_LINE_LOOP);
 *            for(int i=0;i<10;i++){
 *                glVertex2f((GLfloat) *x+k_charSizeX/2.0*(1+cos(2*pi/10*i)), (GLfloat) *y+k_charSizeY/2.0*(1+sin(2*pi/10*i)));
 *            }
 *            glEnd();
 *            break;
 *        case '1':
 *            printf("1");
 *            glBegin(GL_LINES);
 *                glVertex2f((GLfloat) *x+k_charSizeX/10.0, *y);
 *                glVertex2f((GLfloat) *x+k_charSizeX*9/10.0, *y);
 *                glVertex2f((GLfloat) *x+k_charSizeX/2.0, *y);
 *                glVertex2f((GLfloat) *x+k_charSizeX/2.0, *y + k_charSizeY);
 *                glVertex2f((GLfloat) *x+k_charSizeX/2.0, *y + k_charSizeY);
 *                glVertex2f((GLfloat) *x+k_charSizeX/10.0, *y + k_charSizeY*4/6.0);
 *            glEnd();
 *            break;
 *        case '2':
 *            printf("2");
 *            glBegin(GL_LINE_LOOP);
 *                
 *            glEnd();
 *    }
 *    *x += k_charSizeX;
 *}
 */

/*
 *void drawString(char *s, int x, int y){
 *    while(*s != '\0'){
 *        //drawChar(*s, &x, &y);
 *        glutj
 *        s++;
 *    }
 *    printf("\n");
 *}
 */

void reveal(){ //prints the number of objects
    glfwMakeContextCurrent(window);
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //char *s[100];
    //sprintf(s, "%d", numObjs);
    //drawString("101", 100, 100);
    glutBitmapString(GLUT_STROKE_MONO_ROMAN, "101");
    glfwSwapBuffers(window);
}

void draw(){
    glfwMakeContextCurrent(window);
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float x, y;
    for(int i=0;i<numObjs;i++){
        x = rand() % width;
        y = rand() % height;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<1000;i++){
            glVertex2f((GLfloat) x+k_circSize*cos(2*pi/1000*i), (GLfloat) y+k_circSize*sin(2*pi/1000*i));
        }
        glEnd();
    }

    glfwSwapBuffers(window);
    reveal();
}


void update(){
    numObjs = rand() % 10 + 1;
}

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(action == GLFW_PRESS){
        update();
        draw();
    }
}

void init(){
    srand(time(NULL));
    update();
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(800, 800, "Estimation Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowPos(window, 100, 50);

    glfwSetKeyCallback(window, key_callback);
    draw();
}

void deinit(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main(void){
    init();
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }
    deinit();
    exit(EXIT_SUCCESS);
}
