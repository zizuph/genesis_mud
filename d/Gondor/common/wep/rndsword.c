/*
 *            A random sword - varies between mediocre to fairly good
 *            which is decided at creation.    -Elessar, 30/1-92
 *
 *		Updated to recover properly. Olorin, 8-feb-1996
 */
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public varargs void rnd_func(int hit = -1, int pen = -1);

public void
create_weapon()
{
    rnd_func();
    set_name("sword");
    set_pname("swords");
    set_adj("steel");
}

public varargs void
rnd_func(int hit = -1, int pen = -1)
{
    string  swordname;

    if (hit <= 0)
    {
        hit = 18 + random(7);
        pen = 20 + random(10);
    }

    swordname = ONE_OF_LIST( ({"broadsword", "longsword", "sword" }) );

    add_name(swordname);
    add_pname(swordname + "s");
    set_short("steel "+swordname);
    set_pshort("steel "+swordname+"s");
    set_long(BSN("This "+swordname+" has a sharp blade made of solid steel. "
        + "The hilt is made from wood and covered with leather. The crosspiece "
        + "was also forged from steel and consists of a simple metal rod about "
        + "as wide as the blade is where it meets with the crosspiece."));
    set_default_weapon(hit, pen, W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(hit, W_SWORD) + random(21) * 30 - 300);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen) + random(501) - 250);
}

public string
query_recover()
{
    return MASTER+":"
         + "#H#" + query_hit() 
         + "#P#" + query_pen()
         + "#" + query_wep_recover();
}

public void
init_recover(string arg)
{
    int     hit,
            pen;
    string  foo;

    sscanf(arg, "%s#H#%d#P#%d#%s", foo, hit, pen, foo);
    rnd_func(hit, pen);

    init_wep_recover(arg);
}

