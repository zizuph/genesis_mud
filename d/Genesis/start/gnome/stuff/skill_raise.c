/*
    /lib/skill_raise.c

    This is generic routines for advancing in skills. It is used by inheriting
    this file and configuring which skills that are teached. 

    As all /lib packages it can not be used alone. It must be used in 
    combination with something from /std

    Skill cost are calculated with the formula:

           cost = (skilllev ^ 3 * skill_cost_factor) / 100

	   
    This object is best used together with /lib/trade.c for handling of
    the actual paying for the relevant skills.

*/


#pragma save_binary

#include "/sys/ss_types.h";

static 	mapping	sk_trains,	/* The available skills to train */
		sk_default,	/* The default basic skills */
		sk_tdesc;       /* The description printed */
static  string  *desc,
                *subdesc;

/*
 * Description: Initialize the package
 */
sk_init()
{
    sk_default = SS_SKILL_DESC;
    sk_trains = ([]);
    sk_tdesc = ([]);
    
    subdesc =
	({
	    "novice",
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
 *                desc: Text written when raising the skill
 *		  name: Name of skill
 *		  costf: The costfactor for this skill
 *                maxskill: The maxlevel that we can teach to.
 */
public varargs void
sk_add_train(mixed snum, string desc, string name, int costf, int maxskill)
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

    skval = sk_default[snum];
    
    if (pointerp(skval))
	sk_trains[snum] = ({ skval[0], skval[1], maxskill });
    else
	sk_trains[snum] = ({ name, costf, maxskill });

    sk_tdesc[snum] = desc;
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
    string tdesc;

    if (!mappingp(sk_default))
	return 0;

    skval = sk_trains[snum];

    if (!sizeof(skval))
	return 0;
 
    if (!living(pl))
	return 0;

    if (to_lev > skval[2])
	return 0;
    
    tdesc = sk_tdesc[snum];
    if (!strlen(tdesc))
	tdesc = "You train " + skval[0] + ", you make progress.\n";
    
    pl->set_skill(snum, to_lev);
    pl->catch_msg(this_object()->check_call(tdesc));
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

    if (!sizeof(desc))
	sk_init();

    if (!lev)
	return "without skill";
    lev -= 1;
    mainl = (lev / sizeof(desc));

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
    