/*
 * File         : /d/Genesis/start/hobbit/obj/linnen_hood.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is a common linnen hood from the hobbit startloc.
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
inherit "/std/object";
inherit "/lib/wearable_item";


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
 * Function name:       create_object
 * Description  :       set up the object
 */
void
create_object()
{
    set_name("hood");
    
    set_long(
      "This is a linnen hood.\n");
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_layers(1);
    set_looseness(1);
    set_pname("hoods");
    set_short("linnen hood");
    set_adj("linnen");
    set_slots(A_HEAD);
    
    
}
/*
 * Function name: leave_env
 * Description  : let object know it leaves the environment
 */
public void
leave_env(object env, object to)
{
    /*
     * override leave_env to detect when object is dropped
     */
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

/*
 * Function name: appraise_object
 * Description  : let object be appraised properly
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

