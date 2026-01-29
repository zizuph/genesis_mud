/*
 * hobgshield.c
 *
 * A crude shield for the hobgoblins to wield.
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
 *  Creates the shield.
 *
 */
public void
create_armour()
{
    set_name("shield");
    set_adj( ({ "spiked", "wooden" }) );

    set_short("spiked wooden shield");
    set_long("Nasty iron spikes have been hammered into this " +
        "crude wooden shield to make it look more dangerous. It " +
        "has been fitted with a basic leather strap at the back " +
        "and painted with the green markings of the dragonarmy.\n");

    set_default_armour(12 + random(4), A_SHIELD, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(13) + random(30));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_SHIELD) + random(10));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}

