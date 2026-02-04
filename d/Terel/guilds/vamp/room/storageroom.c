/*
 * Storage room in the vampire manor
 * Louie 2006
 *
 * * Lucius May 2009: The recentish secret passageway is removed.
 * 	/d/Terel/dark/ (and thus dark/hob) aren't part of Terel any
 * 	longer and there are plans to do something productive with them
 * 	that precludes yet another secret vampire trick.
 */  
#pragma strict_types
#include "defs.h"
#include "../guild.h";

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("empty storage room");
    set_long("This large room was once used to store a multitude "+
        "of food to be used in the kitchen northeast of here.  "+
        "It is now completely empty, with dozens of bare shelves "+
        "lining the walls.  "+
        "The entry hall of the manor lies to the west.  "+
        "\n");

    add_exit("entry.c", "west");
    add_exit("kitchen.c", "northeast");

    add_item(({"shelf","shelves","bare shelf","bare shelves",
        "walls","wall"}),
        "The shelves lining the walls of this room are completely "+
        "empty, yet strangely free of any dust or decay.\n");
#if 0
    add_cmd_item(({"shelf","shelves","bare shelf","bare shelves",
        "walls","wall"}), ({"push", "pull", "move"}), "@@do_shelf");
#endif

    add_item(({"northeast","ne","kitchen"}),
        "The kitchen lies to the northeast.\n");

    add_item(({"west","hall","entry hall"}),
        "The entry hall of the manor lies to the west.\n");


}
#if 0
int
do_shelf()
{
    if (!IS_VAMP(TP) && !IS_BG(TP))
    {
        notify_fail(capitalize(query_verb()) +" what?\n");
        return 0;
    }       

    TP->catch_msg("There is a whoosh of air as the shelves swing "+
        "outward.\n");
    say(QCTNAME(TP)+" steps into the darkness behind the shelves!\n");
    TP->move_living("M", "/d/Terel/dark/hob/n7", 1, 0);
    return 1;
}
#endif
