/*
w5.c is W
w7.c is E
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
  set_short("Smooth-cut tunnel");
  set_long("This is an east-to-west section of the twisting"
+" western tunnel.  You notice that the walls here are cut fairly smooth"
+" and square, as if with great care.\n");

  add_exit(L4 + "w5","south",0);
  add_exit(L4 + "w7","east",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
}

