/* Stun object
 * clones fx. when the spiderweb spell is used
 * Midnight 20-3-2004
 *
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Faerun/defs.h"

#define STUN_CANNOT_DO  ({"climb", "enter", "leave", "push", "pull" })


int stun_alarm = 0;
float stun_time = 0.0;
int restrict_movement = 0;

void create_object()
{
  if (!IS_CLONE)
    {
      return;
    }
  add_prop(OBJ_I_INVIS, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  add_prop(OBJ_I_NO_DROP,1);
  add_prop(OBJ_I_NO_STEAL, 1);
  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_VALUE, 0);
  set_no_show();

  set_name("_faerun_stun_");
}

public void unstun_player()
{
  object victim;

  if (stun_alarm)
    {
      remove_alarm(stun_alarm);
    }
  stun_alarm = 0;
  victim = environment(this_object());
  if (living(victim))
    {
      victim->remove_stun();
    }
  victim->catch_msg("You are able to move again.\n");
  remove_object();
}

public void stun_player(int time)
{
  object victim;

  victim = environment(this_object());
  if (living(victim))
    {
      victim->add_stun();
    }
  stun_time = itof(time);
  stun_alarm = set_alarm(itof(time), 0.0, &unstun_player());
}

public void set_restrict_movement(int value)
{
  restrict_movement = value;
}

public string
stat_object()
{
  return ::stat_object() +
    "Time      : " + ftoi(stun_time) + "\n" +
    "Movement  : " + (restrict_movement ? "not allowed" : "allowed") + "\n";
}


int stop_movement(string sArgs)
{
  object victim = environment(this_object());
  string verb;

  if (!living(victim))
    {
      return 0;
    }
  if (!restrict_movement)
    {
      return 0;
    }

  verb = query_verb();
  if (member_array(verb, environment(victim)->query_exit_cmds()) < 0 &&
      member_array(verb, STUN_CANNOT_DO) < 0)
    {
      return 0;
    }
  write("You are unable to move.\n");
  
  return 1;
}

void init()
{
  ::init();
  add_action(stop_movement, "", 1);
}
