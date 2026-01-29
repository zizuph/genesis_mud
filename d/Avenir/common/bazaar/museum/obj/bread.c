// -*-C++-*-
// file name:	bread.c	
// creator(s): 	Sirra March 98
// last update:	
// purpose:		moderate filler
// note:
// bug(s):		the set_pname doesnt work! :(
// to-do:     

inherit "/std/food.c";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>


void
create_food()
{
	add_pname("loaves of zuccarrot bread");
	set_name("loaf of zuccarrot bread");
	add_name(({"bread", "loaf", "food"}));

	set_long("A warm loaf of zucchini carrot bread, filled "
		+ "with chopped walnuts, shredded carrots, zucchini, "
		+ "and sprinkled with cinnamon and cloves. Your mouth "
		+ "drools in anticipation.\n");

	set_amount(300);
}


void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n"
	+ "Mmmm... It melts in your mouth.\n");

    say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
}

