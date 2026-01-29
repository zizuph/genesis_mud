/*
 * Food item cloned for halfling guild
 * Finwe, January 2015
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("apple");
    add_name("fruit");
    set_adj(({"juicy", "red"}));
    set_short("juicy red apple");
    set_long("It's a juicy, red apple.The fruit round and looks tasty with " +
        "a couple of bumps on the bottom. The apple is slightly green but " +
        "turns red. The bottom of the apple has a couple of bumps.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
