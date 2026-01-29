/*
 *  /d/Genesis/start/human/wild2/s_road3a.c
 *
 *      Hastily constructed road to assist with making Styles'
 *      maps accurate. (Gorboth)
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_items_brightroad();
    set_items_forest();
    set_herbs();

    set_short("Bright road");
    set_long("You are following the white stones of the Bright Road " +
        "as they cut through the dark shadows on the edge of the Jade " +
        "forest. Tall trees rise up into the air, surrounding you in " +
        "all directions, with only the bright white path of the " +
        "highway to interupt them. Endless tales have been told about " +
        "the ferocious ogres or the desperate bandits who make their " +
        "home in these woods, waiting to prey upon any traveller " +
        "who might wander into their clutches. The Bright Road continues " +
        "to run deeper into the forest to the south and out into an " +
        "open field to the north.\n");

    add_trees(1);

    add_exit(THIS_DIR + "s_road2", "north");
    add_exit(THIS_DIR + "s_road3", "south");

    set_no_exit_msg(({"northeast","east","southeast","southwest",
            "west","northwest"}),
        "The dark shadows of the Jade Forest loom above you directly to " +
        "southeast. Taking a quick glance, you decide that this is probably " +
        "not the best place, or time, to enter them.\n");

    add_item(({"horizon"}),
        "You quickly glance across the valley in all directions, but " +
        "you could probably focus on examining the northern, western, " +
        "southern or eastern horizon if you wanted.\n");
    add_item(({"north horizon","northern horizon","north"}),
        "Looking to the north, you can see the Bright Road winding " +
        "through rugged foothills and grassy fields back towards " +
        "Sparkle.\n");
    add_item(({"west horizon","western horizon","west","northwest horizon",
            "northwestern horizon","northwest","southwest horizon",
            "southwestern horizon","southwest","northeastern horizon",
            "northeast","northeast horizon","eastern horizon","east",
            "east horizon","southeastern horizon","southeast","south",
            "southeast horizon","south horizon","southern horizon"}),
        "Try as you might, you cannot see much through the dense shadows " +
        "of the Jade Forest that surround you here.\n");
    add_item(({"field","open field"}),
        "Not too far away, along the highway to the north, you can see " +
        "some open grassy fields, free from the shadowy confines of the " +
        "Jade Forest.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}