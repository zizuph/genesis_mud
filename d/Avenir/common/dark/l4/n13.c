/*
n12.c is S
#include "/d/Avenir/farlong/farlong.h"
n20.c is W
n17.c is N
n14.c is NE
*/

inherit "/d/Avenir/inherit/room";
#include "/d/Avenir/common/dark/dark.h"


create_domain_room()
{

set_short("Round tunnel junction");
set_long("Four wide stone tunnels meet here with a large round room hewn from the stone"+" of the tunnel walls.  The air here is cool and musty, and the dust lays"+" heavily on the stone floor of the cavern.\n");

AE(L4+"n12","south",0,DIRT);
AE(L4+"n14","northeast",0,DIRT);
AE(L4+"n17","north",0,DIRT);
AE(L4+"n20","west",0,DIRT);

BLACK
IN

AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
   "Very uninteresting stone.\n");    
AI("dust", "It is thick on the floor. Your footsteps stir " +
   "it up and cloud the air.\n");

	add_npc(MON + "bat", 2);
}
