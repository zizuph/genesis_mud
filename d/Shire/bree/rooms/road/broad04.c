/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;

object dwarf;

void
create_road_room()
{

    set_areadesc("large");
    set_area("busy");
    set_areaname("road");
    set_land("Bree");

    add_bree_desc("Many houses line the Great East Road. Shallow " +
        "grooves have been cut into the road by carts and wagons " +
        "over the centuries. The road runs northwest and southeast " +
        "through Bree.\n");

    set_add_houses();
    set_add_ger();
    reset_shire_room();

    add_exit(ROAD_DIR + "broad03", "northwest");
    add_exit(ROAD_DIR + "broad05", "southeast");

}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(dwarf))
    {
        dwarf = clone_object(NPC_DIR + "trav_dwarf");
        dwarf->move(TO);
        dwarf->set_restrain_path("/d/Shire/bree");
        dwarf->set_random_move(2);

    }
}
