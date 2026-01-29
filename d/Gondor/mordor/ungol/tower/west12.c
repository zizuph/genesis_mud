/*
 * /d/Gondor/mordor/ungol/tower/west12.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 19 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <money.h>
#include "/d/Gondor/defs.h"

#define TOWER_CHEST    MORDOR_DIR + "obj/tower_chest"
#define TOWER_CHEST_ID "_chest_at_cirith_ungol_"

#define CHEST_HIDE_LEVEL 40 /* Is this a normal level? */

/*
 * Prototypes
 */
void reset_room();

/*
 * Global variables
 */
object orc1; /* mean orcs guard the tower            */
object orc2; /* there are two orcs here to play with */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage" }) );

    set_short("The tower at Cirith ungol, first floor, kitchen");
    set_long(BSN("You are at the first floor in the tower at Cirith Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "There is nothing special in this room. This passage continues to " +
        "the south and to the east."));

    add_exit(CIRITH_DIR + "west10",  "east");
    add_exit(CIRITH_DIR + "west13",  "south");

    reset_room();
}

/*
 * If players kill the orcs in this room they will find a little treasure in
 * the chest in this room. The chest is hidden a little.
 */
void
reset_room()
{
    object chest = present(TOWER_CHEST_ID, TO);

    if (!objectp(chest))
    {
        chest = clone_object(TOWER_CHEST);
        chest->add_prop(OBJ_I_HIDE, CHEST_HIDE_LEVEL);
        chest->move(TO);
    }

    if (!sizeof(all_inventory(chest)))
    {
        MONEY_MAKE_CC(50 + random(100))->move(chest, 1);
        MONEY_MAKE_SC(20 + random(40))->move(chest, 1);
    }

    if (!objectp(orc1))
    {
        orc1 = make_orc(100, 1); /* give the sucker a whip to play with */
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(45);
    }
}
