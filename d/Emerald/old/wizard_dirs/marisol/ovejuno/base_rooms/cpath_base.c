/* Base room for the manor's path.
 * Only basic information is contained in this
 * file. Coded by Marisol (06/8/97)
 * Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol (07/10/98) to be used for the
 * castle_garden in Emerald. Copyright (c) Marisol Ramos 1998 */

#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/room_tell.c";
#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Emerald/marisol/ovejuno/village_OV/castle_path/ctells.h"
#include "/d/Earthsea/sys/properties.h"

void
create_cpath_room()                         
{
}

nomask void
create_emerald_room()
{

    int i;

    set_short("The castle's path.");

    add_item("trees",
        "These are walnut trees. They grow along one side of "+
        "the path.\n");


    add_item(({"ground", "path"}),
        "The ground is hard-packed earth because the traffic of "+
        "men and animals.\n");              


    reset_room();

    create_cpath_room();

    set_tell_time(60);
    for(i = 0; i <4; i++)
    add_tell(CTELLS[random(sizeof(CTELLS))]);

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
       start_room_tells();
}                            
