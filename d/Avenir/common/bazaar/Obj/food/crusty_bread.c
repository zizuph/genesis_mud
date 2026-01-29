// -*-C++-*-
// file name:	bread.c	
// creator(s): 	Lilith Sept 1999
// last update:	
// purpose:	for the bazaar bakery	
// note:
// bug(s):	
// to-do:     

inherit "/std/food.c";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>


void
create_food()
{
    set_short("loaf of crusty bread");
    add_name(({"bread", "loaf", "food"}));
    add_pname("loaves");
    set_pshort("loaves of crusty bread");

    set_long("A loaf of bread still warm from the oven. "+
        "Its flaky, golden crust encloses a moist, chewy "+
        "interior.\n");

    set_amount(300);
}
