/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("ancient highway");
    set_area("north of");
    set_areaname("Bree");
    set_land("Eriador");

    set_extraline("The highway runs north and south. A road meets the " +
        "it and branches off to the east. Claw prints are " +
        "evident in the grass, and a fallen sign is half buried " +
        "in the dirt.\n");
    add_item("sign", "The sign is half buried in the dirt. " +
        "Some writing is still visible even though it's dirty.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    set_add_outside_hedge();
    set_add_dike();
    set_add_claw_prints();
    set_add_nroad();

    add_exit(ROAD_DIR + "nroad07", "north");
    add_exit(ROAD_DIR + "nroad05", "south");
    add_exit(ROAD_DIR + "road02", "east");

}

string
read_sign()
{
    return "On the sign you can barely make out the following:\n"+
        "\t________________\n"+
        "\t|               |\n"+
        "\t|  /\\           |\n"+
        "\t|  ||   F . R N |\n"+
        "\t|               |\n"+
        "\t|  ==>  . . E  /\n"+
        "\t|_____________|\n\n";
}

