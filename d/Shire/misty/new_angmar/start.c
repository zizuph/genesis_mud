/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_shire_room()
{
    object board;

    set_short("Dormitory");
    set_long("You step into a musty, dirty room. Ripped cots and slashed " +
        "mattresses cover the ground. Once the sleeping quarters of " +
        "the soldiers and officers of the Army, this room is destroyed " +
        "almost beyond recognition. Broken tables and chairs are buried " +
        "under the rubble where soldiers would come to relax, play " +
        "dice or cards, or just relax. Now, it's hard to imagine such " +
        "peace and solitude existed in this room.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(NEW_ANGMAR + "train", "east");

}

