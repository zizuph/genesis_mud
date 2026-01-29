/*
 * Any change made here should be notified to Arman and Milan (or other wizards
 * that may take care about dragonarmy).
 */

/*
 * dragon_fear.c
 * -------------
 *
 * Idea from 'fear.c' coded by Erine.
 *
 * Coded ........: 95/03/29
 * By ...........: Jeremiah
 *
 * Rewritten completely by Milan 10.10.1998.
 * Updated by Milan 3.8.1999. Added call to cb_update_speed() after
 *                          LIVE_I_QUICKNESS change.
 * Updated by Milan 3.4.2000. Added PoT member check.
 * Updated by Milan 4.7.2000. Racial Kender affected by awe-stunn
 * Updated by Cotillion, 09092002, Paralyze of Mortals is illegal.
 * Updated by Cotillion, 030707, Cleanups.
 * Louie 05/2005 - Always apply_effects(), regardless if strength is same.
 *
 * Features:
 * Dragonfear lasts while there are dragons present. Its strength depends on
 * size and number of dragons present. It affects stats STR and DEX, skills 
 * DEFENCE and PARRY and LIVE_I_QUICKNESS property. There is also a chance
 * that victim of dragonfear will be paralysed and unable to issue any command.
 * It updates periodically in order to keep its strength and effects in line
 * with the situation.
 *
 * Dragonfear affects all livings with the following exceptions:
 * Dragons, draconians and few selected NPCs are not affected.
 * Members of Dragonarmy with promotion level 2, 3 and 4 are not affected
 * (these are used to dragons from everyday life).
 * Members of knights vith level 5 or level 4 and sublevel greater than 5 are
 * not affected (because of their selfcontrol).
 * Kenders are not affected either.
 * Priests of Thakisis (Priests and High Priests) are not affected.
 *
 * How much a living is affected depends on DIS and WIS. The members of
 * Dragonarmy, PoT and Knight guild have a bonus to this depending on their position
 * in guild.
 */
#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#ifndef LIVE_I_NO_DRAGONFEAR
#define LIVE_I_NO_DRAGONFEAR "_live_i_no_dragonfear"
#endif

/* 
 * Variables
 */
object victim;
int dex_penalty, str_penalty, defence_penalty, parry_penalty, 
    quickness_penalty, dis_stat;
int dragonfear_strength;
int slow_alarm;
int time_bonus;
int scared_stiff;
int start_affect_time;
int paralyse_time;

static string *not_allowed = ({ "north","northeast","east","southeast",
				    "south","southwest","west","northwest",
				    "up","down","sneak","enter","out","in",
				    "climb" });

public int
ansalon_krynn_dragonfear()
{
    return 1;
}

