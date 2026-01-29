/*
 *	The trainer for the Dunedain
 *
 *	Idea taken and copied in parts from
 *	/d/Gondor/common/dwarf_guild/trainer.c by Mercade
 *
 *	Olorin, 14-nov-1994
 *
 *	Modification log:
 *  6-Feb-1997, Olorin    :     Skills adjusted.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/lib/skill_raise.c";
inherit "/d/Shire/lib/training";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

/* A few definitions */
/* 1 = closed,   0 = open.  */
#define CLOSED		0	
#define HIS(x)          (x)->query_possessive()
#define HIM(x)          (x)->query_objective()

/* 
 *	Function declarations:
 */
static void    set_up_skills();

/* 
 *	Global variables:
 */
static int     Closed;

public void
create_dunadan()
{
    set_name("golwadan");
    add_name(({"trainer", "master", }));

    set_long("The trainer for the Dunedain.\n");

    set_title("Master of Arts");
    set_dunedain_house("Haladin");

    set_adj(({"dark-haired", "green-eyed"}));

    default_config_npc(80);

    set_skill(SS_WEP_SWORD , 50);
    set_skill(SS_WEP_AXE,   100);
    set_skill(SS_WEP_KNIFE,  50);
    set_skill(SS_DEFENCE,    75);
    set_skill(SS_PARRY,      75);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_HERBALISM, 100);
    set_skill(SS_ALCHEMY,    50);
    set_skill(SS_SPELLCRAFT, 50);
    set_skill(SS_APPR_MON,   50);
    set_skill(SS_APPR_VAL,   50);
    set_skill(SS_APPR_OBJ,   50);
    set_skill(SS_LANGUAGE,  100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_TRADING,   100);

    set_alignment(500);

    Closed = CLOSED;

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    FIX_EUID;

    create_skill_raise();
    set_up_skills();

}

string
wizinfo() 
{
    return ("This is the trainer for the Dunedain, a race guild for humans.\n"+
      "If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call golwadan close_guild\n"+
      "This will temporarily prevent mortals from training. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n\t\tOlorin.\n");
}

void
init_living()
{
    ::init_living();

    init_skill_raise();
}

void
set_up_skills()
{
    string  me,
    ot;

    me = "use an axe";
    sk_add_train(SS_WEP_AXE,      ({ me, me }), me, 0, 50, -1, 0);
    me = "find and recognize herbs";
    sk_add_train(SS_HERBALISM,    ({ me, me }), me, 0, 50, -1, 0);
    me = "use magic";
    sk_add_train(SS_SPELLCRAFT,   ({ me, me }), me, 0, 50, -1, 0);
    me = "trade and make deals";
    sk_add_train(SS_TRADING,      ({ me, me }), me, 0, 50, -1, 0);

    // These skills can be trained in adventurers' guilds to 
    // the same max levels:
    me = "fight without weapons";
    sk_add_train(SS_UNARM_COMBAT, ({ me, me }),  0, 0, 30, -1, 0);
    me = "defend yourself in combat";
    ot = "defend " + HIM(TP) + "self in combat";
    sk_add_train(SS_DEFENCE,      ({ me, ot }),  0, 0, 20, -1, 0);
    me = "mix and recognize potions";
    sk_add_train(SS_ALCHEMY,      ({ me, me }), me, 0, 20, -1, 0);
    me = "cast spells using the element life";
    sk_add_train(SS_ELEMENT_LIFE, ({ me, me }),  0, 0, 20, -1, 0);
    me = "be aware of your surroundings";
    ot = "be aware of " + HIS(TP) + " surroundings";
    sk_add_train(SS_AWARENESS,    ({ me, ot }),  0, 0, 50, -1, 0);
    me = "appraise your opponents";
    ot = "appraise " + HIS(TP) + " opponents";
    sk_add_train(SS_APPR_MON,     ({ me, ot }),  0, 0, 30, -1, 0);
    me = "swim";
    sk_add_train(SS_SWIM,         ({ me, me }),  0, 0, 30, -1, 0);
    me = "climb";
    sk_add_train(SS_CLIMB,        ({ me, me }),  0, 0, 50, -1, 0);
    me = "speak and understand languages";
    sk_add_train(SS_LANGUAGE,     ({ me, me }),  0, 0, 50, -1, 0);
}

