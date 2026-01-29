/*
 *  /w/petros/sparkle/rooftop/obj/lemon.c
 *
 *  This is a lemon, found in Sparkle. This is part of the book
 *  restoring quest in the Library. The lemon is found on the
 *  rooftop of the Library.
 *  
 *  Created by Petros, April 2008
*/

#pragma strict_types

inherit "/std/food";

// Includes
#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
    set_name("lemon");
    add_name("_library_rooftop_lemon");
    add_name("fruit");
    set_adj( ({ "yellow", "bright" }) );
    set_short("bright yellow lemon");
    set_long("The lemon has a smooth, waxy skin, and looks like it is "
           + "quite ripe.\n");
    set_amount(50); // 50 grams of food.
    add_prop(OBJ_I_WEIGHT, 50); 
    add_prop(OBJ_I_VOLUME, 30);
    
    // Add Item Calls
    add_item( ({ "skin", "waxy skin", "smooth, waxy skin", "smooth skin" }),
                 "The smooth waxy skin on the lemon looks almost too "
               + "perfect. You can only imagine the wonderful taste of "
               + "the juices inside."
               + "\n");
}
