/*
 * The Gondorian Ranger Guild shadow
 *
 * Original code by Elessar
 * Modifications by Olorin and Mercade
 * Added functionability for punishments.
 * Elessar, May 1994.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh.c";
inherit "/d/Gondor/common/guild/lib/r_titles.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <const.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define RANGER_I_PREPARE_BRAWL "_ranger_i_prepare_brawl"
#define MOVED_WHILE_BRAWLING   3

private int  autosneak_on  = 0;
private int  master_ranger = 0;
private int  mentor       = 0;
private int  intro_type    = 0;

/* prototypes */
public int	query_guild_tax_occ();
public string	query_guild_style_occ();
public string	query_guild_name_occ();
public string	query_guild_skill_name(int type);
public int	query_guild_not_allow_join_occ(object player, string type,
  string style, string name);
static varargs void	do_leave_guild(object pl, string reason);
static int      check_kender(object ob);
static int	query_guild_keep_player(object ob);
public string	query_company();
public int	query_master_ranger();
public void	set_master_ranger(int i);
public int      query_ranger_mentor();
public void     set_ranger_mentor(int i);
public int	query_ranger_intro();
public void	set_ranger_intro(int i);
public int	query_incognito_occ();
nomask public string	query_guild_title_occ();
public void	log_killing(object killed, string whom);
public int	notify_you_killed_me(object killed);
public string	query_def_post();
public int	query_guild_leader_occ();
public string	query_guild_trainer_occ();
public void	init_occ_shadow(string arg);
public string	show_subloc(string subloc, object me, object for_obj);
public void	set_autosneak(int a);
public int	query_autosneak();
public varargs int	move_living(string how, mixed to_dest,
  int dont_follow, int no_glance);
public void	set_alignment(int a);
public void	adjust_alignment(int a);
public void	check_alignment();
public int	team_join(object member);
public int	set_leader(object leader);


/*
 * This is the initial taxrate for the guild. Use set_guild_pref() in 
 * the player to change it if needed.
 */
public int
query_guild_tax_occ()
{ 
    if (query_bin_bits( 1, 16, 2, query_shadow_who()) == 0) 
	return PUPIL_TAX;
    return TAXRATE;
}

public string
query_guild_style_occ()
{
    return "ranger";
}

public string
query_guild_name_occ()
{
    return "Gondorian Rangers Guild";
}

int
query_is_ranger_pupil()
{
    return (query_bin_bits(1, 16, 2, query_shadow_who()) == 0);
}

string
query_company()
{
    if (query_bin_bits(1,16,2,query_shadow_who()) == 3)
	set_bin_bits(1,16,2,query_shadow_who(), 2);
    return COMPANY_TITLE[query_bin_bits(1,16,2,query_shadow_who())];
}

public string
query_guild_skill_name(int type)
{
    switch (type)
    {
    case SS_HEARING:
	return "hearing";
	break;
    case SS_BRAWLING:
	return "brawling";
	break;
    case SS_PUNISHMENT:
    case SS_PUNISHED:
    case SS_REWARDED:
    case SS_MASTER_TASK:
	return "";
	break;
    }
    return query_shadow_who()->query_guild_skill_name(type);
}

public int
query_guild_not_allow_join_occ(object player, string type,
  string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
	return 1;
    if (name == "Angmar Army")
    {
	write("No ranger may become a minion of evil and supporter of the Dark Lord!\n");
	return 1;
    }

    if (name == "Drow race guild")
    {
	write("No Ranger may be and Elf of Darkness!\n");
	return 1;
    }
    if (name == "Riders of the Dark Alliance")
    {
	write("No Ranger will make an alliance with Darkness!\n");
	return 1;
    }
    if (style == "mage")
    {
	write("No Ranger may become a magician!\n");
	return 1;
    }
    if (style=="thief")
    {
	write("No Ranger may become a thief!\n");
	return 1;
    }
    if (player->query_race_name() == "kender")
    {
	write("A Kender cannot be a Ranger of the Westlands!\n");
	return 1;
    }
    return 0;
}