public void
create_object() 
{
    set_name("ansalon_krynn_dragonfear");
    add_name("Dragon_fear");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

public int
check_apply_command_filter(object who)
{
    return 1;
}

public int
do_all_commands(string str)
{
    if( !scared_stiff)
	return 0;

    if (TP->query_wiz_level())
    {
        write("Dragons are of no importance, so you ignore it.\n");
        return 0;
    }

    if (TP->query_race_name() == "kender")
    {
	if (member_array(query_verb(), not_allowed) != -1)
	{
	    write("Oooh!... Dragons are so exciting!\n");
	    return 0;
        }
	return 0;
    }
    if (!CMDPARSE_PARALYZE_CMD_IS_ALLOWED(query_verb()))
    {
	write("You are paralyzed by dragon fear.\n");
	return 1;
    }
    return 0;
}

/*
 * Function to check if the victim is part of a team with a dragonarmy or priest.
 * The negative effects of their dragonfear shouldn't affect team members
 * Returns 1 if there is a PoT or DA in the team.
 */
int
check_da_pot_team_member(object victim)
{
    mixed team_members = victim->query_team_others();
    int number_of_members = sizeof(team_members);
 
    for (int i = 0; i < number_of_members; i++)
    {
        object team_member = team_members[i];
        if (interactive(team_member) &&
           (team_member->query_dragonarmy_occ_member() ||
            team_member->query_pot_member()))
        {
            return 1;
        }
    }
    return 0;
}

/*
 * Apply Effects
 *
 * Removes all existing effects and applies the new ones.
 */
static void
apply_effect(int strength)
{
    /* Remove the applied effects */
    victim->set_stat_extra(SS_DEX, victim->query_stat_extra(SS_DEX) - dex_penalty);
    victim->set_stat_extra(SS_STR, victim->query_stat_extra(SS_STR) -str_penalty);
    
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) - defence_penalty);
    victim->set_skill_extra(SS_PARRY, 
        victim->query_skill_extra(SS_PARRY) - parry_penalty);

    victim->add_prop(LIVE_I_QUICKNESS, victim->query_prop(LIVE_I_QUICKNESS) - 
        quickness_penalty);

    if (!strength)
    {
        dex_penalty = 0;
        str_penalty = 0;
        defence_penalty = 0;
        parry_penalty = 0;
        quickness_penalty = 0;
        victim->query_combat_object()->cb_update_speed();
        
        return;
    }
    
    dis_stat = ((2 * victim->query_stat(SS_DIS)) + victim->query_stat(SS_WIS)) / 3;
    dis_stat += victim->query_dragonfear_bonus();
    dis_stat += 3 * victim->query_knight_level();
    if (victim->query_dragonarmy_occ_member())
	dis_stat += victim->query_stat(SS_OCCUP) / 4;
    if (victim->query_pot_member())
	dis_stat += victim->query_priest_sublevel() * 8;
    if (victim->query_prop(NPC_I_NO_FEAR))
	dis_stat *= 2;
	if (dis_stat < 1) //prevent division by zero runtime Milan 22.6.2004
		dis_stat = 1;
    
    /* Calculate the new effects */
    dex_penalty = -MIN(3 * strength / dis_stat, victim->query_stat(SS_DEX) / 7);
    str_penalty = -MIN(3 * strength / dis_stat, victim->query_stat(SS_STR) / 7);
    defence_penalty = -MIN(4 * strength / dis_stat, 
        victim->query_skill(SS_DEFENCE) / 6);
    parry_penalty = -MIN(4 * strength / dis_stat, victim->query_skill(SS_PARRY) / 6);
    quickness_penalty = -MAX(0, 2 * strength - dis_stat);
    
    /* Add the new effect */
    victim->set_stat_extra(SS_DEX, victim->query_stat_extra(SS_DEX) + dex_penalty);
    victim->set_stat_extra(SS_STR, victim->query_stat_extra(SS_STR) + str_penalty);
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) + defence_penalty);
    victim->set_skill_extra(SS_PARRY, 
        victim->query_skill_extra(SS_PARRY) + parry_penalty);
    victim->add_prop(LIVE_I_QUICKNESS, victim->query_prop(LIVE_I_QUICKNESS) + 
        quickness_penalty);
    victim->query_combat_object()->cb_update_speed();
}

