// -*-C++-*-
// file name:	eggplant.c	
// creator(s): 	Sirra March 98
// last update:	
// purpose:		filling food
// note:
// bug(s):
// to-do:     

inherit "/std/food";
#include <composite.h>

void
create_food()
{
    set_name("eggplant");
    set_adj("stuffed");
    set_short("stuffed eggplant");
    set_long("This eggplant has been stuffed with sauted onions, "
	+ "glass rice, diced tomatoes, ground meat, and "
	+ "chopped parsley. It looks both tasty and filling.\n");
    set_amount(500);
}

public void
consume_text(object *arr, string vb)
{
    write("You " + vb + " " + COMPOSITE_DEAD(arr) +
	"slowly, savoring every delicious bite.\n");
}
