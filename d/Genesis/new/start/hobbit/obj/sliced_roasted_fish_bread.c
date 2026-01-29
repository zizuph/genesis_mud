/*
 * File         : /d/Genesis/start/hobbit/obj/sliced_roasted_fish_bread.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is slices of a piece of food sold at the Iron Piece in the
 *        hobbit startlocation. The fish is caught and sold by players to
 *        the publican as a small quest. The bread however is merrely
 *        food. If the publican there finds that the player is too small
 *        for the full bread he will chop it into these smaller slices.
 *        Bon apetit!
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
inherit "/std/food";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"
/* defines */
#define PROP_ID "hsl_sliced_bread"

/* prototypes */
string slice_long();

/* globals */


/*
 * Function name:       create_food
 * Description  :       set up the food
 
 */
void
create_food()
{
    set_name("slice");
    set_pname("slices");
    set_short("slice of roasted fish bread");
    set_pshort("slices of roasted fish bread");
    
    
    set_amount(30);
    add_prop(HEAP_S_UNIQUE_ID, PROP_ID);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    set_long(slice_long);
    
    // Some aliases to let the publican give it easily
    add_name("_food");
    add_pname("_food");
    
}
string
slice_long()
{
    return "The slice" + 
        ((num_heap() == 1) ? " of bread is " : "s of bread are ") + 
        "looking quite tasty stuffed with fish and a red " +
        "sauce topped with some spicy herbs.\n";
}
