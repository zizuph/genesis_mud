/*
 * The Rangers of the North guild shadow
 *
 * Elessar, Sept. 1998.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <const.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/north/lib/ranger_defs.h"

private int  autosneak_on  = 0;
private int  intro_type    = 0;
int  Officer;

public string Rtitle = "",
              ranger_name = "";

/* prototypes */
public int        query_guild_tax_occ();
public string     query_guild_style_occ();
public string     query_guild_name_occ();
public string     query_guild_skill_name(int type);
public int        query_guild_not_allow_join_occ(object player, string type,
					       string style, string name);
static varargs void	do_leave_guild(object pl, string reason);
static int        query_guild_keep_player(object ob);

public int        set_officer(int i);
public int        query_ranger_intro();
public void       set_ranger_intro(int i);
public int        query_incognito_occ();
nomask public string	query_guild_title_occ();
public void	      log_killing(object killed, string whom);
public int        notify_you_killed_me(object killed);
public string     query_def_post();
public int        query_guild_leader_occ();
public string     query_guild_trainer_occ();
public void	      init_occ_shadow(string arg);
/*
public string	show_subloc(string subloc, object me, object for_obj);
*/
public void	      set_autosneak(int a);
public int        query_autosneak();
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
    return "Rangers of the North";
}

public string
query_company()
{
    return "the North";
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
    }
    return query_shadow_who()->query_guild_skill_name(type);
}

public int
query_guild_not_allow_join_occ(object player, string type,
                               string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
	return 1;
    if (name == "Army of Morgul")
    {
        write("No Ranger may become a minion of evil and supporter "
          + "of the Dark Lord!\n");
        return 1;
    }
    if (name == "Soldiers of the Dragonarmy")
    {
        write("A Ranger does not support Evil even in foreign lands!\n");
        return 1;
    }
    if (name == "Drow race guild")
    {
        write("No Ranger may be an Elf of Darkness!\n");
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
    return 0;
}

static varargs void
do_leave_guild(object pl, string reason)
{
    (NORTH_MASTER)->short();
    (NORTH_MASTER)->throw_out(pl, reason);
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
    string  racename;
    FIX_EUID
    racename = ob->query_race();
    if (ob->query_guild_style_lay() == "mage")
    {
        ob->catch_tell("No mages may be a Ranger of the North!\n");
        set_alarm(1.0, 0.0, &do_leave_guild(ob, "mage"));
    }
    else if (ob->query_guild_style_lay() == "thief")
    {
        ob->catch_tell("No thieves are allowed to be a Ranger "
          + "of the North!\n");
        set_alarm(1.0, 0.0, &do_leave_guild(ob, "thief"));
    }
    else if (racename != "human")
    {
        ob->catch_tell("No " + racename + " may be a "
          + "Ranger of the North!\n");
        set_alarm(1.0, 0.0, &do_leave_guild(ob, racename));
    }
    else if (ob->query_guild_name_race() != "Dunedain")
    {
        ob->catch_tell("\nWhen you abandon your Dunadan heritage, you also "
          + "lay waste to your career as a Ranger of the North!\n\n");
        set_alarm(1.0, 0.0, &do_leave_guild(ob, "not Dunadan"));
    }
    else if (ob->query_alignment() < RANGER_MIN_EVIL_ALIGN)
    {
        ob->catch_tell("\nThe Dark Lord has tempted you too much!\n" +
		    "You are no longer worthy of being a Ranger!\n\n");
        if (SECURITY->query_wiz_dom(shadow_who->query_real_name()) != "Gondor")
            set_alarm(1.0, 0.0, &do_leave_guild(ob, "evil"));
        else
            ob->catch_tell("Your wizardhood protects you from being "+
                "evicted from the Rangers of the North.\n");
    }
    else if (ob->query_alignment() <
	     (RANGER_MIN_EVIL_ALIGN + RANGER_ALIGN_WARN))
    {
        ob->catch_tell("\nYou know in your heart that "
          + "you have done things that will eventually lead you into "
          + "the Darkness, contrary to what a Ranger of the North should "
          + "be doing. Follow the light of the Valar, fight for the "
          + "Free Peoples, and aid not the Enemy!\n\n");
    }
    return 1;
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
    return "";
}

public string
query_ranger_name()
{
    if (!strlen(ranger_name))
    {
        ranger_name = (NORTH_MASTER)->query_ranger_name(
          query_shadow_who()->query_real_name());
    }
    return ranger_name;
}

nomask public int
query_ranger_level(int flag = 0)
{
    string *titles;
    int     i, n, rk, r_stat, avg;

    FIX_EUID;
    
    ranger_name = (NORTH_MASTER)->query_ranger_name(
      query_shadow_who()->query_real_name());
    titles = (NORTH_MASTER)->query_ranger_titles();

    rk = shadow_who->query_skill(SS_NRANGER_RANK);
    r_stat = query_shadow_who()->query_stat(SS_OCCUP);
    if (r_stat > 100)
        r_stat = 100;
    n = sizeof(titles);
    avg = ((r_stat * (n - 1)) / 100);
    if (flag <= 0)
    {
        avg /= 2;
        avg += rk;
        if (avg > n)
            avg = n;
    }
    if (avg > RECRUIT_RANK)
    {
        if (!strlen(ranger_name))
            avg = RECRUIT_RANK;
    }
    if (flag >= 0)
    {
        avg += (Officer * n);
    }
    else
    {
        switch(Officer)
        {
            case 1:
            case 2:
                avg = (Officer + 1) * n;
                break;
            case 0:
            default:
                break;
        }
    }
    if (avg < 0)
        avg = 0;
    return avg;
}

public int
set_officer(int i)
{
    if (!intp(i) || (i < 0) || (i > 2))
        return -1;
    Officer = i;
    return Officer;
}

public int
query_officer()
{
    return Officer;
}

public int
set_ranger_rank(int i)
{
    shadow_who->set_skill(SS_NRANGER_RANK, i);
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ());
    return 1;
}

