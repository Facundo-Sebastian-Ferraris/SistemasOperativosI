#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream> 

#define PI 3.14159265359 
#define P2 PI/2
#define P3 (3*PI)/2 
#define DG 0.0174533 

//World
int 
    windowWidth = 1024,
    windowHeight = 720,
    mapX = 30,
    mapY = 40,
    mapS = 64,
    map[]={
        
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
        1, 0, 1, 0, 0, 0, 0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

        1, 0, 0, 0, 0, 0, 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 1, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

    };
//PLAYER ZONE
float
    px,     //player x
    py,     //player y
    pdx,    //player delta x    
    pdy,    //player delta y
    pa;     //player angle

void drawPlayer(){
    glColor3f(1,1,0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px,py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px,py);
    glVertex2i(px+pdx*5,py+pdy*5);
    glEnd();
    

}


// MOVILITY
int keyStates[256] = {0}; 


void update(int value) {
    // Movimiento hacia adelante/atrás
    int
        xo = 10,
        yo = 10;

    if (pdx < 0){
        xo *= -1;
    } 
    if (pdy < 0){
        yo *= -1;
    }
    int
        ipx =  px/64.0,
        ipx_add_xo = (px+xo)/64.0,
        ipx_sub_xo = (px-xo)/64.0,
        
        ipy =  py/64.0,
        ipy_add_yo = (py+yo)/64.0,
        ipy_sub_yo = (py-yo)/64.0;

    if (keyStates['w']) {
        if(map[ipy*mapX + ipx_add_xo] == 0){px += pdx*0.5;}
        if(map[ipy_add_yo*mapX + ipx] == 0){py += pdy*0.5;}
    }
    if (keyStates['s']) {
        if(map[ipy*mapX + ipx_sub_xo] == 0){px -= pdx*0.5;}
        if(map[ipy_sub_yo*mapX + ipx] == 0){py -= pdy*0.5;}
    }

    // Rotación izquierda/derecha
    if (keyStates['a']) {
        if (keyStates['k'])
        {

            if(map[ipy*mapX + ipx_sub_xo] == 0){px -= pdx*0.5;}
            if(map[ipy_sub_yo*mapX + ipx] == 0){py -= pdy*0.5;}
        } else {
            pa -= 0.05;
            if (pa < 0) pa += 2*PI;
            pdx = cos(pa) * 5;
            pdy = sin(pa) * 5;
        }
        
    }
    if (keyStates['d']) {
        pa += 0.05;
        if (pa > 2*PI) pa -= 2*PI;
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
    }



    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS (1000ms / 60 ≈ 16ms)
}

// Callback para tecla presionada
void keyboard(unsigned char key, int x, int y) {
    keyStates[std::tolower(key)] = 1; // Marcar tecla como presionada
    if (key == 27) exit(0); // Salir con ESC
}

// Callback para tecla liberada
void keyboardUp(unsigned char key, int x, int y) {
    keyStates[std::tolower(key)] = 0; // Marcar tecla como liberada
}


void drawMap2D(){
    int
        x,
        y,
        x0,
        y0;

    for(y = 0; y < mapY; y++){
        for(x = 0; x < mapX; x++){

            if(map[y*mapX+x] == 1){
                glColor3f(1,1,1);
            } else {
                glColor3f(0,0,0);
            }

            x0 = x*mapS;
            y0 = y*mapS;
            glBegin(GL_QUADS);
            glVertex2d(x0 + 1,          y0 + 1);
            glVertex2d(x0 + 1,          y0 + mapS - 1);
            glVertex2d(x0 + mapS - 1,   y0 + mapS - 1);
            glVertex2d(x0 + mapS - 1,   y0 + 1);
            glEnd();

        }
    }
}

