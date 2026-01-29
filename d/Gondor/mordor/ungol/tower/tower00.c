/*
 * /d/Gondor/mordor/ungol/tower00.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * on the stairs withing hearing distance.
 *
 * /Mercade, 21-06-1993
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

#define TOWER_DIR UNGOL_DIR + "tower/"
#define ORC MORDOR_DIR + "npc/towerorc"

/*
 * Prototypes
 */

void reset_room();

/*
 * Global variables
 */

object orc1; /* mean orcs guarding the tower             */
object orc2; /* this will be killers heaven or won't it? */

/*
 * This function defines the room.
 */

void
create_room()
{
    make_the_room();

    set_name("Ungol tower, ground level");
    set_short("The tower at Cirith ungol at the ground level");
    set_long(BSN(""));

    add_item("stairs", BSN(""));

    reset_room();
}

/*
 * This procedure is called each time the room needs to be updated. Here also
 * is a check for the orc guards. They will re-appear if killed before.
 */

void
reset_room()
{
    if (!orc1)
    {
        orc1 = clone_object(ORC);
        orc1->make_the_orc(60);
        orc1->move(TO);
    }
    if (!orc2)
    {
        orc2 = clone_object(ORC);
        orc2->make_the_orc(60);
        orc2->move(TO);
    }

    return;
}
