/*
    A big iron pot. Mortricia 920722
 */
inherit "/std/container";
#include <stdproperties.h>

void
create_container()
{
    set_name("cauldron");
    add_name("pot");
    set_short("large blackened cauldron");
    set_pshort("cauldrons");
    set_long("It's a large blackened cauldron.\n");
    set_adj(({"large"}));
    // description is in the room long description
    set_no_show_composite(1); 

    add_prop(OBJ_I_VALUE, 200 + random(20));

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_NO_GET, 1);
}
