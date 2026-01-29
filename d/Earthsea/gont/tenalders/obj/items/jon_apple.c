// a red jonathan apple -- Amelia 5-28-98

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("apple");
    add_adj("jonathan");
    set_adj(({"large", "perfect", "juicy", "red"}));
    set_short("red jonathan apple");
    set_long("A large red jonathan apple.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}
