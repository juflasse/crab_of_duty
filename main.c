#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SANDAL2/SANDAL2.h>
#include <math.h>

#define W_Window 1300
#define H_Window 700
#define H 200
#define W 200
int movement=0;

void move(Element * this,SDL_Keycode c);
void no_move(Element * this,SDL_Keycode c);
void mvtir(Element * this);

int main(){
  Element * crabe;
  int black[] = {0,0,0,0};
  int run = 0;

  if(initAllSANDAL2(IMG_INIT_PNG)){
    puts("Failed to init SANDAL2");
  return -1;
  }

/* creation of your window */
  if(createWindow(W_Window,H_Window,"Crab Of Duty",SDL_WINDOW_MAXIMIZED,black,0)){
    puts("Failed to open the window");
    closeAllSANDAL2();
  }

  crabe = createImage(1,1,W,H,"crab_cannon.png",0,0);

  setAngleElement(crabe,0);

  addClickableElement(crabe,rectangleClickable(0.f,0.f,1.f,1.f),0);
  setKeyPressedElement(crabe,move);
  setKeyReleasedElement(crabe,no_move);

  while(run==0){
  if(PollEvent(NULL))
    run=1;
  mvtir(crabe);
  updateWindow();
  displayWindow();
  SDL_Delay(16);
  }

  closeAllWindow();
  closeAllSANDAL2();

  return 0;
}


void move(Element * this,SDL_Keycode c){

  float x,y;
  float a;
  Element * tir;
  int red[]  = {255,0,0,0};
  getAngleElement(this,&a);
  getCoordElement(this,&x,&y);

  switch (c) {
    //direction x
    case 'q':{
      setAngleElement(this,a+10);
      break;
    }
    case 'd':{
      setAngleElement(this,a-10);
      break;
    }
    //direction y
    case 'z':{
      movement = 1;
      break;
    }
    case 's':{
      movement = -1;
      break;
    }
    case ' ':{
      tir = createBlock(x+W/2,y+H/2,20,20,red,0,1);
      addElementToElement(this,tir);
    }

  }
  a=a*2*3.14/360;
  //printf("%f %f %f %d %f %f %f %f\n",x,y,a,movement,cos(a),sin(a),cos(3.14/2),sin(3.14/2));
  //printf("%c\n",c);
  moveElement(this,10*movement*cos(a),10*movement*sin(a));
  //moveElement(this,10*movement*sin(a),10*movement*cos(a)); drift
}

void no_move(Element * this,SDL_Keycode c){

  switch (c) {
    case 'z':{
      movement = 0;
      break;
    }
    case 's':{
      movement = 0;
      break;
    }
  }
}

void mvtir(Element * this){
  int black[] = {0,0,0,0};
  float a;
  float x,y;
  int red[]  = {255,0,0,0};
  getAngleElement(this,&a);
  a=a*2*3.14/360;
  Element * e=createBlock(0,0,0,0,black,0,0);
  initIteratorElement(this);
  while(e=nextIteratorElement(this)){
    getCoordElement(e,&x,&y);
    moveElement(e,10*sin(a),-10*cos(a));
    if(x<0 || x>W_Window || y<0 || y>H_Window){
      delElementToElement(this,e);
      delElement(e);
    }

  }
}
