/* Ashlar, 20 Oct 97 */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

#define HIT 35
#define PEN 32

create_weapon()
{
    set_name("mace");
    set_adj("silver-trimmed");
    add_adj("one-handed");
    set_short("silver-trimmed one-handed mace");
    set_long("This silver-trimmed one-handed mace consists of a steel " +
    "handle attached to a heavy head. The handle is trimmed with silver " +
    "and has a comfortable one-handed grip.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(30));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2700);
}
