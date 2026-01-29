#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

/*
* Modified from birds_nest.c
* Varian - 11/18/12
*/


inherit "/std/container";

void create_container() {
    set_name("hole");

    set_adj(({ "tree trunk", "tree", "hollow", "hollowed", "hollowed out"}));

    set_short("hole in a tree trunk");
    set_long("This hole has been hollowed out, probably by some " +
        "animal looking for a home. However, this hole now " +
        "appears to be deserted.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);

    set_no_show_composite(1);
    reset_container();
}

public int check_seen(object for_obj) {
    int light_level = environment(this_object())->query_light_level_for_living(for_obj);
    return (light_level == LIGHT_MIDDAY) || (light_level == LIGHT_BRIGHT);
}

void reset_container() {
    ::reset_container();

    if (!sizeof(all_inventory(this_object())) && IS_CLONE) {
        string *treasures = ({
            "/d/Gondor/rhovanion/mirkwood/obj/arm/lost_glove",
            "/d/Gondor/rhovanion/mirkwood/obj/arm/belt"

        });

        setuid();
        seteuid(getuid());
        object treasure = clone_object(treasures[random(sizeof(treasures))]);
        treasure->move(this_object());
    }
}