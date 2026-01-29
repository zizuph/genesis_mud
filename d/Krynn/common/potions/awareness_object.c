#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Krynn/common/defs.h"

static int     time = 120;

void
create_object()
{
    set_name("Awareness_Object");

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

        ob->catch_msg("You feel your senses becoming less heightened, however your " +
          "body feels strong again.\n");
        ob->set_skill_extra(SS_AWARENESS, ob->query_skill_extra(SS_AWARENESS) -40);
        ob->set_stat_extra(SS_STR, (TP->query_stat_extra(SS_STR) + 40));
        ob->set_stat_extra(SS_CON, (TP->query_stat_extra(SS_CON) + 40));
	
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

    to->catch_msg("You feel your senses heighten, however your body suddenly feels " +
      "frail and weak.\n");
    to->set_skill_extra(SS_AWARENESS, to->query_skill_extra(SS_AWARENESS) +40);
    to->set_stat_extra(SS_STR, (TP->query_stat_extra(SS_STR) - 40));
    to->set_stat_extra(SS_CON, (TP->query_stat_extra(SS_CON) - 40));

    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
}

