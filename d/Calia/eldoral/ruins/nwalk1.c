#include "defs.h"

inherit STDROOM;

void
create_room()
{
    set_short("the base of a narrow staircase in " +
        CASTLE_NAME);
    set_long("You are at the end of a short corridor " +
        "that leads southwards, towards the heart of " +
        "the ruins of "+CASTLE_NAME+". The corridor " +
        "isn't very wide, nor spectacularly " +
        "constructed. Just a simply, rectangular-" +
        "shaped passage built from the same grey " +
        "stone blocks that form most of these ruins. " +
        "Great iron sconces hang from the walls " +
        "here at regular intervals. A narrow " +
        "stairway ascends through an opening in " +
        "the ceiling here, and looking closely you " +
        "can see the remnants of what were once " +
        "hinges to a hatch covering the opening, but " +
        "are now just twisted bits of rusted iron.\n\n");

    add_item(({"ceiling", "roof"}),
        "The roof is comprised of long stone slabs which " +
        "been closely fit and laid across the tops of the " +
        "walls.\n");
    add_item(({"walls"}),
        "The walls of the passage are squarely cut and " +
        "finished from blocks of grey stone. Aside from " +
        "a thick coat of dust and a few cracks, they " +
        "are in relatively good shape.\n");
    add_item(({"floor", "ground"}),
        "The floor of the passage consists mainly of " +
        "large flagstones tighly fitted together. They " +
        "are in rather good shape, the only real damage " +
        "is a few chips here and there, and the odd stone "+
        "split completely in two.\n");
    add_item(({"stairway", "stairs"}),
        "A narrow stone stairway ascends the north wall " +
        "through an opening in the ceiling.\n");
    add_item(({"opening", "hatch"}),
        "The opening appears to have been a hatchway at " +
        "one time, but the only evidence of a door covering " +
        "it now is the twisted, rusted remnants of iron " +
        "hinges.\n");
    add_item(({"hinges", "iron hinges"}),
        "Iron hinges, or rather the twisted remains of " +
        "iron hinges, jut out from the stone near the " +
        "opening in the ceiling.\n");

    INSIDE;

    add_exit(RUIN + "nwalk2", "up");
    add_exit(RUIN + "hall-nwalk", "south");
}
