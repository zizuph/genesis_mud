/* 
Citadel, officer room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;
object ob2;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, officers room");
   set_long("You find yourself in a plain room with few noticeable "+
      "items in it except a table and two beds. This is where the "+
      "officers live when they are not on duty, earning their pay.\n");
   
   add_exit(CENTRAL(citadel/entrance),"southwest",0,-1,-1);
   
   add_item ("table","Its a wooden table. Nothing special about "+
      "it at all.\n");
   
   add_item (({"bed","beds"}),"They are made of wood and "+
      "have nothing in them of interest. All they do is to give "+
      "the officers a place to sleep when being off duty.\n");
   
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_officer");
      ob1 -> arm_me();
      tell_room(TO, "An officer enters the room to rest after duty.\n");
      ob1 -> move_living("M", TO);
      
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_officer");
      ob2 -> arm_me();
      ob2 ->move_living("xxx",TO);
      ob2 -> team_join(ob1);
   }
   return;
}


