/*
w1.c is N
w17.c sw SW
*/


inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"
 

void
create_room()
{
  set_short("Western tunnel");
  set_long("The western tunnel is quite large here, and"
+" clear of obstacles.  There is little of interest here, save the"
+" occasional stalagmite.  The passage leads north and southwest from this"
+" position.\n");

  add_exit(L4 + "w1","north",0);
  add_exit(L4 + "w17","southwest",0);

  AI(({"stalagmite","stalagmites"}), 
   "The stalagmites poke up from the ground here.  They are " +
    "conical mineral formations deposited by dripping " +
    "water.  They look like miniature mountains.\n");
  add_prop(ROOM_I_LIGHT,0);
  IN;
    add_npc(MON +"rat", 2);
}


