/*
 * Shadow for daggers that were stuck in an opponent
 * through fling.  The dagger cannot be wielded, or
 * dropped, and will fall out after a short time.
 * The shadow is applied by the fling attack.
 *
 * Author: Lilith 210501
 *
 */
inherit "/std/shadow";

#include "special.h"

string hitloc;
object me;
int alarm_id;

varargs public int move(mixed dest, mixed subloc) {

  if (ENV(me)->query_hp() <= 0) {
    int result = shadow_who->move(dest, subloc);
    if (alarm_id) {
      remove_alarm(alarm_id);
    }
    remove_shadow();
    return result;
  }
  if (subloc == 1 || !living(ENV(me))) {
    int result = shadow_who->move(dest, subloc);
    if (alarm_id) {
      remove_alarm(alarm_id);
    }
    remove_shadow();
    return result;
  }
  ENV(me)->catch_msg("The " + me->short() + " is stuck in your " + hitloc +
     " and is too deep to be pulled out.\n");
  return 7;
}
public void fall_out() {
  tell_room(ENV(ENV(me)), "The " + me->short() + " falls out of the " +
    hitloc + " of " + QTNAME(ENV(me)) + ".\n", ENV(me));
  ENV(me)->catch_msg("The " + me->short() + " falls out of your " +
    hitloc + ".\n");
  me->move(ENV(ENV(me)),1);
  remove_shadow();
}

public mixed wield(object obj) {
  return me->short() + " is stuck in your " + hitloc +
    "and cannot be wielded.\n";
}

void initiate_shadow(object dagger, string location) {
  me = dagger;
  hitloc = location;
  this_object()->shadow_me(dagger);
  alarm_id = set_alarm(30.0, 0.0, fall_out);
}

