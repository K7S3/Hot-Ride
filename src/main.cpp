#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#include "main.h"
#include "timer.h"

#include "floor.h"
#include "player.h"
#include "wall.h"
#include "roof.h"
#include "coins.h"
#include "firelines.h"
#include "boomerang.h"
#include "magnet.h"
#include "speed_powerup.h"
#include "shield_powerup.h"
#include "score.h"
#include "firebeams.h"
#include "lifeup.h"
#include "water_balloon.h"
#include "ring.h"
#include "dragon.h"

#define GLM_ENABLE_EXPERIMENTAL
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
bounding_box_t b1;
bounding_box_t b2;
/**************************
* Customizable functions *
**************************/

//Ball ball1;
//Ball ball2;
Player player1;
Floor floor1;
Roof roof1;
Wall wall1;
Coins coins1[1080];
Boomerang boomerang[10];
Firelines firelines[120];
Firebeams firebeams[10];
Magnet magnets[10];
Speedup speedups[5];
Shieldup shieldups[5];
Score score1[5];
Score lives1;
Lifeup lifeups[5];
Water_balloon water_balloons[10000];
Ring rings[5];
Dragon dragon;
Lifeup lifeup1;
pid_t pid = 0;
int disable = 0;
int shield_number, start_number;
int time1=1, time2=-100, time3=-100;
int temp1;
bool sound = true;
int no_of_coins = 1080, no_of_firelines=120, no_of_boomerang=10, no_of_magnets = 10, no_of_speedups=5,no_of_shieldups=5, no_of_firebeams=10, no_of_lifeups=5, no_of_waterballoon=10000, no_of_rings=5;
int current =0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float time_in_air = 1;
float magnet_pull =0.1;
extern double drag_oldx, drag_oldy;
Timer t60(1.0 / 60);
int collision_firelines(Player a, Firelines b);
int collision_firebeams(Player a, Firebeams b);
int collision_boomerang(Boomerang a, Player b);
int collision_speedup(Speedup a, Player b);
int collision_shieldup(Shieldup a, Player b);
int collision_lifeup(Lifeup a, Player b);
int collision_water_balloon(Water_balloon a, Firelines b);
int collision_ring(Player a, Ring b);
int collision_dragon(Player a, Dragon b);
int collision_dragon_water(Water_balloon a, Dragon b);
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
//    glm::vec3 up (0, 0, 0);

    // Compute Camera matrix (view)player
//    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
     Matrices.view = glm::lookAt(glm::vec3(1+player1.position.x, 0, 3), glm::vec3(1+player1.position.x, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);
//    ball2.draw(VP);
    floor1.draw(VP);
    roof1.draw(VP);
    player1.draw(VP);
    wall1.draw(VP);
    for(int i = 0; i < no_of_coins; i++)
    {
        coins1[i].draw(VP);
    }
    for(int i=0; i<no_of_firelines;i++)
    {
        firelines[i].draw(VP);
    }
    for(int i=0; i<no_of_firebeams;i++)
    {
        firebeams[i].draw(VP);
    }
    for(int i=1; i<no_of_boomerang;i++)
    {
        boomerang[i].draw(VP);
    }
    for(int i=0; i<no_of_magnets;i++)
    {
        magnets[i].draw(VP);
    }

    for(int i=0; i<no_of_speedups;i++)
    {
        speedups[i].draw(VP);
    }
    for(int i=start_number; i<no_of_shieldups;i++)
    {
        shieldups[i].draw(VP);
    }
    temp1 = player1.score;
    for(int i=0;i<5;i++)
    {
        score1[i].draw(VP, temp1%10);
        temp1 = temp1/10;

    }
    for(int i=0;i<no_of_lifeups;i++)
    {
        lifeups[i].draw(VP);
    }
    for(int i=0;i<no_of_rings;i++){
        rings[i].draw(VP);
    }

    if(current<no_of_waterballoon)
   water_balloons[current].draw(VP);
    if(current+1<no_of_waterballoon)
    {water_balloons[current+1].draw(VP);
    }
    lives1.draw(VP, player1.lives);
    dragon.draw(VP);
    lifeup1.draw(VP);
}

