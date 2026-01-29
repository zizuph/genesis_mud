/*
 * Third Trainer for the Mercenary guild, by Morrigan 11/2001
 *
 * Adapted from code by Auberon Gwyneth on 19 February 2001
 *   - Morgan has left the camp. (Gorboth, August 2009)
 */
inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "../merc.h"
#include "room.h"

object gTrainer, guard1;
mapping gMembers = ([ ]);

public void
reset_room()
{
    /* Morgan has gone off to be part of the new Merc guild.
     *
    if (!objectp(gTrainer))
    {
        gTrainer = clone_object(MNPC + "morgan");
        gTrainer->move(this_object(), 1);
    }

    if (!guard1)
	(guard1 = clone_object(MNPC + "merc_base"))->move(this_object());
     */
}

void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_AWARENESS, "be aware of surroundings", "awareness", 0, 30);
    sk_add_train(SS_APPR_OBJ, "appraise objects", "appraise object", 0, 50);
    sk_add_train(SS_APPR_VAL, "appraise the value of items", "appraise value", 0, 50);
    sk_add_train(SS_LANGUAGE, "read and speak languages", "language", 0, 60);
    sk_add_train(SS_LOC_SENSE, "be aware of locations", "location sense", 0, 30);
    sk_add_train(SS_TRACKING, "track something in the wild", "tracking", 0, 30);
    sk_add_train(SS_CLIMB, "climb", "climb", 0, 30);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 30);
}

public void
create_room()
{
    set_short("South side of Camp");
    set_long("The majority of the camp is back toward the north. To the "+
	"northwest, a large building occupies most of the northern area "+
	"of the camp. This part of the camp is quieter than the rest, "+
	"and is surrounded by trees and undergrowth.\n");
    add_item("building", OUT_BUILDING_DESC);
    add_item(({"tent", "tents"}), OUT_TENT_DESC); 
    add_exit(MROOM + "center.c", "north", 0, 1, 0);
    set_up_skills();
    reset_room();
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    return (IS_MERC(who) || who->query_wiz_level());
}

public void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

public void
init()
{
    ::init();

    init_guild_support();
    init_skill_raise();
}

/* Function name: sk_query_max
 * Description  : Give the max skill we can teach to for a skill.
 * Arguments    : int snum - the skill-number to check.
 *                int silent - don't tell anything to the player if true.
 * Returns      : int - the maximum you can train the skill to.
 */
public varargs int 
sk_query_max(int snum, int silent)
{
    mixed skval;
    object pl;
    int lev = 100;
    int int_bonus = 0;

    if (!mappingp(sk_default))
    {
        return 0;
    }

    if (!this_player() || ((this_player() != previous_object()) &&
        previous_object() != this_object()))
        pl = previous_object();
    else
        pl = this_player();

    /* To prevent skill decay of skills, even if mercenary cannot
     * actually train those skills here yet. Doesn't really make
     * sense, but is implemented for playability's sake. */
    if (silent == 1)
    {
        skval = sk_trains[snum];
        return skval[2];
    }


    skval = sk_trains[snum];
    if (snum == SS_LANGUAGE)
    {
    if (pl->query_stat(SS_INT) > 110)
        int_bonus = (pl->query_stat(SS_INT) - 100) / 3;
    else if (pl->query_stat(SS_INT) < 75)
        int_bonus = -(80 - pl->query_stat(SS_INT));
        else
            int_bonus = 0;

    return MAX(30, MIN(pl->query_stat(SS_OCCUP) / 2 + int_bonus,
        MIN(skval[2], lev)));
    }

    if (sizeof(skval) > 2)
    {
        return MAX(30, MIN(pl->query_stat(SS_OCCUP), MIN(skval[2], lev)));
    }

    return 0;
}

/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    gTrainer->command("say You have learned the skills that I teach, you "+
	"should practice instead.");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    gTrainer->command("say I have taught you all I can, for now.");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    gTrainer->command("say You know all that I know about "+skill+".");
    return 1;
}

/*
 * Function name: sk_hook_not_allow_train
 * Description:   Message to print if you are not allowed to train
 * Returns:       string -- fail message
 */
public int
sk_hook_not_allow_train()
{
    gTrainer->command("say I cannot train you, you are not a mercenary.");
    return 1;
}

/*
 * Function name: sk_hook_unknown_skill
 * Description  : Player tries to improve or learn an unknown skill.
 * Arguments    : string skill - The skill he sought for.
 *                string verb  - 'learn' or 'improve'.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    gTrainer->command("say I have no talent for teaching "+
	skill+"!");
    return 1;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description  : Player wants to improve a skill he has never learned.
 * Arguments    : string skill - the skill the player tried to improve.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_improve_unknown(string skill)
{
    gTrainer->command("say You haven't learned "+skill+" skill yet, "+
	"so you certainly cannot improve upon it.");
    return 1;
}

/*
 * Function name: sk_hook_learn_known
 * Description  : Player wants to learn an already known skill.
 * Arguments    : string skill - the skill the player tried to learn.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_learn_known(string skill)
{
    gTrainer->command("say You've already learned "+skill+" skill, my friend.");
    return 1;
}

/*
 * Function name: sk_hook_cant_train
 * Description  : Player can't train that skill that high for some reason.
 * Arguments    : string skill - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    gTrainer->command("say You don't seem to grasp this concept yet, give it "+
	"some time.");
    return 1;
}

/*
 * Function name: sk_hook_cant_pay
 * Description  : Player cannot pay for session. (Kill him?)
 * Arguments    : string skill  - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 *                int cost - the price that is required, in coppers.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    gTrainer->command("say I must collect money for my services, Maligant "+
	"would throw me out, otherwise!");
    return 1;
}

int
sk_improve(string sk)
{
    if (!IS_MERC(TP))
    {
        
        return sk_hook_not_allow_train();
    }

    return ::sk_improve(sk);
}
