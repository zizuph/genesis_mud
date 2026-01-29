/* Bread for luring out the rat in the prisoner cell in Pax Tharkas. */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_name(({"bread", "piece of bread", "_bread_"}));
    set_adj("old");
    set_short("old piece of bread");
    set_pshort("old pieces of bread");
    set_long("This piece of bread is moulden and it doesn't " +
             "look appetizing at all. You'll probably get some " +
             "kind of stomach malady if you eat it.\n");
    set_amount(5);
}

