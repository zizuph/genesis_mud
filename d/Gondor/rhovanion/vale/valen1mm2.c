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
    set_items_oldroad();
    set_items_ford();
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("Tall and yellow, the grass which surrounds you gently " +
        "dances with every faint breeze which twirls past you. Nearby, " +
        "the rushing waters of the legendary Anduin river have cut a " +
        "massive valley through the land, following it south towards " +
        "the sea. A weary old road winds across the lands just south " +
        "of you, tumbling down from the nearby High Pass into the " +
        "Old Ford where it meets the Anduin and into a massive forest " +
        "barely visible on the eastern horizon. Looming up beside you " +
        "to the west are the massive heights of the Misty Mountains, " +
        "scratching at the sky with their snow-capped jagged peaks. " +
        "A barely visible trail here seems to crawl through the grass " +
        "south towards the road and north into the distance.\n");

    add_item(({"trail", "small trail"}),
        "A small trail is barely visible at your feet here, crawling " +
        "through the grass from north to south as if following the " +
        "river.\n");

    add_exit("/d/Shire/anduin/west/rd02", "south");
    add_exit("/d/Shire/anduin/west/rd03", "southwest",0,2,1);
    add_exit("/d/Shire/anduin/west/rd01", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen2mm2", "north",0,2);

    set_no_exit_msg(({"west","northwest"}),
        "The rough, rocky foothills of the Misty Mountains appear to " +
        "be too steep to climb in this direction.\n");
    set_no_exit_msg(({"east","northeast"}),
        "The Anduin appears to have flooded the western bank, " +
        "making travel eastward from here essentially impossible.\n");
}
