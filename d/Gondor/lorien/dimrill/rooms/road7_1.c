/* 
* /d/Gondor/lorien/dimril/p7.c
* Along of the road from the the mountain towards Great gates of Moria in 
* one direction and down past Dimril Stair and Mirrormere, in the other, 
* towards the forest and Lothlorien.  Here Mirrormere is just to the north.
*
*Mona 2020
*/
#pragma strict_types

#include "../../lorien_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit LORIEN_STD_DIR + "dimrill_base";

void 
create_dimrill_room()
{
    set_items_all_dimrill();
    set_items_near_dimrill();
    set_items_mereafar();
    set_tells_dimrill();

    set_short("Along a road between mountain and valley.");
    set_long("Here the " +VBFC("light_type")+ " reflects off the surface of " +
        "a pond or mere to the north. This mere lies between two " +
        "mountains. Just north of here there is some sort of pillar or " +
        "stone statue. " +
        "From here the road continues upwards towards the mountain top. " +
        "To the east the slope of the land lessens as you approach the " +
        "valley below.\n"); 

    add_item( ({"pillar", "stone", "statue", "stone statue", 
        "stone pillar"}),
        "You can't see much more than that from here.  Try going " +
        "closer to get a better look.\n");

    add_exit(DIMRILL_DIR_RM + "road6", "west", 0, 3, 0);	 
    add_exit(DIMRILL_DIR_RM + "road8", "south", 0, 1, 0);		 
    add_exit(MERE_DIR_RM + "durins_stone", "north", 0, 1, 0);
//add body of water	 
// add mereafar
// add orc patrols through here
}