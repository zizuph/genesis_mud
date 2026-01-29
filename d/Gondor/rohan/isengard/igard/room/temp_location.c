/*
 *  temp_location.c
 *
 *  Room for temporary movement of NPCs.
 *
 *  Last modified by Alto, 01 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public void    create_gondor();


string
long_desc()
{
    return "Nothing much to look at here. NPCs come here temporarily "
        + "before casting themselves into the great void.\n";
}

public void
create_gondor()
{
    string  name;

    set_short("A temporary room");
    set_long(&long_desc());

    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}
