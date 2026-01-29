/*
 * rusty_knife.c
 *
 * An old rusty fishing knife that you may some times find
 * on the beaches of Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <wa_types.h>
#include <stdproperties.h> 
#include <formulas.h>
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/weapon";

// D E F I N I T I O N S

// G L O B A L   V A R S

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION: create_weapon
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the weapon with descriptions and more.
 *
 */
public void create_weapon()
{
    set_name("knife");
    add_name("fishing knife");
    set_short("old rusty fishing knife");
    set_long("Old, rusty and slightly battered, this fishing " +
        "knife has been so damaged that it might not be very " +
        "useful. The handle is wooden and faded lines suggest it " +
        "might have had some kind of symbols or designs carved " +
        "into it. Old and battered, the blade is very rusty and " +
        "it would take a very skilled hand to cut anything with " +
        "this knife.\n");

    set_adj("old");
    add_adj("rusty");

    set_hit(8);
    set_pen(9);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 250);
}

