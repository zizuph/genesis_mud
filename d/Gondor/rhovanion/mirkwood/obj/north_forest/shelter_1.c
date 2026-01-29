#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/container";

void create_container() {
    set_name("shelter");
    set_adj(({ "small", "wooden" }));
    set_short("small wooden shelter");
    set_long("This small wooden shelter appears to be the work of some " +
        "unknown woodsman who wished for a secretive place to hide himself. " +
        "It is not very large, nor is it well constructed, but it would " +
        "certainly do a good job of hiding anything inside it.\n");

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
    return (light_level == LIGHT_BRIGHT);
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
