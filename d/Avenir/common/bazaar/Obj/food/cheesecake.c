// -*-C++-*-
// file name:	cheesecake.c	
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
    write("Your eyes widen with surprise at its subtle flavour "+
        "and creamy texture. "+
	"It is delicious beyond description.\n");

    say(QCTNAME(this_player()) + ", with a mixture of tenderness "+
        "and delight, savours " + short() + ".\n");
}


void
create_food()
{
    set_name("cheesecake");
    set_adj(({"elderflower","cake"}));
    set_short("slice of elderflower cheesecake");
    set_pshort("slices of elderflower cheesecake");
    set_long("This is a slice of paradise! How something so "+
        "delicious-looking can come from the humble beginnings "+
        "of cottage curd, cream, dried elderflowers and rose-water "+
        "is beyond your comprehension. Yet here it is, a "+
        "marvellous dessert mildly flavoured with clove and nutmeg "+ 
        "to compliment the floral scents, served to you on a "+
        "thin, crispy crust.\n");

    set_amount(80);
}

