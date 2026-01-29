/*
 * /d/Gondor/.../casket.c
 *
 * This casket is the chest that the White Crown, the crown of the King of
 * Gondor will be in.
 *
 * /Mercade, 6 October 1993
 *
 * Revision History
 */

inherit "/d/Gondor/lib/container.c";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_container()
{
    set_name("casket");

    set_adj("great");
    add_adj("black");
    add_adj("lebethron");

    set_short("great casket of black lebethron");
    set_pshort("great caskets of black leberthon"); /* This isn't possible */
    set_long("@@long_description");

    add_item( ({ "bound", "bounds" }),
        BSN("Silver bounds are used to make this casket strong and well " +
        "decorated."));
    add_item( ({ "lebethron", "black lebethron" }),
        BSN("The casket is made of wood from the fair tree lebethron, " +
        "beloved of the woodwrights of Gondor."));

    add_prop(OBJ_I_VALUE,          500);
    add_prop(CONT_I_VOLUME,     268000); /* 190 * 40 * 70 cm interior */
    add_prop(CONT_I_WEIGHT,      50000);
    add_prop(CONT_I_MAX_VOLUME, 800000); /* 200 * 50 * 80 cm exterior */
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_RIGID,           1);
    add_prop(CONT_I_CLOSED,          1);
}

long_description()
{
    string str = "The casket is great and made of black lebethron. It is " +
        "bound with silver. ";

    if (query_prop(CONT_I_CLOSED))
    {
        return BSN(str + "It is closed.");
    }

    return BSN("It is opened and the interior of the casket is covered " +
        "with velvet. This casket must have been made for someone of high " +
        "office.");
}
