/*
 * Wagon landing between Faerie and VK
 * By Finwe, May 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit FOREST_BASE;
void add_stuff();

int alarm_id;
object wagon;
string extra_line = "";

void
create_forest_room()
{
    FIXEUID;

    set_short("A forest clearing");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The clearing " +
        "looks like it was recently visited. Boot prints run off to " +
        "the north and into the forest. Wagon ruts head south into the " +
        "forest and disappear. A sign hangs from a tree branch.\n");

    set_add_valley();
    add_std_herbs("forest");   
    add_item(({"sign"}),
    "The sign is square shaped and made of metal. It hangs from a branch " +
        "and can be read for more information.\n");
    add_item(({"clearing", "forest clearing"}),
        "This is a wide open area in the forest. It has been cleared of " +
        "trees and full of wagon tracks.\n");
    add_item(({"wagon tracks"}),
        "The wagon tracks run south into the forest. They are wide and " +
        "leave ruts in the forest.\n");
    add_item(({"wagon ruts"}),
        "They are cut deep into the track that runs south into the forest " +
        "and disappear. They appear to have been made by wagons that visit " +
        "here.\n");
    add_item(({"boot prints", "boot tracks"}),
        "They are made from various boots and criss cross the clearing. " +
        "They run in all directions into the forest.\n");
    add_item(({"tracks"}),
        "There are many tracks criss crossing the clearing. You see boot tracks and wagon tracks in the ground.\n");
    
    add_cmd_item("sign", "read", "@@read_sign@@");

    reset_room();

    add_exit(FOREST_DIR + "mttrack01", "northeast");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
//    add_stuff();
}


string read_sign()
{
    return "On the sign you read this:\n" +
    "'I travel between Faerie and Krynn. If there is room in my wagon, you may pay for passage and I'll take you there. The trip can be dangerous, so I ask you pay for it. -- Kelevan\n";
} 

void
add_stuff()
{
    seteuid(getuid(this_object()));
    if(!wagon)
    {
	    wagon = clone_object(VK_SHIP_DIR + "wagon");
	    wagon->start_ship();
    }
}
