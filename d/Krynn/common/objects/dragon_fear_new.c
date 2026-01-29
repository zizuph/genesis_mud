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
 * Petros 02/2009 - Refactor the code.
 * Petros 02/2014 - Use CMDPARSE_PARALYZE_CMD_IS_ALLOWED instead of allowed list
 * Cotillion 12/1024 - Fix shadow cloning to not leave shadows in the void
 * Arman 12/2018 - Disabled paralysis.
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

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <math.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#ifndef LIVE_I_NO_DRAGONFEAR
#define LIVE_I_NO_DRAGONFEAR "_live_i_no_dragonfear"
#endif

#define DRAGONFEAR_SH       (KROBJECT + "dragon_fear_sh")

/* 
 * Variables
 */
object victim;
int dex_penalty, str_penalty, defence_penalty, parry_penalty, 
    quickness_penalty, dis_stat;
int dragonfear_strength;
int scared_stiff = 0;
int start_affect_time;
int paralyse_time;
int last_apply_time;

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
    // Paralysis disabled - Arman December 2018
    return 0;

    if( !scared_stiff)
    {
        return 0;
    }
    
    if (TP->query_wiz_level())
    {
        write("Dragons are of no importance, so you ignore it.\n");
        return 0;
    }

    // Kenders aren't paralyzed, but they are affected by the stat
    // changes to dragonfear.
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
 * Apply Effects
 *
 * Removes all existing effects and applies the new ones.
 */
