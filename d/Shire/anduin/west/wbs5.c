/*
 * western riverbank of the river Anduin
 * By Finwe, June 2001
 *
 * Added an exit to Dol Guldur
 * Varian - November 2020
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;

void create_vale_room()
{
    set_area("along the riverbank of");
    set_areaname("the Anduin");
    set_land("the Vales of the Anduin");
    set_vbfc_extra(vale_desc7);
    set_areatype(0);
    add_my_desc("An ancient path breaks off to the northeast, " +
        "cutting into Mirkwood forest towards the ruins of " +
        "Dol Guldur.\n");

    add_item( ({"city", "dol guldur", "ruins"}),
        "Somewhere to the northeast, deep into Mirkwood forest, " +
        "are the ruins of Dol Guldur.\n");
    add_item( ({"forest", "mirkwood", "mirkwood forest"}),
        "Tall black trees, dark and forboding, rise up along " +
        "the eastern horizon. This is the legendary Mirkwood " +
        "forest.\n");

//    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("A frog croaks in the reeds nearby.");
    add_room_tell("A fish jumps in the river.");
    add_room_tell("Something slaps the water with its tail.");
    add_room_tell("Quack, quack, quack.");
    add_room_tell("An animal slides into the water.");

    set_add_river_close();
    set_add_misty_near();

    reset_shire_room();

    add_exit(WEST_DIR + "wbs4", "north");
    add_exit("/d/Gondor/rhovanion/dolguldur/path1", "northeast", "@@block@@");
    add_exit("/d/Shire/common/gondorlink2", "south");

 
}

void reset_shire_room()
{
}

int
block()
{
    if (this_player()->query_wiz_level()) return 0;
    write("The road to Dol Guldur is not open yet!\n");
    return 1;
}