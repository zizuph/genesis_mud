/* A random gem stone. ~mucalytic/shaangsei/objects/gem */

inherit "/std/object";

#include "../defs.h"
#include "/sys/stdproperties.h"
#include "../../std/throwable_object.c"

#define TYPES	({ "diamond", "sapphire", "ruby", "emerald" })

void create_object()
{
    int ran;

    ran = random(sizeof(TYPES));

    set_name(TYPES[ran]);
    set_adj("large");
    add_adj("shiny");
    set_long("The shiny "+TYPES[ran]+" looks rather valuable to you.\n");

    add_prop(OBJ_I_VALUE, 450);
    add_prop(OBJ_I_WEIGHT, 620);
    add_prop(OBJ_I_VOLUME, 570);
}

void init()
{
    ::init();

    init_throwing();
}
