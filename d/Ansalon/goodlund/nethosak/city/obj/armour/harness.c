inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_armour()
{
    set_name("harness");
    set_ac(19);
    set_at(A_BODY);
    set_am( ({ 4, -3, 0 }) );
    add_adj("leather");
    add_adj("imperial");
    set_short("imperial leather harness");
    set_pshort("imperial leather harnesses");
    set_long("This is a leather harness, which has been "+
    "constructed from blue leather. The harness has "+
    "been made rather big, and it would fit perfectly "+
    "around the body of a muscular dwarf or goblin. "+
    "Small steel studs has been places in small circles "+
    "around the armour, making it a bit more protective "+
    "and connects the different layers of leather with "+
    "eachother.\n"); 

    add_prop(OBJ_I_VOLUME, 5050);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
}


