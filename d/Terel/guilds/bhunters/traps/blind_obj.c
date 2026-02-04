/*
 *    Terel blind object, based on examples from Gondor and Krynn,
 *    thanks Navarre, Tomas,
 *     - Udana
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"

#define BLIND_SUBLOC "_trap_blind_subloc"
#define BLINDED -1000
#define TRAP_BLIND_OBJECT "_trap_blind_object"


object victim;

/* time before the blind is removed. */
int time = 2;

int error_flag,
old_prop,
gAlarm;

void
create_object()
{
  set_name("_blind_");
  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);

  set_no_show(); // <------
}

void set_time(int i)
{
  time += i; 
}

/* returns 1 if it really has removed the blind */
void can_see_again()
{
  /* Sanity check */
  if ((!objectp(victim)) || (victim->query_ghost()) || (!living(victim)))
  {
    error_flag = 1;
    remove_object();
    return;
  }
  /* No more blinds left */
  if (time < 1)
  {
    victim->remove_subloc(BLIND_SUBLOC);
    victim->add_prop(LIVE_I_SEE_DARK, old_prop);
    victim->catch_msg("You blink few times, and slowly regain your sight.\n");
    tell_room(E(victim), QCTPNAME(victim) + " blinks few times, and seems to be able to see again!\n", victim);
    remove_object();
    return;
  }
  /* Still blinded */
  gAlarm = set_alarm(itof(time), 0.0, can_see_again);
  time = 0;
  return;
}

void
do_blind()
{
  victim->catch_msg("You can't see anything, pepper in your eyes hurts too much!\n");
  tell_room(E(victim), QCTNAME(victim) + " covers " + victim->query_possessive() + " eyes and winces in pain!\n", victim);
  victim->add_subloc(BLIND_SUBLOC,TO);
  old_prop = victim->query_prop(LIVE_I_SEE_DARK);
  victim->add_prop(LIVE_I_SEE_DARK, BLINDED);
  gAlarm = set_alarm(itof(time),0.0, &can_see_again());
  time = 0;
}

void
enter_env(object to, object from)
{
  ::enter_env(to, from);

  /* Sanity check */
  if (!objectp(to) || !living(to))
  {
    error_flag = 1;
    remove_object();
    return;
  }
  
  /* There is one such object on this player, no need to create a new one, we can just add some time
    to the previous one. */
  if(objectp(to->query_prop(TRAP_BLIND_OBJECT)))
  {
    to->query_prop(TRAP_BLIND_OBJECT)->set_time(time);
    set_alarm(1.0, 0.0, &remove_object());
    return;
  }
  victim = to;
  do_blind();
  victim->add_prop(TRAP_BLIND_OBJECT, TO);
}

void leave_env(object from, object to)
{
  /* Something messy need to clean */
  if(error_flag)
  {
    if(pointerp(get_alarm(gAlarm)))
      remove_alarm(gAlarm);
    ::leave_env(from, to);
    return;
  }
  
  from->remove_prop(TRAP_BLIND_OBJECT);
  /* Something wrong, possibly a person could stay blind forever */
  if (pointerp(get_alarm(gAlarm)))
  {
    time = 0;
    can_see_again();
  }
  ::leave_env(from, to);  
}

string show_subloc(string subloc, object carrier, object for_obj)
{
  string str;
  if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";
  if (for_obj == carrier)
    str = "";
  else str = capitalize(carrier->query_pronoun()) + " seems to have some problem with "
    + carrier->query_possessive() + " eyes.\n";
  return str;
}

