/*
 * /d/Sparkle/guilds/mercs/lib/merc_defend.c
 *
 * Mercenaries shadow for the defend special.
 *
 * Change log:
 * - Updated and moved to Sparkle by Lunatari 2006
 */
inherit "/std/shadow";

#include "merc.h"

/*
 * This formula gives the mercenary an advantage of 80, given equal stats
 *   and skills. According to 'man task', against TASK_DIFFICULT, this yields
 *   25.99% success
 */

/* (skill(max of 100) * 180% + (int + wis) / 2)) */
#define TASK_LIST       ({ SKILL_WEIGHT, 180, SS_MERC_TACTICS, SKILL_WEIGHT, 50, \
                        SKILL_AVG, TS_INT, TS_WIS, SKILL_END })
/* ((int + wis + dis) * 2 / 3) */
#define VICTIM_LIST     ({ SKILL_WEIGHT, 200, SKILL_AVG, TS_INT, TS_WIS, \
                        TS_DIS, SKILL_END })

object *gDefenders = ({ });

/*
 * Function   : add_defender()
 * Arguments  : def: the object to add
 * Description: Add a defender to this person
 * Returns    : void
 */
public void add_defender(object def)
{
    gDefenders += ({ def });

}

/*
 * Function   : query_defenders()
 * Description: Get a list of defenders
 * Returns    : an array of defenders, or 0 if none
 */
public mixed query_defenders()
{
    return gDefenders;
}

/*
 * Function   : remove_defender()
 * Arguments  : def: the object to remove
 * Description: removes a defender from this person
 * Returns    : void
 */
public void remove_defender(object def)
{
    gDefenders -= ({ def });

    def->set_defending(0);

    if (!sizeof(query_defenders()))
        remove_shadow();
}

/*
 * Function   : query_not_attack_me()
 * Arguments  : who: the attacker, aid: the attack ID
 * Description: Determine whether or not this attack succeeds
 * Returns    : true if it does not succeed, false if it does
 */
int query_not_attack_me(object who, int aid)
{
    object combat_object = who->query_combat_object();
    int attack = combat_object->query_attack(aid), i, task_value, chance;
    object def, shield, leader;
    int my_bonus, enemy_bonus;

    if (!sizeof(query_defenders()))
    {
        shadow_who->query_not_attack_me(who, aid);
        remove_shadow();
    }

    if (!attack)
        return shadow_who->query_not_attack_me(who, aid);

    for (i = 0; i < sizeof(query_defenders());i++)
    {
        /* Increase difficulty by 100% over militia evade */
        task_value = TASK_DIFFICULT;

        /* if merc can't see opponent, make it much harder */
        if (!CAN_SEE(query_defenders()[i], who))
        {
            task_value = task_value +
                ((100 - query_defenders()[i]->query_skill(SS_BLIND_COMBAT)) * 3);
        }
 
        /*
         * Add a bonus if Mercenary is being led by his lord, +3% for
         *    lord, +6% for warlord.
         */

        if ((leader = query_defenders()[i]->query_leader()) && 
	    MCREST->query_members_lord(query_defenders()[i]->query_name()) ==
           leader->query_name())
        {
            switch(MCREST->query_lord_status(leader->query_name()))
	    {
	        case MERC_STATUS_LORD:
		    task_value -= 20;
		    break;
    	        case MERC_STATUS_WARLORD:
		    task_value -= 40;
		    break;
	        default:
	  	    break;
            }
        }

        /*  Add this check to limit the max effectiveness of block */
        my_bonus = query_defenders()[i]->query_skill(SS_MERC_TACTICS) * 2 + 
	    (query_defenders()[i]->query_stat(SS_INT) + 
	    query_defenders()[i]->query_stat(SS_WIS)) / 2;
        enemy_bonus = (who->query_stat(SS_INT) + who->query_stat(SS_WIS) +              	    who->query_stat(SS_DIS)) * 2 / 3;

        /*
         * A max of 50% blocking due to merc task list of 150 more than 
         *   enemy task list 
         */
        if (my_bonus >= enemy_bonus + 150)
            task_value = task_value + 2 * (my_bonus - (enemy_bonus + 150));

        chance = query_defenders()[i]->resolve_task(task_value,
    	    TASK_LIST, who, VICTIM_LIST);

        if (chance > 0)
        {
            def = query_defenders()[i];
            shield = def->query_my_shield();

            if (!present(def, environment(shadow_who)))
            {
               def->stop_defending();

               if (member_array(def, query_defenders()) == -1)
                  remove_defender(def);

               continue;
            }

            if (!shield)
            {
		def->stop_defending();
                continue;
	    }

            def->catch_msg("You defend "+shadow_who->query_the_name(def)+
		" from "+who->query_the_name(def)+"'s attack with your "+
		shield->short()+".\n");
            shadow_who->catch_msg(def->query_The_name(shadow_who)+" defends "+
		"you from "+who->query_the_name(shadow_who)+"'s attack "+
		"with "+POSSESSIVE(def)+" "+shield->short()+".\n");
	    who->catch_msg(def->query_The_name(who)+" defends "+
		shadow_who->query_the_name(who)+" from your attack with "+
		POSSESSIVE(def)+" "+shield->short()+".\n");
	    shadow_who->tell_watcher(QCTNAME(def)+" defends "+QTNAME(shadow_who)+
		" from "+QTNAME(who)+"'s attack with "+POSSESSIVE(def)+" "+
		shield->short()+".\n", def);
	    return 1;
        }
    }
            
    return shadow_who->query_not_attack_me(who, aid);
}

/*
 * Function   : leave_env()
 * Arguments  : from: the old environment, to: the new environment
 * Description: Move a player from one room to another
 * Returns    : void
 */
public void leave_env(object from, object to)
{
    int i, sz;

    if (sizeof(query_defenders()) > 1)
    {
	shadow_who->catch_msg("As you move, "+
	    query_defenders()[0]->query_the_name(shadow_who)+" and "+
	    query_defenders()[1]->query_the_name(shadow_who)+" stop "+
	    "defending you.\n");
        query_defenders()[0]->catch_msg("You are no longer defending "+
	    shadow_who->query_the_name(query_defenders()[0])+".\n");
        query_defenders()[1]->catch_msg("You are no longer defending "+
	    shadow_who->query_the_name(query_defenders()[1])+".\n");
    }
    else
    {
        shadow_who->catch_msg("As you move, "+
	query_defenders()[0]->query_the_name(shadow_who)+" stops "+
	    "defending you.\n");
        query_defenders()[0]->catch_msg("You are no longer defending "+
	    shadow_who->query_the_name(query_defenders()[0])+".\n");
    }

    sz = sizeof(query_defenders());

    /* Decrement i initially, because sizeof returns 2, but I need 0 and 1 */
    for (i = 0; i < sz;i++)
	query_defenders()[0]->stop_defending_silent();
}
