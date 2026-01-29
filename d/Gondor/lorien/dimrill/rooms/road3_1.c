/* 
* /d/Gondor/lorien/dimril/road3.c
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
    set_tells_dimrill();
    set_items_fauna_1();

    set_short("Along a mountain road");
    set_long("Along a mountain road. Upwards from here lies the Dimril " +
        "gate to Moria. Downward from here a dale can be seen, in which " +
        "the " + VBFC("light_type")+ " reflects off the surface of a body " +
        "of  water in the distance. There are birch and fir trees along " +
        "the road.\n"); 
        
    add_exit(DIMRILL_DIR_RM + "road2","north",0,4,0);	 
    add_exit(DIMRILL_DIR_RM + "road4","southeast",0,2,0);
//add body of water	 
// add mereafar
// add orc patrols through here
 }