static varargs void
do_leave_guild(object pl, string reason)
{
    (GUILD)->short();
    (GUILD)->throw_out(pl, reason);
}

/* Function name: check_kender
 * Description:   The kender shadow might load after the ranger
 *                shadow. Gives a delay before checking the race.
 * Arguments:     object ob - the player
 * Returns:       1 
 */
static int
check_kender(object ob)
{
    if (ob->query_race_name() == "kender")
    {
        ob->catch_tell("No kender may be a Ranger of the Westlands!\n");
        set_alarm(1.0, 0.0, &do_leave_guild(ob, "kender"));
    }

    return 1;
}

/* 
 * Function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
static int
query_guild_keep_player(object ob)
{
    // Wizards can do whatever they want :)
    if (!ob->query_wiz_level())
    {
        // Delay in checking kender race, as the kender shadow
        // isn't loaded immediately, and kender will be seen as hobbits.
        set_alarm(10.0, 0.0, &check_kender(ob));

	if (ob->query_guild_style_lay() == "mage")
	{
	    ob->catch_tell("No mages may be a Ranger of the Westlands!\n");
	    set_alarm(1.0, 0.0, &do_leave_guild(ob, "mage"));
	}
	else if (ob->query_guild_style_lay() == "thief")
	{
	    ob->catch_tell("No thieves are allowed to be a Ranger "
	      + "of the Westlands!\n");
	    set_alarm(1.0, 0.0, &do_leave_guild(ob, "thief"));
	}
	else if (ob->query_race() == "goblin")
	{
	    ob->catch_tell("No goblins may be a Ranger of the Westlands!\n");
	    set_alarm(1.0, 0.0, &do_leave_guild(ob, "goblin"));
	}
	else if (ob->query_race_name() == "kender")
	{
	    ob->catch_tell("No kender may be a Ranger of the Westlands!\n");
	    set_alarm(1.0, 0.0, &do_leave_guild(ob, "kender"));
	}
	else if (ob->query_alignment() < RANGER_MIN_EVIL_ALIGN)
	{
	    ob->catch_tell("\nThe Dark Lord has tempted you too much!\n" +
	      "You are no longer worthy of being a Ranger!\n\n");
	    if (SECURITY->query_wiz_dom(shadow_who->query_real_name()) != "Gondor")
		set_alarm(1.0, 0.0, &do_leave_guild(ob, "evil"));
	    else
		ob->catch_tell("Your wizardhood protects you from being "+
		  "evicted from the Rangers.\n");
	}
	else if (ob->query_alignment() <
	  (RANGER_MIN_EVIL_ALIGN + RANGER_ALIGN_WARN))
	{
	    ob->catch_tell("\nYou know in your heart that "
	      + "you have done things that will eventually lead you into "
	      + "the Darkness, contrary to what a Ranger of the Westlands should "
	      + "be doing. Follow the light of the Valar, fight for the "
	      + "Free Peoples, and aid not the Enemy!\n\n");
	}
	return 1;
    }
return 1;
}


int
query_master_ranger()
{
    return master_ranger;
}

void
set_master_ranger(int i)
{
    if (i)
	master_ranger = 1;
    else
	master_ranger = 0;
}

int
query_ranger_mentor()
{
    return mentor;
}

void
set_ranger_mentor(int i)
{
    if (i)
	mentor = 1;
    else
	mentor = 0;
}

int
query_ranger_intro()
{
    return intro_type;
}

void
set_ranger_intro(int i)
{
    if (i)
	intro_type = 1;
    else
	intro_type = 0;
}

int
query_incognito_occ()
{
    object token = present("ranger_guild_object", query_shadow_who());
    if (!objectp(token))
	return 1;
    if (token->query_worn())
	return 0;
    return 1;
}

nomask public string
query_guild_title_occ()
{
    FIX_EUID;
    if (query_shadow_who()->query_wiz_level())
	return query_shadow_who()->query_title();
    return query_ranger_title(intro_type);
}

void log_killing(object killed, string whom)
{
    string file,
    domain;
    file = file_name(environment(query_shadow_who()));
    if((domain = explode(file,"/")[2]) == "Gondor")
	domain = CAP(explode(file,"/")[3]);
    write_file(RANGER_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + ", in " + domain + ".\n");
    write_file(NPC_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + " (" +
      file_name(environment(query_shadow_who())) + ").\n");
}

int
notify_you_killed_me(object killed)
{
    string  killed_race = (string)killed->query_race();
    mixed   whom;

    /* you have to do this in case more than one shadow defines the function, Olorin */
    shadow_who->notify_you_killed_me(killed);
    seteuid(getuid(TO));
    if (interactive(killed))
    {
	write_file(RANGER_KILLS, ctime(time()) + " " +
	  query_shadow_who()->query_name() + " killed " +
	  killed->query_name() + ", a player (" + killed_race + ").\n");
	/*
		if (killed_race == "elf" || killed_race == "hobbit" ||
		    killed_race == "dwarf" || killed_race == "human" ||
		    killed_race == "gnome")
		{
		    tell_object(query_shadow_who(),
			"You are not supposed to kill players, and especially not a "
			+ killed_race + "!\n");
		    tell_object(query_shadow_who(),
			"Consider this a warning from the Rangers Guild.\n");
		}
	*/
    }
    if (killed->id("Cityguard") || killed->id("_gondor_guard"))
    {
	tell_object(query_shadow_who(),
	  "You should not go around killing cityguards and the like.\n");
	tell_object(query_shadow_who(),
	  "Consider this a warning from the Rangers Guild.\n");
    }
    else if(killed->id("ranger"))
    {
	tell_object(query_shadow_who(),
	  "Oh no! You killed one of your own guild!\n" +
	  "Consider this a warning from the Ranger Council.\n");
	log_killing(killed, "ranger");
    }
    else if(killed->id("rohirrim"))
    {
	tell_object(query_shadow_who(),
	  "You should not go around killing Rohirrim, who are our allies!\n" +
	  "Consider this a warning from the Rangers Guild.\n");
	log_killing(killed, "rohirrim");
    }
    else if((function_exists("create_captain", killed) == "/d/Genesis/ship/captain") ||
      (function_exists("create_monster", killed) == "/d/Genesis/ship/captain"))
    {
	tell_object(query_shadow_who(),
	  "You should not go around killing ship captains!\n" +
	  "Consider this a warning from the Rangers Guild.\n");
	log_killing(killed, "ship captain");
    }
    else if((whom = killed->query_prop(GONDOR_M_LOG_RANGER_KILL)))
    {
	tell_object(query_shadow_who(),
	  "You should not go around killing the allies of the White Tower!\n" +
	  "Consider this a warning from the Rangers Guild.\n");
	if (stringp(whom))
	    log_killing(killed, whom);
	else
	    log_killing(killed, killed->short());
    }
    return 1;
}

