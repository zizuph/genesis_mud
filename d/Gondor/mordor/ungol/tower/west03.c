/*
 * /d/Gondor/mordor/ungol/tower/west03.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/*
 * This function defines the room.
 */
void
create_room()
{
    no_torch();   /* Call this before make_the_room to get no add_item torch */
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "cell", "prison" }) );
    add_adj("prison");

    set_short("The tower at Cirith ungol, ground level, in a prison");
    set_long(BSN("You are in a dark prison cell, down below in the tower at " +
        "Cirith Ungol. This cell was hewn out of the mountain. In the door " +
        "to the south is a spy-hole, used to check on the prisoners. It is " +
        "a bare cell with only some straw to lie on."));

    add_item( ({ "hole", "spy-hole", "spy hole" }),
        BSN("There is a small hole in the door. This hole can be used to " +
        "check on the prisoners from outside the prison cell. You cannot " +
        "see though the hole for it is covered with a little cap."));
    add_item( ({ "bunk", "bunks", "straw", "straw bunk", "straw bunks" }),
        BSN("There is a bunk in this cell, made of straw. It is better to " +
        "lie on straw than on the bare floor, hewn out of the mountain " +
        "rock."));
    add_item("something", BSN("Your guess is as good as mine. ;-)"));

    add_cmd_item( ({ "down", "bunk", "straw", "on bunk", "on straw" }),
        ({ "lie", "sleep" }),
        BSN("For a moment you think about lying down on the straw bunk, but " +
        "then see something crawl away from under the bunk you are looking " +
        "at and your desire to lie down disappears completely."));

    make_door(CIRITH_DIR + "west04", "south", 2);
}
