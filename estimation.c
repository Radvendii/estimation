#include <unistd.h>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "helpers.h"
#define k_circSize 50
#define k_time 1
#define k_maxNum 20

GLFWwindow *window;

int numObjs;
bool *font;

void drawChar(char c, int *x, int *y){
    printf("%c", c);
    glPointSize(5.f);
    glBegin(GL_POINTS);
    for(int i=0;i<5*7;i++){
        if(font[(c-48)*5*7+i]){glColor3f(1.f, 1.f, 1.f);}
        else{glColor3f(0.f, 0.f, 0.f);}
        glVertex2f(*x+i%5*10, *y-i/5*10);
    }
    glEnd();
    *x += 10*6;
}

void drawString(char *s, int x, int y){
    while(*s != '\0'){
        drawChar(*s, &x, &y);
        s++;
    }
    printf("\n");
}


void reveal(){ //prints the number of objects
    glfwSetTime(k_time+1);
    glfwMakeContextCurrent(window);
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    //glClear(GL_ACCUM_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    char *s;
    s = salloc(sizeof(char)*100);
    sprintf(s, "%d", numObjs);
    drawString(s, 100, 100);
    free(s);
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
    glColor3f(1.f,1.f,1.f);

    float x, y;
    for(int i=0;i<numObjs;i++){
        x = rand() % width;
        y = rand() % height;
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<100;i++){
            glVertex2f((GLfloat) x+k_circSize*cos(2*pi/100*i), (GLfloat) y+k_circSize*sin(2*pi/100*i));
        }
        glEnd();
    }

    glfwSwapBuffers(window);
    glfwSetTime(0);
}


void update(){
    numObjs = rand() % k_maxNum + 1;
}

static void error_callback(int error, const char* description){
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        update();
        draw();
    }
}

void initFont(char *file){
    font = salloc(sizeof(bool)*5*7*43);
    FILE* f;
    if((f = fopen(file, "r")) == NULL){
        printf("file not found: %s", file);
        exit(1);
    }
    int c;
    int i=0;
    while((c = fgetc(f)) != EOF){
        if(c == '\n'){continue;}
        else{font[i++]= (c == '1' ? true : false);}
    }
}

void init(){
    srand(time(NULL));
    initFont("../dots.font");
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
    free(font);
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main(void){
    init();
    while (!glfwWindowShouldClose(window)){
        if((int)glfwGetTime() == k_time){reveal();}
        glfwPollEvents();
    }
    deinit();
    exit(EXIT_SUCCESS);
}