int
sk_improve(string str)
{
    if (!IS_MEMBER(TP))
    {
	command("say I train only members of the Houses of the Dunedain!");
	return 1;
    }
    return ::sk_improve(str);
}

/*
 * Function name: sk_query_max
 * Description  : This function is used to determine the maximum a player
 *                can train in a certain skill.
 * Arguments    : skill - the skill the player wants to train
 * Returns      : int   - the maximum (s)he can train in it.
 */
public varargs int
sk_query_max(int skill, int silent)
{
    int     max, lev;
    object  tp = TP;

    if (Closed)
	return 0;

    if (!IS_MEMBER(tp))
    {
	command("say I train only members of the Houses of the Dunedain!");
	return 0;
    }

    return ::sk_query_max(skill);
}


/*
 * Function name: sk_do_train
 * Description:   Let a player train a skill a certain number of levels
 * Arguments:     snum:   Skill number
 *		  pl:     Player to train
 *		  to_lev: To which level to train the player in the skill
 * Returns:       True if success
 */
public int
sk_do_train(int snum, object pl, int to_lev)
{
    if (to_lev > pl->query_dunadan_level())
	return 0;

    return ::sk_do_train(snum, pl, to_lev);
}


int
sk_hook_unknown_skill(string skill, string verb)
{
    command("confused");
    command("say I can not teach you how to " + skill
      + ", for I do not know a skill by that name.");
    return 1;
}

int
sk_hook_improve_unknown(string skill)
{
    command("say You shall have to learn how to " + skill +
      " before you can improve it.");
    return 1;
}

int
sk_hook_learn_known(string skill)
{
    command("say have already learned how to " + skill
      + ". Now you might improve it.");
    return 1;
}

int
sk_hook_cant_train(string skill, int to_lev)
{
    int     i,
    *skill_no = m_indexes(sk_default);

    for (i = 0; i < sizeof(skill_no); i++)
	if (sk_default[skill_no[i]][0] == skill)
	    break;

    command("amazed "+TP->query_real_name());
    command("say You will have to rise in status in your House before "
      + "I will help you to become " + sk_rank(to_lev)
      + " in how to " + sk_tdesc[skill_no[i]][0] + ".");
    return 1;
}

int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    command("turn " + TP->query_real_name());
    command("say You do not have sufficient money to pay for my service!");
    return 1;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    write("You improve your ability to " + sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(TP) + " improves " + POSSESSIVE(TP) +
      " ability to " + sk_tdesc[snum][1] + " and receives the rank of " +
      rank + ".\n");
}

void
sk_hook_write_header(int steps)
{
    if (!steps)
	steps = 1;
    command("say These are the skills you are able to " + query_verb() +
      " " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") + ", " +
      TP->query_name() + ", together with the level you will reach then, " +
      "the maximum level I am able to teach you and what I will charge " +
      "you to reach the acquired level.");
    write("  Skill:                Cost:      "+
      "Next level:           Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

void
sk_hook_skillisting()
{
    command("say These are all skills I can teach you, " + TP->query_name() +
      ", together with the next level you will reach, the maximum level " +
      "to which I am able to teach you and what I will charge you to " +
      "reach that next level.");
    write("  Skill:                Cost:      "+
      "Next level:          Max level:\n"+
      "--------------------------------------"+
      "--------------------------------------\n");
}

int
sk_hook_no_list_learn()
{
    command("say There are no new skills I can teach you, " + TP->query_name()
      + ". You might find others who can teach you new things though.");
    return 1;
}

int
sk_hook_no_list_improve()
{
    command("say I can not help you to improve any skills now. "
      + "Maybe there are new skills I can teach or you might find others "
      + "who can teach you more than I can.");
    command("frown");
    return 1;
}

int
sk_hook_improved_max(string skill)
{
    command("say I taught you all I know about how to " + skill
      + ". Maybe someone else might be able to teach you " +
      "more.");
    return 1;
}

/*
 * We are friendly to other domains, Solamnian Knights may not kill him!
 */
int
query_knight_prestige()
{
    return -6;
}

public int
close_guild()
{
    Closed = !Closed;
    if (!Closed)
	write("\nThe guild is now *** open ***!\n\n");
    else
	write("\nThe guild is now *** closed ***!\n\n");
}

/*
 * This has to be done so the master is configured
 * and the skill decay support works!
 */
public int
query_init_master()
{
    return 1;
}
