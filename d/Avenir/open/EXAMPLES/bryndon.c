// -*-C++-*-
// file name:	bryndon.c	
// creator(s): 	
// last update:	
// purpose:		for the bazaar bakery
// note:
// bug(s):
// to-do:     

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

void
special_effect(int amnt)
{
    string str;

    write("Holding the pastry between two fingers, you take a "+
        "nibble.\nThe taste is so delightful that you "+
        "finish the rest off with sybaritic abandon.\n");

    say(QCTNAME(this_player()) + " nibbles upon "+ short() +
        ", then finishes the rest off with sybaritic abandon.\n");
}

void
create_food()
{
    set_name("bryndon");
    add_name("cake");
    set_adj(({"cake","bryndon","sweet","tidbit","confection"}));
    set_short("bryndon cake");
    set_long("A colourful sweet tidbit made with figs, dates, "+
        "pine nuts and currants simmered in sweet wine and "+
        "honey spiced with clove, mace, and mint. A rounded "+
        "spoonful of the reddish confection has been dropped "+
        "into a lightly fried bit of thin pie crust dyed "+
        "yellow with saffron.\n");

    set_amount(20);
}