void tick_input(GLFWwindow *window) {
       int left  = glfwGetKey(window, GLFW_KEY_LEFT);
       int right = glfwGetKey(window, GLFW_KEY_RIGHT);
       int up    = glfwGetKey(window, GLFW_KEY_UP);
       int key_a = glfwGetKey(window, GLFW_KEY_A);
       int key_s = glfwGetKey(window, GLFW_KEY_S);
       int key_d = glfwGetKey(window, GLFW_KEY_D);
       int key_w = glfwGetKey(window, GLFW_KEY_W);
       int key_x = glfwGetKey(window, GLFW_KEY_X);
       glfwSetScrollCallback(window, scroll_callback);
       int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
       if (mouse_clicked) {
               if (drag_oldx == -1 && drag_oldy == -1) {
                   //cout<<"Life"<<endl;
                   glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
               }
               else {
                   //cout << "Life2" << endl;
                   int w, h;
                   double new_x, new_y;
                   float pos_x, pos_y;
                   glfwGetCursorPos(window, &new_x, &new_y);
                   glfwGetWindowSize(window, &w, &h);

                   screen_center_x -= 8 * (new_x - drag_oldx) / (w * screen_zoom);
                   screen_center_y += 8 * (new_y - drag_oldy) / (h * screen_zoom);

                   if (screen_center_x - 4 / screen_zoom + 4 < 0)
                       screen_center_x = -4 + 4 / screen_zoom;

                   if (screen_center_y - 4 / screen_zoom + 4 < 0)
                       screen_center_y = -4 + 4 / screen_zoom;

                   if (screen_center_x + 4 / screen_zoom - 4 > 0)
                       screen_center_x = 4 - 4 / screen_zoom;

                   if (screen_center_y + 4 / screen_zoom - 4 > 0)
                       screen_center_y = 4 - 4 / screen_zoom;

                   drag_oldx = new_x;
                   drag_oldy = new_y;
                   reset_screen();
               }
       }
       if (key_a && screen_center_x - 4/screen_zoom + 4 > 0) {
              screen_center_x -= 0.07;
              reset_screen();
          }

          if (key_s && screen_center_y - 4/screen_zoom + 4 > 0) {
              screen_center_y -= 0.07;
              reset_screen();
          }

          if (key_w && screen_center_y + 4/screen_zoom -4 < 0) {
              screen_center_y += 0.07;
              reset_screen();
          }

          if (key_d && screen_center_x + 4/screen_zoom -4 < 0) {
              screen_center_x += 0.07;
              reset_screen();
          }
          if(key_x){
              if(current==no_of_waterballoon)
                  return;

//              water_balloons[current].xspeed = 0.05;
//              water_balloons[current].yspeed = 0.2;*/
                current++;

          }
          if (left) {
               player1.position.x -= player1.xspeed;
                  if(disable ==1)
                      player1.position.y = -sqrt((rings[0].radius1)*(rings[0].radius1)-player1.position.x*player1.position.x);
              player1.speed = -4.0;
//               if(player1.jump = 1 && abs(player1.rotation)<20)
//                    player1.rotation -= 1.0;
//               player1.rotation = 4.0;
               player1.tick();


                }

                if (right) {

                        //player1.dir = true;
                        player1.position.x += player1.xspeed;
                        player1.speed = 4.0;
                        if(player1.jump = 1 && abs(player1.rotation)<20)
                            player1.rotation += 1.0;
                        player1.tick();

                }
                if (up) {
                    //cout<<"Here"<<endl;
                    if(disable==1)
                        return;
                    player1.jump = 1;
                   if(detect_collision(player1.bounding_box(), roof1.bounding_box()) == 1){
                    player1.position.y += 0.07;
                    player1.jump = 1;
                    player1.rotation=0;

                   }
//                   cout<<time_in_air;
            }
                if(!up&&disable==0) {

                         player1.jump = 0;
                    if(detect_collision(player1.bounding_box(), floor1.bounding_box()) == 0)
                    {
                        player1.position.y += player1.yspeed;
                        player1.yspeed -=0.002;

//                        if(player1.rotation<0)
//                            player1.rotation += player1.speed;
//                        else if (player1.rotation > 0)
//                            player1.rotation -= player1.speed;
//                        else;
                        time_in_air++;
                    }

                    else{
                          player1.yspeed = -0.01;
                          player1.position.y = -0.75;
//                          player1.rotation = 0;
                          player1.jump = 0;
                    }

                }


}

