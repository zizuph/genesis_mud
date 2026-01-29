/* s_road3.c			
 * Styles.   3 Mar 1993
 *
 * Updated to put players in the new Actors club in Sparkle domain
 * Lunatari 1 Feb 2006
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

#define ACTORS_ENTRACE "/d/Genesis/clubs/rpg/theatre"
#define NEW_ACTORS_ENT "/d/Sparkle/clubs/actors/room/theatre"

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
    set_long("You are walking along the Bright Road in the middle of " +
        "the shadowy confines of the Jade Forest. All around you, countless " +
        "trees rise high above, blocking out any light from reaching the " +
        "forest floor away from the highway. The Jade Forest is famous in " +
        "legend and lore, telling frightening tales of the desperate " +
        "bandits and vicious ogres who hide here, waiting to prey upon " +
        "unsuspecting travellers such as yourself. The Bright Road bends " +
        "slightly to the southwest here, curving around a wrought iron " +
        "fence that borders a beautiful looking garden to the south. To " +
        "the west, you notice a small wooden building sitting near the " +
        "road, with doors open waiting for visitors. The highway also " +
        "continues north from here, cutting an open path through the " +
        "woods.\n");

    add_trees(1);

    add_exit(THIS_DIR + "s_road3a","north");
    add_exit(NEW_ACTORS_ENT, "west");
    add_exit("/d/Sparkle/area/memorial/dondon_memorial", "south");
    add_exit(THIS_DIR + "s_road3", "southeast","@@jade@@",1,1);
    add_exit(THIS_DIR + "s_road3", "east","@@jade@@",1,1);
    add_exit(THIS_DIR + "s_road3", "northeast","@@jade@@",1,1);
    add_exit(THIS_DIR + "s_road3", "southwest","@@block@@");
    add_exit(THIS_DIR + "s_road3", "northwest","@@jade@@",1,1);

    add_item(({"horizon"}),
        "You quickly glance across the valley in all directions, but " +
        "you could probably focus on examining the northern, western, " +
        "southern or eastern horizon if you wanted.\n");
    add_item(({"west horizon","western horizon","west","northwest horizon",
            "northwestern horizon","northwest","southwest horizon",
            "southwestern horizon","southwest","northeastern horizon",
            "northeast","northeast horizon","eastern horizon","east",
            "east horizon","southeastern horizon","southeast","south",
            "southeast horizon","south horizon","southern horizon","north",
            "northern horizon","north horizon"}),
        "Try as you might, you cannot see much through the dense shadows " +
        "of the Jade Forest that surround you here.\n");
    add_item(({"garden","memorial garden","fence","garden fence",
            "iron fence"}),
        "A wrought iron fence surrounds a magnificent looking garden " +
        "just south of the bend in the road here. It looks like you " +
        "would be welcome to enter the garden and visit.\n");
    add_item(({"bend","curve"}),
        "The Bright Road curves slightly to the west here, bending " +
        "around a magnificent looking garden that is surrounded by " +
        "a beautiful wrought iron fence.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        jade
 * Description  :        Gives an explanation for why the mortal cannot travel
                         into the forest
 * Returns      :        int 1 - denies moving along the exit path
 */
int
jade()
{
    write("The dark shadows of the Jade Forest loom above you directly to " +
        "southeast. Taking a quick glance, you decide that this is probably " +
        "not the best place, or time, to enter them.\n");
    return 1;
}
/* jade */

/*
 * Function name:        block
 * Description  :        Gives an explanation for why the mortal cannot travel
                         further down the Bright Road
 * Returns      :        int 1 - denies moving along the exit path
 */
int
block()
{
    write("You attempt to move further down the Bright Road to the " +
        "southwest, a patrol of soldiers stop you and turn you back after " +
        "they inform you about some recent bandit attacks.\n");
    return 1;
}
/* block */