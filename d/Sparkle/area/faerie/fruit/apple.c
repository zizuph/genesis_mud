/*
 * Fruit from the Faerie garden
 * Coded by Finwe, May 2005 */
 
inherit "/std/food";
#include <stdproperties.h>
 
public void
create_food()
{
    set_name("apple");
    add_name("fruit");
    set_adj(({"juicy", "red"}));
    set_short("juicy red apple");
    set_long("It's a juicy, red apple. It's perfectly round and looks " +
        "tasty. The top of the apple is slightly green but turns red " +
        "like the rest of the fruit. The bottom of the apple has a " +
        "couple of bumps.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
