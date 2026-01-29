/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit ROAD_BASE;

object hobbit;

void
create_road_room()
{
    set_areadesc("quiet");
    set_area("busy");
    set_areaname("road");
    set_land("Bree");

    add_bree_desc("The road is less travelled here. Quiet hobbit " +
        "holes, lining the road to the east, are surrounded by pretty " +
        "gardens. A stone wall runs along the west side of the road.\n");

    set_add_hobbit_holes();
    set_add_outside_smiths();
    set_add_hill();
    reset_shire_room();

    add_exit(ROAD_DIR + "broad22", "north");
    add_exit(ROAD_DIR + "broad20", "south");
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(hobbit))
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(CITIZEN);
        hobbit->set_power(100);
        hobbit->move(TO);
        hobbit->set_restrain_path("/d/Shire/bree");
        hobbit->set_random_move(2);
    }
}
