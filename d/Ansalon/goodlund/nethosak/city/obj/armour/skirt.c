inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_armour()
{
    set_name("skirt");
    set_ac(19);
    set_at(A_LEGS);
    set_am( ({ 4, -3, 0 }) );
    add_adj("leather");
    add_adj("imperial");
    set_short("imperial leather skirt");
    set_pshort("imperial leather skirts");
    set_long("This is a reinforced skirt, made out of hardened "+
    "leather. The skirt has been made out of several "+
    "different layers of leather that has been reinforced "+
    "with thin iron threads. To provide even more "+
    "protection, small studs has been placed around "+
    "the skirt.\n");   

    add_prop(OBJ_I_VOLUME, 850);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(29, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(29));
}

