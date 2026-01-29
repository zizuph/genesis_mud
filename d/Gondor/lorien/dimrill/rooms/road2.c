/* 
* /d/Gondor/lorien/dimril/road2.c
*The start of the road from the stairs outside the Great gates of Moria
*down past Dimril Stair and Mirrormere, towards the forest and Lothlorien
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

    set_short("A curve in the road");
    set_long("The way turns and opens up. To the west steps climb upwards, " +
        "towards the entrance to Moria. Looking down and to the east a dale " +
        "can be seen in the distance, where " + VBFC("light_type")+ 
        " reflects off the surface of a body of water. There are birch and " +
        "fir trees along the road.\n"); 

    add_exit(DIMRILL_DIR_RM + "road1", "west", 0, 4, 0);	 
    add_exit(DIMRILL_DIR_RM + "road3", "south", 0, 2, 0);		
        
// add mereafar
// add orc patrols through here
}