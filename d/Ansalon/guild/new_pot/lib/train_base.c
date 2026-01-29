/*
 * This is a base file for NPC trainers for PoT.
 * Created by Milan 6.8.1999.
 */

#pragma strict_types
#pragma save_binary
#pragma no_clone

#include "../guild.h"
#include "../admin/admin.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit "/lib/skill_raise";

static int gLevlim = 0;
static object gTrainer;

/* Function name: set_trainer
 * Description: Sets who acts the trainer
 * Arguments: object trainer - the npc who acts as trainer
 */
void
set_trainer(object trainer)
{
    gTrainer = trainer;
}

/* Function name: query_trainer
 * Description: Queries who is the trainer
 * Returns: object - the trainer
 */
object
query_trainer()
{
    return gTrainer;
}

/*
 * Function name: can_train_this_skill
 * Description:   This function make extra checks
 *		  (like magic skills restrictions)
 *		  It also generates message if fail.
 * Arguments:	  snum - skill number
 *		  step - number of steps to train
 * Returns:	  1 if can train, 0 if not
 */
int
can_train_this_skill(int snum, int step)
{
    int i,w,s = TP->query_base_skill(snum);

    /*** we allow to forget anything he wants ***/
    if (step < 0)
        return 1;

    /*
		Prime element (LIFE):           100% of INT
		Secondary element (AIR):        80% of INT
		Total of all elements:          200% of INT

		Any form:                       100% of WIS
		Total of all forms:             200% of WIS
    */
    i = TP->query_stat(SS_INT);
    w = TP->query_stat(SS_WIS);
    switch(snum)
    {
        case SS_ELEMENT_EARTH:
        case SS_ELEMENT_WATER:
        case SS_ELEMENT_AIR:
            i = (80 * i) / 100;
        case SS_ELEMENT_LIFE:
            if (i < s+step)
            {
                gTrainer->command("say to " + OB_NAME(TP) +
                    " You are not able to understand such knowledge.");
                return 0;
            }
            break;

        case SS_FORM_ENCHANTMENT:
        case SS_FORM_DIVINATION:
        case SS_FORM_TRANSMUTATION:
        case SS_FORM_CONJURATION:
            if (w < s+step)
            {
                gTrainer->command("say to " + OB_NAME(TP) +
                    " You are not able to understand such knowledge.");
                return 0;
            }
            break;
    }

    i = TP->query_stat(SS_INT);

    switch(snum)
    {
        case SS_ELEMENT_AIR:
        case SS_ELEMENT_LIFE:
        case SS_ELEMENT_EARTH:
        case SS_ELEMENT_WATER:
	        s = TP->query_base_skill(SS_ELEMENT_AIR) +
                TP->query_base_skill(SS_ELEMENT_EARTH) +
                TP->query_base_skill(SS_ELEMENT_WATER) +
                TP->query_base_skill(SS_ELEMENT_FIRE) +
                TP->query_base_skill(SS_ELEMENT_LIFE) +
                TP->query_base_skill(SS_ELEMENT_DEATH);
            if (2*i < s+step)
            {
                gTrainer->command("say to " + OB_NAME(TP) +
                    " You know too much about elements to comprehend more.");
                return 0;
            }
            break;
        case SS_FORM_ENCHANTMENT:
        case SS_FORM_DIVINATION:
        case SS_FORM_TRANSMUTATION:
        case SS_FORM_CONJURATION:
    	    s = TP->query_base_skill(SS_FORM_ENCHANTMENT) +
                TP->query_base_skill(SS_FORM_DIVINATION) +
                TP->query_base_skill(SS_FORM_TRANSMUTATION) +
                TP->query_base_skill(SS_FORM_CONJURATION) +
                TP->query_base_skill(SS_FORM_ILLUSION) +
                TP->query_base_skill(SS_FORM_ABJURATION);
            if (2*w < s+step)
            {
                gTrainer->command("say to " + OB_NAME(TP) +
                    " You know too much about spell forms to comprehend more.");
                return 0;
            }
            break;
    }

    return 1;
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:	  str - The rest of the command player made
 * Returns:	  1/0
 */
int
sk_improve(string str)
{
    int steps, snum;
    string skill, *tmp;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    if (!present(gTrainer, TO))
    {
        write("There is no one here to train you.\n");
        return 1;
    }

    if (TP->query_guild_name_occ() != GUILD_NAME)
    {
        gTrainer->command("say I only teach Priests of Takhisis.");
        return 1;
    }

    if (GUILD_ADMIN->query_priest_has_punishment(TP->query_real_name(),
        P_TRAINING_RESTRICTED))
    {
        gTrainer->command("say to " + OB_NAME(TP) + " I have been " +
            "told not teach you anything.");
        return 1;
    }

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, query_verb());

    if (can_train_this_skill(snum, steps))
        return ::sk_improve(str);

    return 1;
}

