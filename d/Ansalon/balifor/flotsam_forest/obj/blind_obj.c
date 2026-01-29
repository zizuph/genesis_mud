/*
 *    SPECIAL THNKS TO .. Lord Elessar of Gondor for letting me borrow
 *                        the blind_ob.c used for the Rangers brawl -
 *                        (blinding) special attack.   *praise him* :)
 *
 *    Dragon_gas_blind_object. Based on the ranger_blind_object.
 *
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

#define BLIND_SUBLOC "gas_blind_subloc"


object blinder,
       victim;

int    time,
       desting,
       old_prop,
       gAlarm;

void
create_object()
{
   set_name("Dragon_Gas_Blind_Object");

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

      victim->catch_msg("The pain in your eyes subsides and you are "
        + "able to see again!\n");
      TELL_ROOM(E(victim), victim, " rubs " + POSSESSIVE(victim)
        + " eyes, and seems to be able to see again!", victim);

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

   gAlarm = set_alarm(itof(time),0.0, can_see_again);
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

   victim = to;
   victim->add_subloc(BLIND_SUBLOC,TO);
   do_blind();
}

void
leave_env(object from, object to)
{
   from->remove_subloc(BLIND_SUBLOC);
   ::leave_env(from, to);

   if (desting) return;
   if (pointerp(get_alarm(gAlarm)))
   {
      can_see_again();
   }
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You cannot see! .. everything is a blurry mess!\n";
   else str = C(PRONOUN(carrier)) + " seems to have something in "
                + POSSESSIVE(carrier) + " eyes!\n";
   return str;
}

