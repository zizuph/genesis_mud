#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>

create_weapon(){
    set_name("chisel");
    set_adj("steel");
    set_short("chisel");
    set_long(break_string("This looks like an ordinary, steel chisel. " +
	"it looks too rough so you don't think it was used by a " +
	"sculptor - maybe it used to be a tool of a miner?\n",70));
    add_prop(OBJ_I_VALUE, 200);
    set_hit(5);
    set_pen(5);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop("mystic_weapon", 1);
    add_prop("_mining_axe", 1); /* added Feb 3 94, suggestion mercase */
}
