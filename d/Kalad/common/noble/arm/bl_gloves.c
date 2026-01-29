inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("black");
    add_adj("leather");
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather gloves");
    set_long("These are very fine gloves made of blackened leather. "+
    "They are soft, but have lead plates in them, to make them hurt "+
    "when slaping someone.\n");
    set_ac(3);
    set_at(A_HANDS);
    add_prop(OBJ_I_WEIGHT,80);
    add_prop(OBJ_I_VOLUME,50);
}

