/*
 * Fruit from the Faerie garden
 * Coded by Finwe, September 1999 */
 
inherit "/std/food";
#include <stdproperties.h>
 
public void
create_food()
{
    set_name("orange");
    add_name("fruit");
    set_adj(({"large", "sweet"}));
    set_short("large sweet orange");
    set_long("This is a " + short() + ". It's perfectly round with a " +
        "thick, textured rind. The fruit is sweet smelling and looks " +
        "delicious to eat.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
