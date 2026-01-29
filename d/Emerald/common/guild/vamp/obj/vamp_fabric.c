inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>

static int bolt_flag = 0;

int fabric_is_on_bolt() { return bolt_flag; }

void create_fabric()
{
}

nomask void create_object()
{
    set_name(({ "fabric", "cloth", "_vamp_fabric" }));
    set_long("Several meters of heavy fabric.  " +
        "It seems to be well made; though, it isn't a fabric " +
        "that you have seen before.  A slightly dark aura surrounds " +
        "it, as if it were absorbing a bit of the light around it.\n");

    add_prop(OBJ_I_VALUE,  2500);
    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "The fabric is somehow enchanted.\n", 5,
        "The fabric is enchanted to be extremely sturdy.\n", 15,
        "It also seems to absorb small amounts of light in a very " +
        "short radius.  If it were made into clothing, it would " +
        "serve well to shield the wearer from the light.\n", 20 }));

    create_fabric();
}

void enter_env(object env, object from)
{
    ::enter_env(env, from);

    if ((file_name(env) == (VAMP_ROOM_DIR + "storage")) && !from)
    {
        bolt_flag = 1;
        set_no_show_composite(1);
    }
}

void leave_env(object env, object to)
{
    ::leave_env(env, to);

    if (bolt_flag)
    {
        set_no_show_composite(0);
        bolt_flag = 0;
    }
}
