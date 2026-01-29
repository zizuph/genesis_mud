/* s_road3.c
 * Styles.   3 Mar 1993
 *
 * Updated to put players in the new Actors club in Sparkle domain
 * Lunatari 1 Feb 2006
 *
 *  Modified - Varian  March, 2016
 *  Added entrance to deeper Jade Forest - Mar, June 2016
 */

/* THIS IS A REPLACEMENT FOR AN EXISTING ROOM -
 * belonging in /d/Genesis/start/human/wild2.
 * To activate, move to that directory, switch directory include files,
 * uncomment W/S exits, update E exit,
 * update WILD_DIR definition used by the /jade rooms
 */

#pragma strict_types

#include "../defs.h"
//#include "wild.h"
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
        "woods. A narrow trail leads east into the depths of the " +
        "forest.\n");

    add_trees(1);

    add_exit("/w/mar/s_road3a","north");
    //add_exit(NEW_ACTORS_ENT, "west");
    //add_exit("/d/Sparkle/area/memorial/dondon_memorial", "south");
    add_exit(ROOM_DIR + "jade_forest_w","east");

    set_no_exit_msg(({"northeast","southeast","southwest","northwest"}),
        "The dark shadows of the Jade Forest loom above you and you can " +
        "barely see the dense underbrush that covers the ground. " +
        "Taking a quick glance, you decide that this is probably " +
        "not the best place, or time, to enter them.\n");

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
    add_item( ({"trail", "path", "narrow trail", "depths", "east",
        "depths of the forest", "underbrush"}),
        "A narrow path has been hacked through the dense underbrush to the " +
        "east. Unlike the road, it looks recent.");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}
