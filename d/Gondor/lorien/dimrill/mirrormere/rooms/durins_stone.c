/* 
* /d/Gondor/lorien/dimril/mere/room/durins_stone.c
* the botom edge of Mirrormere.  This is where Durins Stone is
* there should be a tour added here. It is north off  of the road 
* between the Great gates of Moria to the northwest and the forest 
* of Lothlorien in the east.
*
* Mona 2020
*/
#pragma strict_types

#include "../../../lorien_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit LORIEN_STD_DIR + "dimrill_base";


void 
create_dimrill_room()
{
    set_items_all_dimrill();
    set_items_near_dimrill();
    set_tells_dimrill();
    set_items_mirrormere();
    set_items_sunnymere();
    set_herbs_sunnymere();

    set_short("At the opening of a deep valley.");
    set_long("At the opening of a vale. Here the " + VBFC("light_type") +
        " shimmers on of the surface of a large shallow pond. The water " +
        "stretches to the north. There is a narrow sward of green around " +
        "the water's edge. To either side of the mere, the mountains climb " +
        "sharply up, shadowing the pond so that it grows more shady as it " +
        "extends further north. Where you currently stand, the " +
        VBFC("light_type") + " is enough to light the reflective surface of " +
        "the waters, and you can see the " + VBFC("day_desc") +
        " sky in perfect detail on the mirrored surface.\n");

    add_exit(DIMRILL_DIR_RM + "road7", "south", 0, 1, 0);
//    add_exit(MERE_DIR_RM + "mere5", "northwest", 0, 1, 0);
//    add_exit(MERE_DIR_RM + "mere6", "northeast", 0, 1, 0)
// add object pillar
// add body of water	 
// add mereafar
// add orc patrols through here
// add tour
}
