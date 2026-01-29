/*      The commander kroug's sword of darkness.

    coder(s):   Glykron
    history:
                 6/6/96   made keepable                    Maniac
                 6/4/96    some properties added           Maniac
                18/8/95     wieldable in any hand           Maniac
                24. 2.93    recovery added                  Glykron
                 9. 2.93    header added                    Glykron

*/

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep"; 
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_weapon()
{
    set_name("sword of darkness"); 
    add_name( ({ "sword", "dark_sword" }) );
    set_adj("dark");
    set_short("sword of darkness");
    set_pshort("swords of darkness");
    set_long("This sword exudes darkness.\n" );
    set_hit(40);
    set_pen(40);
    set_hands(W_ANYH);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_LIGHT, -1);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40)); 
    add_prop(OBJ_M_NO_BUY, 1); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, "evil");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchanted" }) );
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO, ({"A quite powerfully enchanted weapon, " +
                        "the darkness it exudes appears to be not of this " +
                        "world, being unusually deep and carrying a " +
                        "damageing charge.\n", 10}));
    add_prop(OBJ_S_WIZINFO, "This object is magical, and is obtainable " +
                            "by killing the kroug commander in the " +
                            "foothills.\n");
}


string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover() + 
	"#w_oa#" + query_prop(OBJ_S_ORIGIN_ALIGNMENT) + "#";
}


void
init_recover(string arg)
{
    string str, origin_alignment;
    sscanf(arg, "%s#w_oa#%s#", str, origin_alignment);
    init_wep_recover(str);
    init_keep_recover(str); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, origin_alignment);
}

