// -*-C++-*-
// file name:	muffin_buckler.c
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
    set_adj(({"cake","seed","buckler"}));
    set_short("buckler muffin");
    set_long("This buckler muffin is so named because its "+
        "circular shape reminds one of the buckler, a round "+
        "shield. This particular muffin is made with the "+
        "bakers secret ingredient (ale) and a variety of "+
        "seeds, such as poppy, anise, and caraway.  It is "+
        "sweet and tasty.\n");

    set_amount(50);
}

