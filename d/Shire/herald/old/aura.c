
/* The light object of the Heralds of the Valar          */
/* Modified from the candle.c                            */
/* by Sir Denbarra of Gondor                             */
/* 7 May 1995                                            */

#pragma save_binary

inherit "/std/object";
 
#include "herald.h"
#include <macros.h>
#include <stdproperties.h>
 
#define MAX_TIME 900    /* about 15 mins */
#define SUBLOC "light_aura_subloc"

/* prototypes */
int query_max();
void burned_out();

int time_left, maxtime;

void
create_object() {
   time_left = query_max();
   set_name("aura");   /* extra unique name */
   set_pname("auras");
   set_adj("light");
   set_no_show();

   add_prop(OBJ_I_LIGHT,0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_S_WIZINFO, "This is the radiant aura of the Heralds of " +
      "the Valar guild, summoned to provide light.");
   maxtime = 30;
}

void
set_max(int time)
{
   if (time > MAX_TIME)
      maxtime = MAX_TIME;
   else if (time < 30)
      maxtime = 30;
   else
      maxtime = time;
}

int
query_max()
{
   return maxtime;
}

void
ignite()
{
   add_prop(OBJ_I_LIGHT,1);
   add_prop(OBJ_M_NO_INS, 1);
   add_prop(OBJ_M_NO_GIVE, 1);
   add_prop(OBJ_M_NO_DROP, 1);
   set_alarm(itof(query_max()), 0.0, &burned_out());
}

void
burned_out()
{
   object ob;

   time_left = 0;
   add_prop(OBJ_I_LIGHT,0);
   ob = environment();
   if (!ob)
      return;
   if (living(ob))
   {
      ob->catch_msg("Your radiant aura fades and disappears.\n");
      tell_room(environment(ob), "The radiant aura surrounding " + QTNAME(ob)
          + " fades and vanishes.\n", this_player());
      this_object()->remove_object();
      return;
   }
}

void
enter_inv(object to, object from)
{
    ::enter_env(to, from);
    if (objectp(to) && living(to))
    {
         to->add_subloc(SUBLOC);
    }
}

void
leave_inv(object from, object to)
{
    ::leave_env(from, to);
    if (objectp(from) && living(from))
        from->remove_subloc(SUBLOC);
}

string
show_subloc(string subloc, object on, object for_obj)
{
    string  str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == on)
        str = "your";
    else
        str = on->query_possessive();

    str = "Outlining "+str+" body is a glowing, radiant aura.\n";

    return str;
}
