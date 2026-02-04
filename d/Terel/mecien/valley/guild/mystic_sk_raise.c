/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
    /lib/skill_raise.c

    This is generic routines for advancing in skills. It is used by inheriting
    this file and configuring which skills that are teached. 

    As all /lib packages it can not be used alone. It must be used in 
    combination with something from /std

    Skill cost are calculated with the formula:

           cost = (skilllev ^ 3 * skill_cost_factor) / 100

*/

#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <language.h>

#define  IMPROVE    "study"
#define  LEARN      "learn"
#define  GUILD_NAME "The Ancient Mystic Order"
#define  MEMBER(xx) xx->query_guild_member(GUILD_NAME)

static 	mapping	sk_trains,	/* The available skills to train */
		sk_default,	/* The default basic skills */
		sk_tdesc;       /* The description printed */
static  string  *desc,
                *subdesc;

/*
 * Function name: create_skill_raise
 * Description:   Initialize the package
 */
create_skill_raise()
{
    sk_default = SS_SKILL_DESC;
    sk_trains = ([]);
    sk_tdesc = ([]);
    
    subdesc =
	({
	    "novice",
	    "junior",
	    "apprentice",
	    "",
	    "confident",
	    "seasoned",
	    "expert",
	    "eminent",
	    "brilliant", 
	    "superior",
	});

    desc = 
	({
	    "student",
	    "amateur",
	    "layman",
	    "acolyte",
	    "journeyman",
	    "craftsman",
	    "professional",
	    "veteran", 
	    "master",
	    "guru",
	});

}

/*
 * Description: Give the array of main levels
 */
public string *
sk_query_main_levels() { return desc + ({}); }

/*
 * Description: Give the array of sublevels
 */
public string *
sk_query_sub_levels() { return subdesc + ({}); }

/*
 * Function name: sk_add_train
 * Description:   Add a skill that can be trained.
 * Arguments:     snum: Skill number
 *                desc: Text written when raising the skill, ({ str1, str2 })
 *			str1: what player sees
 *			str2: what all other sees
 *		  name: Name of skill
 *		  costf: The costfactor for this skill
 *                maxskill: The maxlevel that we can teach to.
 *                stat: The limiting stat
 *                weight: The limit weight
 */
public varargs void
sk_add_train(mixed snum, mixed desc, string name, int costf, 
    int maxskill, int stat, int weight)
{
    int il;
    mixed skval;

    if (!mappingp(sk_default))
	return 0;

    if (pointerp(snum))
    {
	for (il = 0; il < sizeof(snum); il++)
	    sk_add_train(snum[il], desc, name, costf, maxskill);
	return;
    }

    if (!intp(snum))
	return;

    if (weight == 0)
    {
        stat = -1;
        weight = 100;
    }
    skval = sk_default[snum];
    
#ifdef STAT_LIMITED_SKILLS
    if (pointerp(skval))
         sk_trains[snum] = ({ skval[0], skval[1], maxskill, 
            skval[2], skval[3] });
    else
	sk_trains[snum] = ({ name, costf, maxskill, stat, weight });
#else
    if (pointerp(skval))
         sk_trains[snum] = ({ skval[0], skval[1], maxskill });
    else
	sk_trains[snum] = ({ name, costf, maxskill});
#endif

    if (pointerp(desc))
    {
	if (sizeof(desc) > 1)
    	    sk_tdesc[snum] = desc;
	else
	    sk_tdesc[snum] = ({ desc[0], desc[0] });
    } else
	sk_tdesc[snum] = ({ desc, desc });

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
    mixed skval;

    if (!mappingp(sk_default))
	return 0;

    skval = sk_trains[snum];

    if (!sizeof(skval))
	return 0;
 
    if (!living(pl))
	return 0;

    if (to_lev > skval[2])
	return 0;
    
#ifdef STAT_LIMITED_SKILLS
    if ((skval[3] >= 0) && (skval[4] > 0) && 
        ((skval[4] * pl->query_stat(skval[3]) / 100) < to_lev))
        return 0;
#endif

    pl->set_skill(snum, to_lev);
    return 1;
}

/*
 * Function name: sk_query_max
 * Description:   Give the max skill we can teach to for a skill.
 * Arguments:     snum: skill
 * Returns:       Max skill, 0 => We can not teach it.
 */
public int 
sk_query_max(int snum)
{
    mixed skval;

    if (!mappingp(sk_default))
	return 0;

    skval = sk_trains[snum];

    if (sizeof(skval)>2)
	return skval[2];
    else
	return 0;
}

