/*
 * Vencar november 2003 - Project day in Palanthas (tm)
 *
 * The speed object behind the speed potion.
 *
 * Cotillion - 2008-12-27
 * - Fixed the quickness addition to work correctly with some
 *   mudlib changes.
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "potion_defs.h"
/* local define of strengths, prices etc */

#include <ss_types.h>
/* need for decreasing wis */

#include "/d/Krynn/common/defs.h"

int time;
object target;

void
set_duration(int i)
{
    time = i;
}

void
create_object()
{
    ::create_object();
    set_name("_speed_obj");
    set_no_show();

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
       "speed potion");
}


void
end_effect()
{

    target->catch_msg("You feel everything around you speed up.\n");
    say(QCTNAME(E(TO)) + " seems to slow down!\n");
    set_alarm(0.0, 0.0, remove_object);

    target->set_stat_extra(SS_WIS, 
			   (target->query_stat_extra(SS_WIS) + SPEED_POTION_WIS));    
    target->add_prop(LIVE_I_QUICKNESS,
		     target->query_prop(LIVE_I_QUICKNESS) - SPEED_POTION_SPEED);    
}

void
set_target(object obj)
{
    target = obj;
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

    to->catch_msg("You feel everything around you begins to move slower!\n");
    say(QCTNAME(to) + " seems to move faster!\n");
    
    to->add_prop(LIVE_I_QUICKNESS,
		 to->query_prop(LIVE_I_QUICKNESS) + SPEED_POTION_SPEED);
    to->set_stat_extra(SS_WIS, (to->query_stat_extra(SS_WIS) - SPEED_POTION_WIS));
    
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
}


