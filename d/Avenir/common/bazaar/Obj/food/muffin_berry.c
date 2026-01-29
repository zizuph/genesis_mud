// -*-C++-*-
// file name:	muffin_berry.c
// creator(s): 	Lilith, Sept 1999
// last update:	
// purpose:	Food for the Bazaar Bakery
// note:
// bug(s):
// to-do:     

inherit "/std/food.c";

void
create_food()
{
    set_name("muffin");
    set_adj(({"berry"}));
    set_short("berry muffin");
    set_long("This muffin is like a small cake. Berries have "+
        "been stirred into the batter just prior to baking. "+
        "It is sweet and moist and should be quite tasty.\n");

    set_amount(40);
}

