inherit "/std/object";

#include <stdproperties.h>

#define SMOKE_MSG  "The smoke is too thick to"
#define SMOKE_LONG "Thick smoke fills the area.\n"

static mixed dmsg, dlong;
static object env;

void
create_object()
{
    set_no_show();
    set_name("smoke_bomb_effect");

    add_prop(OBJ_I_LIGHT, -100);
}

void
clear_smoke()
{
    if (env)
    {
        if (env->query_prop_setting(ROOM_S_DARK_MSG) == SMOKE_MSG)
	{
            env->add_prop(ROOM_S_DARK_MSG, dmsg);
	}

        if (env->query_prop_setting(ROOM_S_DARK_LONG) == SMOKE_LONG)
	{
            env->add_prop(ROOM_S_DARK_LONG, dlong);
	}
    }

    env = environment(this_object());
    set_alarm(0.0, 0.0, &env->update_light());
    tell_room(env, "The smoke dissipates.\n");

    remove_object();
}

void
start()
{
    env = environment(this_object());

    dmsg = env->query_prop_setting(ROOM_S_DARK_MSG);
    env->add_prop(ROOM_S_DARK_MSG, SMOKE_MSG);

    dlong = env->query_prop_setting(ROOM_S_DARK_LONG);
    env->add_prop(ROOM_S_DARK_LONG, SMOKE_LONG);

    set_alarm(30.0, 0.0, clear_smoke);
}

void
init()
{
    ::init();

    if (env)
    {
        write("You walk into a dense cloud of smoke!\n");
    }
}