string
query_def_post()
{
    if (query_bin_bits(1,16,2,query_shadow_who()) == 3)
	set_bin_bits(1,16,2,query_shadow_who(), 2);
    return COMPANY_POST[query_bin_bits(1,16,2,query_shadow_who())];
}

int
query_guild_leader_occ()
{
    FIX_EUID
    (R_COUNCIL)->load_me();
    if ((R_COUNCIL)->is_officer(query_shadow_who()->query_name()) ||
      (query_shadow_who()->query_skill(SS_MASTER_TASK) == RECRUITER))
	return 1;
    return 0;
}

string
query_guild_trainer_occ()
{
    if (query_bin_bits(1,16,2,query_shadow_who()) == 3)
	set_bin_bits(1,16,2,query_shadow_who(), 2);
    return COMPANY_TRAIN[query_bin_bits(1,16,2,query_shadow_who())];
}

void
init_occ_shadow(string arg)
{
    object pl;
    ::init_occ_shadow(arg);
    pl = query_shadow_who();
    TO->query_guild_keep_player(pl);
    pl->add_subloc(RANGER_S_SUBLOC, TO);
    FIX_EUID
    (R_SPONSORS)->load_me();
    if ((COUNCIL)->query_is_master(pl->query_name()))
	set_master_ranger(1);
    if ((R_SPONSORS)->query_can_sponsor(pl->query_name()))
	set_ranger_mentor(1);
}

