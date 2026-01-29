// -*-C++-*-
// file name:	jam.c	
// creator(s): 	Sirra March 98
// last update:	
// purpose:		minor dessert
// note:
// bug(s):
// to-do:     

inherit "/std/food.c";

void
create_food()
{
	set_name("jelly");
	set_adj("rose");
        set_short("rose jelly");
	set_long("Made of rose leaves, sugar, and lemon salt "
		+ "cubes, this jelly is a delightful dessert.\n");

	set_amount(40);
}
