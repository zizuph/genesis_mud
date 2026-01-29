/* 
* /d/Gondor/lorien/dimril/road5.c
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

    set_short("Along a mountain road");
    set_long("Along a mountain road. Further up the mountain to the west " +
        "lies the Dimril gate to Moria. Downward and to the east a vale " +
        "can be seen. The vale steepens and narrows to the north, where " +
        VBFC("light_type")+ 
        " reflects off the surface of a distant body of water. " +
        "There are birch and fir trees along the road.\n"); 

    add_exit(DIMRILL_DIR_RM + "road4", "northwest", 0, 4, 0);	 
    add_exit(DIMRILL_DIR_RM + "road6", "southeast", 0, 2, 0);
//add body of water	 
// add mereafar
// add orc patrols through here
}