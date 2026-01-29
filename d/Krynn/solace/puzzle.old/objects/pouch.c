/* Pouch with bird-seed. ~solace/puzzle/objects/pouch */

inherit "/std/receptacle";

#include "../defs.h"
#include "/sys/stdproperties.h"

void add_bird_seed()
{
    seteuid(getuid(TO));
    clone_object(OBJECTS + "bird_seed")->move(TO);

    change_prop(CONT_I_CLOSED, 1);
}

void create_receptacle()
{
    set_name("pouch");
    set_adj("small");
    add_adj("leather");

    add_prop(OBJ_I_VALUE, 20);

    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);

    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 100);

    add_prop(CONT_I_MAX_WEIGHT, 100);
    add_prop(CONT_I_MAX_VOLUME, 200);

    add_bird_seed();
}

string long(object for_obj)
{
    return "A small pouch made of light brown leather that seems to have "+
        "been treated with a water-repellant oil. Its draw-strings "+
        ((query_prop(CONT_I_CLOSED)) ? "have been tied to keep it closed.\n" :
        "hang loosely so that you can get at the contents.\n");
}
