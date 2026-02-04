/*
    A wooden desk. Mortricia 920910
 */
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

create_container()
{
    set_name("desk");
    set_short("wooden desk");
    set_long("It's a large wooden desk.\n");
    set_adj(({"large"}));

    add_prop(OBJ_I_VALUE, 1024);

    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(CONT_I_VOLUME, 20000);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
}