/*
 * Function name: sk_cost
 * Description:   Give the cost for raising in a specific skill
 * Arguments:     snum: skill
 *                fr:   From level
 *		  to:   To level
 * Returns:       Cost or 0 if it can not be tought or if fr == to.
 */
public int
sk_cost(int snum, int fr, int to)
{
    int cf, c_old, c_new;
    mixed skval;

    if (!mappingp(sk_default))
	return 0;

    skval = sk_trains[snum];

    if (!sizeof(skval) || fr == to)
	return 0;

    c_old = (fr * fr * fr * skval[1]) / 100;
    c_new = (to * to * to * skval[1]) / 100;

    cf = (c_new ? c_new : 1) - (c_old ? c_old : 1);
    
    return (cf > 0 ? cf : 1);
}

/*
 * Function name: sk_rank
 * Description:   Give the textual level of a skill
 * Arguments:     lev: The skill level
 * Returns:       The skill rank descriptions
 */
public string
sk_rank(int lev)
{
    int subl, mainl;

    if (!desc)
	create_skill_raise();

    if (!lev)
	return "without skill";
    if (--lev > 99)
	lev = 99;
    mainl = (lev / sizeof(desc));
    if (mainl >= sizeof(desc))
	mainl = sizeof(desc) - 1;

    subl = (100 / sizeof(desc));

    subl = sizeof(subdesc) * (lev % subl) / subl;

    return (strlen(subdesc[subl]) ? subdesc[subl] + " " : "") + desc[mainl];
}	

/*
 * Function name: sk_query_train
 * Description:   Give a list of the skills we can train here.
 */
public int *
sk_query_train()
{
    return m_indexes(sk_trains);
}

/*
 * Function name: sk_query_name
 * Description:   Give the name of the skill for a skill number
 * Arguments:     skill: The skill number
 */
public string
sk_query_name(int skill)
{
    if (!mappingp(sk_default))
	return 0;

    if (sizeof(sk_trains[skill]))
	return sk_trains[skill][0];
}

/*
 * Function name: sk_find_skill
 * Description:   Find the number of a skill, when we have a string
 * Arguments:     skname: The skill name
 * Returns:       Skill number or -1 if not found
 */
public int
sk_find_skill(string skname)
{
    mixed *skarr, *skix;
    int il;

    if (!mappingp(sk_default))
	return -1;

    skix = m_indexes(sk_trains);
    for (il = 0; il < sizeof(skix); il++)
    {
	skarr = sk_trains[skix[il]];
	if (sizeof(skarr) && (skarr[0] == skname))
	    return skix[il];
    }
    return -1;
}
    
/*
 * Function name: init_skill_raise
 * Description:	  Call this to add standard skill raising commands
 */
void
init_skill_raise()
{
    add_action("sk_improve", IMPROVE);
    add_action("sk_improve", LEARN);
}

/*
 * Function name: sk_fix_cost
 * Description:   Fix each line in the improve/learn list
 * Arguments:	  snum  - The skill to check
 *		  steps - How many steps player wants to raise
 * Returns:	  A formatted string
 */
varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = steps ? this_level + steps : this_level + 1;

    if (next_level > (max = sk_query_max(snum)))
	cost = "---";
    else
	cost = sk_cost(snum, this_level, next_level) + " copper";

    if (this_level >= 100)
	next_rank = "maxed";
    else
    	next_rank = sk_rank(next_level);

    max_rank = sk_rank(max);

    return sprintf("  %-17s %13s  %-20s %-20s\n", sk_trains[snum][0],
		cost, next_rank, max_rank);
}

/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 * Arguments:	  skill - The skill he sought for
 *		  verb  - 'learn' or 'improve' or as defined by
 *                        IMPROVE and LEARN
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
 * Function name: sk_hook_no_member
 * Description:	  Player wants to improve a skill he isn't entitled to
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_no_member()
{
    notify_fail("You are not entitled to study here.\n");
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
    notify_fail("You must "+LEARN+" a skill before you can improve it.\n");
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
    notify_fail("You already know that skill, try to "+IMPROVE+" it.\n");
    return 0;
}

/*
 * Function name: sk_hook_no_language
 * Description:	  Player wants to study, but hasn't enough language
 *                skill
 * Arguments:	  verb - The verb, skill - The skill
 * Returns:	  0
 */
