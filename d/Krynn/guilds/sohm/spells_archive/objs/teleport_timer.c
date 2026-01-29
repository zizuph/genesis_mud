/*
Teleport timer, restricting how regularly casters can re-cast it

Re-cast timer will be based on arcane focus skill:
      min(0, 90 - arcane focus), meaning superior master skill gets no
      re-cast penalty, while max arcane focus for SoHM has a minimum
      timer of 15 minutes before recast.

Arman - 2017
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

#define TIMER_PROP "_sohm_teleport_timer"

int timer;
object caster;

create_object() 
{
    seteuid(getuid());
    set_name("_sohm_teleport_timer_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

void
remove_teleport_object(object caster)
{
    caster->remove_prop(TIMER_PROP);
    caster->catch_msg("You feel focused enough to be able to " +
       "teleport again.\n");
    remove_object();
}

void
reduce_timer_number(object caster)
{
    timer = caster->query_prop(TIMER_PROP);

    caster->add_prop(TIMER_PROP, (timer - 1));

    if(timer > 1)
       set_alarm(60.0, 0.0, "reduce_timer_number", caster);
}

void
set_teleport_timer(object caster, int time)
{
    // time in minutes the teleport delay timer is in effect
    time = time * 60;

    float alarm_time = itof(time);
    

    set_alarm(60.0, 0.0, "reduce_timer_number", caster);
    set_alarm(alarm_time, 0.0, "remove_teleport_object", caster);
}


