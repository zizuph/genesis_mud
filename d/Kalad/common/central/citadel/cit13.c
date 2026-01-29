/* 
Citadel, dining room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;

create_room()
{
   ::create_room();
   INSIDE;
   hear_bell = 2;
   set_short("Citadel, office");
   set_long("You see a large desk here in this office with a single chair "+
      "next to it. Several books and accounts lies spread out on it in a "+
      "neat order, showing that the man working here likes to have control. "+
      "You see several exits fanning out northwards into other offices, and "+
      "you notice that the desk is turned towards them as a centre in a "+
      "panoptical structure. A door to the east leads into what looks like "+
      "a mess room from here.\n");
   
   add_item("desk","The desk is of plain oak and contains several books "+
      "and sheets, all neatly arranged.\n");
   add_item("chair","The chair is a solid construction of wood with one "+
      "simple function in life; to be sitted in.\n");
   
   add_exit(CENTRAL(citadel/cit16),"northeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit17),"north",0,-1,-1);
   add_exit(CENTRAL(citadel/cit18),"northwest",0,-1,-1);
   add_exit(CENTRAL(citadel/cit14),"east",0,-1,-1);
   add_exit(CENTRAL(citadel/cit6),"south","@@go_south@@",-1,-1);
   
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_cleric");
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
}

go_south()
{
   write("You start to walk, and soon the hallway turn to the west.\n\n");
}

