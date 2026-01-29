/*
 * dc_satchel.c
 *
 * A small military satchel to carry importalt documents.
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
inherit "/d/Genesis/std/wearable_pack";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_wearable_pack
 *  Arguments: none
 *  Returns  : Void
 * 
 *  Basic creation.
 *
 */
public void
create_wearable_pack()
{
    set_name("satchel");
    add_name(DC_SATCHEL);
    add_adj("leather");
    add_adj("small");
    add_adj("green");
    set_long("A simple black image of a dragon adorns this small " +
        "green military satchel. Barely large enough to hold a " +
        "few folded documents, it is quite small and easy to " +
        "carry in all situations. Made from dark green rough " +
        "leather, it is about 20 cm long, 15 cm wide and 4-5 cm " +
        "thick, and it has a long leather shoulderstrap, so that " +
        "it can be worn slung over one shoulder.\n");

    add_item(({ "image", "black image", "dragon" }),
        "A small black image of a dragon in silhouette has been " +
        "stamped onto the small green military satchel.\n");

    set_mass_storage(0);

    add_prop(CONT_I_WEIGHT, 1200);
    add_prop(CONT_I_MAX_WEIGHT, 1500);
    add_prop(CONT_I_VOLUME, 1200);
    add_prop(CONT_I_MAX_VOLUME, 1500);
    add_prop(CONT_I_CLOSED, 1);

    add_prop(OBJ_I_VALUE, 120);
}



