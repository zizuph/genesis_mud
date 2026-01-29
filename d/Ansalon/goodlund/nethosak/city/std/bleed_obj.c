/* Navarre June 2006, Fixed typo, when bleeding stops
 * Had: The bleeding from the ugly wound on he stops.
 * Changed to use QTNAME to get the correct description.
 */

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"

int time;
int bleeds;

object victim;
object blood;

void create_object()
{
   seteuid(getuid());
   set_name("Bleeding_Wound_Object");

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);
   add_prop(OBJ_I_VALUE, 0);

   set_no_show();
}

void stop_bleeding()
{
   if (bleeds < 1)
   { 
      victim->catch_msg("The bleeding from the ugly wound " +
         "slows down to a small trickle.\n");
      tell_room(E(victim), "The bleeding from the ugly " +
         "wound on " + QTNAME(victim) + " stops.\n", victim, TO);

      remove_object();
   }
   else
   {
      victim->catch_msg("You grimace in pain as the ugly wound " +
         "continues to bleed, and small pool of blood forms " +
         "where you are standing.\n");
      tell_room(E(victim), QCTNAME(victim) + " grimaces in " +
         "pain as the ugly wound continues to bleed.  A small " +
         "pool of blood forms where " + HE(victim) + " is " +
         "standing.\n", victim, TO);

      --bleeds;

      blood = clone_object("/d/Ansalon/goodlund/nethosak/city/std/blood.c");
      blood->move(E(victim));
      
      victim->heal_hp(-150);

      /* Decided to remove the death-from-wound element - Arman Kharas 2/3/2005

      if (victim->query_hp() <= 0)
      {
         victim->do_die(TO);
      }
      */

      time = 30;
      set_alarm(itof(time), 0.0, "stop_bleeding", victim);
   }
}

void do_bleeding()
{
   bleeds = 500 / (victim->query_stat(SS_CON));

   time = 30;
   set_alarm(itof(time), 0.0, "stop_bleeding", victim);
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        remove_object();
        return;
    }

    if(!living(to))
    {
        remove_object();
        return;
    }

    victim = to;
    do_bleeding();
}                   