/* Barracks */
/* Made by Korat 100195 */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"


void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Barracks");
   set_long("This plain hallway can lead you two ways: either downstairs "+
      "again or to walk along the plain carpet on the floor "+
      "towards a door in the southern end.\n");
   add_item("carpet","It's a plain carpet that soften the sounds of your "+
      "feet when you walk on it. They must appreciate silence here.\n");
   
   add_exit(CENTRAL(barracks/barracks2),"down",0,-1,-1);
   clone_object("/d/Kalad/common/central/doors/barracks_door1")->move(TO);
   
   
}

