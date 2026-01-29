/*
 * A puddle in the Pelargir newbiecamp.
 *
 * NCAMP_OBJ + "puddle8.c"
 *
 * Alto, 18 November 2002
 *
 */


inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

object gear;

void
create_container()
{
    set_short("wide puddle");
    set_name("puddle");
    set_adj("wide");
    set_long("This is a particularly wide puddle in the middle "
        + "of the path. It has become wider over the years as "
        + "people walked around it, further depressing the dirt "
        + "at its edges.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "How exactly do you take a puddle?\n");
    add_prop(OBJ_I_VOLUME,      10000);
    add_prop(OBJ_I_WEIGHT,      10000);
    add_prop(CONT_I_VOLUME,     20000);
    add_prop(CONT_I_WEIGHT,     20000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    setuid();
    seteuid(getuid());
    
    switch (random(4))
    {
        case 0:
            gear = clone_object(NCAMP_WEP + "ncamp_hscim.c");
            gear->move(TO);
            break;
        case 1:
            gear = clone_object(NCAMP_WEP + "ncamp_oclub.c");
            gear->move(TO);
            break;
        case 2:
            gear = clone_object(NCAMP_ARM + "hhelm.c");
            gear->move(TO);
            break;
        case 3:
            gear = clone_object(NCAMP_ARM + "hmail.c");
            gear->move(TO);
            break;
        default:
            gear = clone_object(NCAMP_ARM + "hshield.c");
            gear->move(TO);
            break;
    }
}

