/*
 * File         : /d/Genesis/start/hobbit/obj/spectacles.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        These spectacles is the type the clerk in the hobbit startloc
 *        uses.
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
    set_name("spectacles");
    
    set_long(
      "This is a pair of glasses. They are used by people to see better.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 110);
    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_slots(A_EYES);
    set_layers(1);
    set_looseness(0);
    set_pname("pair of spectacles");
    set_short("pair of spectacles");
    
    
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

