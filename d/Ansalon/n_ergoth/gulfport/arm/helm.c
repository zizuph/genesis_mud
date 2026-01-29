
/*
 * helm.c
 * Plate helm
 * Ergothian Guards
 * Gulfport, Northern Ergoth
 * Tibbit, 22 May 1998
 *
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("helm");
    add_adj("shiny");
    add_adj("plate");
    set_short("shiny plate helm");

    set_long("This simple-looking plate helm is padded inside "+
        "and is one of the most protective designs available. "+
        "The exterior has been proudly polished to a shine.\n");

    set_at(A_HEAD);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 1000);

}

