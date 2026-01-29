/*
 * dc_bloodybone.c
 *
 * A small bone with meat, that you can give to the wolves in the camp.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit "/std/object";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_object
 *  Arguments: None
 *  Returns  : Void
 * 
 *  Creates the object and sets up descriptions.
 *
 */
public void create_object()
{
    set_name(DC_BONENAME);
    add_name("bone");
    set_adj(({ "large", "bloody", "meatfilled"}));
    set_short("meatfilled bone");
    set_long("Still dripping with blood, this large bone is " +
        "covered with plenty of meat and is relatively fresh, " +
        "having been thrown away only recently. Possibly the bone " +
        "from the lower leg of a deer, it is thick and about 25-30 " +
        "centimeters long. The bone has some charring, probably " +
        "from being chopped at with some tool to strip away the " +
        "meat.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE, 10);
}

