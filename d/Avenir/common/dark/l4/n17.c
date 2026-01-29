/*
n13.c is S
n18.c is N
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{

set_short("Northbound passage");
set_long("The wide northbound tunnel continues here, leading north into further darkness and south into what appears to be a large cavern.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
   "Very uninteresting stone.\n");  
add_exit("/d/Avenir/common/dark/l4/n13","south",0);
add_exit("/d/Avenir/common/dark/l4/n18","north",0);
 
	add_npc(MON + "rat", 1);
BLACK
IN

}
