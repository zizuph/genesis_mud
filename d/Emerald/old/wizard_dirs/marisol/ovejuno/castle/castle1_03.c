
/* Castle_room03-Corridor.
 * Coded by Marisol (09/03/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types
#include "defs.h"
inherit CASTLE_OV;


void
create_castle_room()
{

    set_long("This corridor runs straight through the residence. To "+
        "one side is the Dining Room. In the other side is the "+
        "Kitchen of the residence. Straight ahead there are more "+
        "rooms. Tapestries and paintings decorate the walls of the "+
        "corridor, between the open doors of the other rooms. "+
        "Torch-lights burn brightly high in the walls.\n");

    add_item("floor",
        "Beautiful porcelain tiles cover the floor of the corridor.\n");



    add_exit("castle1_02.c", "south");
    add_exit("castle1_04.c", "north");
    add_exit("castle1_07.c", "east");
    add_exit("castle1_08.c", "west");

    reset_room();

}
                                                
