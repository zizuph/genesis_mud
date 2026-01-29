/* The pear fruit picked from the tree in Qualinesti. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("pear");
    add_name( ({"pear fruit", "fruit" }) );
    set_adj("yellow");
    set_short("yellow fruit");
    set_long("This yellow pear is thinner at the top than at " +
        "the bottom. Even if it looks a bit funny it is probably " +
        "delicious.\n");
    set_amount(13);
}

