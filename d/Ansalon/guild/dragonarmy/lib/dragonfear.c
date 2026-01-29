/*
 * Created by Milan
 *
 * Milan, modified 13.3.2000
 * shortened preparation time and extended reset time by 25 seconds
 *
 * Modified 22.8.2000 by Milan
 * Dragonfear summon costs 200 mana and 0 fatigue (was 300/35)
 * Still at least 30 fatigue points are required for success.
 *
 * Modified 21.8.2017 by Arman
 * Altered to allow soldiers to summon dragons. Note mana costs are
 * now around 30 along with 35 fatigue. 
 */

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#include "../guild.h"

#define DSUMMON_PROP "_dragonarmy_summon_dragon_prop"

private void
reset_dragon_flyby(object tp)
{
    if (!objectp(tp))
	return;

    if ( IN_ARRAY(tp, users()) )
    {
      tp->catch_tell("You feel you are once again able to summon "+
        "dragons to your aid.\n");
    }

    tp->remove_prop(DSUMMON_PROP);
    tp->special_command_enabled("dragonfear");
}

string
dragonfear_dragon_age(object tp)
{
    string age;

    switch(tp->query_dragonarmy_promotions())
    {
    case 1:
	age = "young";
	break;
    case 2:
	age = "adult";
	break;
    case 3:
	age = "aged"; 
        break;
    case 4:
	age = "ancient";
        break;
    }
    return age;
}

private void
dragon_fear_room(object tp)
{
    int soldier_lvl, alarm;
    object dragon;

    if (!objectp(tp))
	return;

    if(E(tp)->query_prop(ROOM_I_INSIDE))
    {
	tp->catch_tell("The sensation you know as " +
	  "dragonfear dissapears. Dragons probably departed your "+
	  "neighbourhood.\n");
	alarm = set_alarm(20.0, 0.0, &reset_dragon_flyby(tp));
	tp->add_prop(DSUMMON_PROP, alarm);
	return;
    }

    soldier_lvl = tp->query_dragonarmy_rank_stat();
    alarm = set_alarm(itof(85+soldier_lvl), 0.0, &reset_dragon_flyby(tp));
    tp->add_prop(DSUMMON_PROP, alarm);

    setuid();
    seteuid(getuid());

    dragon = clone_object(DRAGONARMY_DRAGON + "strike_dragon");
    dragon->set_summoner(tp);
    dragon->set_age(dragonfear_dragon_age(tp));
    dragon->heal_hp(10000);
    dragon->set_dragonfear_time(20+soldier_lvl+random(40));
    dragon->follow_summoner();

    if(interactive(tp)) /* we log only use by players */
    {
	log_file("dragonarmy_dragonfear", extract(ctime(time()),4,15) +
	    ": " + tp->query_name() + " - " + file_name(E(tp)) +
	    " - dragon avg. stat = " + dragon->query_average_stat() + "\n");
    }
}

private void
approach_message(object tp)
{
    int alarm;

    if (!objectp(tp))
	return;

    tp->catch_tell("An eerie sensation that you recognise as " +
      "dragonfear forewarns you of the approach of a dragon.\n");
    if(!E(tp)->query_prop(ROOM_I_INSIDE))
    {
	tell_room(E(tp), "The hairs on your neck suddenly rise, followed " +
	  "by an eerie sensation that makes you reflexively " +
	  "look up into the skies with concern.\n", tp);
    }
    alarm = set_alarm(2.0, 0.0, &dragon_fear_room(tp));
//    alarm = set_alarm(10.0, 0.0, &dragon_fear_room(tp));
    tp->add_prop(DSUMMON_PROP, alarm);
}

int
dragon_summon(string str)
{
    object enemy, tp = TP;
    mixed *call;
    int alarm, i;

    if (!str || str != "dragonfear")
    {
	NF(C(query_verb())+" what?\n");
	return 0;
    }

    if(!dragonfear_dragon_age(tp))
    {
	write("Dragons do not answer calls from someone so low in the army.\n");
	return 1;
    }

    alarm = tp->query_prop(DSUMMON_PROP);
    if (alarm)
    {
	call = get_alarm(alarm);
	if(call)
	{
	    switch(call[1])
	    {
	    case "approach_message":
	    case "dragon_fear_room":
		write("The dragons are on their way! Be patient!\n");
		break;
	    default:
		write("You have yet to catch your breath from your last summoning.\n");
	    }
	    return 1;
	}
	else
	{
	    /* should not happen but we check it for safety */
	    tp->remove_prop(DSUMMON_PROP);
	}
    }

    enemy = tp->query_attack();
    if (!objectp(enemy))
    {
	write("You don't think the dragons you are about to call "+
	  "would be particularly impressed to find you summoned "+
	  "them without even entering combat!\n");
	return 1;
    }
    if (enemy->query_dragonarmy_occ_member())
    {
	write("No, you do not want your dragon to witness your "+
	    "skirmishes with other dragonarmy soldiers.\n");
	return 1;
    }

    if (E(tp)->query_prop(ROOM_I_INSIDE))
    {
	write("You are not outdoors! The dragons would not be able to " +
	  "reach you.\n");
	return 1;
    }

    if(tp->query_prop(LIVE_I_ATTACK_DELAY) ||
      tp->query_prop(LIVE_I_STUNNED))
    {
	/* Note that this is only called at the beginning of the 
	special. If the summoner is stunned at a later
	point of this sequence, that doesn't stop the 
	dragon from coming to his assistance. */
	write("You are too stunned to summon a dragon.\n");
	return 1;
    }

    if(tp->query_fatigue() < 30)
    {
	write("You are too exhausted to be able to summon a dragon.\n");
	return 1;
    }
    if(tp->query_mana() < 30)
    {
	write("You are not able to concentrate enough to summon dragon.\n");
	return 1;
    }

    tp->command("blow _dragonarmy_horn");
    tp->add_mana(-1 * (20 + random(10)));
//    tp->add_fatigue(-35);

    i = tp->query_dragonarmy_rank_stat();
    i *= tp->query_dragonarmy_promotions() - 1;
    i /= 2;
    if((tp->query_skill(SS_ANI_HANDL) < (40 + random(30))) ||
	!random(i))
    {
	write("You have a sinking feeling nothing " +
	  "is going to answer your call.\n");
	alarm = set_alarm(20.0, 0.0, &reset_dragon_flyby(tp));
	tp->add_prop(DSUMMON_PROP, alarm);
	return 1;
    }

    alarm = set_alarm(3.0, 0.0, &approach_message(tp));
//    alarm = set_alarm(20.0, 0.0, &approach_message(tp));
    tp->add_prop(DSUMMON_PROP, alarm);
    return 1;
}
