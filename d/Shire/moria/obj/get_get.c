inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("get_get");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE,  0);
    add_prop(OBJ_I_INVIS,  1);
    add_prop(OBJ_I_NO_DROP,1);
    set_alarm(5.0, 0.0, "arm_me");
}

void
arm_me()
{
    object me;
    me = environment(this_object());
    me->command("get all");
    me->command("wear all");
    me->command("wield all");
    remove_object();
}