private void
refresh_dragon_fear()
{
    int index, count, avg, new_strength, paralyse_str, bonus, kender;
    object *dragons;

    /* check for not affected livings */
    if (victim->query_prop(LIVE_I_NO_DRAGONFEAR) ||
        victim->query_dragonfear_immunity() ||
        victim->query_wiz_level() ||
	QRACE(victim) == "draconian" ||
	QRACE(victim) == "dragon" ||
	(victim->query_dragonarmy_promotions() > 1) ||
	(victim->query_pot_member() && victim->query_priest_level() > 0) ||
        check_da_pot_team_member(victim))
    {
        this_object()->remove_object();
	return;
    }



    /* high knights can control dragonfear */
    if (victim->query_knight_level() == 5 || 
        (victim->query_knight_level() == 4 && victim->query_knight_sublevel() > 5))
    {
	victim->catch_msg("Terror sweeps over you, threatening to overcome you "+
            "fully. Gritting your teeth, you fight the fear back, keeping "+
            "control of yourself.\n");
	tell_room(E(victim), QCTNAME(victim)+" grits "+HIS(victim)+" teeth as "+
            "the dragonfear sweeps over "+HIM(victim)+", but "+HE(victim)+
            " manages to keep control of "+HIM(victim)+"self.\n", victim, TO);
        this_object()->remove_object();
	return;
    }
    
    kender = (victim->query_race_name() == "kender");

    dragons = filter(all_inventory(E(victim)), &->ansalon_krynn_dragon());
    index = count = sizeof(dragons);
    while (index--)
    {
	avg = dragons[index]->query_average_stat();
	new_strength += avg * avg;
	paralyse_str = MAX(paralyse_str, avg);
	bonus += avg / 6;
    }
    new_strength /= 400;

    if (count > 1)
	paralyse_str += (bonus * (count - 1)) / count;
    paralyse_str = (paralyse_str * paralyse_str) / 400;

    /* No dragons? bah */
    if (!new_strength && !dragonfear_strength) {
        this_object()->remove_object();
    }

    /*Changed by Louie.  Always apply new effect - this */
    /*allows for repeating effects in Dragonarmy dragons*/
    apply_effect(new_strength);

    if (new_strength == dragonfear_strength && !scared_stiff) {
        return;
    }

    /* The dragon left */
    if (!new_strength)
    {
        dragonfear_strength = new_strength;

        if (kender)
            return;

        victim->catch_tell("Your fear eases. You think you have shaken off " +
            "the dragon fear.\n");
	tell_room(E(victim), QCTNAME(victim) + " seems to have shaken off " + 
            "the dragon fear.\n", victim, TO); 
        this_object()->remove_object();
        return;
    }
    
    /* A dragon arrived and should affect the victim */
    if (!dragonfear_strength) 
    {
	start_affect_time = time();
	if (kender)
	{
	    victim->catch_msg("How exciting! A real dragon!\n");
	    tell_room(E(victim), QCTNAME(victim)+
                " is excited from the sight of dragon.\n", victim, TO);
	}
	else
	{
	    victim->catch_tell("You are suddenly overcome by a tremendous " +
                "dragon fear! Your face turns pale. The blood in your " +
                "veins run cold.\n");
	    tell_room(E(victim), "Suddenly " +QTNAME(victim)+ " stiffens. " +
                C(HIS(victim)) + " face turns pale and " + 
                HIS(victim) + " eyes widen.\n", victim, TO);
	}
    }

    dragonfear_strength = new_strength;

    /*
     * The DA dragonfear object is not allowed to paralyze interactives.
     * Other similar checks might be needed.
     */
    if (!check_apply_command_filter(victim)) {
        return;
    }

    /* If the victim is paralyzed the new condition and the time 
     * bonus might make him not so */
    time_bonus += 3;

    if (scared_stiff && 
        (time_bonus > 15) && (time_bonus + dis_stat > 30 + paralyse_str))
    {
        paralyse_time = time() - scared_stiff;
        scared_stiff = 0;
        
        if (kender)
        {
            victim->catch_tell("Ohhh... Even dragons get boring after a while.\n");
            tell_room(E(victim), QCTNAME(victim) + 
                " turns looking for something new.\n", victim, TO); 
        }
        else
        {
            victim->catch_tell("Your fear eases a bit. You can move again.\n");
            tell_room(E(victim), QCTNAME(victim) + 
                " seems to be able move again.\n", victim, TO); 
        }
        
        /* We need to get out here, otherwise he will be paralyzed again below */
        return;
    }

    /* If the victim is not paralyzed, the new condition might 
     * make him so */
    if (!scared_stiff && (dis_stat < 30 + random(paralyse_str)))
    {
        scared_stiff = time();
        time_bonus = 0;
        if (kender)
        {
            victim->catch_tell("You decide to study the dragon thoroughly.\n");
            tell_room(E(victim), QCTNAME(victim)+
                " decides to study the dragon thoroughly.\n", victim, TO);
        }
        else
        {
            victim->catch_tell("You are paralyzed by dragon fear.\n");
            tell_room(E(victim), QCTNAME(victim)+" is paralyzed to the "+
                "spot by dragon fear.\n", victim, TO);
        }
    } 
    
    dragonfear_strength = new_strength;
}

void
slow_refresh_dragonfear()
{
    if (!get_alarm(slow_alarm))
    {
        slow_alarm = set_alarm(1.0, 5.0, refresh_dragon_fear);
    }
}

public void
init()
{
    ::init();

    if (check_apply_command_filter(this_player()))
    {
        add_action(do_all_commands, "", 1);
    }
}

public void
enter_env(object to, object from)
{
    object *inv;
    
    ::enter_env(to, from);
    
    if (!objectp(to) || !living(to))
    {
	::remove_object();
	return;
    }

    victim = to;
    inv = all_inventory(victim) - ({ TO });
    if (sizeof(inv = filter(inv, &->ansalon_krynn_dragonfear())))
    {
	inv[0]->slow_refresh_dragon_fear();
	::remove_object();
	return;
    }

    slow_refresh_dragonfear();
}

void
remove_object()
{
    if (objectp(victim))
    {
        apply_effect(0);
    }
    
    if (scared_stiff)
    {
        paralyse_time = time() - scared_stiff;
    }
    
    /* we log only longer effects */
    if(start_affect_time && (time() - start_affect_time > 15))
    {
        setuid();
        seteuid(getuid());
        log_file("dragonfear_log", extract(ctime(start_affect_time),4,15) + ": " +
            (interactive(victim) ? victim->query_name() : file_name(victim)) +
            " (" + victim->query_average_stat() + ") affected " +
            (time() - start_affect_time) + " s" +
            (paralyse_time ? " - paralysed " + paralyse_time + " s\n" : "\n"));
    }
    ::remove_object();
}
