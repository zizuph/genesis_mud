/*
 *      top5.c                  Styles.   3 Mar 1993
 *
 * Updated by Varian, March 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

public int       check_exit();

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_mountain();

    set_short("Grey Mountains");
    set_long("You are at the end of a narrow mountain trail. All around " +
        "you, the horizon is filled with the jagged snow-capped peaks " +
        "of the Grey Mountains, whose slopes slowly melt into patches " +
        "of long green grass and colourful wildflowers. Dozens of " +
        "rocks and boulders are littered all across the mountainside, " +
        "a testament to the unstable nature of the land away from the " +
        "trail that leads east from here. A tall stone arch has been " +
        "built here, leading into a brightly lit cave that opens up " +
        "before you to the north.\n");
        
        add_trees(0);

    add_exit(THIS_DIR + "top4","east");
    add_exit("/d/Sparkle/area/goblin_caves/rooms/level1/roome", "north",
        check_exit, 1);

    set_no_exit_msg(({"southwest","south","southeast","west","northwest",
            "northeast"}),
        "The mountains are simply too dangerous to climb in that " +
        "direction, you will have to find another way around.\n");

    add_item(({"cave","goblin cave","caves","goblin caves"}),
        "You can see a brightly lit cave beyond the arch that stands " +
        "at the north end of the trail. The cave looks quite large and " +
        "well inhabited, with a flat dirt floor that stretches out " +
        "for some distance.\n");
    add_item(({"arch","cave opening","opening","tall arch","tall stone arch"}),
        "This tall arch has been well crafted from a hard black stone, " +
        "providing entrance into the large and brightly lit cave that " +
        "spreads out to the north.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        check_exit
 * Description  :        alert a wizard when a player enters his area 
 * Returns      :        int 0 - always allow
 */
public int
check_exit()
{
    find_living("boreaulam")->catch_tell("\n\n\t\t----****  "
      + capitalize(this_player()->query_real_name()) + " enters the"
      + " goblin caves!  ****----\n\n");

    return 0;
} 
/* check_exit */
