/* 	
 * field10.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();
    set_items_field();
    set_herbs();

    set_short("Dark Road");
    set_long("You are following the Dark Road as it travels east and west " +
        "on the northern edge of Sparkle valley. A sturdy stone building " +
        "stands on the north side of the road, under the shadow of the " +
        "jagged peaks of the Grey Mountains which march west from here " +
        "before turning south to surround the valley. A stone oven has been " +
        "built beside the building, but the curly wisps of grey smoke rise " +
        "up from the chimney that stands atop the building. Wide grassy " +
        "fields are filled with colourful wildflowers and stretch out far " +
        "to the south, disrupted by a small dirt trail that leads towards " +
        "some broken ruins that are just visible on the horizon. Following " +
        "the road east should eventually bring you back to the city of " +
        "Sparkle.\n");

    add_trees(1);

    add_exit(THIS_DIR + "field9","west");
    add_exit(THIS_DIR + "ruin","south");
    add_exit(THIS_DIR + "field11","east");
    add_exit(THIS_DIR + "sparkle_forge","north","@@smithy@@");
    add_exit(THIS_DIR + "field7", "southeast", 0,1,1);
    add_exit(THIS_DIR + "pond", "southwest", 0,1,1);

    set_no_exit_msg(({"northwest","northeast"}),
        "The mountainside is far too difficult to climb here, you will " +
        "need to find another way around.\n");

    add_item(({"oven","stone oven","bloomery"}),
        "This actually appears to be a bloomery, an oven designed to " +
        "help extract iron during the smelting process.\n");
    add_item(({"iron","ore","iron ore"}),
        "You cannot see any iron ore here, but the presence of a " +
        "bloomery and a smithy suggests that there might be some " +
        "nearby.\n");
    add_item(({"ruin","ruins","broken ruins"}),
        "So far as you can tell from this distance, these ruins look " +
        "ancient.\n");
    add_item(({"smoke","wisps"}),
        "Delicate wisps of grey smoke drift up and out from a chimeny " +
        "on the roof of the building, suggesting that the smith is " +
        "currently occupied.\n");
    add_item(({"chimney","stone chimeny"}),
        "This stone chimney stands atop the slate roof of the smithy, " +
        "spewing out a trail of grey smoke.\n");
    add_item(({"slate","slate tiles","slate tile","roof"}),
        "The roof of the building appears to have been constructed out of " +
        "small tiles of slate, laid in an overlapping manner to help " +
        "keep the smithy dry.\n");
    add_item(({"building","smithy","sturdy building","stone building",
            "study stone building"}),
        "As you look closely, you begin to suspect that this building is " +
        "actually the workshop of a blacksmith. You are not entirely " +
        "certain why a blacksmith would place his forge out in the " +
        "middle of the wilderness, but judging from the smoke, \n");
    add_item(({"trail","small trail","dirt trail","small dirt trail"}),
        "This small dirt trail interupts the wide fields of grass and " +
        "wildflowers, winding away in the direction of some broken ruins " +
        "that sit upon the southern horizon.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "Looking to the south, you can see some broken ruins outlined on " +
        "the grassy fields in the distance. Farther beyond, you see the " +
        "slopes of the Grey Mountains covered in the bundled masses of " +
        "dark trees known as the Jade Forest which march down to huddle " +
        "around the bright road.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        smithy
 * Description  :        Provides an echo for atmosphere while moving into
 *                       another room
 * Returns      :        int 0 - moves into the forge
 */
int
smithy()
{
    write("A sudden blast of heat from the forge rolls over your skin as " +
        "you enter the smithy.\n");
    return 0;
}
/* smithy */