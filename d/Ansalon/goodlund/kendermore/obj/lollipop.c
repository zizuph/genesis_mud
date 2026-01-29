inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#define adjecs query_adjs()

string *adjs=({"red", "pink", "orange", "green", "yellow"});

void
create_food()
{
    set_name("lollipop");
    add_name("pop");
    add_name("candy");
    set_pname("lollipops");
    add_pname("candies");
    add_pname("pops");
    set_adj("sweet");
    add_adj(adjs[random(5)]);
    set_long("Wrapped in colourful " + adjecs[1] + " paper, you know this " + 
             "lollipop holds a sweetness that will tingle your tastebuds.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}

void
init()
{
    ::init();
    add_action("crunch_pop", "crunch");
}

/* Function name: crunch 
 * Description: This allows a person to crunch on their lollipop
 */

int
crunch_pop(string str)
{
    NF("Crunch what?\n");
    if ((str == "pop") || (str == "lollipop"))
    {
        write("You crunch down hard on your sweet " + adjecs[1] + 
              " lollipop and bite a few pieces off.\n");
        say(QCTNAME(TP) + " crunches on " + HIS(TP) + " " + adjecs[1] + 
            " lollipop.\n");
        return 1;
    }
    return 0;
}
