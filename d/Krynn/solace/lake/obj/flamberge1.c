/* created by Splunge 01/14/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("flamberge");
    add_name("sword");
    set_adj("wicked");
    set_short("wicked flamberge");
    set_long("Wicked is all you can think of to describe this sword! " +
         "Its razor sharp blade consists of many sharp curves, and " +
         "to say the least, it looks deadly!\n");
    set_default_weapon(39, 36, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3500);
}






