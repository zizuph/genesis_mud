/*
 * /d/Gondor/anorien/nimrais/trolls/cave3.c
 *
 * Coder: Unknown
 *
 * Modification log:
 * Gwyneth, 10/02/02: Updated and cleaned up the code. Changed inheritance.
 */
inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

object gTroll;
object xTroll = allocate(1);

void
reset_room()
{
    ::reset_room();
    gTroll = clone_npc(gTroll, NPC_DIR + "hilltroll3");
    xTroll = clone_npc(xTroll, "/d/Gondor/arnor/npc/massive_troll");
}

void
create_gondor()
{
    set_short("A dead-end tunnel in a hill-troll lair");
    set_long("The tunnel ends here, in this little chamber inside the " +
        "hill. The walls are shaped roughly, as if this chamber is a " +
        "recent expansion of the lair, awaiting further mining some time " +
        "in the future. The tunnel leads north where you can see a " +
        "junction of passages.\n");
    remove_prop(ROOM_I_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);
    add_item("walls","The walls look solid. They seem to be roughly carved " +
        "out of the rock by the strong trolls, probably awaiting expansion " +
        "later.\n");
    add_item("chamber", "The chamber is small and empty, and the only exit " +
        "is north.\n");
    add_exit(NIMRAIS_DIR + "trolls/cave2", "north");
    reset_room();
}

