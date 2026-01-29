/* Herbalist's gloves by Teth Jan 22 1997 */
/* Modified into leather gloves by Gwyneth, 11/8/99 */
/*
 * Revisions:
 *   Lucius, Aug 2016: Made always recoverable.
 *
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_armour(void)
{
    set_name("gloves");
    add_name("pair of gloves");

    set_pname("gloves");
    add_pname("pairs of gloves");

    set_adj(({"leather","herbalist's"}));
    set_short("pair of leather gloves");
    set_pshort("pairs of leather gloves");
    set_long("This pair of gloves is merely for protection against " +
        "the various contact poisons an herbalist may find while " +
        "collecting plants. The pair of gloves offers no protection against " +
        "blunt attacks on the hands, and a little protection against " +
        "slashing and impaling weapons.\n");

    set_ac(1);
    set_am(({0, 1, -1}));
    set_at(A_HANDS);

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));

    set_keep(1);
    set_alarm(1.5, 0.0, set_may_recover);
}
