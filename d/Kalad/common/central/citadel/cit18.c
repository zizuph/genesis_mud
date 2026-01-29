/*      /d/Kalad/common/caravan/shop/clmerchant
 *      Created by:     Korat, Feb 14. 1995   
 *      Purpose:        
 *      Modified:       
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
   set_short("Citadel, office");
   set_long("You see a single table here in this office with a single chair "+
      "next to it. Several books and accounts lies spread out on it in a "+
      "chaotic order, because some kind of order must be in this system of "+
      "sheets or else the official working here would soon be out of a job.\n");

   add_item("table","The table is of plain oak and contains several books "+
      "and sheets.\n");
   add_item("chair","The chair is a simple construction of wood with one "+
      "simple function in life; to be sitted in.\n");
 
   add_exit(CENTRAL(citadel/cit13),"southeast",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_official");
      ob1 -> arm_me();
      ob1 -> move_living("A human hurries into the room.", this_object());
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_official");
      ob2 -> arm_me();
      ob2 -> set_random_move(20);
      ob2 -> move_living("A worker comes in carrying some notes.", this_object());
   }
}
