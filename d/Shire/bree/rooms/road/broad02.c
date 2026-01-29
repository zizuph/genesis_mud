/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types
 
#include "defs.h"

inherit ROAD_BASE;
 
void
create_road_room()
{

    set_areadesc("large");
    set_area("busy");
    set_areaname("crossroads");
    set_land("Bree");

    add_bree_desc("Everyone passes this way as they go through Bree. " +
        "The road branches off and runs north while the Great East " +
        "road bends runs south through Bree, west to the West " +
        "Gate, and east to the famous Prancing Pony.\n");
    add_item(({"west gate", "gate", "city gate"}),
        "The gate opens during the day letting travellers in " +
        "and out and closes at night keeping ruffians out. It " +
        "is made of heavy timbers and with iron bands.\n");
    add_item("timbers",
        "The timbers are used in gate construction. They are " +
        "tall and smooth,\n");
    add_item(({"bands", "iron bands"}),
        "The iron bands are thick and hold the timbers together " +
        "in the city gates.\n");
    add_item(({"prancing pony", "prancing pony inn", "the prancing pony", 
            "the prancing pony inn", "inn"}),
        "The famous Prancing Pony inn stands to the west. It is a "+
        "large building where travellers as well as townsfolk gather " +
        "to share a drink or rest from their travels.\n");
    
    clone_object("/d/Genesis/obj/donation/column")->move(this_object(), 1);
    set_add_ger();
    
    add_exit(ROAD_DIR + "broad06", "north");
    add_exit(ROAD_DIR + "broad03", "south");
    add_exit(ROAD_DIR + "broad01", "west");
    add_exit(TOWN_DIR + "innyard", "east");
}
