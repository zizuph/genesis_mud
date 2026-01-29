/*
 * File:     train.c
 * Created:  Cirion, 1998.06.28
 * Purpose:  General training library for the monks
 * 
 * OK, here is how the training works. Since we will be
 * having the same rooms be the training rooms for both
 * lay and occupational members of the guilds, we cannot
 * have the training skill setup in the room itself,
 * so we need to clone a separate object for each of
 * the skill setups (i.e., one for the occupational
 * members, and one for the layman members). In these
 * objects we will have the skill raise commands.
 * We also want to have one central place where the skills
 * are defined (this module), so when setting up skills in the
 * monks training rooms, we do a call as follows:
 * 
 * mt_setup_skills(<branch>, ({ skill1, skill2, skill3, etc. }));
 * 
 * i.e.,
 * mt_setup_skills(SS_LAYMAN, ({ SS_UNARM_COMBAT, SS_DEFENCE, SS_BLIND_COMBAT }));
 * mt_setup_skills(SS_OCCUP, ({ SS_UNARM_COMBAT, SS_DEFENCE, SS_BLIND_COMBAT }));
 * 
 * These functions will clone, configure, and move into the
 * room two objects that will handle the raising of the
 * skills, one for layman members, and the other of occupational
 * members. mt_setup_skills() is defined in ~monks/lib/roombase.c (!),
 * since it is just a cover function to clone and configure an
 * object.
 * 
 * Modification Log:
 *
 */
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <money.h>

inherit "/lib/skill_raise";
inherit "/std/object";
inherit MONKLIB;

// we may only want to allow the raising of skills if a
// training NPC is present. If this is the case, then
// the room that clones this will call set_monk_trainer(),
// and skill improvement will be disabled if monk_trainer
// is not present.
static object monk_trainer;
static int    enable_monk_trainer = 0;


// mapping of the configuration of all the monk
// trainable skills.
static mapping monk_sk_map = MONK_SKILL_CONFIG_MAPPING;

// This is the type of object this is, either for SS_OCCUP or
// SS_LAYMAN.
public int skill_module_type;

void trainer_say(string str);


/*
 * Function name: set_monk_trainer
 * Description:   If our skill raising is only done when a
 *                certain training NPC is around, then the object
 *                that clones this should call set_monk_trainer().
 *                If this has been called, and monk_trainer is
 *                no longer around, the skill improvement
 *                will be disabled.
 * Arguments:     object - the training object
 * Returns:       void
 */
void
set_monk_trainer(object trainer)
{
    monk_trainer = trainer;
    enable_monk_trainer = 1;
}

/*
 * Function name: query_monk_trainer
 * Description:   Returns the monk_trainer that was specified
 *                with set_monk_trainer.
 * Returns:       The trainer object.
 */
object
query_monk_trainer()
{
    return monk_trainer;
}

void
create_object()
{
    create_skill_raise();
    set_name("skilltrain");
    set_short("monk skill trainer");
    set_no_show(); // invisible object
}

/*
 * Function name: mt_setup_skills_config
 * Description:   This function will add the skills to the
 *                training object based on the guild_type
 *                passed in. The skills to be added are the
 *                list of trainable_skills.
 * Arguments:     guild_type - either SS_OCCUP or SS_LAYMAN
 *                trainable_skills - array of skills that will
 *                    be trainable from this object.
 * Returns:       void
 */
void
mt_setup_skills_config (int guild_type, int *trainable_skills)
{
    int i, type_index;
    mixed skdata;

    skill_module_type = guild_type;

    if (guild_type == SS_OCCUP)
        type_index = MONK_SKILL_INDEX_OCC;
    else if (guild_type == SS_LAYMAN)
        type_index = MONK_SKILL_INDEX_LAY;
    else // invalid guild_type passed in: raise an error
    {
        throw("Error in mt_setup_skills_config: first "
            + "argument must either be SS_OCCUP or SS_LAYMAN.\n");
        return;
    }


    // now setup the skills as specified in the
    // MONK_SKILL_CONFIG_MAPPING definition.
    for (i=0;i<sizeof(trainable_skills);i++)
    {
        // get the data of the skill configuration based on:
        //    1. the skill passed in,
        //    2. the type of guild we want to do this for
        skdata = monk_sk_map [trainable_skills[i]] [type_index];

        if(!sizeof(skdata))
            continue; // skill was not in our mapping.

        if(skdata [MONK_SKILL_INDEX_MAX] <= 0)
            continue; // maximum skill is 0 -- no point in adding it.

        // add the skill to train based on the configuration
        sk_add_train(trainable_skills[i],
            skdata [MONK_SKILL_INDEX_DESC],
            skdata [MONK_SKILL_INDEX_SKNAME],
            skdata [MONK_SKILL_INDEX_COST],
            skdata [MONK_SKILL_INDEX_MAX],
            skdata [MONK_SKILL_INDEX_LIMITING_STAT],
            skdata [MONK_SKILL_INDEX_LIMIT_WEIGHT]);

    }

}

