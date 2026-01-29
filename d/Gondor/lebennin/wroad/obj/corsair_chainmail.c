/*
 * Steel chainmail - a standard issue chainmail for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name("chainmail");
    set_short("rough chainmail");
    set_pshort("rough chainmails");
    set_long("Made from links of steel, this strong armour covers the upper " +
        "torso of its wearer. The chainmail is well worn and the steel has " +
        "gone dark from wear and tear.\n");
    add_item(({"links", "chains"}), "Small solid steel chains interlocking " +
        "to make a sturdy protection against various weapons. Some of the " +
        "chains bear the marks of previous combat.\n");

    set_default_armour(20, A_BODY, ({-2, 1, -2}));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
