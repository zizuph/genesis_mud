/*
 * The bench in the Royal Stables of Minas Tirith.
 *
 * /d/Gondor/minas/obj/stable_bench.c
 *
 * Alto, 10 April 2001
 *
 */


inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

object crop, mallet, rake;


void
create_container()
{
    set_short("large bench");
    set_name("bench");
    set_adj("large");
    set_long("This is a large wooden bench used by the Stablemaster "
        + "and his assistants to store their various grooming tools. "
        + "It is bleached almost white from many years in the sun. "
        + "It is also covered with a liberal coating of dust.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The bench is far too heavy to pick up.\n");
    add_prop(OBJ_I_VOLUME,      1000);
    add_prop(OBJ_I_WEIGHT,      1000);
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_WEIGHT,     2000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_ATTACH,    1);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    crop = clone_object(INNER_MINAS + "/obj/horse_crop.c");
    crop->move(TO);

    mallet = clone_object(INNER_MINAS + "/obj/horse_mallet.c");
    mallet->move(TO);

    rake = clone_object(INNER_MINAS + "/obj/horse_rake.c");
    rake->move(TO);


}

