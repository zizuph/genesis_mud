/*
 * 	field2.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_field();
    set_items_driver();
    set_herbs();

    set_short("A large field");
    set_long("You are following a narrow dirt path that winds through a " +
        "wide field of tall yellow grass sprinkled with colourful " +
        "wildflowers. To the north, the tumbling waters of the Diamond " +
        "River dash east through Sparkle valley on its journey to the Pen " +
        "Sea. Rising high above you, a rugged spur of the Grey Mountains " +
        "drives deep into the valley, running alongside the river. The " +
        "mountains stretch out along the western and northern horizon, " +
        "surrounding the lush fields of the valley. The path splits here, " +
        "running east towards the Dark Road, and north and west through " +
        "the fields.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field5", "north");
    add_exit(THIS_DIR + "field3", "west");
    add_exit(THIS_DIR + "field1", "east");
    add_exit(THIS_DIR + "field2", "southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "field2", "south","@@mount@@",1,1);
    add_exit(THIS_DIR + "field2", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "field4", "northwest",0,1,1);
    add_exit(THIS_DIR + "field2", "northeast","@@riv@@",1,1);

    add_item(({"mountain spur","spur","mountainside"}),
        "The rugged mountainside which juts up into the sky before you, " +
        "is the eastern end of a mountain spur that has cut through the " +
        "middle of Sparkle valley.");
    add_item(({"mountains","mountain","grey mountains"}),
        "They Grey Mountains surround the entire Sparkle valley, including " +
        "the jagged spur that juts up immediately before you to the south.");
    add_item(({"south horizon","southern horizon","southwest horizon",
            "southwestern horizon","south","southwest"}),
        "You cannot really see much to the south except a massive " +
        "spur of the Grey Mountains.\n");
    add_item(({"stream","river","diamond river","water","waters"}),
        "The rushing waters of the Diamond River rush eastward on a journey " +
        "to the Pen Sea.\n");
    add_item(({"path","dirt path","small dirt path","small path",
            "narrow path","narrow dirt path"}),
        "This small dirt path winds through the fields between the Diamond " +
        "River and the spur of the Grey Mountains that has thrust into " +
        "the valley nearby.");
    add_item(({"road","dark road","highway"}),
        "The Dark Road can be found by following the path east from here.");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "river", "diamond river"}));
}

void

init()
{
    ::init();
    init_drink();
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
/* drink_message */

/*
 * Function name:        riv
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the river in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
riv()
{
    write("The river is too wide to cross here, you will have to find a " +
        "bridge or something.\n");
    return 1;
}
/* riv */

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");
    return 1;
}
/* mount */