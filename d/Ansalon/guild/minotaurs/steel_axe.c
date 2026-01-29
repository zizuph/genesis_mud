#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";

create_weapon()
{
    set_name("axe");
    add_name("waraxe");
    add_adj("large");
    add_adj("steel");
    add_adj("metal");
    set_short("large steel waraxe");
    set_long("This is a plain steel waraxe. " +
             "It's blade is sharp and it is well polished.\n");
    
    set_default_weapon(40, 40, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 1300);
}
