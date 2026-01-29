
inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"


void
create_weapon()
{
    set_name("lance");
    add_adj("footmans");
    add_adj("footman's");
    add_adj("deadly");
    set_short("deadly footman's lance");
    set_long("This lance is essentially a long spear with a nasty looking " +
        "tip that is covered with bright runes. This weapon looks extremely " +
        "deadly, being light and quick to maneuver into position.\n");

    set_hit(42);
    set_pen(45);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"This footman's lance has had minor enchantments placed upon it " +
        "to make it easier to hit and penetrate armour with.\n",55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,45) + 500 + random(500)); 
}

mixed
wield(object what)
{
    return 0;
}

