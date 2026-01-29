/*
 *  /d/Gondor/minas/citadel/battlement10.c
 *
 *  Stairs to the Battlement: Upper Landing
 *
 *  Alto, 20 April 2001
 *
 *  
 *  Modification log:
 *
 *  -- Toby, 10th-Sept-2007: Fixed remove_item add_item for stairs to give proper desc.
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
    set_short("Landing above the stairs");
    set_long("This is a broad white-paved landing at the top of "
        + "a wide flight of stairs leading down from the Battlement. "
        + "A narrow walk leads east toward the peak of the bastion, "
        + "where an embrasure in the walls allows a clear view "
        + "of the lands east of Minas Tirith.\n");

    add_exit(INNER_MINAS + "/citadel/battlement9", "west", 0, 1);
    add_exit(INNER_MINAS + "/citadel/battlement11", "east", 0, 1);

    add_item(({"landing", "battlement"}), "In times of peace, this would be a "
        + "pleasant place to take in the fresh mountain air. Well-tended "
        + "hedges and flowerbeds "
        + "line the square landing. No Men of Gondor can be seen here "
        + "today, however. War leaves little time for leisure.\n");
    add_item(({"hedges", "hedge"}), "Even in times of war, the "
        + "Master Gardener of the city and his assistants work tirelessly "
        + "to maintain the beauty of its green treasures. The hedges "
        + "are tall and square, and stand around the periphery of the "
        + "landing. They are broken only by the stairs climbing down from the "
        + "bastion, and also the narrow walk leading toward an embrasure "
        + "in the walls to the east.\n");
    add_item(({"flowerbeds", "flowers"}), "Just as the hedges are kept "
        + "neatly groomed by the Master Gardener and his assistants, so "
        + "are colourful flowers kept in bloom throughout the city. The "
        + "vibrant colours seem especially vivid against the grey "
        + "darkness creeping toward the city from the east.\n");
    add_item(({"ground", "floor", "squares", "paving stones"}), "The "
        + "landing is paved with great squares of native white stone.\n");
    add_item(({"walk", "stone"}), "Cobbled in colourful red and blue-grey stone, "
        + "the narrow walk forms a straight path to the east.\n");
    add_item(({"embrasure", "walls", "gap"}), "To the east is a gap in the walls "
        + "of the Battlement. You will have to walk closer to look through "
        + "it at the lands beyond.\n");
    add_item(({"citadel"}), "Due to the curve of the bastion, only the "
        + "White Tower of Ecthelion can be seen from here.\n");


    add_battlement_items();

    remove_item(({"stairs", "flight", "steps"}));
    add_item(({"stairs", "flight", "steps"}), "Great steps are cut into "
        + "the rock of the bastion. From here they lead back down toward "
        + "the Citadel.\n");

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




