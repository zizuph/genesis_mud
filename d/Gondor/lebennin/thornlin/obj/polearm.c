inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"polearm","weapon"}));
    set_short("long polearm");
    set_pshort("long polearms");
    set_long(BSN("This a polearm, an axe with a long wooden shaft, used by "+
	"the militia in villages in Lossanach. The metal is "+
	"some kind of light metal."));
    set_adj(({"light", "long", "sharp"}));
    set_default_weapon(18,18,W_POLEARM,W_IMPALE,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,18)+random(200)-100);
    add_prop(OBJ_I_WEIGHT,
      (F_WEIGHT_DEFAULT_WEAPON(18, W_POLEARM) + random(200) - 100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
}

query_recover()
{
    return MASTER + ":" + query_wep_recover();
}
init_recover(arg)
{
    init_wep_recover(arg);
}
