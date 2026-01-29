/*
 * hobgmace.c
 *
 * The axe for the hobgoblins.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/weapon";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_weapon
 *  Arguments: None
 *  Returns  : Void
 * 
 *  Creates the weapon.
 *
 */
public void
create_weapon()
{
    set_name("axe");
    set_adj("felling");
    add_adj("iron");
    set_short("iron felling axe");
    set_long("This is a heavy axe with a blade of iron used for felling " +
        "trees.\n");

    set_default_weapon(20, 23, W_AXE, W_SLASH, W_BOTH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(20, W_CLUB) +
        random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15, 23) + random(30));
}

