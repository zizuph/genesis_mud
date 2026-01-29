/* 	The sword of light wielded by the white knight in the crystalline palace

    coder(s):   Glykron
    history:
                24. 2.93    recovery added                  Glykron
                 9. 2.93    header added                    Glykron

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_weapon()
{
    set_name( ({ "sword", "light_sword" }) );
    set_adj("light");
    set_short("sword of light");
    set_pshort("swords of light");
    set_long("This sword glows with a brilliant white aura.\n" );
    set_hit(40);
    set_pen(40);
    set_hands(W_RIGHT);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, "good");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchanted" }) );
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() +
	"#w_oa#" + query_prop(OBJ_S_ORIGIN_ALIGNMENT) + "#";
}

void
init_recover(string arg)
{
    string str, origin_alignment;
    sscanf(arg, "%s#w_oa#%s#", str, origin_alignment);
    init_wep_recover(str);
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, origin_alignment);
}
