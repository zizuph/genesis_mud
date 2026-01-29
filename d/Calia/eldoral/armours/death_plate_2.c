#pragma strict_types

#include "defs.h"

#define AC 40

inherit "/std/armour";

public void
create_armour()
{
    set_name("armour");
    set_adj("charred");
    add_adj("plate");
    set_short("charred plate armour"); 
    set_pshort("charred plate armours"); 
    set_long("This plate armour is of excellent work, " +
        "but like nothing you've seen before, and not " +
        "aging very well. It appears to have been charred, " +
        "badly, and gets its colour from a soot-like residue. " +
        "The breastplate of the armour is quite common, forged" +
        "and hammered to fit to the chest. The shoulders have " +
        "what look like small, curved shields attached to them. " +
        "From beneath the breastplate, extra heavy chainmail " +
        "descend to cover the lower torso, and similar links " +
        "descend from the shoulder-shields to drape across " +
        "the arms.\n");
    set_ac(AC);
    set_at(A_BODY | A_ARMS);
    set_af(TO);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
