/*
    A bag.
 */
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

create_container()
{
    set_name("bag");
    set_short("large purple bag");
    set_long("It's a large bag.\n");
    set_adj(({"large","purple"}));

    add_prop(OBJ_I_VALUE, 40 + random(20));

    add_prop(CONT_I_WEIGHT, 600);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 0);
}
