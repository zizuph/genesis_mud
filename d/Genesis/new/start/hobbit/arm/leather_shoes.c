/*
 * File         : /d/Genesis/start/hobbit/obj/leather_shoes.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        These shoes comes from the hobbit startloc.
 * 
 * TODO         :

 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types
/* inherits */
inherit "/std/armour";



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
 * Function name:       create_armour
 * Description  :       set up the armour
 */
void
create_armour()
{
    set_name("shoes");
    
    set_long(
      "This is a pair of brown shoes made of soft leather with a " +
      "hardened leather sole.\n");
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/12/99.\n");
    
    set_layers(1);
    set_looseness(2);
    set_pname("shoes");
    set_short("pair of leather shoes");
    set_adj("leather");
    set_ac(5);
    set_am( ({ -2, 1, 0 }) );
    set_at(A_FEET);
    
    
}


