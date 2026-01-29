/*   
 *   The Rangers base training hall - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   This file is to be inherited by the train halls of all three 
 *   Ranger companies.
 *   Modified by Olorin, 30-Oct-1993
 *
 *   Added "estimate all", cleanup -- Gnadnar 21 August 1998
 *   Fixed minor book with meditation -- Alto 14 September 2002
 *   
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <state_desc.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

/* A few definitions */
#define NUM		sizeof(query_money_types())
#define CLOSED		0	/* 1 = closed,   0 = open.  */


/* Prototypes */
public void		create_trainhall();
public nomask void	create_gondor();
public void		init();
public string		exa_poster();
public string		wizinfo();
public int		cmax(int sk);
public int		pupil_max(int sk);
public void		set_up_skills();
public string		close_guild();
public int		query_closed();
public void		enter_inv(object ob, object from);
public void		set_up_skills();
public int		gs_hook_already_meditate();
public void		gs_hook_start_meditate();
public void		gs_hook_rise();
public void		sk_hook_write_header(int steps);
public void		sk_hook_skillisting();
public int		sk_list(int steps);
public varargs string	sk_fix_cost(int snum, int steps);
public varargs int	sk_query_max(int sknum, int silent);
public int		sk_improve(string str);
public void		leave_inv(object ob, object to);
/*
public int		assess(string stat);
*/


/* Global variables */
int     closed;
int     company_no;


/*
 * Function name:	create_trainhall
 * Description	:	configure your hall here
 */
public void 
create_trainhall()
{
    set_short("Ranger Training Hall");
    set_long("This is a training hall of the Rangers.\n");
} /* create_trainhall */


/*
 * Function name:	create_gondor
 * Description	:	set up the training hall
 */