static void
apply_effect(int strength)
{   
    /* Remove the applied effects */
    victim->set_stat_extra(SS_DEX, victim->query_stat_extra(SS_DEX) - dex_penalty);
    victim->set_stat_extra(SS_STR, victim->query_stat_extra(SS_STR) - str_penalty);
    
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) - defence_penalty);
    victim->set_skill_extra(SS_PARRY, 
        victim->query_skill_extra(SS_PARRY) - parry_penalty);

    victim->add_prop(LIVE_I_QUICKNESS, victim->query_prop(LIVE_I_QUICKNESS) - 
        quickness_penalty);

    if (!strength)
    {
        // Zero out all penalties if there are no more dragons.
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

public int
query_is_dragonfear_immune()
{
    /* check for not affected livings */
    if (victim->query_prop(LIVE_I_NO_DRAGONFEAR) ||
        victim->query_dragonfear_immunity() ||
        victim->query_wiz_level() ||
    	QRACE(victim) == "draconian" ||
    	QRACE(victim) == "dragon" ||
    	(victim->query_dragonarmy_promotions() > 1) ||
    	(victim->query_pot_member() && victim->query_priest_level() > 0))
    {
        return 1;
    }

    return 0;       
}

public int
query_is_dragonfear_unaffected()
{
    if (victim->query_race_name() == "kender")
    {
        return 1;
    }
    
    return 0;
}

private int
calculate_dragon_strength(object * dragons)
{
    int avg, strength;
    foreach (object dragon : dragons)
    {
    	avg = dragon->query_average_stat();
    	strength += avg * avg;
    }
    strength /= 400;
    
    return strength;
}

public int
calculate_paralyze_strength(object * dragons)
{
    int bonus, paralyse_str, count;
    
    count = sizeof(dragons);
    bonus = SUM_ARRAY(map(dragons, &->query_average_stat())) / 6;
    bonus = (bonus * (count - 1)) / count;
    paralyse_str = applyv(max, map(dragons, &->query_average_stat()));
    paralyse_str += bonus;
    paralyse_str = (paralyse_str * paralyse_str) / 400;
    
    return paralyse_str;
}

public void
hook_no_dragons_remaining()
{
    if (!query_is_dragonfear_unaffected())
    {
        victim->catch_tell("Your fear eases. You think you have shaken off " +
            "the dragon fear.\n");
        tell_room(E(victim), QCTNAME(victim) + " seems to have shaken off " + 
                "the dragon fear.\n", victim, TO); 
    }
    set_alarm(0.0, 0.0, remove_object);
}

public void
hook_dragon_arrived()
{
	start_affect_time = time();
	if (query_is_dragonfear_unaffected())
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

public void
hook_dragon_paralyze_start()
{
    scared_stiff = time();
    if (query_is_dragonfear_unaffected())
    {
        victim->catch_tell("You decide to study the dragon thoroughly.\n");
        tell_room(E(victim), QCTNAME(victim)+
            " decides to study the dragon thoroughly.\n", victim, TO);
    }
    else
    {
        // victim->catch_tell("You are paralyzed by dragon fear.\n");
        // tell_room(E(victim), QCTNAME(victim)+" is paralyzed to the "+
        //    "spot by dragon fear.\n", victim, TO);
    }
}

public void
hook_dragon_paralyze_end()
{
    paralyse_time = time() - scared_stiff;
    scared_stiff = 0;
    
    if (query_is_dragonfear_unaffected())
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
}

static void
update_dragonfear_paralyze(object * dragons)
{
    int paralyse_str;
    
    paralyse_str = calculate_paralyze_strength(dragons);
    
    send_debug_message("dragonfear", "Paralyze Strength of " + paralyse_str);
    
    if (scared_stiff 
        && (scared_stiff + 15 < time()))
    {
        paralyse_time = time() - scared_stiff;
        if (paralyse_time + dis_stat > 30 + paralyse_str)
        {
            /* If the victim is paralyzed the new condition and the time 
             * bonus might make him not so */
            hook_dragon_paralyze_end();
        }
    }
    else if (!scared_stiff && (dis_stat < 30 + random(paralyse_str)))
    {
        /* If the victim is not paralyzed, the new condition might 
         * make him so */        
        hook_dragon_paralyze_start();
    } 
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


public void
refresh_dragon_fear()
{
    int new_strength;
    object *dragons;

    // There are 4 Classifications for Reacting to Dragonfear
    // 1. Immune - cannot be affected, just removed. No messages.
    // 2. Controlled - cannot be affected. Show control message then remove
    // 3. Unaffected - not affected by the effects. Display messages.
    // 4. Affected - affected fully by dragonfear.
    
    /* check for immune livings */
    if (query_is_dragonfear_immune())
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // Some people aren't immune, but they can control it. eg. Knights.
    if (victim->query_can_control_dragonfear() || check_da_pot_team_member(victim))
    {
        victim->hook_controlled_dragonfear();
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    
    dragons = filter(all_inventory(E(victim)), &->ansalon_krynn_dragon());
    if (!sizeof(dragons))
    {
        /* No dragons left */        
        hook_no_dragons_remaining();
        return;
    }
    
    // Obtain the strength based on the current dragons in the room
    new_strength = calculate_dragon_strength(dragons);
    
    /* No dragons? bah */
    if (!new_strength) 
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    /* A dragon arrived and should affect the victim */
    if (!dragonfear_strength) 
    {
        hook_dragon_arrived();
    }

    // Apply the effect of the dragonfear. We do this even if the
    // strength remains the same so that repeating effects like
    // panic can continue to have effect.
    if (!query_is_dragonfear_unaffected())
    {   
        // Dragonfear effect can only be applied once every round for
        // repeating effects. (round == 5 seconds)
        if (last_apply_time + 5 <= time())
        {
            send_debug_message("dragonfear", "Applying dragonfear effect with "
                + "strength of " + new_strength);
            apply_effect(new_strength);
            last_apply_time = time();
        }        
    }
    
    if (new_strength == dragonfear_strength && !scared_stiff) 
    {
        // Same amount of strength. Simply return after applying
        // the ongoing effect.
        return;
    }
    
    // Set the dragonfear strength to the new strength
    dragonfear_strength = new_strength;

    /*
     * The DA dragonfear object is not allowed to paralyze interactives.
     * Other similar checks might be needed.
     */
    if (!check_apply_command_filter(victim)) 
    {
        return;
    }

    update_dragonfear_paralyze(dragons);
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
        inv[0]->refresh_dragon_fear();
        ::remove_object();
        return;
    }

    // Clone the dragonfear shadow
    if (!victim->has_dragonfear_shadow())
    {

        setuid();
        seteuid(getuid());
        object fear_shadow = clone_object(DRAGONFEAR_SH);

        try {
        
            if (!fear_shadow->shadow_me(victim))
            {
                fear_shadow->remove_shadow();
            }
        } catch (mixed e) {
            // An error occurred when shadowing. This is likely because
            // the npc has nomask for move_living
            // Without a shadow, there won't be automatic refresh when
            // someone moves in and out.
	    fear_shadow->remove_shadow();
        }
    }
    
    // Begin the Dragonfear Process
    refresh_dragon_fear();
    set_alarm(5.0, 5.0, &refresh_dragon_fear());
}

void
remove_object()
{
    if (objectp(victim))
    {
        apply_effect(0);
        // Remove the dragonfear shadow
        victim->remove_dragonfear_shadow();
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
