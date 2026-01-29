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

    write("How wonderful! The sweetness of the mascarpone is an "+
        "excellent foil for the vague smoke-salt flavour of the salmon."+
        "\n");

    say(QCTNAME(this_player()) + " savours "+ short() +".\n");
}

void
create_food()
{
    set_name("salmon canape");
    add_name(({"salmon", "canape", "smoked salmon", "mascarpone", "morsel", "delicacy"}));
    set_pname(({"canapes", "salmons", "mascarpones"}));
    set_short("smoked salmon and mascarpone canape");
    set_pshort("smoked salmon and mascarpone canapes");
    add_adj(({"bite-sized", "tiny" }));
    set_long("A small round slice of bread is spread with chive butter. "+
        "Atop the butter is a cone of thinly sliced smoked salmon "+
        "filled with a swirl of mascarpone cheese sprinkled with "+
        "dill.\n");
    set_amount(75);
}
