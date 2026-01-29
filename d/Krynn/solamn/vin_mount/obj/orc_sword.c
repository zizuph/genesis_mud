/* created by Aridor 06/20/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("sword");
    set_short("nice sword");
    set_adj("nice");
    set_long("This is not a hobgoblin sword! He must have stolen it "
        +    "somewhere.\n");
    set_default_weapon(25, 27, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1600);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
