/*
 *  /d/Gondor/minas/citadel/battlement1.c
 *
 *  Stairs to the Battlement: Lower Landing
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/minas/lib/dinen_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_gondor()
{
    set_short("Landing below the Battlement");
    set_long("This is a broad white-paved landing at the foot of "
        + "a wide flight of stairs leading up to the Battlement. "
        + "A narrow walk leads southwest toward the Court of the "
        + "Fountain.\n");

    add_exit(INNER_MINAS + "/citadel/fountain", "southwest", 0, 1);
    add_exit(INNER_MINAS + "/citadel/battlement2", "up", 0, 1);

    add_item(({"landing"}), "In times of peace, this would be a "
        + "pleasant place to take in the fresh mountain air. Small "
        + "stone benches amid well-tended hedges and flowerbeds "
        + "line the square landing. No Men of Gondor can be seen here "
        + "today, however. War leaves little time for leisure.\n");
    add_item(({"benches"}), "They look as though they would comfortably "
        + "seat two people. It probably would not be a good idea to "
        + "sit down, however. The grim folk of Minas Tirith would not "
        + "look kindly at strangers taking their ease while the residents "
        + "prepare for siege.\n");
    add_item(({"hedges", "hedge"}), "Even in times of war, the "
        + "Master Gardener of the city and his assistants work tirelessly "
        + "to maintain the beauty of its green treasures. The hedges "
        + "are tall and square, and stand around the periphery of the "
        + "landing. They are broken only by the stairs climbing up the "
        + "bastion, and also the narrow walk leading toward the Court of the "
        + "Fountain.\n");
    add_item(({"flowerbeds", "flowers"}), "Just as the hedges are kept "
        + "neatly groomed by the Master Gardener and his assistants, so "
        + "are colourful flowers kept in bloom throughout the city. The "
        + "vibrant colours seem especially vivid against the grey "
        + "darkness creeping toward the city from the east.\n");
    add_item(({"ground", "floor", "squares", "paving stones"}), "The "
        + "landing is paved with great squares of native white stone. "
        + "The benches themselves appear to be contiguous with the paving stones. "
        + "The craft of such stonemasonry has sadly been lost to the "
        + "ages.\n");
    add_item(({"walk", "stone"}), "Cobbled in colourful red and blue-grey stone, "
        + "the narrow walk curves toward the Court of the Fountain.\n");
    add_item(({"court of the fountain"}), "It cannot be seen from here, but "
        + "its fountain can be heard playing in the distance.\n");

    add_battlement_items();

    add_prop(ROOM_I_INSIDE, 0);

    set_tell_time(120);

    add_battlement_tells();

    reset_room();

}   


/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}




