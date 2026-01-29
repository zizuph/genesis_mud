inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>


void
create_weapon()
{
    set_name("scimitar");
    set_pname("scimitars");
    add_pname("weapons");
    add_pname("swords");
    add_name("sword");
    set_adj("large");
    add_adj("steel");
    set_long("This weapon feels wonderfully balanced and is extremely sharp, " +
    "too! That a very skilled smith has been at work here is very evident. "+
    "\nAny swordmaster would envy the wielder of this blade.\n");
    set_short("large steel scimitar");
    set_default_weapon(40, 40, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40));
}
