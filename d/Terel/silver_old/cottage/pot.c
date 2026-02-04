/*
    A big iron pot. Mortricia 920722
 */
inherit "/std/container";
#include <stdproperties.h>

create_container()
{
    set_name("pot");
    set_short("iron pot");
    set_pshort("iron pots");
    set_long("It's a large iron pot.\n");
    set_adj(({"large"}));

    add_prop(OBJ_I_VALUE, 200 + random(20));

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
}