void
init()
{
    ::init();

    // this object will only train monks of the type that is
    // specified in the skill_module_type. E.g., if this object
    // is the occupational training object, and I am an occupational
    // monk, than we will add the occupational training skills.
    if(m_query_monk(TP, skill_module_type))
        init_skill_raise();
}


/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:     str - The rest of the command player made
 * Returns:       1/0
 */
int
sk_improve(string str)
{

    // check to see if the guild was closed down for any reason
    if(m_query_guild_state() != MONK_GUILD_STATE_OPEN)
    {
        write("The guild has been shut down due to problems, so "
            + "training is impossible.\n"
            + "Try back later.\n");
        return 1;
    }

    // if we specified a monk trainer, check to see if it is
    // present before initializing skill training.
    if (enable_monk_trainer)
    {
        if(!query_monk_trainer()) // dead?
            return 0;

        if(!present(query_monk_trainer(), environment(this_object()))) // here?
            return 0;
    }

    // double-check to make sure this person is a monk, and
    // of the correct type. This is already done in the
    // init() function, this check is redundant (but safe).
    if(!m_query_monk(TP, skill_module_type))
        return 0;

    return ::sk_improve(str);
}

/*
 * Function name: sk_do_train
 * Description:   Let a player train a skill a certain number of levels
 * Arguments:     snum:   Skill number
 *                pl:     Player to train
 *                to_lev: To which level to train the player in the skill
 * Returns:       True if success
 */
public int
sk_do_train(int snum, object pl, int to_lev)
{
    // only players who have passed the guru quest can pass
    // level 90.
    if((to_lev >= 90) && !MONK_TRAIN_GURU(pl))
        return 0;

    return ::sk_do_train(snum, pl, to_lev);
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:     skill  - The skill
 *                to_lev - The level to wich the player wanted training
 * Returns:       0
 */
int
sk_hook_cant_train(string skill, int to_lev)
{
    if(to_lev >= 90) // probably didn't pass the guru quest
    {
        notify_fail("You are not yet ready for that level of mastery.\n");
        return 0;
    }
    else
    {
        this_player()->catch_msg("You fail to adopt what "
            + QTNAME(query_monk_trainer())
            +" attempts to teach you.\n");
        query_monk_trainer()->command("grumble");
        return 1;
    }
}


/*
 * Function name: sk_cost_desc
 * Description:   Fix each line in the improve/learn list
 * Arguments:     snum  - The skill to check
 *                steps - How many steps player wants to raise
 * Returns:       A formatted string
 */
varargs string
sk_cost_desc(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;

    if (next_level > (max = sk_query_max(snum)))
        cost = "---";
    else
        cost = LANG_WNUM(sk_cost(snum, this_level, next_level)) + " copper coins";

    if (this_level >= 100)
        next_rank = "superior guru";
    else
        next_rank = sk_rank(next_level);

    max_rank = sk_rank(max);


    return capitalize(sk_trains[snum][0]) + " for " + cost + ", which "
        + "would make you " + LANG_ADDART(next_rank) + " in the study, and "
        + "with a maximum possible rank of " + max_rank + ".";
}


/*
 * Function name: sk_list
 * Description:   Someone wants a list of skills
 * Arguments:     steps - How many steps the player wants to raise
 * Returns:       1
 */
int
sk_list(int steps)
{
    int i, *guild_sk, learn;

    if(!enable_monk_trainer)
        return ::sk_list(steps);

    // have the trainer speak the skill levels rather than
    // just write them;
    guild_sk = sk_query_train();
    if (!steps)
        steps = 1;

    if (steps < 0)
    {
        sk_hook_skillisting();
        steps = 1;
    }
    else if (query_verb() == "learn")
    {
        guild_sk = filter(guild_sk, &sk_filter_learn(, steps));
        if (!sizeof(guild_sk))
            return sk_hook_no_list_learn();
        sk_hook_write_header(steps);
    }
    else
    {
        guild_sk = filter(guild_sk, &sk_filter_improve(, steps));
        if (!sizeof(guild_sk))
            return sk_hook_no_list_improve();
        sk_hook_write_header(steps);
    }

    for (i = 0; i < sizeof(guild_sk); i++)
        set_alarm(itof(i + 1), 0.0, &trainer_say(sk_cost_desc(guild_sk[i], steps)));

    return 1;
}

/*
 * Function name: sk_hook_write_header
 * Description:   Write the header to the improve or learn list
 * Arguments:	  steps - How many steps we are talking about
 */
void
sk_hook_write_header(int steps)
{
    if(!enable_monk_trainer)
        return ::sk_hook_write_header(steps);

    if (!steps)
	steps = 1;
    trainer_say("These are the skills you are able to " + query_verb() +
	" " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
	" here:");
}

void
trainer_say(string str)
{
    monk_trainer->command("say " + str);
}

