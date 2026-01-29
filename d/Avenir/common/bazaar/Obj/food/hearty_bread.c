// -*-C++-*-
// file name:	bread.c	
// creator(s): 	
// last update:	
// purpose:	for the bazaar bakery
// note:
// bug(s):		
// to-do:     

inherit "/std/food.c";

void
create_food()
{
    set_short("large loaf of hearty bread");
    set_pshort("large loaves of hearty bread");
    add_name(({"bread", "loaf", "food"}));
    add_adj(({"hearty", "rye"}));
    set_long("A warm loaf of hearty bread made with "+
        "light and dark rye. It has a wonderful rich "+
        "smell and hearty taste.\n");

    set_amount(350);
}


