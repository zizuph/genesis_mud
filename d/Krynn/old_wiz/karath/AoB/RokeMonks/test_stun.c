/* This objects stuns the victim of a plexus hit.
 * 
 * Glindor Jul-94
 */

#pragma save_binary

inherit "/std/object";

#define DEBUG_WHO find_player("shiva")
#define DEBUG_ON
#undef DEBUG_ON
#include "debug.h"

#include "../guild.h"
#define MONK_I_STUNNED "_monk_i_stunned"

int aid;
int inactive;
object victim;
float stuntime, waittime;

#define MAYDO ({ "commune", "quit", "look", "v", "vitals", "help", \
                 "groan", "moan", "whine", "drop", "put" })
#define MIGHTDO ({ "north", "south", "east", "west", "up", "down", "in", \
		   "out", "northeast", "northwest", "southeast", "southwest",\
		   "say" })
void create_object()
{
  set_no_show();
  set_name("plexus_stun");
  add_prop(OBJ_M_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  inactive = 0;
}

int stop(string str)
{
  string verb;
  float time;
  mixed alarm;
  int chance;

  /* Only paralyze our environment */
  if (environment() != this_player())
  {
    return 0;
  }

  if (inactive)
  {
    return 0;
  }

  /* Don't affect wizards */
  if (IS_WIZ(this_player()))
  {
    return 0;
  }

  verb = query_verb();

  if (member_array(verb, MAYDO) >= 0) 
  {
    return 0;
  }

  if (member_array(verb, MIGHTDO) < 0)
  {
    write("You are not able to do that.\n");
    return 1;
  }

  alarm = get_alarm(aid);
  time = alarm[2];

  chance = (time == 0.0 ? 100 : ftoi(400.0 / time));
  if (random(100) > chance) 
  {
    return 0;
  }
    
  write("You couldn't manage to do that.\n");
  return 1;
}

void deactive()
{
  if (inactive) return;

  if (objectp(victim))
  {
    victim->catch_msg("You feel your breath returning.\n");
    victim->remove_stun();
  }

  inactive = 1;
}

void expire()
{
  deactive();
  victim->remove_prop(MONK_I_STUNNED);
  remove_object();
}

start_time(float time, float wtime)
{
  stuntime = time;
  waittime = wtime;

  aid = set_alarm(stuntime, 0.0, deactive);
  set_alarm(waittime, 0.0, expire);
}

void init()
{
  ::init();

  if (environment() != this_player())
  {
    return;
  }

  DEBUG("Stunning: " + file_name(this_player()));
  add_action(stop, "", 1);

  this_player()->add_stun();
  this_player()->add_prop(MONK_I_STUNNED, 1);

  victim = this_player();
  inactive = 0;
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (!env || !living(env))
  {
    remove_object();
  }
}

string
stat_object()
{
    string str;
    mixed alarms;
    int t;
    str = "This object is used to paralyze the victim of a plexus attack.\n";
    str += "Original stuntime : "+ftoa(stuntime)+"\n";
    str += "Original waittime : "+ftoa(waittime)+"\n";
    str += "Inactive : "+inactive+ "\n";
    alarms = get_all_alarms();
    for (t = 0; t < sizeof(alarms); t++)
    {
	str+="Alarm   F: "+ alarms[t][1]+"  Time: "+ ftoa(alarms[t][2]) + "\n";
    }
    return str;
}