string
show_subloc(string subloc, object me, object for_obj)
{
    int    as,
    rt,
    mmp;
    string str;

    if (subloc != RANGER_S_SUBLOC)
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (me->query_prop("_player_i_bath"))
	return "";
    FIX_EUID;
    if (query_company() == "the North")
    {
	if (query_incognito_occ())
	    return "";
    }

    as = query_shadow_who()->query_stat(SS_OCCUP) / 2;
    as += query_shadow_who()->test_ranger_skills() / 2;
    rt = 100 / sizeof(RANGER_LOOKS);
    as = as / rt;
    if (as >= sizeof(RANGER_LOOKS))
	as = sizeof(RANGER_LOOKS) - 1;

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";
    str += "looking " + RANGER_LOOKS[as] + ".\n";
    return str;
}

public void
set_autosneak(int a)
{
    autosneak_on = a;
}

public int
query_autosneak()
{
    return autosneak_on;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;
    object me;

    me = shadow_who;
    if (me->query_prop(RANGER_I_PREPARE_BRAWL))
	me->add_prop(RANGER_I_PREPARE_BRAWL, MOVED_WHILE_BRAWLING);

    if (
      !me->query_prop(LIVE_I_SNEAK) &&
      autosneak_on &&
      !(me->query_prop("_fogey_is_limping_")) &&
      query_verb() &&
      !(me->query_prop(OBJ_I_LIGHT) && (me->query_prop(OBJ_I_LIGHT) >
	  environment(me)->query_prop(OBJ_I_LIGHT))) &&
      !(objectp(me->query_attack()))
    )
    {
	hiding = environment(me)->query_prop(ROOM_I_HIDE);
	bval = me->query_skill(SS_SNEAK) * 2 + me->query_skill(SS_HIDE) / 3;
	bval = (bval - hiding) / 2;

	if (hiding >= 0 && bval > 0)
	{
	    val = bval + random(bval);
	    me->add_prop(OBJ_I_HIDE, val);
	    me->add_prop(LIVE_I_SNEAK, 1);
	    did_sneak = 1;
	}
	if (!did_sneak)
	    tell_object(me, "You failed to sneak.\n");
    }

    retval = me->move_living(how, to_dest, dont_follow, no_glance);

    if (!did_sneak)
	return retval;

    hiding = environment(me)->query_prop(ROOM_I_HIDE);
    bval = me->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;

    set_this_player(me);
    if (hiding < 0 || bval <= 0)
    {
	write("It's too difficult to hide in here, you're visible again.\n");
	me->reveal_me(0);
    }
    else if (me->query_prop(OBJ_I_LIGHT) &&
      (me->query_prop(OBJ_I_LIGHT) >
	environment(me)->query_prop(OBJ_I_LIGHT)))
    {
	write("You can't hide here, shining like that!\n");
	me->reveal_me(1);
    }

    val = bval + random(bval);
    me->add_prop(OBJ_I_HIDE, val);
    return retval;
}

/*
 * Function name: set_alignment
 * Description  : Set the amount of alignment points of the living. There is
 *                a maximum alignment a player can get. There is a Dutch
 *                proverb about trying to be more Roman-Catholic than the
 *                pope himself. We don't need that.
 * Arguments    : int a - the new alignment.
 */
public void
set_alignment(int a)
{
    shadow_who->set_alignment(a);
    check_alignment();
}

