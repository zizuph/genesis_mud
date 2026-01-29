/*
 * Gold hoop earring - Gold earring worn by corsairs near Linhir
 * Based on Haradrim earrings
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_armour()
{
    set_name("earring");
    set_short("gold hoop earring");
    set_pshort("gold hoop earrings");
    set_long("A wide gold hoop earring with a solid clasp. A gold bead with an " +
        "engraving of a rising sun is threaded on the hoop.\n");
    set_default_armour(8, A_ANY_EAR);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 1);
}
