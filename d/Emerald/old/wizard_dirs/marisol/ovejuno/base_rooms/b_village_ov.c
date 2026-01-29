/* Base room for the village of Re Albi.
 * Only basic information is contained in this
 * file. Coded by Marisol (12/1/97)
 * Copyright (c) Marisol Ramos 1997 */

/* Base_room modified in (07/09/98) to be used for the village 
 * of Ovejuno in Emerald. Modify by Marisol. Copyright (c) Marisol
 * Ramos 1998. */

#pragma strict_types

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h";
#include "/d/Emerald/lib/room_tell.c"
#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Emerald/marisol/ovejuno/village_OV/vtells.h"


void
create_ov_room()
{
}

nomask void
create_emerald_room()
{

    int i;

    set_short("A village path");

    add_item("village",
        "The village of Ovejuno is over a cliff known as the "+
        "Tabla Rasa, or the Flat Mountain. This is not a very rich "+
        "village, although it has its own lord. The villagers are "+
        "farmers and shepherds of some small herds. The "+
        "houses in the village are poor-looking but neat. The "+
        "air in this high altitude is fresh and wholesome, full "+
        "with forest scents.\n");

    add_item("houses",
        "The village' houses are mostly of wood and straw. Some "+
        "of them have stone chimneys with the smoke drifting with "+
        "the wind.\n");

    add_item(({"ground", "path"}),
        "The ground of this path is hard-packed earth because the "+
        "traffic of men and animals.\n");


    reset_room();

    create_ov_room();

    set_tell_time(100);
    for(i = 0; i <4; i++)
    add_tell(VTELLS[random(sizeof(VTELLS))]);

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
       start_room_tells();
}
