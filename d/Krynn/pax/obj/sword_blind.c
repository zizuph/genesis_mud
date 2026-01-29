/*
   SPECIAL THANKS TO .. Lord Elessar, for letting me borrow the blind_ob.c
                        used for the Rangers brawl(blind). *praise* ;)

   nightbringer_blind_object. Based on the ranger_blind_object, borrowed
   with permission from Lord Elessar. 

   night_ob.c
   ----------

   Copied........: 95/02/10 (ranger_blind_object)
   By............: Jeremiah

   latest update.: 95/03/24
   By............: Jeremiah

   24/06/2003
   Modified by Blizzard, for Verminaard's war-sword.
   
*/

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int    time, desting, old_prop, gAlarm;
object blinder, victim;

void
create_object()
{
   set_name("Blindness_Object");

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);

   set_no_show();
}

void
set_time(int i)
{
   time += i; 
}

void
set_blinder(object ob)
{
   blinder = ob;
}

void
can_see_again()
{
   if (time < 1)
   {
      /* Ok, this means my eyes are cleared and I can see */

      victim->add_prop(LIVE_I_SEE_INVIS, old_prop);

      if ((!objectp(victim)) || (victim->query_ghost()) || (!living(victim)))
      {
         desting = 1;
         remove_object();
         return;
      }

      desting = 1;
      remove_object();
   }
   /* Oops, somebody has blinded me again!! */

   else 
   {
      gAlarm = set_alarm(itof(time), 0.0, can_see_again);
      time = 0;
   }
}

void
do_blind()
{
   int old_prop = (int)victim->query_prop(LIVE_I_SEE_INVIS);

   victim->add_prop(LIVE_I_SEE_INVIS, -1);

   gAlarm = set_alarm(0.1, 0.0, can_see_again);
   time = 0;
}

void
enter_env(object to, object from)
{
   ::enter_env(to, from);

   if (!objectp(to))
   {
      desting = 1;
      remove_object();
      return;
   }

   if (!living(to))
   {
      desting = 1;
      remove_object();
      return;
   }

   do_blind();
}

void
leave_env(object from, object to)
{
   ::leave_env(from, to);

   if (desting) return;
   if (pointerp(get_alarm(gAlarm)))
   {
      can_see_again();
   }
}

