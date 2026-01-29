#pragma strict_types
#pragma no_clone

#include "defs.h"
#include <tasks.h>
#include <ss_types.h>

#define FALL_DAMAGE (300+random(300))

private static int safe_average = 30+random(30);

public int
climb_chasm(string str)
{
   object tp = this_player();

   if(!str || (str != "down" && str != "down chasm" && str != "down the chasm"
     && str != "chasm" && str != "the chasm"))
   {
      return notify_fail("Climb what?\n");
   }

   if(tp->resolve_task(TASK_FORMIDABLE, ({ SS_CLIMB, TS_STR, TS_DEX })) <= 0)
   {
      notify_fail(
         "You take one look down the chasm and decide that it would " +
         "be better not to try climbing it.\n"
      );

      if(tp->query_average_stat() < safe_average)
      {
         return 0;
      }

      if(random(6) > 1)
      {
         return 0;
      }

      write(
         "You drop to the ground and begin searching for a " +
         "foothold on the edge of the chasm, but lose your balance " +
         "and begin to plunge towards the bottom!\n\n"
      );

      tp->command("$scream");
      tp->heal_hp(-FALL_DAMAGE);

      write(
         "\nAs you plummet through the air, you notice a ledge on the " +
         "chasm wall and before you know it, your body is slammed " +
         "brutally against the ledge.\n"
      );

      if(tp->query_hp() <= 0)
      {
         write(
            "Sadly, your head reaches the ledge before the rest of " +
            "your body, promptly detaching it and leaving your body " +
            "falling into the depths of the chasm.\n"
         );

         tp->do_die(this_object());

         return 1;
      }

      write(
         "Thankfully you are able to recover, and manage to pull " +
         "yourself to your feet.\n"
      );

      tp->move_living("falling through the air", ROOM + "ledge", 1, 0);

      return 1;
   }

   write("You carefully climb down the chasm wall.\n");

   tp->move_living("climbing down the chasm wall", ROOM + "ledge", 1, 0);

   return 1;
}
