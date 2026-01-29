/*
 * /d/Gondor/mordor/ungol/tower/east13.c
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

#define HAMMER_ORC        (MORDOR_DIR + "npc/hammer_orc")
#define TOWER_TOOLBOX     (MORDOR_DIR + "obj/toolbox")
#define TOWER_TOOLBOX_ID  "_toolbox_at_cirith_ungol_"
#define TOWER_TOOL_AXE    (MORDOR_DIR + "obj/wep/tool_axe")
#define TOWER_TOOL_AXE_ID "_tool_axe_at_cirith_ungol_"
#define TOWER_SQUARE      (MORDOR_DIR + "obj/square")
#define TOWER_SQUARE_ID   "_square_at_cirith_ungol_"
#define LOCKPICKS         (WEP_DIR + "lockpicks")
#define LOCKPICKS_ID      "_lockpicks_"

/*
 * Prototype
 */
void reset_room();

/*
 * Global variables
 */
object orc1; /* There are orcs guarding this tower   */
object orc2; /* Many orcs and they are all after you */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* add a real torch, don't get an add_item */
    make_the_room(); /* including several add_items :-)         */

    set_name("Ungol tower, first floor");
    add_name( ({ "room" }) );

    set_short("The tower at Cirith ungol, first floor, hardware room");
    set_long(BSN("You are at the first floor in the tower at Cirtih Ungol. " +
        "This room is a storage room, used by the orcs to store their " +
        "hardware in."));

    add_item( ({ "hardware", "tool", "tools" }),
         BSN("There are several tools to be found here."));

    make_door(CIRITH_DIR + "east14", "south", 2);

    reset_room();
}

void
reset_room()
{
    object box = present(TOWER_TOOLBOX_ID, TO);

    FIX_EUID;

    if (!objectp(box))
    {
        (box = clone_object(TOWER_TOOLBOX))->move(TO);
    }

    if (!present(TOWER_TOOL_AXE_ID, box))
    {
        clone_object(TOWER_TOOL_AXE)->move(box, 1);
    }
    if (!present(TOWER_SQUARE_ID, box))
    {
        clone_object(TOWER_SQUARE)->move(box, 1);
    }
    if (!present(LOCKPICKS_ID, box))
    {
        clone_object(LOCKPICKS)->move(box, 1);
    }

    if (!objectp(orc1))
    {
        orc1 = clone_orc(HAMMER_ORC);
        orc1->make_the_orc((60 + random(40)), 0);
        orc1->move(TO);
    }
    if (!objectp(orc2))
    {
        orc2 = make_orc(55, 0);
    }
}
