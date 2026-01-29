/*
 * File         : /d/Genesis/start/hobbit/obj/cotton_robe.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is the adv guild trainers cotton robe from the hobbit
 *        startloc.
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
    set_name("robe");
    
    set_long(
      "This is a thick white robe made of cotton and ideal for training " +
      "purposes as it absorbes some of the energy from uncontrolled " +
      "feet and fists.\n");
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4));
    add_prop(OBJ_I_VOLUME, 1300);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(4,A_BODY|A_HIPS));
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/12/99.\n");
    
    set_layers(2);
    set_looseness(3);
    set_pname("robes");
    set_short("thick cotton robe");
    set_adj(({"thick", "cotton"}));
    set_ac(4);
    set_am( ({ -1, -1, 0 }) );
    set_at(A_BODY | A_HIPS);
    
    
}


