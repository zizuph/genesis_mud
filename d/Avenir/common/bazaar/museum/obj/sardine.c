// -*-C++-*-
// file name:	sardine.c	
// creator(s): 	Sirra March 98
// last update:	
// purpose:		appetizer
// note:
// bug(s):
// to-do:     

inherit "/std/food";

void
create_food()
{
    set_name(({"sardine", "food", "fish", "leaf", "grape leaf"}));
    set_adj("leafy");
    set_short("sardine in grape leaves");
    set_pshort("sardines in grape leaves");	
    set_long("A sardine fish wrapped in grape-vine leaves and "
	+ "topped with olive oil, lemon juice and parsley. "
	+ "It looks and smells surprisingly appetizing.\n");

    set_amount(125);
}

