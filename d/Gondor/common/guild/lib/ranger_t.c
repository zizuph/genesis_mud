/*   
 *   The Rangers base training hall - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   This file is to be inherited by the train halls of all three 
 *   Ranger companies.
 *   Modified by Olorin, 30-Oct-1993
 *   
 */

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/binbit.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

/* A few definitions */
#define NUM		sizeof(query_money_types())
#define CLOSED		0	/* 1 = closed,   0 = open.  */

/* Function declaration */
void    set_up_skills();

/* Global variables */
int     closed;
int     company_no;
object  meditate;

void create_trainhall()
{
    set_short("Ranger Training Hall");
    set_long("This is a training hall of the Rangers.\n");
}

nomask void create_room() 
{ 
    closed = CLOSED; 

    create_trainhall();

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item(({"poster","skill list","skill-list","list"}), VBFC_ME("exa_poster"));

    RECRUITHALL->load_me();
    COUNCIL->load_me();
}

string exa_poster()
{
    int     i;
    int     snum;
    int     smax;
    int    *guild_sk = sk_query_train();
    string  list     = "These are the skills you can train here if you are a Ranger of " +
                       COMPANIES[company_no] + ":\n\n";

    guild_sk = sort_array(guild_sk);
    for(i = 0; i < sizeof(guild_sk); i++)
    {
        snum = guild_sk[i];
        smax = ::sk_query_max(snum,0);
        if(smax)
            list += sprintf("  %-25s  %-25s\n", sk_trains[snum][0], sk_rank(smax));
    }

    return list + "\n";
}

int do_read(string str)
{
    NF("Read what?\n");
    if(!str || (str != "poster" && str != "skill list" && str != "skill-list" && str != "list"))
        return 0;

    write(exa_poster());
    return 1;
}

string wizinfo() 
{
   return ("This is an occupational guild for elves, humans and dwarves only.\n"+
           "The style is Ranger, an occupation that specializes in outdoor-\n"+
	   "life, tracking, hunting and scouting.\n"+
	   "If there should be due cause to close down the guild, do so by\n"+
	   "typing:  Call here close_guild\n"+
	   "This will temporarily prevent mortals from entering. After a\n"+
	   "reboot, the guild will be open by default. Please send me some\n"+
	   "mail if there is anything that needs to be fixed.\n\n   /Elessar.\n");
}

int skill_loc(int sk)
{
    int a;
    a = member_array(sk, SKILLS);
    if (a < 0) 
        return -1;
    return a;
}

int cmax(int sk)
{
    int a;
    a = skill_loc(sk);
    if (a < 0) 
        return 0;
    if (company_no > 3) 
        return 0;
    return COMPANY_SKILLS[company_no][a];
}

int pupil_max(int sk)
{
    int a;
    a = skill_loc(sk);
    if (a < 0) 
        return 0;
    return PUPIL_SKILLS[a];
}

void company_set_skills()
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
    sk_add_train(SS_FORM_CONJURATION,({ me, me }), 0,0, cmax(SS_FORM_CONJURATION));
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
}

void init() 
{
  ::init();
  add_action("gs_meditate","meditate");
  add_action("gs_meditate","enter");
  add_action("do_read","read");
  init_skill_raise();
}

string close_guild() 
{
  if (closed) 
  {
    closed = 0;
    return "  **The guild is now open**";
  }
  closed = 1;
  return "  **The guild is now closed**";
}

int query_closed() { return closed; }

void set_up_skills() 
{
  company_set_skills();
}

void
gs_hook_already_meditate()
{
    write(BSN("You are already in the pool. If you wish to finish "+
	  "your meditating bath you can do so by typing 'rise'. "));
}

void
gs_hook_start_meditate()
{ 
  write(BSN("Slowly you sit down in the hot herb-bath, and "+
	"close your eyes. As the trance-inducing herb-smoke reaches into "+
	"your mind, a feeling of great ease and self control falls upon you. "+
	"You block off your senses and concentrate solely upon your "+
	"own mind. You find yourself able to <estimate> your different "+
	"preferences and <set> them at your own desire. "+
	"Just <rise> when you are done bathing. "));
}

