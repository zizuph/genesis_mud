/*
w10.c is W
w8.c is E
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
set_short("Clean tunnel");
set_long("The wide, clean tunnel continues here to the east and"
+" west.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");

add_exit("/d/Avenir/common/dark/l4/w8", "west",0);
add_exit("/d/Avenir/common/dark/l4/w10","east",0);

add_prop(ROOM_I_LIGHT,0);
IN

}
