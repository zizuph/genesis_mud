/*n1.c is S
n13.c is N
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{

set_short("Tunnel");
set_long("The rough stone tunnel is wide and spacious here, with room for several to walk abreast. It continues on into darkness to the north and south.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
   "Very uninteresting stone.\n"); 
add_exit("/d/Avenir/common/dark/l4/n1","south",0);
add_exit("/d/Avenir/common/dark/l4/n13","north",0);

BLACK
IN

add_npc(MON + "rat", 3);
}