public nomask void 
create_gondor() 
{ 
    closed = CLOSED; 

    create_trainhall();

    add_prop(OBJ_S_WIZINFO, wizinfo);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_INSIDE, 1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item( ({"poster", "skill list", "skill-list", "list"}),
	exa_poster());
    add_cmd_item( ({"poster", "skill list", "skill-list", "list"}),
	"read", exa_poster());

    RECRUITHALL->load_me();
    COUNCIL->load_me();
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void 
init() 
{
    ::init();

    add_action(gs_meditate, "meditate");
    add_action(gs_meditate, "enter");
    add_action(gs_list    , "list");

    init_skill_raise();
} /* init */


/*
 * Function name:	exa_poster
 * Description	:	gen text for the poster
 * Returns	:	string -- the description
 */
public string 
exa_poster()
{
    int     i, s;
    int     snum;
    int     smax;
    int    *guild_sk = sk_query_train();
    string  list     =  "These are the skills you can train here if "+
			"you are a Ranger of " + 
			COMPANIES[company_no] + ":\n\n";

    guild_sk = sort_array(guild_sk);
    for (i = 0, s = sizeof(guild_sk); i < s; i++)
    {
        snum = guild_sk[i];
        smax = ::sk_query_max(snum, 0);
        if (smax)
	{
            list += sprintf("  %-25s  %-25s\n", sk_trains[snum][0],
			    sk_rank(smax));
	}
    }

    return list + "\n";
} /* exa_poster */


/*
 * Function name:	wizinfo
 * Description	:	describe guild to wizards
 * Returns	:	string -- the info
 */
public string 
wizinfo() 
{
   return (
	"This is an occupational guild for elves, humans and dwarves only.\n"+
	"The style is Ranger, an occupation that specializes in outdoor-\n"+
	"life, tracking, hunting and scouting.\n"+
	"If there should be due cause to close down the guild, do so by\n"+
	"typing:  Call here close_guild\n"+
	"This will temporarily prevent mortals from entering. After a\n"+
	"reboot, the guild will be open by default. Please send me some\n"+
	"mail if there is anything that needs to be fixed.\n\n   /Elessar.\n");
} /* wizinfo */


/*
 * Function name:	cmax
 * Description	:	determine max level this company will train
 *			a particular skill
 * Arguments	:	int sk -- the skill
 * Returns	:	int -- the max level
 */
public int 
cmax(int sk)
{
    int a = member_array(sk, SKILLS);

    if (a >= 0 &&
        company_no <= 2) 
    {
	return COMPANY_SKILLS[company_no][a];
    }
    return 0;
} /* cmax */


/*
 * Function name:	pupil_max
 * Description	:	determine max level of a skill for pupils 
 * Arguments	:	int sk -- the skill
 * Returns	:	int -- the max level
 */
public int 
pupil_max(int sk)
{
    int a = member_array(sk, SKILLS);
    if (a >= 0) 
    {
	return PUPIL_SKILLS[a];
    }
    return 0;
} /* pupil_max */


/*
 * Function name:	set_up_skills
 * Description	:	add all the ranger skills
 */
public void 
set_up_skills()
{
    string me;

    /* Combat skills */
    me = "use a sword effectively";
    sk_add_train(SS_WEP_SWORD,({ me, me }), 0,0, cmax(SS_WEP_SWORD));
    me = "use polearms effectively";
    sk_add_train(SS_WEP_POLEARM,({ me, me }), 0,0, cmax(SS_WEP_POLEARM));
    me = "defend in combat";
    sk_add_train(SS_DEFENCE,({ me, me }),0,0, cmax(SS_DEFENCE));
    me = "parry blows with a weapon";
    sk_add_train(SS_PARRY, ({ me, me }), 0,0,cmax(SS_PARRY));

    /* Magical skills */
    me = "recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM, ({ me, me }), 0,0,cmax(SS_HERBALISM));
    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY, ({ me, me }), 0,0,cmax(SS_ALCHEMY));
    me = "understand magic";
    sk_add_train(SS_SPELLCRAFT, ({ me, me }), 0,0, cmax(SS_SPELLCRAFT));
    me = "cast healing spells";
    sk_add_train(SS_ELEMENT_LIFE, ({ me, me }), 0,0, cmax(SS_ELEMENT_LIFE));
    me = "summon energy from magical sources";
    sk_add_train(SS_FORM_CONJURATION,({ me, me }), 0,0,
	cmax(SS_FORM_CONJURATION));
    me = "cast abjuration spells";
    sk_add_train(SS_FORM_ABJURATION,({ me, me }), 0,0,
	cmax(SS_FORM_ABJURATION));

    /* Thief skills */
    me = "sneak and move stealthily about";
    sk_add_train(SS_SNEAK, ({ me, me }), 0,0, cmax(SS_SNEAK));
    me = "hide and conceal";
    sk_add_train(SS_HIDE,	({ me, me }), 0,0, cmax(SS_HIDE));
    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP, ({ me, me }), 0,0, cmax(SS_FR_TRAP));

    /* General skills */
    me = "hunt wild animals";
    sk_add_train(SS_HUNTING, ({ me, me }), 0,0, cmax(SS_HUNTING));
    me = "be aware of the surroundings";
    sk_add_train(SS_AWARENESS, ({ me, me }), 0,0,cmax(SS_AWARENESS));
    me = "find and follow tracks";
    sk_add_train(SS_TRACKING, ({ me, me }), 0,0,cmax(SS_TRACKING));
    me = "navigate and sense the directions";
    sk_add_train(SS_LOC_SENSE, ({ me, me }), 0,0, cmax(SS_LOC_SENSE));
    me = "befriend and handle animals";
    sk_add_train(SS_ANI_HANDL, ({ me, me }), 0,0, cmax(SS_ANI_HANDL));

    /* Special Ranger-skills */
    me = "hear living beings nearby";
    sk_add_train(SS_HEARING, ({ me, me }), "hearing",20, cmax(SS_HEARING));
    me = "use dirty tricks in combat";
    sk_add_train(SS_BRAWLING, ({ me, me }), "brawling",50, cmax(SS_BRAWLING));

} /* set_up_skills */


/*
 * Function name:	close_guild
 * Description	:	toggle closed status
 * Returns	:	string -- the new status
 */
public string 
close_guild() 
{
    if (closed) 
    {
	closed = 0;
	return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
} /* close_guild */


int query_closed() { return closed; }


/*
 * Function name:	enter_inv
 * Description	:	mask parent to move players out of room if closed
 * Arguments	:	object ob -- the entering object
 *			object from -- where it came from
 */
public void 
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);

    if (!closed ||
	!interactive(ob))
    {
	return;
    }
    
    if (ob->query_wiz_level()) 
    {
	write("\n\nWARNING!\nYou shouldn't be here. "+
	    "I'm doing some work on the guild.\n");
    }
    else
    {
	write("\n\n***** The guild training hall is closed. "+
	    "Come back later. *****\n\n");
	ob->move(from);
    }
} /* enter_inv */



