inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>

static int last_time;

varargs void reduce_powder(int delay);

string query_auto_load()
{
  return MASTER + ":";
}

void create_object()
{
  set_name( ({ "dust", "pile", "vamp_dust" }) );
  set_short("pile of dust");
  set_pshort("piles of dust");
  set_adj("pile of");
  add_adj("clear");

  set_long("A pile of clear dust.\n@@blowing_desc@@");

  add_prop(OBJ_I_WEIGHT, 12);
  add_prop(OBJ_I_VOLUME, 6);
  remove_prop(OBJ_I_VALUE);
}

string blowing_desc()
{
  return (last_time ? "The breeze is scattering it across the " +
      "ground.\n" : "");
}

string long(string str, object for_obj)
{
  if (!reduce_powder())
  {
    return "You glance at the pile of clear dust just as the " +
        "last few grains are blown away in the breeze.\n";
  }

  return ::long(str, for_obj);
}

string short(object for_obj)
{
  reduce_powder(1);
  return ::short(for_obj);
}

void init()
{
  if (reduce_powder())
  {
   ::init();
  }
}

/* Reduce the amount of powder in time and remove it if there is none
 * left.  Returns 1 if there is any left, 0 if not.
 */
varargs int reduce_powder(int delay)
{
  int n;

  if (!last_time)
  {
    return 1;
  }

  if (n = (time() - last_time) / 60)
  {
    if (query_prop(OBJ_I_WEIGHT) <= (2 * n) ||
        query_prop(OBJ_I_VOLUME) <= n)
    {
      if (delay)
      {
        set_alarm(0.5, 0.0, remove_object);
      }
      else
      {
        remove_object();
      }

      return 0;
    }
  }

  CP(TO, OBJ_I_WEIGHT, -2 * n);
  CP(TO, OBJ_I_VOLUME, -n);

  return 1;
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

/* If a living creature picks this up, some will be lost, but
 * it won't blow away
 */
  if (living(env))
  {
    env->catch_msg("Some of the powder slips through your " +
        "fingers and is lost.\n");

    CP(TO, OBJ_I_VOLUME, -1);
    CP(TO, OBJ_I_WEIGHT, -2);

    reduce_powder(1);
    last_time = 0;

    if (query_prop(OBJ_I_VOLUME) < 1 ||
        query_prop(OBJ_I_WEIGHT) < 1)
    {
      env->catch_msg("All that remains are a few grains on " +
          "your hands.\n");
    }

    return;
  }

// Don't blow away if put in a regular container or an inside room
  if (!QP(env, ROOM_I_IS) || QP(env, ROOM_I_INSIDE))
  {
    last_time = 0;
    return;
  }

// The powder should be in an outside room, so start blowing
  if (!last_time)
  {
    last_time = time();
  }
}
