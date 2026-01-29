/*
 * /d/Gondor/minas/obj/horse_crop.c
 *
 * A tool for the bench in the Royal Stables
 *
 * Alto 23 April 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"


void
create_object()
{
    set_name("crop");
    set_adj("leather");
    add_adj("riding");
    set_short("leather riding crop");
    set_pshort("leather riding crops");
    set_pname("crops");
    set_long("This is a leather riding crop used by the grooms of the stables "
        + "to motivate the horses during exercise. On the handle is a small "
        + "inscription.\n");
    add_item(({"inscription", "small inscription"}), "The inscription "
        + "reads: Property of the Royal Stables.\n");
    add_item(({"handle"}), "It bears a small inscription.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}

