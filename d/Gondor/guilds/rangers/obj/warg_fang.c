/*
 * /d/Gondor/guilds/rangers/obj/warg_fang.c
 * Object returned from 8th ranger task
 * Tigerlily--October 22, 2004
 */
inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_short("sharp bloody fang");
    set_pshort("sharp bloody fangs");
    set_long("This is the long, sharp fang of a warg, reddened " +
        "with blood from a recent battle.\n");
    set_name("fang");
    set_adj(({"sharp", "bloody", "long", "warg"}));
    add_name("_Ranger_Task_Eight_Proof");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}

