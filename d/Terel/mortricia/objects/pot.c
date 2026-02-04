/*
    A big iron pot. Mortricia 920722
 */
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

init()
{
    add_action("stir", "stir");
    ::init();
}

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

stir(string how)
{
    object powder, snow;

    powder = present("powder");
    snow = present("snow");
    if (powder && snow) {
        write("You managed to stir the powder and snow together.\n");
        say(QCTNAME(this_player()) + " is making something in the pot.\n");
        powder -> remove_object();
        snow -> remove_object();
    } else {
        write("Nothing happened. Wrong ingredients?\n");
    }
    return 1;
}
