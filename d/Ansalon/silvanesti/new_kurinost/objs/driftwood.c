/*
 * driftwood.c
 *
 * A piece of driftwood, found at the beach.
 *
 * Copyright (C): Kellon, september 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/object";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_object
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the object and sets up descriptions.
 *
 */
public void create_object()
{
    set_name(DC_DRIFTWOOD);
    add_name(({ "driftwood", "wood" }));
    set_adj(({ "smooth", "dried" }));
    set_short("piece of smooth dried driftwood");
    set_pshort("pieces of smooth dried driftwood");
    set_long("Smooth and round, this piece of wood has been " +
        "polished clean over time, having been in the ocean or on " +
        "a beach. About a half meter long and as thick as your " +
        "arm, the wooden log is perfectly dry and clean.\n");

    add_prop(OBJ_I_WEIGHT, 1250);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 25);
}

