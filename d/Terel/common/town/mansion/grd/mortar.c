/*
    A big iron pot. Mortricia 920722
    Janus 921021
 */
inherit "/std/container";
#include "/d/Terel/common/terel_std_rec.h"
#include <stdproperties.h>
#include <macros.h>

init()
{
    add_action("mix", "mix");
    ::init();
}

create_container()
{
    set_name("pot");
    set_short("iron pot");
    set_pshort("iron pots");
    set_long("A small and rusty iron pot. Used to mix ingredients.\n");
    set_adj(({"small"}));

    add_prop(OBJ_I_VALUE, 200 + random(20));

    add_prop(CONT_I_WEIGHT, 1100);
    add_prop(CONT_I_MAX_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_VOLUME, 20000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
}

mix(string how)
{
    object bflow, tflow, gflow;

    bflow = present("black flower");
    tflow = present("white flower");
    gflow = present("green flower");
    if (bflow && gflow) {
        write("You managed to mix the ingredients.\n");
        say(QCTNAME(this_player()) + " is mixing something in the pot.\n");
        bflow -> remove_object();
        gflow -> remove_object();
    } else {
        write("Nothing happened. Wrong ingredients?\n");
    }
    return 1;
}
