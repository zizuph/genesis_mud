#include <macros.h>

#include "defs.h"

inherit TRICKSTER_STD_ROOM;

#define TRICK_SIDE 1
#define GONT_SIDE 2
#define MOVING 3
#define TIME_BETWEEN_MSG 5.0

int loc=TRICK_SIDE;
string dest="none";
int progress=0;
int alarm_h;
object wagon;

int query_moving() {return (loc==MOVING ? 1 : 0);}

void i_am_the_wagon(object wag) {wagon=wag;}

object query_wagon() { return wagon; }

void create_room()
{
 set_short("Inside a wagon");
 set_long("@@wagon_long");

 add_item(({"seat","seats"}),"Seats are as rusty as wagon and don't "+
   "look too comfortable. You decide not to sit on them.\n");
 add_item(({"wall","walls"}),"Rusty walls , as rusty and old as "+
   "wagon.\n");
 add_item("door","@@door_desc");
 add_item("lever","You'll have to pull it if you want to get this "+
   "piece of junk moving.\n");

 add_cmd_item("lever","pull","@@pull_lever");

 add_exit(TRICK_TUNNEL,"out");
}

string wagon_long()
{
 string res;

 res="You are inside of rusty old wagon. You see couple of seats "+
   "near the walls , small door leads out. Large lever placed on "+
   "the wall.\n";
 if(loc==MOVING) res+=" Wagon is moving with rumbling noice.\n";

 return res;
}

string door_desc()
{
 string res;

 res="Door leads outside of wagon. You look outside and find out "+
   "you are ";
 switch(loc)
  {
   case TRICK_SIDE: res+="at Tricksters side of the tunnel.\n"; break;
   case GONT_SIDE: res+="at Gont side of the tunnel.\n"; break;
   case MOVING: res+="moving through the tunnel towards "+dest+".\n";
  }

 return res;
}

void move_mesg()
{
 string msg;

 progress++;
 switch(progress)
  {
   case 1: msg="With low rumbling noice wagon starts to move.\n"; break;
   case 2: msg="The light seems to dim as wagon continues to move "+
     "down the tunnel.\n"; break;
   case 3: msg="Wagon keeps moving and you suddenly covered with "+
     "total darkness.\n"; break;
   case 4: msg="Wagon keeps rolling down the tunnel.\n"; break;
   case 5: msg="You see some light source ahead.\n"; break;
   case 6: msg="Wagon starts to slow down. You are close to the "+
     "destination.\n"; break;
   case 7: msg="Wagon suddenly stops as it reaches the end of the "+
     "tunnel.\nYou may leave the wagon now.\n"; break;
  }

 tell_room(TO,msg);
 if(progress==7)
  {
   remove_alarm(alarm_h);
   if(dest=="Gont") wagon->move(find_object(GONT_TUNNEL)); 
   else wagon->move(find_object(TRICK_TUNNEL)); 
   tell_room(ENV(wagon),"With low rumbling noice "+wagon->short()+
     " rolls in.\n");
   if(dest=="Gont") loc=GONT_SIDE; else loc=TRICK_SIDE;
   if(loc==GONT_SIDE) add_exit(GONT_TUNNEL,"out");
   else add_exit(TRICK_TUNNEL,"out");
   dest="none";
  }
}

void start_moving()
{
 if(!wagon) wagon=(TRICK_TUNNEL)->give_me_wagon();

 remove_exit("out");
 progress=0;
 tell_room(ENV(wagon),C(wagon->short())+" starts moving away.\n");
 wagon->move(find_object(TUNNEL));
 if(loc==TRICK_SIDE) dest="Gont"; else dest="Tricksters";
 loc=MOVING;
 alarm_h=set_alarm(1.0,TIME_BETWEEN_MSG,&move_mesg());
}

int pull_lever()
{
 if(loc==MOVING)
  {
   write("But you already moving!\n");
   say(QCTNAME(TP)+" looks kinda silly as "+PRO(TP)+" tries to pull "+
     "the lever , as wagon is already moving.\n");
   return 1;
  }

 write("You pull the lever.\n");
 say(QCTNAME(TP)+" pulls the lever.\n");
 start_moving();
 return 1;
}

