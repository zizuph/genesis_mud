/* Coded by Ckrik May 1998, for the Elite Gont Guards */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    add_name("longsword");
    add_pname("longswords");
    set_adj("steel");
    set_adj("shiny");
    set_short("shiny steel longsword");
    set_pshort("shiny steel longswords");
    set_long("This longsword is standard issue for the elite" +
        " Gont guards. It is long and of medium width giving it strength," +
        " without too much extra weight. Its metallic" +
        " colour gives off a dull silver shine. It is well" +
        " forged and balanced, an excellent weapon indeed.\n");
    set_hit(28);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 32) + random(20) - 10);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}
