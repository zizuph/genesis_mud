/*   
 *   The training hall for the Rangers of the North
 *   Separated from the Gondorian Rangers Guild 1998
 *   Elessar.
 *   Added "estimate all", cleanup -- Gnadnar 21 August 1998
 *   
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/north/lib/ranger_defs.h"

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
public void		gs_hook_already_meditate();
public void		gs_hook_start_meditate();
public void		gs_hook_rise();
public void		sk_hook_write_header(int steps);
public void		sk_hook_skillisting();
public int		sk_list(int steps);
public varargs string	sk_fix_cost(int snum, int steps);
public varargs int	sk_query_max(int sknum, int silent);
public int		sk_improve(string str);
public void		leave_inv(object ob, object to);


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

    set_short("The Training Hall of the Rangers of the North");
    set_long(BS("You are in the training hall. The hall is large "+
        "and has a vaulted ceiling. Tapestries hang on each of "+
        "the four walls. Corridors lead east and south out of the "+
        "hall. A master ranger is here to assist you with the "+
        "training and education.\n"));

    add_exit(RANGER_NORTH_DIR+"n_corridor","east",0);
    add_exit(RANGER_NORTH_DIR+"w_corridor","south",0);

    add_item(({"tapestries", "tapestry"}),
        BS("Each tapestry shows a different forest, and "+
        "the forests also have different seasons. On the west "+
        "tapestry a willow-meadow in spring, on the south an "+
        "elm-wood in summer, on the east a beech-forest in "+
        "autumn and on the north wall pine-trees in winter.\n"));
    add_item("ceiling",BS("The arches of the ceiling connect in a "+
        "central point. The central point is carved to resemble "+
        "a star.\n"));
    add_item(({"master ranger","ranger"}),BSN(
	"This is one of the veteran rangers who have retired from "+
      "active duty, and have decided to help run this hideout. He "+
      "tells you that you may "+
      "<meditate> to set your stat-training preferences, and "+
      "<learn> or <improve> skills. "+
      "You may also <list guilds> to discover information about " +
      "the guilds of which you are a member. " +
      "A poster on the north wall shows you to which " +
      "level you can train skills here as one of the "+
      "Rangers of the North."));


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

void enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from);
    
    if (!interactive(ob) || !closed)
        return;
    
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here. "+
          "I'm doing some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move(RANGER_NORTH_DIR+"n_corridor");
    }
}

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
    string  list     =  "These are the skills you can train here "+
                        "if you are a Ranger of the North:\n\n";

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
	"This is the training hall for the Rangers of the North.\n"
     +"They are an occupational ranger-style guild, specializing\n"
     +"in stealth and fighting.\n"
     +"Any question may be directed to me.\n"
     +" - Elessar.\n");
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

    if (a >= 0) 
    {
        return NORTH_SKILLS[a];
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
 * Function name:	gs_hook_already_meditate
 * Description	:	write a already-meditating msg
 */
public void
gs_hook_already_meditate()
{
    WRITE("You are already in the pool. If you wish to finish "+
	  "your meditating bath you can do so by typing 'rise'. ");
} /* gs_hook_already_meditate */


void
gs_hook_start_meditate()
{ 
    write(BS("Slowly you sit down in the centre of the room, and "+
        "close your eyes. As trance-inducing smoke from burning "+
        "herbs reaches into your mind, a feeling of great ease "+
        "and self control falls upon you. "+
        "You block off your senses and concentrate solely upon "+
        "your own mind. You find yourself able to <set> your "+
        "different preferences at your own desire. "+
        "Just <rise> when you are done meditating.\n"));
}

void
gs_hook_rise() 
{
    write(BSN("As if ascending from a great depth, you rise to "+
      "the surface of your consciousness. You exhale and feel "+
      "very relaxed as you get up from your sitting position."));
}

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
    write("Here follows all skills we teach, and your next level "+
        "in those skills:\n");
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
    } 
    else 
    {
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
    
    pl = this_player();
    wisint = (pl->query_base_stat(SS_INT) + pl->query_base_stat(SS_WIS)) / 6;
    wisint += 50;

    if (silent)
    {
        return cmax(sknum);
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

    if (!strlen(pl->query_ranger_name())) 
    {
        write_file("/d/Gondor/common/guild/north/log/training",
          pl->query_name() + " trains at recruit level. " + ctime(time()) + ".\n");
        orig_max = cmax(sknum);
    }
    else 
    {
        orig_max = cmax(sknum);
    }

    current_max += pl->query_base_skill(sknum);
    if (current_max < 0) 
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

    if (!IS_NRANGER(tp)) 
    {
        write("\n" +
	  BSN("The Master Ranger says: Since you are not a Ranger " +
          "of the North, you cannot be allowed to train here. "));
        if (!str)
	{
          write(BSN("The Master Ranger says: You will have to join "
            + "us before I will tell you what training we offer. "));
          return 1;
	}
      else
	{
          return 1;
	}
    }
    else if (tp->query_captain()) 
    {
        write("\nThe Master Ranger bows before you, saying:\n"
          + "      Honoured Captain of the Rangers of "+TP->query_company()
          + ", greetings!\n");
    }
    else if (tp->query_ranger_name())
    {
        write("\nThe Master Ranger says: Greetings, "
          + tp->query_ranger_name() + "!\n");
    }
    else
    {
        write("\n" + BSN("The Master Ranger says: You are welcome, "
          + "newcomer! We will train you so you may join the "
          + "ranks of the Rangers of the North. "));
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



