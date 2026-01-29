/*
 * File:    temple_balcony
 * Creator: Cirion, 1998.06.14
 * Purpose: Balcony that looks over the great temple in
 *          the monk's guild hall.
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("temple balcony");
    set_long("This narrow balcony stands halfway up the eastern "
        + "wall of the massive, eerily lit temple. A small "
        + "doorway to the east enters into the souther "
        + "end of the upper hall. The edge of the balcony is "
        + "unprotected by any railing or guard.\n");
    add_item(({"temple","down"}),
        "The great temple spreads down below, leading "
        + "westward to a vast statue of a noble dragon, at "
        + "the base of which lies a simple altar.\n");
    add_item(({"dragon","statue"}),
        "It is enormous, reaching up to the western part of "
        + "the ceiling, on the level with the balcony.\n");
    add_item("altar",
        "It is simple, resting between the claws of the "
        + "statue.\n");
    add_item(({"balcony","ledge","railing"}),
        "This is a very narrow, simple balcony looking out "
        + "over the great temple. The thick stone slab seems "
        + "unsupported from below.\n");


    WIZINFO("This balcony looks over the great temple.\n");

    // where, command
    add_exit("hall_upper_south", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You walk out onto a narrow balcony "
        + "that looks over the vast temple, giving you "
        + "a feeling of vertigo.\n");
}

