// -*-C++-*-
// file name:	
// creator(s): 	
// last update:	
// purpose:	
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

    write("Now that is refreshingly cool treat."+
        "\n");

    say(QCTNAME(this_player()) + " savours "+ short() +".\n");
}

void
create_food()
{
    set_name("shaved ice");
    add_name(({"snack", "fruit juice", "shaved ice", "cup", "ice"}));
    set_pname(({"cups", "ices"}));
    set_short("cup of shaved ice");
    set_pshort("cups of shaved ice");
    add_adj(({"bite-sized", "tiny", "cold" }));
    set_long("A small cone-shaped cup mounded with ice shaved so "+
        "finely it looks like snow. It has been sprinkled with a "+
        "bit of fruit juice, making it a healthy and refreshing "+
        "treat.\n");
    set_amount(75);
}
