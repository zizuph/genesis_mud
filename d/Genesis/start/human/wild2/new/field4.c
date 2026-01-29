/*
 * 	field4.c			Styles.   3 Mar 1993
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
    set_long("You are walking along a small dirt path that follows the " +
        "banks of the Diamond River as it rushes east towards the Pen Sea." +
        "A small pond has pooled on the northern side of the river, " +
        "half-hidden in the tall rushes and reeds that have grown up " +
        "around it. Dozens of colourful wildflowers peek out from behind " +
        "the tall grasses that grow across the wide rolling fields of " +
        "Sparkle valley. Surrounding the valley on almost every horizon, " +
        "are the Grey Mountains, their jagged peaks clawing up into the " +
        "blue sky above. The path continues along the river to the north " +
        "and east, while also splitting into a third path that leads " +
        "south towards the mountains.\n");

    add_trees(1);

    add_exit(THIS_DIR + "field8","north");
    add_exit(THIS_DIR + "field3","south");
    add_exit(THIS_DIR + "field5","east");
    add_exit(THIS_DIR + "field4", "southwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "field2", "southeast",0,1,1);
    add_exit(THIS_DIR + "big_tree", "northwest",0,1,1);
    add_exit(THIS_DIR + "field4", "west","@@mount@@",1,1);
    add_exit(THIS_DIR + "field4", "northeast","@@riv@@",1,1);

    add_item(({"mountain spur","spur","mountainside"}),
        "The rugged mountainside which juts up into the sky before you, " +
        "is the eastern end of a mountain spur that has cut through the " +
        "middle of Sparkle valley.");
    add_item(({"mountains","mountain","grey mountains"}),
        "They Grey Mountains surround the entire Sparkle valley, including " +
        "the jagged spur that juts up immediately before you to the south.");
    add_item(({"stream","river","diamond river","water","waters"}),
        "The rushing waters of the Diamond River rush eastward on a journey " +
        "to the Pen Sea.\n");
    add_item(({"bank","riverbank","riverbanks","banks"}),
        "The banks of the river are filled with tall grass and " +
        "colourful wildflowers.\n");
    add_item(({"pond","pool","small pond","small pool"}),
        "A small pond has pooled on the north side of the river, with " +
        "tall green reeds and rushes obscuring most of it.\n");
    add_item(({"reeds","rushes","tall reeds","tall rushes","green reeds",
            "green rushes","tall green reeds","tall green rushes"}),
        "Several clusters of green reeds and tall rushes surround a " +
        "small pool on the northern side of the river.\n");
    add_item(({"path","dirt path","small dirt path","small path",
            "narrow path","narrow dirt path","branch"}),
        "This small dirt path follows along the banks of the Diamond " +
        "River, with a small branch that trails off here deeper into the " +
        "fields to the south.");

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

/*
 * Function name:        riv
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the river in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
riv()
{
    write("The stream is too wide to cross here, you will have to find a " +
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