/* 
* /d/Gondor/lorien/dimril/road6.c
*Along of the road from the the mountain towards Great gates of Moria in 
*one direction and down past Dimril Stair and Mirrormere, in the other, 
*towards the forest and Lothlorien
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
    set_long("Here the " +VBFC("light_type")+ " reflects of the surface of " +
        "a pond or mere to the north. This mere lies between two " +
        "mountains. To reach it you must first travel to the southeast. " +
        "From here the road continues upwards towards the mountain top. " +
        "To the east the slope of the land lessens as you approach the " +
        "valley below.\n"); 

    add_exit(DIMRILL_DIR_RM + "road5", "northwest", 0, 4, 0);	 
    add_exit(DIMRILL_DIR_RM + "road7", "east", 0, 2, 0);		
//add body of water	 
// add mereafar
// add orc patrols through here
}