void tick_elements() {
    lifeup1.set_position(3.3+player1.position.x, -2.3);
    time1 = glfwGetTime();
//    if(current!=0)
   water_balloons[current].tick();
//    for(int i=current;i<no_of_waterballoon;i++){
        water_balloons[current+1].set_position(player1.position.x+0.1, player1.position.y);
//    }
    for(int i = 0; i< no_of_coins; i++)
    if (detect_collision(coins1[i].bounding_box(), player1.bounding_box()) == 1)
    {
        player1.score += 10;
        coins1[i].position.y = 3.5;
    }
    for(int i=0;i<no_of_coins;i++)
    {
        coins1[i].tick();
    }
    for(int i=0;i<no_of_speedups;i++){
        speedups[i].tick();
        if(collision_speedup(speedups[i], player1)==1)
            time2 = glfwGetTime();

    }
    for(int i=0;i<no_of_magnets;i++){
        magnets[i].tick1();
        if(abs(player1.position.x - magnets[i].position.x) <1){
            player1.position.y += magnet_pull;
            magnet_pull +=0.0001;
        }
        if(detect_collision(player1.bounding_box(), roof1.bounding_box()) == 0){
         player1.position.y -= 0.07;
         player1.jump = 1;

        }
    }

    for(int i =0 ; i<5; i++){
       score1[i].set_position(-0.5*i + player1.position.x, -2);
    }
    lives1.set_position(4+player1.position.x, -2);
    if(time1-time2<4){
         player1.speedtick();
         return ;
    }
    if(time1-time3<=6){
        shieldups[shield_number].set_position(player1.position.x-.25, player1.position.y+0.12);
        if(time1-time3==6){
            shieldups[shield_number] ={};
            start_number = shield_number+1;
        }
        return;
    }
    for(int i=start_number; i<no_of_shieldups;i++){
        shieldups[i].tick();
        if(collision_shieldup(shieldups[i], player1)==1)
        {
             time3 = glfwGetTime();
             shield_number = i;
//             shieldups[i].set_position(player1.position.x, player1.position.y);
        }
    }
    for(int i=0; i<no_of_lifeups;i++){
        lifeups[i].tick();
        if(collision_lifeup(lifeups[i], player1)==1)
        {
             player1.lives++;
             lifeups[i].set_position(-200,-200);
        }
    }
    dragon.tick();
    if(collision_dragon(player1, dragon)==1)
    {
        player1.lives--;
        player1.score -= 100;
        player1.position.x -=3;
        player1.position.y = -0.75;

    }
    if(collision_dragon_water(water_balloons[current], dragon)==1)
    {
        dragon.lives--;
        if(dragon.lives <= 0){
            dragon.set_position(-200,-200);
            quit(window);
        }
    }
    for(int i=0;i<no_of_firebeams;i++){
        firebeams[i].tick();
        if(abs(player1.position.x - firebeams[i].position.x)<4)
        {
            firebeams[i].attack =1;
        if(detect_collision(player1.bounding_box(), firebeams[i].bounding_box())==1){
            player1.lives--;
            player1.score -= 30;
            player1.position.x +=3;
            player1.position.y = -0.75;
            firebeams[i].position.y = -160;

        }
        return ;
        }
    }


    for(int i=1;i<no_of_boomerang;i++)
    {
        if(collision_boomerang(boomerang[i], player1)==1)
        {
            player1.lives--;
            player1.score -= 20;
            player1.position.x +=3;
            player1.position.y = -0.75;
            boomerang[i].position.y = -16;
        }
        if(boomerang[i].position.x -player1.position.x <=-6){
            boomerang[i].set_position(-200,-200);
        }
        if(abs(boomerang[i].position.x - player1.position.x) < 6)
        {
            boomerang[i].tick1();
            if(boomerang[i].position.x - player1.position.x <= -2)
            {
                boomerang[i].xspeed = -0.04;
                if(boomerang[i].position.y <= 0)
                    boomerang[i].yspeed = 0;
//                boomerang[i].tick2();
            }

        }

    }
    for(int i=0;i<no_of_firelines;i++)
    {
        firelines[i].tick();
        if(collision_firelines(player1, firelines[i])==1)
        {
            player1.lives--;
            player1.score -= 50;
            player1.position.x +=3;
            player1.position.y = -0.75;

        }
        if(collision_water_balloon(water_balloons[current], firelines[i])==1)
        {
            firelines[i].set_position(-200,-200);
        }
        if(player1.lives<=0)
            quit(window);

    }
    for(int i=0;i<no_of_rings;i++){

        if(collision_ring(player1, rings[i])==1)
        {
            disable = 1;
            player1.position.x -= player1.xspeed;
//            player1.position.y += player1.yspeed;
        }
        else if(collision_ring(player1, rings[i])==2)
        {
//            player1.position.x += player1.xspeed/20;
//            player1.position.y += 0.2;
            disable = 1;
            player1.set_position(player1.position.x, player1.radius-sqrt(rings[i].radius1*rings[i].radius1 - (rings[i].position.x-player1.position.x)*(rings[i].position.x-player1.position.x)));
//            if(player1.position.y = -rings[i].radius + 1)
        }

        else
           {
            disable = 0;
//            player1.position.y+=0.005;
//            player1.position.y += rand()/100;
        }
    }




}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    floor1       = Floor(0, -1.0,COLOR_BLACK);
    roof1        = Roof(0, -1.0,COLOR_BLACK);
    player1      = Player(-2, -0.75, COLOR_GREEN);
    wall1        = Wall(0, 0, COLOR_VIOLET);
    lives1        = Score(4+player1.position.x, -2, COLOR_WHITE);
    dragon        = Dragon(20, 0, COLOR_YELLOW);
    lifeup1       = Lifeup(3.3+player1.position.x, -2.3, COLOR_PINK);

    for(int i=0;i<no_of_waterballoon;i++){
        water_balloons[i] = Water_balloon(player1.position.x+0.1, player1.position.y, COLOR_BLUE);
    }
    for(int i=0; i<5; i++){
        score1[i] = Score(-0.5*i + player1.position.x, -2, COLOR_WHITE);
    }

    for(int i = 0; i< no_of_coins; i++){

        int x=rand();
        int y=rand();
        coins1[i]       = Coins(x%no_of_coins, y%3, {x%255, y%255, (x*y)%255});
    }
    for(int i=0; i<no_of_firelines;i++){
        int x=rand();
        int y=rand();
        firelines[i] = Firelines(x%1080, y%2+.5, COLOR_RED);
    }

    for(int i=1; i<no_of_boomerang;i++){
        boomerang[i] = Boomerang(50*i, 3, COLOR_RED);
    }
    for(int i=0; i<no_of_magnets;i++){
        int x=rand();
        int y=rand();
        magnets[i] = Magnet(75*i, 3.5, COLOR_MAGNET);
    }

    for(int i=0; i<no_of_speedups;i++){
        speedups[i] = Speedup(160*i+40, 2.5, COLOR_DARKGREEN);
    }
    for(int i=0; i<no_of_shieldups;i++){
        shieldups[i] = Shieldup(240*i+20, 2.5, COLOR_YELLOW);
    }
    for(int i=0;i<no_of_firebeams;i++){
        int x=rand();
        int y=rand();
        firebeams[i] = Firebeams(y%1080,x%2, COLOR_RED);
    }
    for(int i=0;i<no_of_lifeups;i++){
        int x=rand();
        int y=rand();
        lifeups[i] = Lifeup(x%1080, y%2, COLOR_PINK);
    }
    for(int i=0;i<no_of_rings;i++){
        int x=rand();
        int y=rand();
        rings[i] = Ring(x%1080+100, 0, COLOR_BROWN);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;
    system("aplay ./assets/audio.wav&");

    window = initGLFW(width, height);

    initGL (window, width, height);


    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
//            b1.x = ball1.position.x;
//            b1.y = ball1.position.y;
//            b1.width = 2.0f;
//            b1.height = 2.0f;
//            b2.height = 2.0f;
//            b2.width = 2.0f;
//            b2.x = ball2.position.x;
//            b1.y = ball2.position.y;
////
//            if(detect_collision(b1, b2) == 1)
//                quit(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(yoffset<0)
        screen_zoom += 0.01;
    else if(yoffset>0)
        screen_zoom -= 0.01;
    reset_screen();
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.01f, 500.0f);

}

