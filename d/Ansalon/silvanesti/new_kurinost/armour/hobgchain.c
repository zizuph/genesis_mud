/*
 * hobgchain.c
 *
 * Chainmail with metal plates for the hobgoblins to wear.
 *
 * Copyright (C): Kellon, september 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

// I N H E R I T E D   F I L E S
inherit "/std/armour";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_armour
 *  Arguments:
 *  Returns  :
 * 
 *  Creates the chainmail.
 *
 */
public void
create_armour()
{
    set_name("chainshirt");
    add_name(({ "chain", "chainmail", "chainshirt" }));
    set_adj(({ "rusty", "iron"}));

    set_short("rusty iron chainshirt");
    set_long("Crude and mismatching metal plates have been bolted " +
        "onto this rusty chainshirt. Though they have been buffed " +
        "to a nice shine, the metal plates add little protection " +
        "and are probably just strapped on to make the wearer " +
        "feel more brave.\n");

    set_default_armour(20 + random(10), A_BODY, ({ -1, 2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(10)-5);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(25,A_BODY)+random(40)-20);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

