/* 
Citadel, guards room.
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
   set_short("Citadel, guards room");
   set_long("You find yourself in a plain room with few noticeable "+
      "items in it except a table and some beds. This is where the "+
      "guards live when they are not on duty, earning their pay. "+
      "You see two similar rooms to the southeast and east.\n");

   add_exit(CENTRAL(citadel/cit2),"east",0,-1,-1);
   add_exit(CENTRAL(citadel/cit4),"southeast",0,-1,-1);

   add_item ("table","Its a wooden table. Nothing special about "+
      "it at all. Some cards lies scattered out on it.\n");

   add_item ("cards","When you count them, you notice that all 52 "+
      "of them are there....how odd.\n");

   add_item (({"bed","beds"}),"They are made of wood and "+
      "have nothing in them of interest. All they do is to give "+
      "the guards a place to sleep when being off duty.\n");

   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob1 -> arm_me();
      ob1 -> move_living("An officer arrives.", this_object());
      
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob2 -> arm_me();
      ob2 -> move_living("An officer arrives.", this_object());
      ob2 -> team_join(ob1);
   }
   return;
}


