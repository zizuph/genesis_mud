#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Rhovanion/defs.h"

#define WEAPON_HIT 19+random(5)
#define WEAPON_PEN 14+random(10)

void
create_weapon()
{
    set_name("sword");
    add_name("_filip_sword_");

    set_adj("elven");

    set_short("elven sword");
    set_pshort("elven swords");

    set_long("This is elven made sword.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt((W_SLASH | W_IMPALE));
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, (6000+random(1100)));
    add_prop(OBJ_I_VOLUME, (2500+random(1100)));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) *
                          (90+random(21)) / 100);
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
