/*
 * File         : /d/Genesis/start/hobbit/wep/stick.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999, Joakim Larsson
 * Date         : 3/17/1999
 * Related Files: 
 * Purpose      : 
 *     This is a wooden stick found on the ground in the hobbit startloc
 *    and has been adjusted to fight seagulls with.
 * Todo         : 
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/weapon";

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <wa_types.h> 
#include <formulas.h> 
#include "../hobbit.h"
/* defines */

/* prototypes */

/* globals */


/*
 * Function name:       create_weapon
 * Description  :       set up the weapon
 */
void
create_weapon()
{
    set_name("stick");
    set_pname("sticks");
    set_short("wooden stick");
    set_pshort("wooden sticks");
    set_adj(({"stright", "iron mounted"}));
    set_long(
        "This is a stright wooden stick about 1 meters long with a leather " +
        "handle at one end and a iron mounting at the other.\r");
    set_hit(5);
    set_pen(5);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(5,5));
    add_prop(OBJ_I_VOLUME, 2827);
    add_prop(OBJ_I_WEIGHT, 1796);
    
    
}

/* EOF */
