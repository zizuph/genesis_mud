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

    write("What a refreshing and subtle morsel!\n");

    say(QCTNAME(this_player()) + " savours "+ short() +".\n");
}

void
create_food()
{
    set_name("cucumber sandwich");
    add_name(({"cucumber", "sandwich", "morsel", "delicacy"}));
    set_pname(({"cucumbers", "sandwiches", "morsels", "delicacies"}));
    set_short("cucumber sandwich");
    set_pshort("cucumber sandwiches");
    add_adj(({"bite-sized", "tiny"}));
    set_long("Very thin slices of cucumber sprinkled with salt and "+
        "vinegar lay atop small rectangle of bread spread daubed "+
        "with tarragon butter.\n");
    set_amount(50);

}
