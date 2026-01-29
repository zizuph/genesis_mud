#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/container";

void create_container() {
    set_name("nest");
    set_adj(({ "bird's", "birds" }));
    set_short("bird's nest");
    set_long("The bird that owns this nest is nowhere to be found, and "
        + "if you had to guess, you would probably suspect that the "
        + "nest has now been abandoned.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);

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
        string *gems = ({
            "/d/Genesis/gems/obj/quartz",
            "/d/Genesis/gems/obj/pyrite",
            "/d/Genesis/gems/obj/agate",
            "/d/Genesis/gems/obj/jasper",
            "/d/Genesis/gems/obj/coral"
        });

        setuid();
        seteuid(getuid());
        object gem = clone_object(gems[random(sizeof(gems))]);
        gem->move(this_object());
    }
}

public void describe_contents(object for_obj, object *obarr) {
    if (sizeof(obarr)) ::describe_contents(for_obj, obarr);
}
