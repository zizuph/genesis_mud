/*
 * /d/Gondor/mordor/ungol/tower/west06.c
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

#define TOWER_CHEST     MORDOR_DIR + "obj/tower_chest"
#define TOWER_CHEST_ID  "_chest_at_cirith_ungol_"
#define TOWER_DAGGER    MORDOR_DIR + "obj/wep/dagger"
#define TOWER_DAGGER_ID "_poisonous_dagger_at_cirith_ungol_"

/*
 * Global variables
 */
object orc1; /* An orc guarding the gate           */
object orc2; /* Another orc also guarding the gate */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* do it here to get no add_item torch as well */
    make_the_room(); /* including several add_items :-)             */

    set_name("Ungol tower, ground level");
    add_name("room");

    set_short("The tower at Cirith ungol at the ground level");
    set_long(BSN("This is a dark room on the mountain side of the tower, " +
        "here at Cirith Ungol. This room is probably used by orcs to that " +
        "guard the arched gate that you see north of here. Some torches are " +
        "flaring in their brackets, giving some light to this place."));

    add_item( ({ "gate", "door", "arched gate" }),
        BSN("North of this room you see an arched gate. It is a strong " +
        "gate that orcs guard from this room. The gate must lead to a " +
        "system of tunnels in the mountains."));

    add_exit(CIRITH_DIR + "west02", "east");
    add_exit(CIRITH_DIR + "west05", "north");

    TO->reset_room();
}

void
reset_room()
{
    object chest = present(TOWER_CHEST_ID, TO);

    FIX_EUID;

    if (!objectp(chest))
    {
        chest = clone_object(TOWER_CHEST);
        chest->move(TO);
    }

    if (!present(TOWER_DAGGER_ID, chest))
    {
        clone_object(TOWER_DAGGER)->move(chest, 1);
    }

    if (!objectp(orc1))
    {
        orc1 = make_orc(70);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(100);
    }
}
