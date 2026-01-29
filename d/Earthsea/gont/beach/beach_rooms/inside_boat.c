inherit "/std/room";

#include <macros.h>

#include "default.h"

#define ISLAND 1
#define GONT 2
#define TIME_BETWEEN 1.0
#define STOPS 5
#define STAGES 20
#define CHANCE_TO_STOP 5

int dest=ISLAND;
object fisherman;
int stg=0;
int stop=0;
int alarm_h=0;

void i_am_the_fisherman(object f) {fisherman=f;}

void create_room()
{
 set_short("Inside fishing boat");
 set_long("You are inside small fishing boat. You start wondering "+
   "if it was good idea at all to sail to the island.\n");

 add_item("view","@@view");
}

string view()
{
 return "You are sailing towards "+(dest==ISLAND ?
   "island.\n" : "Gont.\n");
}

void disembark()
{
 tell_room(TO,"Boat stops near some old damaged pier.\n");
 fisherman->command("say We arrived... Be careful , karg are very "+
   "mecriless.");
 fisherman->command("say If you want me to pick you up just set up "+
   "some kind of signal i would notice and I will be right back!");
 fisherman->command("say Good luck!");
 write("You leave the boat and step onto the pier...\n");
 tell_room(find_object(ISLAND_PIER),QCTNAME(TP)+" leaves the boat and "+
   "steps onto pier.\n");
 TP->move_living("M",ISLAND_PIER);
}

void msg_alarm()
{
 string msg;

 if(stop)
  {
   stop++;
   if(stop==STOPS)
    {
     fisherman->command("say They passed us by... We are prety lucky.");
     tell_room(TO,QCTNAME(fisherman)+" starts rowing again.\n");
     stop=0;
     stg++;
     return;
    }
   return;
  }

 if(random(100)<CHANCE_TO_STOP)
  {
   stop=1;
   tell_room(TO,QCTNAME(fisherman)+" suddenly stops rowing.\n");
   fisherman->command("say Damn... I see warship ahead... be quiet! "+
     "We will have to wait till it passes by.");
   return;
  }

 stg++;

 switch(random(4))
  {
   case 0: msg="Boat sways slightly on the waves.\n"; break;
   case 1: msg="The boat is thrown aside by sudden gust of wind.\n";
           break;
   case 2: msg=QTN(fisherman,TP)+" keeps rowing , advancing the boat.\n";
           break;
   case 3: msg="You feel sick as boat rides some big waves.\n"; break;
  }

 tell_room(TO,msg);

 if(stg==STAGES)
  {
   disembark();
   remove_alarm(alarm_h);
  }
}

void start_moving()
{
 (OUTSIDE)->remove_boat();
 tell_room(find_object(OUTSIDE),"The boat starts moving away.\n");
 tell_room(TO,QCTNAME(fisherman)+" sits on the rowing bench and "+
   "starts rowing.\n");
 stg=0;stop=0;
 set_alarm(1.0,TIME_BETWEEN,&msg_alarm());
}

