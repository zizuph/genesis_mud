inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("dish of bread and cheese");
    set_pshort("dishes of bread and cheese");
    set_name("dish");
    set_pname("dishes");
    add_name("bread");
    add_pname("breads");
    set_long("A dish filled with bread and cheese.\n");
    set_amount(150);
}