/*
 * Function name:	gs_hook_already_meditate
 * Description	:	write a already-meditating msg
 */
public int
gs_hook_already_meditate()
{
    WRITE("You are already in the pool. If you wish to finish "+
	  "your meditating bath you can do so by typing 'rise'. ");
          
    return 1;
} /* gs_hook_already_meditate */


/*
 * Function name:	gs_hook_start_meditate
 * Description	:	write a start-meditating msg
 */
public void
gs_hook_start_meditate()
{ 
    WRITE("Slowly you sit down in the hot herb-bath, and "+
	"close your eyes. As the trance-inducing herb-smoke reaches into "+
	"your mind, a feeling of great ease and self control falls upon you. "+
	"You block off your senses and concentrate solely upon your "+
	"own mind. Just <rise> when you are done bathing. ");
} /* gs_hook_start_meditate */


/*
 * Function name:	gs_hook_rise
 * Description	:	write a end-meditating msg
 */
public void
gs_hook_rise() 
{
    write(BSN("As if ascending from a great depth, you rise to the surface "+
	"of your consciousness. You exhale and feel very relaxed as "+
	"you get up and walk out of the herb bath. "));
} /* gs_hook_rise */


/*
 * Function name:	sk_hook_write_header
 * Description	:	Write the header to the improve or learn list
 * Arguments	:	int steps - How many steps we are talking about
 */
