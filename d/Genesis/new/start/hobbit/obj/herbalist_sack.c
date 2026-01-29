/*
 * File         : /d/Genesis/start/hobbit/obj/herbalist_sack.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The sack of the wandering herbalist war hero, Zagarn!.
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
inherit "/std/receptacle";
inherit "/lib/store_support";



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
create_container()
{
    set_name("sack");
    
    set_long(
      "This leather sack seems to be quite old since it is covered with " +
      "dirt, stains and scratches but still of good quality.\n");
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_adj(({"old", "leather"}));
    set_short("old leather sack");
    add_prop(OBJ_M_NO_SELL, "@@check_contents@@");
    
    
}
/*
 * The function store_update should always be called with the object that
 * enters the store.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

/*
 * override leave_env to detect when the object is dropped
 *
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}
*/
/*
* Lets be friendly. If someone tries to sell the sack, we check for him
* or her whether it is empty and if it is not, we disallow him/her to
* sell it.
*/
mixed
check_contents()
{
    if (sizeof(all_inventory()))
    {
        return "You cannot sell the sack for it is not empty.\n";
    }
    return 0;
}

