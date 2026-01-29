/* Castle_room04-Corridor.
 * Coded by Marisol (09/03/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV;


void
create_castle_room()
{
    set_em_long("The corridor ends here. To one side is the "+
        "Library. In the other side are stairs that go up to the "+
        "second floor. Tapestries and paintings decorate the walls at "+
        "the end of corridor, between the open doors of the other "+
        "rooms. Torch-lights burn brightly high on the walls.\n");

    add_exit("castle1_03", "south");
    add_exit("castle1_09", "west");
    add_exit("castle1_10", "east");
    add_exit("castle2_01.c", "up");
}                                                               
