/* A dwarven pickaxe
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
    add_name("pickaxe");
    set_adj("steel");
    add_adj("dwarven");
    set_short("dwarven steel pickaxe");
    set_long("This is a mining pickaxe of dwarven make, finely crafted " +
        "to break through the earth to find underground riches. In " +
        "typical dwarven fashion this pickaxe also has utility as a " +
        "nasty weapon in the hands of a warrior.\n");

    add_prop(OBJ_S_WIZINFO, "A non-magical pickaxe that has better " +
         "hit/pen in the hands of a dwarf or gnome.\n");

    set_default_weapon(20, 25, W_AXE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 8000);

    set_wf(TO);
}


void
miner_wield()
{
    if(E(TO) != wielder)
        return;
    wielder->catch_tell("For someone of your size and stature this " +
        "pickaxe balances well in your hands.\n");

    set_hit(30);
    set_pen(35);
    wielder->update_weapon(TO);
}

void
default_wield()
{
    if(E(TO) != wielder)
        return;

    set_hit(20);
    set_pen(25);
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