void
gs_hook_rise() 
{
  write(BSN("As if ascending from a great depth, you rise to the surface "+
	"of your consciousness. You exhale and feel very relaxed as "+
	"you get up and walk out of the herb bath. "));
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
    write("  Skill:                  Cost:    "+
          "Next level:            Max level:\n"+
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
    write("  Skill:                  Cost:    "+
          "Next level:           Max level:\n"+
          "--------------------------------------"+
          "--------------------------------------\n");
}

/*
 * Function name: sk_list
 * Description:	  Someone wants a list of skills
 * Arguments:	  steps - How many steps the player wants to raise
 * Returns:	  1
 */
int
sk_list(int steps)
{
    int i, *guild_sk, learn;

    guild_sk = sort_array(sk_query_train());
    if (!steps)
	steps = 1;

    if (steps < 0)
    {
	sk_hook_skillisting();
	steps = 1;
    }
    else if (query_verb() == "learn")
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

    if (next_level > (max = sk_query_max(snum,0)))
	cost = "---";
    else
	cost = sk_cost(snum, this_level, next_level) + " cc";

    if(!max)
        return "";

    if (this_level >= 100)
	next_rank = "maxed";
    else
    	next_rank = sk_rank(next_level);

    max_rank = sk_rank(max);

    return sprintf("  %-21s %9s  %-21s %-20s\n", sk_trains[snum][0],
		cost, next_rank, max_rank);
}

varargs int
sk_query_max(int sknum, int silent)
{
    /* Should log silent calls to debug the decay system.
     * Skillno, returned value, name and current skill, if TP == 0.
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
         cs,
         ntp;
    object pl;
    string name,
           logtxt;

    if (!objectp(TP))
    {
        pl = previous_object();
        if (!objectp(pl))
            ntp = 1;
    }
    else
        pl = TP;

    wisint = (pl->query_stat(SS_INT) + pl->query_stat(SS_WIS)) / 6;

    if (silent)
    {
        if (ntp && !objectp(pl))
        {
            name = "Unknown";
            rv = cmax(sknum);
        }
        else if (pl->query_skill(SS_PUNISHMENT) == NOTRAIN  ||
                 pl->query_skill(SS_PUNISHMENT) == NOACCESS)
        {   
            name = pl->query_name() + " (punished)";
            rv = 0;
        }
        else if (query_bin_bits(1,16,2,this_player()) == 0)
        {
            name = pl->query_name() + " (pupil)";
            rv = pupil_max(sknum);
        }
        else
        {
            name = pl->query_name() + " (full)";
            rv = cmax(sknum);
        }
        logtxt = name + ", SkNum: " + sknum + ", MaxLvl: " + rv + ". ";
        if (ntp)
            logtxt += "No TP. ";
        else
            logtxt += "CurSkill: " + pl->query_base_skill(sknum) + ". ";
        logtxt += ctime(time()) + "\n";
        write_file("/d/Gondor/log/rangerdecay", logtxt);
        /* Finally we return the max-value for the decay to use. */
        return rv;
    }
    if (member_array(sknum,SUBTERFUGE_SKILLS) >= 0 )
    {
        i = 0;
        skill_sum = 0;
        while (i<sizeof(SUBTERFUGE_SKILLS)) 
        {
            if ((n = TP->query_skill(SUBTERFUGE_SKILLS[i])) >= 0) 
                skill_sum +=n;
            i++;
        }
        occup_stat = TP->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else if (member_array(sknum,NATURE_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i<sizeof(NATURE_SKILLS))
        {
            if ((n = TP->query_skill(NATURE_SKILLS[i])) >= 0) 
                skill_sum += n;
            i++;
        }
        occup_stat = TP->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else if (member_array(sknum,COMBAT_SKILLS) >= 0)
    {
        i = 0;
        skill_sum = 0;
        while (i<sizeof(COMBAT_SKILLS))
        {
            if ((n = TP->query_skill(COMBAT_SKILLS[i])) >= 0) 
                skill_sum += n;
            i++;
        }
        occup_stat = TP->query_stat(SS_OCCUP);
        current_max = (LEARN_FACTOR * occup_stat)+wisint - skill_sum;
    }
    else current_max = 100;
    if (query_bin_bits(1,16,2,TP) != company_no ) 
        orig_max = pupil_max(sknum);
    else orig_max = ::sk_query_max(sknum,silent);
    current_max = current_max + TP->query_skill(sknum);
    if (current_max < 0) 
        return 0;
    /* If the Ranger Council punishes a Ranger with no access to
     ** training, skill-decay will intentionally be affecting the poor b***ard.
     */
    if (TP->query_skill(SS_PUNISHMENT)==NOTRAIN ||
        TP->query_skill(SS_PUNISHMENT) == NOACCESS)
        return 0;
    if (current_max <= orig_max) 
        return current_max;
    return orig_max;
}
 
int
sk_improve(string str)
{
    object  tp = TP;
    int     rbit = query_bin_bits(1,18,2,tp),
            cbit = query_bin_bits(1,16,2,tp);
    if (rbit == 0) 
    {
        write("\n" + BSN("The Master Ranger says: Since thou art not a Ranger, " +
          "thou canst not be allowed to train here. "));
        if (!str)
          write(BSN("The Master Ranger says: But thou art welcome to have "
            + "a look at what we offer. "));
        else
            return 1;
    }
    else if (rbit == 3) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art banned from the "
          + "Rangers for thy evil deeds, so thou art not allowed to train "
          + "here!") + BSN("The Master Ranger says: Seek a way to redeem "
          + "thyself, or begone! "));
        return 1; 
    }
    else if ((TP->query_skill(SS_PUNISHMENT) == NOTRAIN)
            || (TP->query_skill(SS_PUNISHMENT) == NOACCESS)) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art not allowed to "
          + "train skills at present, for the Council of Rangers hath thee "
          + "punished!"));
        write(BSN("The Master Ranger says: Seek a way to redeem thyself, or "
          + "begone!"));
        return 1;
    }
    else if (rbit == 2) 
        write("\nThe Master Ranger bows before you, saying:\n"
          + "      Honoured Captain of the Rangers of "+TP->query_company()
          + ", greetings!\n");
    if (rbit >0 && cbit != company_no) 
    {
        write("\n" + BSN("The Master Ranger says: Thou art welcome "
          + "to train here, but we cannot offer thee more than pupil "
          + "training as thou art not one of the Rangers of "
          + COMPANIES[company_no] + ". "));
    }
    return ::sk_improve(str);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    ob->remove_prop(LIVE_I_MEDITATES);
}