int
sk_hook_no_language(string verb, string skill)
{
    notify_fail(break_string("Since you don't understand the old " +
       "books, hence you cannot "+verb+" "+skill+". You better improve " +
       "your ability to understand the ancient languages first.\n", 72));
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
    notify_fail("You fail to adapt what the old book tells you.\n");
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

    this_player()->catch_msg("You improve your ability to " +
	sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(this_player()));
    say(break_string("" + 
	" improves " + this_player()->query_possessive() +
	" ability to " + sk_tdesc[snum][1] + " and receives the" +
	" rank of " + rank + ".\n", 60));
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
          "Next level:          Max level:\n"+
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
    write("Here follows all skills that you may study, and your next " +
	  "level in those skills:\n");
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
    write("For you there are no unknown skills here. You may try to\n" +
       IMPROVE+" some other skill or seek out new guilds elsewhere.\n");
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
    write("There are no skills you can "+IMPROVE+" here. Perhaps you\n" +
	"would like to learn some new skills, or try to find a new\n" +
	"guild elsewhere?\n");
    return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:	  skill - The skill player wanted to improve
 * Returns:	  0
 */
int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot rise this skill any further here, you have to\n" +
		"seek that knowledge elsewhere.\n");
    return 0;
}

/*
 * Function name: sk_list
 * Description:	  Someone wants a list of skills
 * Arguments:	  steps - How many steps the player wants to rise
 * Returns:	  1
 */
int
sk_list(int steps)
{
    int i, *guild_sk, learn;

    guild_sk = sk_query_train();
    if (!steps)
	steps = 1;

    if (steps < 0)
    {
	sk_hook_skillisting();
	steps = 1;
    }
    else if (query_verb() == LEARN)
    {
	guild_sk = filter(guild_sk, "sk_filter_learn", this_object(), steps);
	if (!sizeof(guild_sk))
	    return sk_hook_no_list_learn();
        sk_hook_write_header(steps);
    } else {
	guild_sk = filter(guild_sk, "sk_filter_improve", this_object(), steps);
	if (!sizeof(guild_sk))
	    return sk_hook_no_list_improve();
        sk_hook_write_header(steps);
    }

    for (i = 0; i < sizeof(guild_sk); i++)
	write(sk_fix_cost(guild_sk[i], steps));

    return 1;
}

/*
 * Function name: sk_filter_learn
 * Description:   Filter out what skills this player can learn
 * Arguments:	  sk    - The skill
 *		  steps - The number of steps play wants to learn
 * Returns:	  1 if play can learn skill
 */
int
sk_filter_learn(int sk, int steps)
{
    int tmp;

    if ((tmp = this_player()->query_base_skill(sk)) == 0 &&
		tmp + steps <= sk_query_max(sk))
	return 1;
    return 0;
}

/*
 * Function name: sk_filter_improve
 * Description:   Filter out what skills this player can improve
 * Arguments:     sk    - The skill
 *		  steps - The number of steps player wants to improve
 * Returns:       1 if play can improve skill
 */
int
sk_filter_improve(int sk, int steps)
{
    int tmp;

    if ((tmp = this_player()->query_base_skill(sk)) > 0 &&
		tmp + steps <= sk_query_max(sk))
        return 1;
    return 0;
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
    int steps, *guild_sk, *known_sk, snum, level, cost;
    string skill, verb, *tmp;

    if (!MEMBER(this_player()))
	return sk_hook_no_member();

    if (!str || sscanf(str, "%d", steps))
	return sk_list(steps);

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
	skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
	skill = str;
	steps = 1;
    }

    guild_sk = sk_query_train();
    known_sk = this_player()->query_all_skill_types();
    if (!known_sk)
	known_sk = ({});

    verb = query_verb();
    if ((snum = sk_find_skill(skill)) < 0)
	return sk_hook_unknown_skill(skill, verb);

    level = this_player()->query_base_skill(snum);

    if (!level && verb == IMPROVE)
	return sk_hook_improve_unknown(skill);
    if (level && verb == LEARN)
	return sk_hook_learn_known(skill);
    if (level + steps > this_player()->query_base_skill(SS_LANGUAGE))
	return sk_hook_no_language(verb, skill);
    if (level + steps > sk_query_max(snum))
	return sk_hook_improved_max(skill);
    if (!sk_do_train(snum, this_player(), level + steps))
	return sk_hook_cant_train(skill, level + steps);

    cost = sk_cost(snum, level, level + steps);

    if (!MONEY_ADD(this_player(), -cost))
    {
	this_player()->set_skill(snum, level);
	return sk_hook_cant_pay(skill, level + steps, cost);
    }

    sk_hook_raise_rank(snum, level + steps, cost);
    return 1;
}
