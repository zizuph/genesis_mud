/*
w16.c is NE
w18.c is W
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("Western tunnel");
  set_long("The well-kept western tunnel goes further on here,"
+" heading west and northeast.  A burnt-out torch hangs securely fastened to"
+" the stone wall, and there are a few stalagmites here.\n");

  add_exit(L4 + "w16","northeast",0);
  add_exit(L4 + "w18","west",0);
  
  
  AI(({"stalagmite","stalagmites"}), 
     "The stalagmites poke up from the ground here.  They are " +
     "conical mineral formations deposited by dripping " +
     "water.  They look like miniature mountains.\n");
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
 	add_npc(MON + "bat", 1); 
	add_npc(MON +"rat", 2);

}

