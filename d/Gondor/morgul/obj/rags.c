/*
 * /d/Gondor/morgul/obj/rags.c
 *
 * Rags worn by the elf prisoner in the torture chamber.
 *
 * Gwyneth, June 3, 2000
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("tunic");
    set_pname("tunics");

    set_adj("bloody");
    add_adj("torn");

    set_short("bloody torn tunic");
    set_pshort("bloody torn tunics");

    set_long("Once a garment of fine quality, all that is left " +
        "is threadbare patches of fabric stained with blood.\n");

    set_default_armour(1, A_TORSO, 0, 0);

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 9);
    add_prop(OBJ_I_VOLUME, 3);
}
