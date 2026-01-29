/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";


void 
create_vale_room()
{
    set_items_vale();
    set_items_west();
    set_items_mist();
    set_herbs_3();
    
    set_short("Vale of the Anduin");
    set_long("Gentle breezes push the tall yellow-green grass into " +
        "a wild dance, swirling all around you. While just to the " +
        "east, the rushing roar of the great Anduin river tumbles " +
        "across the vale as the river rushes away southward. " +
        "The fields of grass and wildflowers tumble down over the " +
        "rugged foothills which march up towards the jagged " +
        "peaks of the Misty Mountains as they pierce the sky above. " +
        "Far in the distance, covering the eastern horizon, you can " +
        "spy the mighty mass of the infamous Mirkwood forest. " +
        "A barely visible trail here seems to crawl through the grass " +
        "south towards the road and north into the distance.\n");

    add_item(({"trail", "small trail"}),
        "A small trail is barely visible at your feet here, crawling " +
        "through the grass from north to south as if following the " +
        "river.\n");

    add_exit(VALE_DIR + "valen1mm2", "south",0,2);
    add_exit(VALE_DIR + "valen3mm2", "north",0,2);

    set_no_exit_msg(({"west","northwest", "southwest"}),
        "The rough, rocky foothills of the Misty Mountains appear to " +
        "be too steep to climb in this direction.\n");
    set_no_exit_msg(({"east","northeast", "southeast"}),
        "The Anduin appears to have flooded the western bank, " +
        "making travel eastward from here essentially impossible.\n");
}
