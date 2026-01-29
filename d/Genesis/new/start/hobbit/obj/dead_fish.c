/*
 * File         : /d/Genesis/start/hobbit/obj/dead_fish.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/28/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is a dead fish. Players get it by hitting or killing
 *        seagulls. They can then be sold to the pub owner, Tan in the
 *        hobbit startloc.
 * 
 * TODO         :
 * - add decay, let it rot => smell
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


/* includes */
#include <stdproperties.h> 
#include <macros.h> 

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
    set_name("fish");
    
    set_long(
      "This is a small dead fish. \n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/28/99.\n");
    
    set_adj(({"small", "dead"}));
    
    
}
void
hook_smelled()
{
    write("The fish smells fresh and could probably be eaten " +
        "if prepared correctly.\n");
}

