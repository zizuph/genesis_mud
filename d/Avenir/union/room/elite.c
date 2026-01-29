/*  Elite training room for the            */
/*           Shadow Union                  */
/*           Cirion 031996                 */
/*
 * Revisions:
 * 	Lucius, Aug 2017: Re-Code and cleanup.
 */
#pragma strict_types

#include "../defs.h"
#include "../lib/skills.h"

#include <math.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit BASE;
inherit "/lib/skill_raise";

/* these skills are going to be obscenely expensive to
 * train. After all, this is pretty much the last thing
 * you can do in the guild.
 */
#define PLATS_TO_INCREASE_ONE_LEVEL	TP->query_average_stat()
#define MIN_PLATS_TO_INCREASE_ONE_LEVEL	80


public object trainer;

public void set_up_skills(void);


public void
union_room()
{
    set_short("shadow chamber");
    set_long("Shadows melt and merge everywhere.\n");

    add_prop(ROOM_I_LIGHT, ALWAYS_DARK);
    add_prop(ROOM_S_DARK_MSG, "The shadows binding you make it "+
	"impossible to");
    add_prop(ROOM_S_DARK_LONG, "This dark chamber swirled with "+
	"deep and forgotten shadows.\n");

    add_exit("stairwel", "up");

    create_skill_raise();
    set_up_skills();

    /* Wiz info for stat_object */
    add_prop(OBJ_S_WIZINFO, "This is one of the training halls "
      +"for the Union of the Warriors of Shadow. If a problem "
      +"occurs and you find it necessary to shut down the "
      +"guild, do 'Call /d/Avenir/union/list close_guild' (NOT "
      +"Call here close_guild). Note that this will shut down "
      +"ALL of the training rooms in the guild, and it will "
      +"remain so until someone calls open_guild (ie, it will "
      +"last through reboots). In other words, make sure you "
      +"have a good reason for doing it!\n");
}

/* Skill functions and hooks */
public void
set_up_skills(void)
{
    sk_add_train(SS_WEP_KNIFE,  /* sknum         */
      "use a knife with skill", /* desc          */
      0,                        /* skname        */
      1000,                     /* cost factor   */
      MAX_QUEST_KNIFE,          /* max skill     */
      SS_OCCUP,                 /* limiting stat */
      100);                     /* limit weight  */

    sk_add_train(SS_DEFENCE,
      "defend against attacks",
      0,
      1000,
      MAX_QUEST_DEFENCE,
      SS_OCCUP,
      100);

    sk_add_train(SS_SWAY,
      "enter the Sway",
      "sway",
      1000,
      MAX_QUEST_SWAY,
      SS_OCCUP,
      100);
}

/*
 * Function name: sk_cost
 * Description:   Give the cost for raising in a specific skill
 * Arguments:     snum: skill
 *                fr:   From level
 *                to:   To level
 * Returns:       Cost or 0 if it can not be tought or if fr == to.
 */
public int
sk_cost(int snum, int fr, int to)
{
    int cst;
    int factor;
    int increase;

    if (fr == to)
	return 0;

    if (snum != SS_SWAY &&
	snum != SS_DEFENCE &&
	snum != SS_WEP_KNIFE)
    {
	return 0;
    }

    increase = to - fr;
    cst = max(PLATS_TO_INCREASE_ONE_LEVEL, MIN_PLATS_TO_INCREASE_ONE_LEVEL);

    /* Need some slight random factor, lest players figure out
     * their stats by the amount it takes to increase the skill!
     */
    factor = NAME_TO_RANDOM(TP->query_name(), snum, 10) - 5;

    cst += factor;

    return increase * cst * (12 * 12 * 12);
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:	  str - The rest of the command player made
 * Returns:	  1/0
 */
public int
sk_improve(string str)
{
    if (GUILD_CLOSED)
    {
	write("The Union has been shut down due to problems, so "+
	    "training is impossible.\nTry back later.\n");
	return 1;
    }

    if (!present(trainer) || !IS_MEMBER(TP) ||
	!TP->test_bit("Avenir", GUILD_GROUP, TRAINING))
    {
	return 0;
    }

    if (!STATE)
    {
	trainer->command("us You have let the flame go out. I "+
	    "will teach you nothing.\n");
	return 1;
    }

    return ::sk_improve(str);
}

public void
trainer_leave(void)
{
    if (!trainer || !present(trainer))
	return;

    tell_room(TO, "You feel alone in the darkness.\n");
    trainer->remove_object();
}

public int
call(string str)
{
    NF(CAP(query_verb())+" out to what?\n");
    if (!strlen(str))
	return 0;

    str = lower_case(str);
    if (!parse_command(str, ({}),
	    "[out] 'to' [the] 'shadows' / 'shadow'"))
    {
	return 0;
    }

    if (present(trainer))
    {
	write("There is no need.\n");
	return 1;
    }

    if (TP->query_mana() <= 20)
    {
	write("You lack the mental strength needed.\n");
	return 1;
    }

    TP->add_mana(-20);
    write("You "+ query_verb() +" out to the shadows with "+
	"all your might.\n");
    say(QCTNAME(TP)+" cries out to the darkness.\n");

    trainer = clone_object(NPC+"riyligan");
    trainer->move(TO);
    trainer->command("say I am here.");

    set_alarm(30.0, 0.0, trainer_leave);
    return 1;
}

public void
init(void)
{
    ::init();
    init_skill_raise();

    add_action(call,  "cry");
    add_action(call, "call");
}
