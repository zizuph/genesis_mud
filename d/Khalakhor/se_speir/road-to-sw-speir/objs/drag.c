/*
 * Slowing object from the special
 * Tapakah, 09/2021
 */

#include <stdproperties.h>

#include "../defs.h"

inherit "/std/object";
inherit KLOGGER;

int time;
int _drag;
int _level;
object tp;

void create_object ()
{
  seteuid(getuid());
  set_name(WARRIOR_DRAG);

  add_prop(OBJ_I_VOLUME, 0);
  add_prop(OBJ_I_WEIGHT, 0);
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  add_prop(OBJ_I_VALUE, 0);

  set_no_show();
}

void
stop_drag ()
{
  tp->catch_msg("The pain subsides somewhat, and you seem to be able to "+
                "move quicker again\n");
     
  tp->change_prop(LIVE_I_QUICKNESS,
               tp->query_prop(LIVE_I_QUICKNESS) + _drag);
  (tp->query_combat_object())->cb_update_speed();
  remove_object();
}

void
start_drag ()
{
  tp->change_prop(LIVE_I_QUICKNESS,
                  tp->query_prop(LIVE_I_QUICKNESS) - _drag);
  tp->query_combat_object()->cb_update_speed();
  int a1 = 20.0 + 5.0*itof(random(_level))+0.5;
  log_me(sprintf("Drag of %d for %.1f seconds (level %d)", _drag, a1, _level),
         "info",
         "camp-drag");
  set_alarm(a1, 0.0, stop_drag);
}

void
configure (int drag, int level)
{
  _drag  = drag;
  _level = level;
}

void
enter_env (object to, object from)
{
  ::enter_env(to, from);
  if (! objectp(to)) {
    remove_object();
    return;
  }

  if( !living(to)) {
    remove_object();
    return;
  }

  tp = to;
  start_drag();
}
