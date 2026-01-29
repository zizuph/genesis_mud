#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"


static int     time = 1200;

void
create_object()
{
    set_name("Swim_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_duration(int i)
{
    time = i;
}

void
end_effect()
{
    object  ob = E(TO);

        ob->catch_msg("You feel less proficient at swimming.\n");
        ob->set_skill_extra(SS_SWIM, ob->query_skill_extra(SS_SWIM) -40);
	
	TO->remove_object();

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    to->catch_msg("You feel more proficient at swimming.\n");
    to->set_skill_extra(SS_SWIM, to->query_skill_extra(SS_SWIM) +40);
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
}

