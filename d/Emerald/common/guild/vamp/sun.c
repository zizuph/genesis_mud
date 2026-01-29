/* sun.c created by Shiva@Genesis.  This file simply maintains
 * an alarm which calls sunlight_damage() in objects registered
 * with it.
 */

#pragma save_binary

#include "guild.h"

static object *obarr;
static int sun_alarm;

static void do_damage()
{
  int i = 0;

  while (i < sizeof(obarr))
  {
    if (!obarr[i])
    {
      obarr = exclude_array(obarr, i, i);
      continue;
    }

    obarr[i++]->sunlight_damage();
  }
}

int register(object ob)
{
  if (!ob)
  {
    return 0;
  }

  if (!obarr)
  {
    obarr = ({ });
  }

  if (member_array(ob, obarr) < 0)
  {
    obarr += ({ ob });
  }

  if (!get_alarm(sun_alarm))
  {
    sun_alarm = set_alarm(SUNLIGHT_DAMAGE_INTERVAL,
        SUNLIGHT_DAMAGE_INTERVAL, do_damage);
  }

  return 1;
}

int unregister(object ob)
{
  if (!sizeof(obarr) || member_array(ob, obarr) < 0)
  {
    return 0;
  }

  if (!sizeof(obarr -= ({ ob })))
  {
    remove_alarm(sun_alarm);
  }

  return 1;
}

int query_registered(object ob)
{
  return (member_array(ob, obarr) >= 0);
}
