/*
 * /d/Gondor/common/guild/obj/stun_ob.c
 *
 * This is an object that is cloned into a player to stun him for some time.
 * It is used with the "brawl" command of the Rangers of the North.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 * /Elessar, 19. Sept. 1994. Modified from disarm_ob.c to be used with
 *  the new stun-effect.
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"


int    rtime, desting;
int    seen = 0;
int    rsa_aid;
object brawler;
object victim;

void
create_object()
{
    set_name("Ranger_Stun_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_time(int i)
{
    rtime = i;
}

void
set_seen(int i)
{
    seen = i;
}

void
set_brawler(object ob)
{
    brawler = ob;
}

void
remove_stun_again()
{
  int bp;
  rsa_aid = 0;
  if (brawler && ENV(brawler) == ENV(victim)) bp = 1;
  if (victim->query_ghost() || !living(ENV(TO))) {
    desting = 1;
    rtime = 0;
    remove_object();
    return;
    }
  if (!rtime) 
    {
      victim->remove_stun();
      if (victim->query_prop(LIVE_I_STUNNED) <= 0)
	{
	  victim->catch_msg("You recover your balance again.\n");
	  if (bp)
	    brawler->catch_msg("You notice that "+QTNAME(victim)+
	      " has recovered "+POSSESSIVE(victim)+" balance again.\n");
	}
      if (bp && seen)
	{
	  victim->command("glare "+brawler->query_name());
	  victim->command("kill "+brawler->query_name());
	}
    desting = 1;
    remove_object();
    return;
    }
  if (rtime > 0)
  rsa_aid = set_alarm(itof(rtime), 0.0, remove_stun_again);
  rtime = 0;
}

void
do_stun()
{
  /*
  victim->add_stun();
  //The actual stunning is handled in the main brawl-code instead.
  */
  rsa_aid = set_alarm(itof(rtime), 0.0, remove_stun_again);
  rtime = 0;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        desting = 1;
        return;
    }

    if (!living(to))
    {
        set_alarm(1.0, 0.0, remove_object);
        desting = 1;
        return;
    }

    victim = to;
    set_alarm(3.0, 0.0, do_stun);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (desting) return;
    if (rsa_aid)
    {
        remove_stun_again();
    }
}

