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
    set_name("sabre");
    set_pname("sabres");
    add_pname("weapons");
    add_pname("swords");
    add_name("sword");
    set_adj("light");
    add_adj("green");
    set_long("This weapon is incredible light, quite fitted for fast attacks. "+
    "It is also less durable than regular swords if not used by a master swordsman. "+
    "The sabre has a round guard that offers additional protection to the hand, "+
    "giving the wielder the ability to focus more on his own attacks than the "+
    "difficulty of defending.\n");
    set_short("light green sabre");
    set_default_weapon(40, 40, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40));
}
