
/* Castle_room02-Corridor.
 * Coded by Marisol (09/03/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types

#include "../defs.h"
inherit CASTLE_OV;

void
create_castle_room()
{
    set_em_long("This corridor goes straight through the residence. To "+
        "one side is the Audience Room, where the elven lord of "+
        "this residence, gives audience to visitors and other "+
        "dignataries. In the other side is the Meeting Room, "+
        "where important meeting takes place. Straight ahead there "+
        "are more rooms. Tapestries and paintings decorate the walls "+
        "of the corridor, between the open doors of the other rooms. "+
        "Two elven soldiers stand guard in front of the Audience "+
        "Room. Torch-lights burn brightly high on the walls.\n");

    add_item(({"elven guards", "guards"}),
        "These guards look alert to their environment. They look "+
        "quite strong too.\n");

    add_exit("castle1_01", "south");
    add_exit("castle1_03", "north");
    add_exit("castle1_05", "east");
    add_exit("castle1_06", "west");
}
