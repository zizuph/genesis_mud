/* Ashlar, 4 Oct 97 */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 40
#define PEN 37

create_weapon()
{
    set_name("mace");
    set_adj("silver-trimmed");
    add_adj("two-handed");
    set_short("silver-trimmed two-handed mace");
    set_pshort("silver-trimmed two-handed maces");
    set_long("This silver-trimmed two-handed mace consists of a steel " +
    "handle attached to a heavy head. The handle is trimmed with silver " +
    "and has a comfortable two-handed grip.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(30)+50);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4500);
}


