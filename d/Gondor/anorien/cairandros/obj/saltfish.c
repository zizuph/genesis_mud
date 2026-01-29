/*
 * Salted fish to eat
 * /d/Gondor/anorien/cairandros/obj/saltfish
 *
 * Varian - February, 2020
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "../../defs.h"

inherit "/std/food";

void
create_food() 
{
    set_name("fish");
    set_short("salted fish");
    set_adj("salted");
    set_long("This is a salted and cured fish. It looks like " +
        "it should be edible for quite a long while.\n");

    set_amount(50);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 90);
    add_prop(OBJ_I_VALUE, 35);
}
