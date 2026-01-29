/* created by Aridor 09/95 */

#include "../local.h"

inherit "/std/object";
inherit MAGIC_OBJECT;

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/open/sys/combat.h"

object spellcaster;
object *seen_spellcaster;

void
create_object()
{
    set_name("clouds");
    add_name("cloud");
    add_name("stormcloud");
    set_adj("storm");
    add_adj("giant");
    add_adj("dark");
    set_short("Giant stormclouds are hanging in the air");
    set_long("The clouds look very menacing and heavy with " +
	     "suppressed violence. Even though it is not "+
             "raining you feel the air crackling with "+
             "hair-raising energy.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_M_NO_GET, "You cannot reach the clouds.\n");
    add_prop(OBJ_I_RES_ACID, 100);
    add_prop(OBJ_I_RES_WATER, 100);
    add_prop(OBJ_I_RES_FIRE, 10);  
}

void
init_spell(object caster, object target, object prev)
{
    spellcaster = caster;
    if (!target)
      seen_spellcaster = ({});
    else
      seen_spellcaster = FILTER_LIVE(all_inventory(target));
    if (!seen_spellcaster)
      seen_spellcaster = ({});
    //set_alarm(itof(duration),0.0,"dissolve");
    set_alarm(itof(random(4) + 3),0.0,"hurt_everyone_around");
    find_living("aridor")->catch_msg("STORM P:" + query_power() + " D:" +
				     query_duration() + ".\n");
    find_living("grace")->catch_msg("STORM P:" + query_power() + " D:" +
				     query_duration() + ".\n");
}

void
remove_object()
{
    TO->change_prop(CONT_I_NO_REM, 0);
    tell_room(E(TO),
	      "The clouds slowly vanish into thin air.\n");
    ::remove_object();
}


void
hurt_it(object livin)
{
    object co;
    int hitp;
    mixed result;
    string str;

    hitp = 2 * query_power() + random(10);
    
    co = livin->query_combat_object();
    
    /*hitpoint modifier on RES_FIRE and LIGHT:*/
    hitp -= hitp * livin->query_magic_res(MAGIC_I_RES_FIRE) / 100;
    hitp -= hitp * livin->query_magic_res(MAGIC_I_RES_ELECTRICITY) / 100;
    
    hitp = -hitp;

    if (hitp > 0)
      hitp = 0;
    else
      {
	if (hitp > -20)
	  str = "a little ";
	else if (hitp > -50)
	  str = "partly ";
	else if (hitp > -100)
	  str = "badly ";
	else
	  str = "very badly ";
	tell_object(livin,"You are hit and " + str + "burnt.\n");
	tell_room(E(livin), QCTNAME(livin) + " was struck by lightning.\n",livin);
	result = livin->hit_me(-hitp, MAGIC_DT, TO, -1);

	/* initiate combat here if necessary */
	if ((livin->query_stat(SS_INT) > 30 ||
	     livin->query_stat(SS_WIS) > 25) &&
	    member_array(livin,seen_spellcaster) >= 0)
	  {
	      set_this_player(livin);
	      str = c_can_attack(spellcaster,"kill");
	      if (!stringp(str) && livin->query_attack() != spellcaster)
		{
		  livin->catch_msg("Making the connection between the casting " +
				   "of the spell and the lightning, you decide " +
				   "to attack " + QTNAME(spellcaster) + ".\n");
		  spellcaster->catch_msg(QCTNAME(livin) + " attacks you!\n");
		  tell_room(E(livin),QCTNAME(livin) + " attacks " + QTNAME(spellcaster) +
			    "!\n",({spellcaster,livin}));
		  livin->attack_object(spellcaster);
		}
		
	  }

	find_living("aridor")->catch_msg("STORM HIT: " + (-hitp) + "\n");
	seteuid(getuid(TO));
	write_file("/d/Krynn/solamn/guild/log/stormspell",
		   "STORM HIT: " + (livin->query_name()) +  " " +
		   (-hitp) + " " + file_name(livin) + " " + result[3] + "\n");

	co->cb_add_panic(-hitp / (3 + random(2)));
	co->cb_may_panic();
    }
    if (!livin->query_ghost())
      livin->do_die(TO);
}


void
hurt_everyone_around()
{
    int i;
    object *things;
    int *nums = ({});

    seteuid(getuid(TO));
    things = all_inventory(E(TO));
    tell_room(E(TO),
	      "Lightning strikes down from the clouds.\n");

    for (i = 0; i < sizeof(things); i++)
      if (things[i]->query_prop(OBJ_I_RES_LIGHT) < random(100))
      {
	if (things[i]->query_prop(LIVE_I_IS) &&
	    !things[i]->query_ghost() &&
	    things[i]->query_alignment() < -random(50) - 30)
	  nums += ({ i });
	  /*hurt_it(things[i]);*/
      }
    /* pick one of all possible targets */
    if (sizeof(nums) > 0)
      hurt_it(things[nums[random(sizeof(nums))]]);

    set_alarm(itof(random(10) + 8),0.0,"hurt_everyone_around");
}

string
query_the_name()
{
    return short();
}

string
query_The_name()
{
    return capitalize(short());
}