int collision_firelines(Player a, Firelines b)
{

    if(abs(a.position.x-b.position.x)*abs(a.position.x-b.position.x)+abs(a.position.y-b.position.y)*abs(a.position.y-b.position.y)<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;
    if(abs(a.position.x-(b.position.x+0.5))*abs(a.position.x-(b.position.x+0.5))+abs(a.position.y-(b.position.y+0.5))*abs(a.position.y-(b.position.y+0.5))<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;

    if(abs(a.position.x-b.position.x-1)*abs(a.position.x-b.position.x-1)+abs(a.position.y-b.position.y-1)*abs(a.position.y-b.position.y-1)<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;

}

int collision_boomerang(Boomerang a, Player b){
    if(abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) < b.radius + a.radius)
            return 1;
}
int collision_speedup(Speedup a, Player b){
    if(abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) < (b.radius + a.radius)*(b.radius+a.radius))
            return 1;
}
int collision_shieldup(Shieldup a, Player b){
    if(abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) < (b.radius + a.radius)*(b.radius+a.radius))
            return 1;
}
int collision_firebeams(Player a, Firebeams b){
    if(abs(a.position.x-b.position.x)<3 && abs(a.position.y - b.position.y) <= abs(a.radius + b.width))
        return 1;
}
int collision_lifeup(Lifeup a, Player b){
    if(abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) < (b.radius + a.radius)*(b.radius+a.radius))
            return 1;
}