public void
sk_hook_write_header(int steps)
{
    if (!steps)
    {
	steps = 1;
    }
    write("These are the skills you are able to " + query_verb() +
	" " + LANG_WNUM(steps) + (steps == 1 ? " step" : " steps") +
	" here.\n");
    write("  Skill:                  Cost:    "+
          "Next level:            Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
} /* sk_hook_write_header */


/*
 * Function name:	sk_hook_skillisting
 * Description	:	Write the header to the list of skills
 */
public void
sk_hook_skillisting()
{
    write("Here follows all skills we teach, and your next level in " +
	  "those skills:\n");
    write("  Skill:                  Cost:    "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
} /* sk_hook_skillisting */


/*
 * Function name:	sk_list
 * Description	:	Someone wants a list of skills
 * Arguments	:	int steps - How many steps the player wants to raise
 * Returns	:	1 -- always succeeds
 */
public int
sk_list(int steps)
{
    int i, s, *guild_sk, learn;

    guild_sk = sort_array(sk_query_train());
    if (!steps)
    {
	steps = 1;
    }

    if (steps < 0)
    {
	sk_hook_skillisting();
	steps = 1;
    }
    else if (query_verb() == "learn")
    {
	guild_sk = filter(guild_sk, &sk_filter_learn(, steps));
	if (!sizeof(guild_sk))
	{
	    return sk_hook_no_list_learn();
	}
        sk_hook_write_header(steps);
    } else {
	guild_sk = filter(guild_sk, &sk_filter_improve(, steps));
	if (!sizeof(guild_sk))
	{
	    return sk_hook_no_list_improve();
	}
        sk_hook_write_header(steps);
    }

    for (i = 0, s = sizeof(guild_sk); i < s; i++)
    {
	write(sk_fix_cost(guild_sk[i], steps));
    }

    return 1;
} /* sk_list */


/*
 * Function name:	sk_fix_cost
 * Description	:	Fix each line in the improve/learn list
 * Arguments	:	int snum  - The skill to check
 *			int steps - How many steps player wants to raise
 * Returns	:	string -- a formatted list of skills & costs
 */
public varargs string
sk_fix_cost(int snum, int steps)
{
    int this_level, next_level, max;
    string next_rank, max_rank, cost;

    this_level = this_player()->query_base_skill(snum);
    next_level = this_level + (steps ? steps : 1);

    if (next_level > (max = sk_query_max(snum, 0)))
    {
	cost = "---";
    }
    else
    {
	cost = sk_cost(snum, this_level, next_level) + " cc";
    }

    if (!max)
    {
        return "";
    }

    if (this_level >= 100)
    {
	next_rank = "maxed";
    }
    else
    {
    	next_rank = sk_rank(next_level);
    }

    max_rank = sk_rank(max);

    return sprintf("  %-21s %9s  %-21s %-20s\n", sk_trains[snum][0],
		cost, next_rank, max_rank);
} /* sk_fix_cost */


/*
 * Function name:	sk_query_max
 * Description	:	give the max we will teach for a particular skill
 * Arguments	:	int sknum -- the skill
 *			int silent -- no msgs to player if set
 * Returns	:	int -- the max
 */
public varargs int
sk_query_max(int sknum, int silent)
{
    /*
     * At one time, logged silent calls to debug the decay system.
     * Skillno, returned value, name and current skill, if TP == 0.
     *
     * The actual write of the log was commented out.  I have instead
     * put #ifdef LOG_IF_SILENT around the prep of the logtxt, so we
     * don't do the work if we're not going to write the log.  Gnadnar
     */
    int  occup_stat, 
         skill_sum, 
         current_max, 
         wisint, 
         orig_max, 
         i, 
         n;
    int  sn,
         rv,
         plcomp,
         npo,
         nco,
         ntp;
    object pl;
    string name,
           logtxt;

    FIX_EUID
    if (!objectp(previous_object()))
    {
        npo = 1;
        pl = calling_object();
        if (!objectp(pl))
	{
            nco = 1;
	}
    }
    else
    {
        pl = previous_object();
    }
    /* The above lines are still there due to the log */
    
    if (!this_player() ||
	(this_player() != previous_object() &&
         previous_object() != this_object()))
    {
        pl = previous_object();
    }
    else
    {
        pl = this_player();
    }
    
    wisint = (pl->query_base_stat(SS_INT) + pl->query_base_stat(SS_WIS)) / 6;

    if (silent)
    {
        if (objectp(pl))
	{
            plcomp = query_bin_bits(1, 16, 2, pl);
	}
        if (npo &&
	    nco &&
	    !objectp(pl))
        {
            name = "Unknown";
            if (objectp(TP))
	    {
                name += " <" + TP->query_name() + ">";
	    }
            rv = cmax(sknum);
        }
        else if (pl->query_skill(SS_PUNISHMENT) == NOTRAIN  ||
                 pl->query_skill(SS_PUNISHMENT) == NOACCESS)
        {   
            name = pl->query_name() + " (punished)";
            rv = 0;
        }
        else if (plcomp == 0)
        {
            name = pl->query_name() + " (pupil)";
            rv = pupil_max(sknum);
        }
        else
        {
            name = pl->query_name() + " (full)";
            rv = cmax(sknum);
        }
#ifdef LOG_IF_SILENT
        logtxt = name + ", SkNum: " + sknum + ", RetLvl: " +
	    rv + ", CompHall: " + company_no + ". ";
        if (npo)
	{
            logtxt += "No PO. ";
	}
        if (nco)
	{
            logtxt += "No CO. ";
	}
        else
	{
            logtxt += "CO is " + calling_object()->query_name() + ". ";
	}
        if (objectp(TP))
	{
            logtxt += " TP is <" + TP->query_name() + "> ";
	}
        if (objectp(pl))
	{
            logtxt += "PlayComp: " + plcomp + ", Cursk: "
              + pl->query_base_skill(sknum) + ". ";
	}
        logtxt += ctime(time()) + "\n";
        write_file("/d/Gondor/log/rangerdecay", logtxt);
#endif /* LOG_IF_SILENT */

        /* Finally we return the max-value for the decay to use. */
        return rv;
    } /* if (silent) */


    if (member_array(sknum,SUBTERFUGE_SKILLS) >= 0 )
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(SUBTERFUGE_SKILLS)) 
        {
            if ((n = pl->query_base_skill(SUBTERFUGE_SKILLS[i])) >= 0) 
	    {
                skill_sum +=n;
	    }
            i++;
        }
        occup_stat = pl->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else if (member_array(sknum,NATURE_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(NATURE_SKILLS))
        {
            if ((n = pl->query_base_skill(NATURE_SKILLS[i])) >= 0) 
                skill_sum += n;
            i++;
        }
        occup_stat = pl->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else if (member_array(sknum,COMBAT_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i < sizeof(COMBAT_SKILLS))
        {
            if ((n = pl->query_base_skill(COMBAT_SKILLS[i])) >= 0) 
	    {
                skill_sum += n;
	    }
            i++;
        }
        occup_stat = pl->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else 
    {
        current_max = 100;
    }

    if (query_bin_bits(1,16,2,pl) != company_no) 
    {
        orig_max = pupil_max(sknum);
    }
    else 
    {
        orig_max = ::sk_query_max(sknum,silent);
    }

    current_max += pl->query_base_skill(sknum);
    if (current_max < 0) 
    {
        return 0;
    }

    /* If the Ranger Council punishes a Ranger with no access to
     ** training, skill-decay will intentionally be affecting the poor b***ard.
     */
    if (pl->query_skill(SS_PUNISHMENT)==NOTRAIN ||
        pl->query_skill(SS_PUNISHMENT) == NOACCESS)
    {
        return 0;
    }

    if (current_max <= orig_max) 
    {
        return current_max;
    }

    return orig_max;
} /* sk_query_max */

 
/*
 * Function name;	sk_improve
 * Description	:	player did "improve" -- write suitable mgs before 
 *			calling parent to do the work.
 * Arguments	:	string str -- whatever they typed
 * Returns	:	1 on success, 0 on failure
 */
public int
sk_improve(string str)
{
    object  tp = TP;
    int     rbit = query_bin_bits(1,18,2,tp),
            cbit = query_bin_bits(1,16,2,tp);

    if (rbit == 0) 
    {
        write("\n" +
	  BSN("The Master Ranger says: Since thou art not a Ranger, " +
          "thou canst not be allowed to train here. "));
        if (!str)
	{
          write(BSN("The Master Ranger says: But thou art welcome to have "
            + "a look at what we offer. "));
	}
        else
	{
            return 1;
	}
    }
    else if (rbit == 3) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art banned from the "
          + "Rangers for thy evil deeds, so thou art not allowed to train "
          + "here!") + BSN("The Master Ranger says: Seek a way to redeem "
          + "thyself, or begone! "));
        return 1; 
    }
    else if ((TP->query_skill(SS_PUNISHMENT) == NOTRAIN) ||
             (TP->query_skill(SS_PUNISHMENT) == NOACCESS)) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art not allowed to "
          + "train skills at present, for the Council of Rangers hath thee "
          + "punished!"));
        write(BSN("The Master Ranger says: Seek a way to redeem thyself, or "
          + "begone!"));
        return 1;
    }
    else if (rbit == 2) 
    {
        write("\nThe Master Ranger bows before you, saying:\n"
          + "      Honoured Captain of the Rangers of "+TP->query_company()
          + ", greetings!\n");
    }

    if (rbit > 0 &&
	cbit != company_no) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art welcome "
          + "to train here, but we cannot offer thee more than pupil "
          + "training as thou art not one of the Rangers of "
          + COMPANIES[company_no] + ". "));
    }
    return ::sk_improve(str);
} /* sk_improve */



/*
 * Function name:	leave_inv
 * Description	:	mask parent to remove LIVE_I_MEDITATES
 * Arguments	:	object ob -- the departing object
 *			object to -- its destination
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    ob->remove_prop(LIVE_I_MEDITATES);
} /* leave_inv */



/*
 * Function name: assess
 * Description:   mask parent to allow "estimate all"
 * Parameters:    stat - one of "STR", "DEX", "CON", "INT", "WIS",
 *				"DIS", "ALL".
 *                lower case is ok as well
 * Returns:       1 - success, 0 - stat not found
 */
/*
int
assess(string stat)
{
    int		i, s;
    string     stat_names = SD_STAT_NAMES;
    notify_fail("Usage: " + query_verb() + " <stat>\n"+
		"Or: " + query_verb() + " ALL\n");
    if (!strlen(stat))
    {
	return 0;
    }
    stat = LOW(stat);
    if (stat != "all")
    {
	i = ::assess(stat);
	notify_fail("Possible choices are: " +
	    implode(stat_names, ", ") +  ", or ALL \n");
	return i;
    }

    for (i = 0, s = sizeof(stat_names); i < s; ++i)
    {
	::assess(stat_names[i]);
    }
    return 1;
}
*/