/*
 * Function name: adjust_alignment
 * Description  : When a player has solved a quest, his alignment may be
 *                adjusted if the quest is considered good or evil. This
 *                may only be done when the player receives experience and
 *                the quest bit is subsequently being set. When a quest is
 *                considered solvable for all players in the game, ie both
 *                'good' and 'evil' players, no alignment should be given
 *                out.
 * Arguments    : int align - the alignment of the quest. this should be
 *                            a value in the range -1000 .. 1000 and acts
 *                            the same as alignment in combat, though in
 *                            this case, 'good' players should naturally
 *                            receive positive alignment (ie solve good
 *                            quests).
 */
public void
adjust_alignment(int a)
{
    shadow_who->adjust_alignment(a);
    check_alignment();
}


/*
 * Function name: check_alignment
 * Description  : called from set_alignment() and adjust_alignment() to
 * 		  ensure that player is still worthy of being a ranger.
 */
public void
check_alignment()
{
    int		a = shadow_who->query_alignment();

    if (a < RANGER_MIN_EVIL_ALIGN)
    {
	shadow_who->catch_tell("The Dark Lord has tempted you too much!\n" +
	  "You are no longer worthy of being a Ranger!\n");
	if ( !shadow_who->query_wiz_level() )
	{
	    do_leave_guild(shadow_who, "evil: "+a);
	}
	else
	{
	    shadow_who->catch_tell("Your wizardhood protects you from being "+
	      "evicted from the Rangers.\n");
	}
    }
    else if (a < (RANGER_MIN_EVIL_ALIGN + RANGER_ALIGN_WARN))
    {
	shadow_who->catch_tell("You are giving in to the temptation of "+
	  "the Dark Lord!\n" +
	  "Mend your ways or you will become unworthy of being a ranger!\n");
    }
}



/*
 * Function name:   team_join
 * Description:     Sets this living as the leader of another.
 *                  Mask parent so that teaming with evils affects
 *		    ranger's alignment.
 * Arguments:       member: The objectpointer to the new member of my team
 * Returns:         True if member accepted in the team
 */
public int
team_join(object member)
{
    int		rval,
    al,
    before,
    diff;
    rval = shadow_who->team_join(member);
    if (rval &&
      (al = member->query_alignment()) < 0)
    {
	if (shadow_who->query_skill(SS_MASTER_TASK) == 4)
	{
	    log_file("alignadj",
	      shadow_who->query_name() + " lead evil (" + al
	      + ") being " + member->query_name() + ", avoiding penalty as "
	      + "Emissary. " + ctime(time()) + ".\n");
	    return rval;
	}
	before = shadow_who->query_alignment();
	shadow_who->adjust_alignment(al);
	diff = shadow_who->query_alignment() - before;
	log_file("alignadj",
	  shadow_who->query_name()+"'s alignment adjusted "+
	  "by "+diff+" for leading evil ("+al+") "+
	  member->query_name()+". "+ctime(time())+".\n");
    }
    return rval;
}

/*
 * Function name:    set_leader
 * Description:      Sets this living as a member in a team
 *                   Mask parent so that teaming with evils affects
 *		     ranger's alignment.
 * Arguments:        leader: The objectpointer to the leader of the team
 * Returns:          True if successfull
 */
public int
set_leader(object leader)
{
    int		rval,
    al,
    before,
    diff;
    rval = shadow_who->set_leader(leader);
    if (rval &&
      (al = leader->query_alignment()) < 0)
    {
	if (shadow_who->query_skill(SS_MASTER_TASK) == 4)
	{
	    log_file("alignadj",
	      shadow_who->query_name() + " joined evil (" + al
	      + ") being " + leader->query_name() + ", avoiding penalty as "
	      + "Emissary. " + ctime(time()) + ".\n");
	    return rval;
	}
	before = shadow_who->query_alignment();
	shadow_who->adjust_alignment(al);
	diff = shadow_who->query_alignment() - before;
	log_file("alignadj",
	  shadow_who->query_name()+"'s alignment adjusted "+
	  "by "+diff+" for joining evil ("+al+") "+
	  leader->query_name()+". "+ctime(time())+".\n");
    }
    return rval;
}
