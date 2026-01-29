// Stalagmite room, player climbs up here from l4/n29
// Part of magic square quest.
// Made by Boriska

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"

inherit "/std/room";

void
reset_room()
{
  if (!present (VIAL_ID, this_object()))
    clone_object(VIAL)->move(this_object(),1);
}

void
create_room()
{
  set_short("on the top of stalagmite");
  set_long("You are close to the stalagmite top, luckily stalagmite's\n" +
	   "surface is quite rough, providing support for your feet.\n");
  
  add_exit (L4 + "n29", "down", 0, 10);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}

