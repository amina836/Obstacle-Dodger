 #include <iostream.h>
  #include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#define MAX_RECTS 200
class Point
{


private:

  int x;
  int y;

public:
Point (){

}

Point(int m,int n){
 x=m;
 y=n;


}

void setX(int m){

 x=m;
}
void setY(int n){

y=n;
}

int getX(){

 return x;

}
int getY(){

 return y;
}

};




class Rect
{

private:
 Point ul;
 Point lr;

 public:
 Rect():ul(),lr(){

 }

 Rect(int x1, int y1, int x2,int y2):ul(x1 ,y1),lr(x2,y2){


 }

  void draw(){

 setcolor(RED);
 rectangle(ul.getX(),ul.getY(),lr.getX(),lr.getY());
   setfillstyle(SOLID_FILL,RED);
   floodfill((ul.getX()+lr.getX())/2,(ul.getY()+lr.getY())/2,RED);
 }

 void moveDown(int step){

  ul.setY(ul.getY()+step);
  lr.setY(lr.getY()+step);

 }


  float isOffScreen(){
   return ul.getY()>= getmaxy();
  }
	 int getX1(){ return ul.getX();}
	 int getY1(){ return ul.getY();}
	 int getX2(){ return lr.getX();}
	 int getY2(){ return lr.getY();}
 };

 class Circle
 {
 private:
 Point center;
 int radius;

 public:
 Circle():center(){
 radius=0;

 }

 Circle(int m,int n,int r):center(m,n){
 radius=r;

 }


 void draw (){
 setcolor(YELLOW);
 circle(center. getX(),center.getY(),radius);
 setfillstyle(SOLID_FILL,YELLOW);
 floodfill(center. getX(),center.getY(),YELLOW);
 }



 void moveCircle(char dir){
  int screenWidth=getmaxx();
  int screenHeight=getmaxy();

  if(dir=='w'&& center.getY()-radius-20>=0){center.setY(center.getY()-20);
  }
  if(dir=='s'&& center.getY()+radius+20<=screenHeight){center.setY(center.getY()+20);}
  if(dir=='a'&& center.getX()-radius-20>=0){center.setX(center.getX()-20);}
  if(dir=='d'&& center.getX()+radius+20<=screenWidth){center.setX(center.getX()+20);}


 }
	 int getX()
	 {return center.getX();
	 }

	  int getY()
	 {return center.getY();
	 }

	  int getRadius()
	 {return radius;
	 }

 };

   class Picture
   {
	 private:


	 int cNum;
	 int rectCount;

	 Rect  rects[MAX_RECTS];
	 Circle *pCircles;


	 public:

	 Picture()
	 {

	rectCount=0;
	cNum=0;

	pCircles=NULL;
	}

	Picture(int cn,Circle *pC)
	{

	cNum=cn;


	pCircles=pC;

	}

	 void setCircles(int ,Circle *);


	 void paint();
		void movePic(char dir);
		void moveRects(int step ,int&score);


		void addRect(const Rect&rect){
		if (rectCount <MAX_RECTS){
		rects[rectCount++]=rect;
		}
		}
		void removeOffScreenRects(int &score){

		 int j=0;
		 for(int i=0; i<rectCount;i++){

		  if(!rects[i].isOffScreen()){
		   rects[j++]=rects[i];
		  }
		  else{
		   score++;
		  }


		 }
		   rectCount=j;
		}

		//collision

		int checkCollision(){


		 for(int i=0;i<rectCount;i++){
		  int circleX=pCircles[0].getX();
		  int circleY=pCircles[0].getY();
		  int radius= pCircles[0].getRadius();

		  int rectX1=rects[i].getX1();
		  int rectY1=rects[i].getY1();
		  int rectX2=rects[i].getX2();
		  int rectY2=rects[i].getY2();


		  if(circleX + radius >rectX1 &&  circleX-radius<rectX2 && circleY +radius >rectY1 &&circleY-radius <rectY2){
		  return 1;
		  }



		 }
		 return 0;

		}
	 };


	   void Picture::setCircles(int cn,Circle *cptr)
	  {

	   cNum=cn;
	   pCircles=cptr;
	   }



	  void Picture::paint ()
	  {

		 int i;


	  for( i=0;i<rectCount;i++){

	   rects[i].draw();
	  }

	 for( i=0;i<cNum;i++){

	   pCircles[i].draw();
	   }
	  }
	void Picture:: movePic(char dir){


		 for(int i=0;i<cNum;i++){

	   pCircles[i].moveCircle(dir);
	  }



   }
	void Picture:: moveRects(int step, int &score){
	 for (int i=0;i<rectCount;i++){

	  rects[i].moveDown(step);

	 }
	 removeOffScreenRects(score);
	}


int main(){

 int gd =DETECT,gm;
 initgraph (&gd,&gm,"D:/BGI/");
	 Picture myPic;
	   srand(time(0)); //intial random speed

   Circle cArr[3]={Circle(300,420,6)};

   int spawnInterval=10;
   int frameCounter=0;
   int step=20;
   int score=0;

  myPic.setCircles(1 ,cArr);



	  while(1){

	  if(frameCounter%spawnInterval==0){

	   int x1=rand()%(getmaxx()-50);
	   int width =100+rand()%50;
	   int height=20+rand()%20;
	   myPic.addRect(Rect(x1,0,x1+width,height));




	  }
	  cleardevice();
	  char scoreText[20];
	  sprintf(scoreText,"Score :%d ",score);
	  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	  outtextxy(5,5,scoreText);

	  myPic.paint();
	  myPic.moveRects(step,score);

	  if(myPic.checkCollision()){
	  cleardevice();
	  setcolor(RED);

	  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	  outtextxy(getmaxx()/2-100,getmaxy()/2,"GAME OVER");
	   setcolor(WHITE);
	  outtextxy(230,150,scoreText);
	  delay(2000);


		cleardevice();
		outtextxy(getmaxx()/2-280,getmaxy()/2-20,"press R to play again or Q TO  quite");


		  while(1){

		  if(kbhit()){
		  char choice=getch();
		  if(choice =='r' || choice =='R'){
		  myPic=Picture();
		  myPic.setCircles(1,cArr);
		  frameCounter=0;
		  score=0;

		  break;
		  }
		   else if(choice=='q'|| choice=='Q'){
		   closegraph();
		   return 0;
		   }
		   }
		   }
		   }

  delay (50);
	  frameCounter++;
	

	  if(kbhit()){
	   char key =getch();

	   if (key==13){
					break;
						  }


		myPic.movePic(key);

		cleardevice();

	  }


	  }

  getch();
  closegraph();
  return 0;


}
