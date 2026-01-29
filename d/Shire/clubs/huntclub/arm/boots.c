inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("boots");
    set_short("weathered leather boots");
    set_adj(({"weathered","leather"}));
    set_long("This " + short() + " are made from boiled leather " +
       "with raw hide stitching. The souls are made from hardened leather souls, " +
       "that still have some use in them.\n");
    set_ac(1);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 100);
}