/*
 * Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    mixed skval;
    int lev, max, tmp, i, w;

    gLevlim = 0;
    max = ::sk_query_max(snum, silent);
    skval = SKILL_LEVELS[snum];

    if (TP->query_guild_name_occ() != GUILD_NAME)
        return 0;

    if(max > 90)
    {
	if(TP->test_bit("ansalon", 3, 19)) /* Guru quest */
	    max = 100;
        else
            max = 90;
    }

    if (skval)
    {
        lev = TP->query_skill(PS_GUILD_LEVEL) / 10;
        if (lev > 10)
            lev = 10;
            
        tmp = skval[lev];
    }
    else
        return max;

    if (tmp < max)
    {
        gLevlim = 1;
        max = tmp;
    }

    return max;
}

/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 * Arguments:	  skill - The skill he sought for
 *		  verb  - 'learn' or 'improve'
 * Returns:	  0
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    notify_fail("I'm afraid there is no skill named '" + skill + "' to " +
        verb + ".\n");
    return 0;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description:	  Player wants to improve a skill he has never learned
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_improve_unknown(string skill)
{
    notify_fail("You must learn a skill before you can improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_learn_known
 * Description:	  Player wants to learn an already known skill
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_learn_known(string skill)
{
    notify_fail("You already know that skill, try to improve it.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 * Returns:	  0
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    notify_fail("You fail to adopt what the guildmaster teaches you.\n");
    return 0;
}

/*
 * Function name: sk_hook_cant_pay
 * Description:   Player can't pay for session (kill him?)
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 *		  cost   - The price
 * Returns:	  0
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    notify_fail("You don't have enough money with you.\n");
    return 0;
}

/*
 * Function name: sk_hook_raise_rank
 * Description:   The player trains and pays, write something
 * Arguments:	  snum  - The skill he trained
 *		  to_lev - Wich level he reached
 *		  cost   - How much he payed
 */
void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    TP->catch_msg(gTrainer->query_The_name(TP)+" improves your ability to " +
        sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(TP) + " learns from " + QTNAME(gTrainer) + " about " +
        sk_tdesc[snum][1] + " and reaches the rank of " + rank + ".\n");
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:	  steps - How many steps we are talking about
 */
void
sk_hook_write_header(int steps)
{
    if (!steps)
        steps = 1;
    write("These are the skills you are able to " + query_verb() +
        " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
        " here.\n");
    write("  Skill:                Cost:      "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_skillisting
 * Description:   Someone is listing the skills
 */
void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
        "those skills:\n");
    write("  Skill:                Cost:      "+
          "Next level:          Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:	  1
 */
int
sk_hook_no_list_learn()
{
    gTrainer->command("say to "+OB_NAME(TP)+" I can't teach you any new skills "+
        "but maybe I can improve some?");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:	  1
 */
int
sk_hook_no_list_improve()
{
    gTrainer->command("say to "+OB_NAME(TP)+" I can't improve any of your skills "+
        "but maybe I can teach you a new one?");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:	  skill - The skill player wanted to improve
 * Returns:	  1
 */
int
sk_hook_improved_max(string skill)
{
    if (gLevlim)
        gTrainer->command("say to "+OB_NAME(TP)+" Improve your standing in "+
            "Takhisis eyes. Then I will teach you more.");
    else
        gTrainer->command("say to "+OB_NAME(TP)+
            " You already know all I could teach you.");

    return 1;
}
