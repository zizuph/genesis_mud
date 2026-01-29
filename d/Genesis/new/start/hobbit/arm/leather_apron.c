/*
 * File         : /d/Genesis/start/hobbit/obj/leather_apron.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is the apron of Sheena Rabbit in the hobbit startloc.
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
    set_name("apron");
    
    set_long(
      "This is an apron made of hardened leather to protect blacksmiths " +
      "in their craftmansship.\n");
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8,A_TORSO|A_LEGS));
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 1/12/99.\n");
    
    set_layers(2);
    set_looseness(3);
    set_pname("aprons");
    set_short("leather apron");
    set_adj("leather");
    set_ac(8);
    set_am( ({ -1, 1, 0 }) );
    set_at(A_TORSO | A_LEGS);
    
    
}


