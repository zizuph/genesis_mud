/*
 * /d/Emerald/telberin/arts/thespian_plaza.c
 *
 * This plaza marks the center of the visual performing arts activity
 * in Telberin. It is northeast of the Ri Circle in the Arts Quarter.
 *
 * Copyright (c) May 2000 by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_street";


/* prototypes */
public void    create_telberin_street();
#include <macros.h>


/*
 * Function name:        create_telberin_street
 * Description  :        set up the room with area presets
 */
public void
create_telberin_street()
{
    config_street_room("Arts", "Thespian Plaza");

    set_em_long(this_object()->short() + ". Just a placeholder room.\n");

    add_exit("/d/Emerald/telberin/arts/actors_guild", "northwest");
    add_exit("/d/Emerald/telberin/arts/amphitheatre", "northeast");
    add_exit("/d/Emerald/telberin/arts/dancers_guild", "southeast");
} /* create_telberin_street */