float dist(float ax, float ay, float bx,float by, float ang){
    return sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay));
}
//Rayos y centellas
void drawRays2D(){
    int
        r,      //rayo
        mx,     //mexico ahre no, es la posicion de la matriz en X
        my,     // celda de la matriz Y
        mp,     // es el pasaje de 2D a 1D
        dofx,    // es la profundidad de campo en X, es para evitar recorrer de mas (en este caso es mapX o mapY <<8>>)
        dofy,    // es la profundidad de campo en Y, es para evitar recorrer de mas (en este caso es mapX o mapY <<8>>)
        disT;   // distancia del rayo
    float
        rx,     //posicion del rayo en X
        ry,     //posicion del rayo en Y
        ra,     //Angulo del rayo
        x0,     // incrementos en X
        y0;     // incrementos en Y

    float rayos = 60; //cantidad de rayos a visualizar
    ra = pa - DG * (rayos/2) ;
    if (ra<0.0){
        ra += 2*PI;
    } else if (ra>2*PI){
        ra -= 2*PI;
    }
    


    for (r = 0; r < rayos; r++){//se crea cada rayo con lo siguiente:
        //--fijar las lineas horizontales--
        dofy = 0;
        float 
            disH = 1000000,
            hx = px,    //auxiliar para distancia horizontal en X
            hy = py;    //auxiliar para distancia horizontal en Y
        float aTan = -1/tan(ra);

        if (ra > PI){ //si el jugador esta mirando abajo
            ry = (((int)py>>6)<<6) - 0.0001; // >>6 es equivalente a divir el numero por 2^6, y el <<6 vuelve a multiplicar por 2^6
            rx = (py-ry)*aTan + px;
            y0 = -64;
            x0 = -y0 * aTan;
        }
        
        if (ra < PI){ //si el jugador esta mirando arriba
            ry = (((int)py>>6)<<6) + 64; // >>6 es equivalente a divir el numero por 2^6, y el <<6 vuelve a multiplicar por 2^6
            rx = (py-ry)*aTan + px;
            y0 = 64;
            x0 = -y0 * aTan;
        }

        if (ra == 0 || ra == PI){ // si el jugador mira exactamente derecha o izquierda
            rx = px;
            ry = py;
            dofy = mapY;
        }

        while (dofy<mapY){
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my*mapX+mx;

            
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1){
                hx = rx;
                hy = ry;
                disH = dist(px,py,hx,hy, pa);
                dofy = mapY; //hit wall
            } else {
                rx += x0;
                ry += y0;
                dofy += 1;
            }
        }
        //--fijar las lineas verticales--
        dofx = 0;
        float disV = 1000000, vx = px, vy = py;
        float nTan = -tan(ra);

        if (ra > P2 && ra < P3){ //si el jugador esta mirando izquierda
            rx = (((int)px>>6)<<6) - 0.0001; // >>6 es equivalente a divir el numero por 2^6, y el <<6 vuelve a multiplicar por 2^6
            ry = (px-rx)*nTan + py;
            x0 = -64;
            y0 = -x0 * nTan;
        }
        
        if (ra < P2 || ra > P3){ //si el jugador esta mirando derecha
            rx = (((int)px>>6)<<6) + 64; // >>6 es equivalente a divir el numero por 2^6, y el <<6 vuelve a multiplicar por 2^6
            ry = (px-rx)*nTan + py;
            x0 = 64;
            y0 = -x0 * nTan;
        }

        if (ra == 0 || ra == PI){ // si el jugador mira exactamente derecha o izquierda
            rx = px;
            ry = py;
            dofx = mapX;
        }

        while (dofx<mapX){
            mx = (int) (rx) >> 6;
            my = (int) (ry) >> 6;
            mp = my*mapX+mx;

           
            if (mp > 0 && mp < mapX * mapY && map[mp] == 1){
                vx = rx;
                vy = ry;
                disV = dist(px,py,vx,vy, pa);
                dofx = mapX; //hit wall
            } else {
                rx += x0;
                ry += y0;
                dofx += 1;
            }
        }

        if(disV<disH){
            rx = vx;
            ry = vy;
            disT = disV;
            glColor3f(0,1,0);
            
        }
        if(disH<disV){
            rx = hx;
            ry = hy;
            disT = disH;
            glColor3f(0,0.7,0);

        }

        //===walls 3d ===
        float ca = pa - ra;
        if (ca<0)
        {
            ca +=2*PI;
        }

        if (ca>2*PI)
        {
            ca -=2*PI;
        }
        disT *= cos(ca);
        
        float lineH = mapS*320/disT;
        float lineO = 160. - lineH/2.;
        // if(lineH>320){
        //     lineH=320;
        // }
        glLineWidth((windowWidth/rayos)+1);
        glBegin(GL_LINES);
        glVertex2i(r*(windowWidth/rayos) + 1, lineO);
        glVertex2i(r*(windowWidth/rayos) + 1, lineO + lineH);
        glEnd();

        ra += DG;
        if (ra<0){
            ra = 2*PI;
        }
        if (ra>2*PI){
            ra = 0;
        }
        // glColor3f(1,0,0);
        // glLineWidth(1);
        // glBegin(GL_LINES);
        // glVertex2d(px,py);
        // glVertex2d(rx,ry);
        // glEnd();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // drawMap2D();
    drawRays2D();
    // drawPlayer();
    glutSwapBuffers();

}
void init(){
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0,1024,512,0);
    px = 300;
    py = 300;
    pa = 0;
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;

}

void resize(int w, int h){
    glutReshapeWindow(windowWidth,windowHeight);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(200,200);
    glutCreateWindow("EFARRSIR RayCasting");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, update, 0); // Iniciar temporizador
    glutMainLoop();
    return 0;
}
