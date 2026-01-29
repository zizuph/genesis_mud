/* A dwarven waraxe
 * Crafted to suit the smaller races of gnomes and dwarves.
 *
 * Arman July 2017
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

void
create_weapon()
{
    seteuid(getuid(TO));
    set_name("axe");
    add_name("waraxe");
    set_adj("steel");
    add_adj("dwarven");
    set_short("dwarven steel waraxe");
    set_long("This is a waraxe crafted by dwarven smiths of the " +
        "Theiwar Clan. While not as renowned weaponsmiths as some of " +
        "their other mountain dwarf cousins, this weapon is exquisite " +
        "in make and would be the envy of smiths of other races.\n");

    add_prop(OBJ_S_WIZINFO, "A non-magical waraxe that has better " +
        "hit/pen in the hands of a dwarf or gnome.\n");

    set_default_weapon(30, 30, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 10000);

    set_wf(TO);
}


void
miner_wield()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_tell("For someone of your size and stature this " +
        "waraxe balances well in your hands.\n");

    set_hit(35);
    set_pen(35);
    wielder->update_weapon(TO);
}

void
default_wield()
{
    if(E(TO) != wielder)
        return;

    set_hit(30);
    set_pen(30);
    wielder->update_weapon(TO);
}

mixed
wield(object what)
{
    wielder = TP;

    if(TP->query_race_name() == "dwarf" || 
       TP->query_race_name() == "gnome")
        set_alarm(1.0, 0.0, miner_wield);
    else
        set_alarm(1.0, 0.0, default_wield);
    return 0;
}