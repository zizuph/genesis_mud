// -*-C++-*-
// file name:	meatpie.c	
// creator(s): 	
// last update:	
// purpose:	for the bazaar bakery	
// note:
// bug(s):
// to-do:     

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
special_effect(int amnt)
{
    write("Your mouth waters with each flavorful bite.\n");
}

void
create_food()
{
    set_name("pie");
    set_adj("meat");
    set_short("savory meat pie");
    set_long("What a delicious-looking pie!  The crust is "+
        "perfectly browned and through the slits in the "+
        "surface you can see bits of meat, onion, peas, and "+
        "a thick brown gravy.  It is a nice, small pie, "+
        "easily fitting in the palm of one hand, and would "+
        "make a suitable meal for one.\n");
    set_amount(250);
}

