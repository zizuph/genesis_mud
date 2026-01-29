inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 20
#define PEN 10

create_weapon()
{
    set_name("hammer");
    set_adj("heavy");
    add_adj("iron");
    set_short("heavy iron hammer");
    set_long("This heavy iron hammer consists of a wooden " +
    "handle attached to a heavy head. It's doesn't look "+
    "like it's a good weapon.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4500);
}


