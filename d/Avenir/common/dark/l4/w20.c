/*
w19.c is E
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"


void
create_room()
{
  set_short("old guard room");

  set_long("This small, square chamber appears to have once"
+" been a guard room of some sort.  A few signs of the former occupants"
+" are left, including several niches cut into the walls where"
+" weapons might have been stored.\n");

  add_exit(L4 + "w19","east",0);

  add_prop(ROOM_I_LIGHT,0);
  IN

  add_item(({"niche","niches"}),
	   break_string("Each of the niches seems"
+" to have been cut by a knowledgeable stonemason.  They"
+" apparently were once used to store weapons.  Now they are empty.\n",75));
  
  add_item (({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}),
	    "Very uninteresting stone.\n");
 	add_npc(MON +"ogre_kid", 2, &->equip_me());  
	add_npc(MON + "ogre_mom", 1,&->equip_me());
    add_npc(MON + "ogre_dad", 1,&->equip_me());
}
