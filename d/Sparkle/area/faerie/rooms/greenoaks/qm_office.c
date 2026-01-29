/*
 * Basic indoor room of Green Oaks
 * By Finwe, August 2004
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;

static object menerial;

void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Office of the Chief Delegate");
    set_long("This is the " + short() + ". It is very clean and organized. " +
        "A large table sits in the middle of the room, with papers and " +
        "documents stacked neatly on it. This is where the Chief Delegate " +
        "receives visitors and conducts her business.\n");



    set_add_dome();

    add_item(({"buildings"}),
        "You can't examine any buildings since you're indoors.\n");
    add_item(({"building"}),
        "This is the inside of the " + short() + ".\n");
    add_item(({"papers", "documents"}),
        "These are reports for the Chief Delegate. They come from all over and are stacked neatly on the table.\n");
    add_item(({"desk", "table"}),
        "The table is simple and made of wood. It has slender legs that curve out and then narrows downward to the ground. The table is polished to a honey color. There is a sign on the desk for you to read.\n");
    
    add_item("sign", "It is square shaped with some word written on it. You can probably read the sign to see what it says.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");    

    set_add_arch("There is one that leads outside to the park.");

    add_exit(GO_DIR + "park07", "north");

}

void reset_room()
{
    if (!menerial)
        menerial = clone_object(NPC_DIR + "qm");
        menerial->move(this_object());

}

void
init()
{
    ::init();

}


string read_sign()
{
    return "In fine elven letters you read the following on the sign:\n" +
    "This is the office of the Chief Delegate of Green Oaks. If you have been summoned here, please leave your report on the desk.\n\n" +
    "For those interested, there are various reports that need to be gathered. If you are interested, you may <ask elf task>. If she has any, she will tell you to <accept task> to do it.\n\n"+
    "Once you have finished, return here and <give note to elf> to receive reward. Be sure you give the note to right elf in case there is a crowd here, so it is recommended you introduce youself to her and give give the note to her by name.\n\n" +
    "The tasks are easy and shouldn't take too much of your time, and you will be rewarded for doing them.\n";
}
