/*
 * caper.c
 *
 * The caper that you can collect from small bushes on the rocky
 * shores of Silvanesti.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

// I N H E R I T E D   F I L E S
inherit "/std/food";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_food
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creating the food with descriptions.
 *
 */
public void
create_food()
{
    set_name("caper");
    set_adj(({ "small", "green" }));
    set_short("small green caper");
    set_pshort("small green capers");

    set_long("Roughly the size of a large pea, the caper is the " +
        "unopened flowerbud of a caper plant. With layers of small " +
        "green leaves that would eventually blossom and become a " +
        "beautiful white flower, this small caper has a sharp " +
        "piquant and salty flavor, similar to mustard.\n");

    set_amount(20);

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 1);
}

