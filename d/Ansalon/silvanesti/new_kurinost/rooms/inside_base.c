/*
 * inside_base.c
 *
 * Standard file for Tower / Cave in Kurinost.
 *
 * Copyright (C): Kellon, november 2011
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include "local.h"

/* Inherit the Krynn room */
inherit R_FILE

// G L O B A L   V A R S

// P R O T O T Y P E S
public void create_kurinost_room(){}
public void reset_kurinost_room(){}


nomask public void
create_krynn_room()
{
    create_kurinost_room();
    reset_krynn_room();
}

nomask public void
reset_krynn_room()
{
    reset_kurinost_room();
}


// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : enter_inv
 *  Arguments: ob, from - who entered the room and from where?
 *  Returns  : none.
 * 
 *  Start room tells when someone enters the room.
 *
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        start_room_tells();
    }
}
