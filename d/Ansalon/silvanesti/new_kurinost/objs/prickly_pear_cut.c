/*
 * prickly_pear_cut.c
 *
 * The pear that you can collect from cactus plants on the rocky
 * shores of Silvanesti. This version is cut and can be eaten.
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
    set_name(({ "pear", "prickly pear", "cactus pear", "cactus" }));
    add_name("cut_prickly_pear");
    add_pname("cacti");
    set_adj(({ "red", "purple", "purple-red" }));
    set_short("cut purple-red prickly pear");
    set_pshort("cut purple-red prickly pears");

    set_long("Deep red and purple and shaped like an avocado or " +
        "pear, this fruit is protected by a thick outer skin. " +
        "Usually covered with big thorns, as is common on most " +
        "cacti, this pear has been neatly cut and the thorns are " +
        "gone. Tasting like a somewhat tough green pepper, the " +
        "pears grow throughout the year on the top of large " +
        "oval cactus pads.\n");

    add_item(({ "thorn", "thorns" }), "Usually thick, tough and " +
        "piercing thorns cover the purple-red prickly pear, but " +
        "this pear has been neatly cut and the thorns are gone.\n");
    set_amount(20);

    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 240);
    add_prop(OBJ_I_VALUE, 10);
}

