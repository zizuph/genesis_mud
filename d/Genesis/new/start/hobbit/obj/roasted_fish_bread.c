/*
 * File         : /d/Genesis/start/hobbit/obj/roasted_fish_bread.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1999 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is a piece of food sold at the Iron Piece in the hobbit
 *        startlocation. The fish is caught and sold by players to the
 *        publican as a small quest. The bread however is merrely food.
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


/* prototypes */


/* globals */


/*
 * Function name:       create_food
 * Description  :       set up the food
 
 */
void
create_food()
{
    set_name("bread");
    set_pname("breads");
    set_short("roasted fish bread");
    set_pshort("roasted fish breads");
    
    set_long(
      "This is a sliced bread with a salt fish, some spices and a " +
      "strange red sauce on top. It looks....special.\n");
    set_amount(150);
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    // Some aliases to let the publican give it easily
    add_name("_food");
    add_pname("_food");
    
}

