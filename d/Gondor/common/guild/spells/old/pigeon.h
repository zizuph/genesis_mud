/*  Pigeon.h - The Rangers' form of communicating. By 'whistling' the
 *  player summons a pigeon. According to the player's skill in animal
 *  handling, he can then send messages with the pigeon a certain number
 *  of times.  Summoning the pigeon will cost 5-10 manapoints.
 */

#include "/d/Gondor/defs.h"

object pigeon;

void no_result(object player);

int
summon_pigeon(object player)
{
  if (pigeon)
  {
    if (pigeon->query_busy())
    {
      write("You feel that your pigeon is too busy to return right now.\n");
      return 1;
    }
    if (living(environment(pigeon)))
    {
      if (!environment(environment(pigeon))) 
        {
            set_alarm(10.0, 0.0, &no_result(TP));
            return 1;
        }
      if (environment(environment(pigeon))->query_prop(ROOM_I_INSIDE))
      {
        set_alarm(10.0, 0.0, &no_result(TP));
        return 1;
      }
      if (environment(pigeon)->query_prop(ROOM_I_INSIDE))
      {
        set_alarm(10.0, 0.0, &no_result(TP));
        return 1;
      }
      pigeon->return_to(TP);
      return 1;
    }
  }

  seteuid(getuid(this_object()));
  pigeon = clone_object("/d/Gondor/common/guild/obj/pigeon");
  pigeon->set_owner(TP);
  pigeon->set_times_to_fly((TP->query_skill(SS_ANI_HANDL) / 6)+1);
  pigeon->start_place();
  return 1;
}

void
no_result(object player)
{
  player->catch_msg("You don't see any sign of your carrier-pigeon.\n");
}

object
query_has_pigeon()
{
    return pigeon;
}

