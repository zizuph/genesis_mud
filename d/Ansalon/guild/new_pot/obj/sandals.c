/* Stralle @ Genesis 010604
 *
 * A pair of sandals
 *
 * Revisions:
 *   Lucius, Aug 2016: Made always recoverable.
 *
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

public void
create_armour(void)
{
    set_name("sandals");
    add_name("pair of sandals");
    set_pname("pairs of sandals");
    set_adj(({"black", "leather"}));

    set_short("pair of black leather sandals");
    set_pshort("pairs of black leather sandals");
    set_long("This pair of black leather sandals has a hard base " +
        "with leather straps that fastens over the foot and the " +
        "lower ankles.\n");

    set_ac(1);
    set_at(A_FEET);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 30);

    set_keep(1);
    set_alarm(1.5, 0.0, set_may_recover);
}
