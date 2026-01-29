/*
n19.c is N
n17.c is S
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
set_short("Northbound passage");
set_long("The passageway continues farther, leading both north" +
   " and south from here.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");

add_exit("/d/Avenir/common/dark/l4/n17","south",0);
add_exit("/d/Avenir/common/dark/l4/n19","north",0);

BLACK
IN

}