int collision_water_balloon(Water_balloon a, Firelines b)
{

    if(abs(a.position.x-b.position.x)*abs(a.position.x-b.position.x)+abs(a.position.y-b.position.y)*abs(a.position.y-b.position.y)<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;
    if(abs(a.position.x-(b.position.x+0.5))*abs(a.position.x-(b.position.x+0.5))+abs(a.position.y-(b.position.y+0.5))*abs(a.position.y-(b.position.y+0.5))<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;

    if(abs(a.position.x-b.position.x-1)*abs(a.position.x-b.position.x-1)+abs(a.position.y-b.position.y-1)*abs(a.position.y-b.position.y-1)<(a.radius+b.radius)*(a.radius+b.radius))
        return 1;

}

int collision_ring(Player a, Ring b){
    if((a.position.y)>=0)
        return 0;
    if(abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) <= (a.radius+b.radius)*(a.radius+b.radius)  && abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) >(a.radius+b.radius1)*(a.radius+b.radius1))
        return 1;
    else if (abs(a.position.x - b.position.x)*abs(a.position.x - b.position.x) + abs(a.position.y - b.position.y)*abs(a.position.y - b.position.y) <=(a.radius+b.radius1)*(a.radius+b.radius1))
        return 2;
    else
        return 0;
}
int collision_dragon(Player a, Dragon b)
{
    float tmp_x = a.position.x - b.position.x;
    float tmp_y = a.position.y - b.position.y;
    if(tmp_x*tmp_x + tmp_y*tmp_y < a.radius*a.radius)
        return 1;
    float tmp1_x = tmp_x + 1;
    float tmp1_y = tmp_y +1.5;
    if(tmp1_x*tmp1_x + tmp1_y*tmp1_y < a.radius*a.radius)
        return 1;
    float tmp2_x = tmp_x + 2.5;
    if(tmp2_x*tmp2_x + tmp1_y*tmp1_y < a.radius*a.radius)
        return 1;

    float tmp3_x = tmp_x + 1.3;
    float tmp3_y = tmp_y + 1.0;
    if(tmp3_x*tmp3_x + tmp3_y*tmp3_y < b.radius*b.radius)
        return 1;


}
int collision_dragon_water(Water_balloon a, Dragon b)
{
    float tmp_x = a.position.x - b.position.x;
    float tmp_y = a.position.y - b.position.y;
    if(tmp_x*tmp_x + tmp_y*tmp_y < a.radius*a.radius)
        return 1;
    float tmp1_x = tmp_x - 0.5;
    float tmp1_y = tmp_y - 0.3;
    if(tmp1_x*tmp1_x + tmp1_y*tmp1_y < b.radius*b.radius)
        return 1;
//    float tmp2_x = tmp_x + 2.5;
//    if(tmp2_x*tmp2_x + tmp1_y*tmp1_y < a.radius*a.radius)
//        return 1;
//    float tmp3_x = tmp_x - 1.5;
//    float tmp3_y = tmp_y - 0.8;
//    if(tmp2_x*tmp2_x + tmp1_y*tmp1_y < b.radius*a.radius)
//        return 1;
//       if(a.position.x-a.radius < b.position.x - 1 && a.position.x +a.radius >b.position.x - 2.5)
//            return 1;

}
