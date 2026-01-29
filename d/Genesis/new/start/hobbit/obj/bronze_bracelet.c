/*
 * File         : /d/Genesis/start/hobbit/obj/bronze_bracelet.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This bracelet was made by the master who taught Sheena Rabbit
 *        everything about smith craft. It has two fighting snakes on it
 *        as a symbol for the good and evil within each living creature.
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
    set_name("bracelet");
    
    set_long(
      "This is a very nice resizeable bracelet made of bronze and " +
      "decorated with two fighting snakes.\n");
    add_prop(OBJ_I_VALUE, 144);
    add_prop(OBJ_I_VOLUME, 130);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_slots(A_ANY_ARM);
    set_layers(1);
    set_looseness(0);
    set_pname("bracelets");
    
    
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

