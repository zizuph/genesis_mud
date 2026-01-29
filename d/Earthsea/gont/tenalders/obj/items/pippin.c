// a tart green pippin apple
// Amelia 5-27-98

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("apple");
    add_adj("pippin");
    set_adj(({"tart", "green"}));
    set_short("tart green pippin apple");
    set_long("This is a tart green pippin apple.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}
