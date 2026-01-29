/*
 * Steel buckler - a standard issue shield for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name(({"buckler", "shield"}));
    set_short("black buckler");
    set_pshort("black bucklers");
    set_long("A small round buckler crafted from quality steel. The handle " +
        "is wrapped with leather straps for improved grip. The face of the " +
        "buckler is adorned with an outline of a rising red sun across a " +
        "black background. A central protrusion is set in the face to aid in " +
        "parrying attacks.\n");
    add_item("handle", "The steel handle is skillfully riveted to the " +
        "buckler. Cured leather straps is wrapped around the handle to " +
        "improve the grip\n");
    add_item("face", "The face of the buckler is skillfully hammered into " +
        "a smooth round shape, with no visible weakness in the shaping of " +
        "the central protrusion. The outline of a rising red sun across a " +
        "black background is adorning the entire face.\n");
    add_item("protrusion", "The central protrusion of the buckler gives " +
        "effective aid when parrying blows.\n");
    set_default_armour(30, A_SHIELD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    // Seeing as this is a small shield, reduce the weight
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_SHIELD) / 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
