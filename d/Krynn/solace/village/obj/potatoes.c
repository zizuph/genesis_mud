/* The potatoes served at the Inn of Last homes. */

inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("plate of spiced potatoes");
    set_pshort("plates of spiced potatoes");
    set_name("potatoes");
    set_pname("potatoes");
    add_name("plate");
    add_pname("plates");
    set_adj("spiced");
    set_long("They look very tasty.\n");
    set_amount(351);
}

