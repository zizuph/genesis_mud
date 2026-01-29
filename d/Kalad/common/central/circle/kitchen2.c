/*
A house for a simple family along the circle street
by Korat
mars 1995
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

int recently_searched;


void
create_room()
{
   ::create_room();
   hear_bell = 2;
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_short("a kitchen");
   set_long(
      "This kitchen smells like ... like your own mothers "+
      "kitchen. The aroma of fresh-baked bread whifts into your nostrils, "+
      "making your mouth water. When you look around, you "+
      "see a wooden bench, a bucket of water and a small "+
      "oven that still radiates some heat.\n");
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(circle/house2),"northeast",0,-1,-1);
   
   add_item("oven","Its a black oven that is warm to the touch.\n");
   add_item("bench","Its a plain wooden bench that is used to "+
      "prepare food on.\n");
   add_item("bucket","Its a bucket filled with water.\n");
   
   
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   recently_searched = 0;
}
void
init()
{
   ::init();
   add_action("search_oven","search");
}
int
search_oven(string str)
{
   if(!str || str != "oven")
      return 0;
   if(recently_searched)
      {
      write("You find nothing save for a few crumbles of bread.\n");
      return 1;
   }
   write("You start to search the oven.\n");
   say(QCTNAME(TP)+" starts to search the oven.\n");
   set_alarm(5.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You find a fresh-baked bread inside the oven. Ahhh, "+
      "it smells wonderful!\n");
   say(QCTNAME(TP)+" takes something from the oven.\n");
   clone_object("/d/Kalad/common/central/obj/bread")->move(TP);
   return;
}
