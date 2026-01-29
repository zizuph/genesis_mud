/*  standard bronze scimitar wielded by kargs in Gont
*  Ten Alders 
*  Amelia 5/3/97
*/
inherit "/std/weapon";
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>

void
create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    set_adj(({"bloody", "razor-edged", "bronze"}));
    set_short("razor-edged bronze scimitar");
    set_long(break_string("Honed to a sharp razor edge, this "+
	"scimitar is crafted from fine mirror-like bronze. Its curved "+
	"blade looks thirsty for the blood of its next victim, "+
	"even though still dripping from the blood of its last.\n", 70));
    set_hands(W_BOTH);
    set_hit(31);
    set_wt(W_SWORD);
    set_pen(21);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(31, 21) +
      random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31, 21) + random(10));
}

void
query_recover()
{
    return MASTER+":"+query_wep_recover();
}
void
init_recover(string arg)
{
    init_wep_recover(arg);
}
