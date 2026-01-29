/*
w3.c is W
w1.c is S
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
 


void
create_room()
{
  set_short("eastern tunnel");
  set_long("The spacious eastern tunnel bends here, heading"
+" to the southwest and southeast. The rough stone walls are"
+" featureless and uninteresting. You can hear rats nearby,"
+" and a musty odor fills your nostrils.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", 
    "passage", "passageway"}), "Very uninteresting stone.\n"); 

  add_exit(L4 + "n2","southwest",0);
  add_exit(L4 + "w3","southeast",0);

  add_prop(ROOM_I_LIGHT,0);
  IN;
 	add_npc(MON +"ogre_kid", 2, &->equip_me());
}