public int
query_ranger_rank()
{
    return shadow_who->query_skill(SS_NRANGER_RANK);
}

public nomask string
query_ranger_title()
{
    FIX_EUID;
    /*
     * Officers
     */
    if (Officer)
    {
        return (NORTH_MASTER->query_officer_titles())[Officer-1];
    }
    /*
     * Elders
     */
    if (query_ranger_rank() > (sizeof(NORTH_MASTER->query_ranger_titles()) -1))
        return (NORTH_MASTER->query_elder_titles())[0];
    /*
     * Ordinary
     */
    return (NORTH_MASTER->query_ranger_titles())[query_ranger_level()];
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
        killed->query_name() + ", " + LANG_ADDART(whom) + ", in " 
          + domain + ".\n");
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

    shadow_who->notify_you_killed_me(killed);
    seteuid(getuid(TO));
    if (interactive(killed))
    {
        write_file(RANGER_KILLS, ctime(time()) + " " +
            query_shadow_who()->query_name() + " killed " +
            killed->query_name() + ", a player (" + killed_race + ").\n");
    }
    if (killed->id("Cityguard") || killed->id("_gondor_guard"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing cityguards and the like.\n");
        tell_object(query_shadow_who(),
            "Is your soul controlled by the Dark Lord?\n");
    }
    else if(killed->id("ranger"))
    {
        tell_object(query_shadow_who(),
            "Oh no! You killed one of your own guild!\n" +
            "How long before the Dark Lord can claim your heart now?\n");
        log_killing(killed, "ranger");
    }
    else if(killed->id("rohirrim"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing Rohirrim, who are "
              + "of the Free Peoples!\n" +
            "Search your heart, are you fit to be a Ranger?\n");
        log_killing(killed, "rohirrim");
    }
    else if((function_exists("create_captain", killed) == "/d/Genesis/ship/captain") ||
            (function_exists("create_monster", killed) == "/d/Genesis/ship/captain"))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing ship captains!\n" +
            "Consider carefully your path; it is heading towards "
              + "Darkness.\n");
        log_killing(killed, "ship captain");
    }
    else if((whom = killed->query_prop(GONDOR_M_LOG_RANGER_KILL)))
    {
        tell_object(query_shadow_who(),
            "You should not go around killing the allies of the White "
              + "Tower!\n" +
            "Darkness must be clouding your mind!\n");
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
  return "/d/Gondor/common/guild/north/post";
}

int
query_guild_leader_occ()
{
    FIX_EUID
    return (Officer ? 1 : 0);
}

string
query_guild_trainer_occ()
{
  return "/d/Gondor/common/guild/north/north_train";
}

void
init_occ_shadow(string arg)
{
    object pl;
    ::init_occ_shadow(arg);
    pl = query_shadow_who();
    TO->query_guild_keep_player(pl);
    FIX_EUID
    set_officer((NORTH_MASTER)->is_officer(pl->query_name()));
/*
    pl->add_subloc(RANGER_S_SUBLOC, TO);
*/
}

/*
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
 
    as = query_shadow_who()->query_stat(SS_OCCUP);
    
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
*/
 
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
    bval = me->query_skill(SS_HIDE) * 2 + me->query_skill(SS_SNEAK) / 3;
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
