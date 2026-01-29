#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma strict_types
/*
 * - /d/Avenir/union/list.c
 *
 * If any object is the Master object of the Union,
 * this is it. It handles logs, any removal of the player,
 * lists of membership, council, enemies of the guild,
 * the closed/open state of the guild. do
 * 'stat /d/Avenir/union/list' for up to date info.
 *   Cirion, 041696
 *
 * Revisions:
 *   Lucius, Oct 2005: Changed remove_union_punishment so that passing a
 *                     type will work and selectively remove only a specific one.
 *   Lucius, Aug 2006: Much cleanup, correction and removal of dead bits.
 *   Lucius, Oct 2006: Added toggleable options bits.
 *   Lucius, Jan 2009: Changed Guildmaster query methods.
 *   Lucius, Jul 2011: Add block/unblock. Some cleanups, also sync the
 *                     logging format with that from room/council.c
 *   Lucius, Apr 2016: Removed never used elect code.
 *   Lucius, May 2016: Modified expel code, added union texts, misc cleanups.
 *   Lucius, Aug 2017: Added visions handling code.
 *
 */
inherit "/std/object";
inherit "/d/Avenir/inherit/avenir_time";

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>

#include "defs.h"
#include "/d/Avenir/include/guilds.h"

#define DAY	86400
#define MONTH	2592000

#define QY      (SAVINGS + "members")

#define M_SPHERE	0
#define M_JOINED	1
#define M_MSGS		2
#define M_PUNISH	3
#define M_OPTS		4
#define M_ACTIVE	5
// RESERVED		6
// RESERVED		7
#define M_SIZEOF	8

/* mapping of form:
 * name: ({ sphere, joined, ({ msgs }), punished, options, active, empty, empty })
 *            0   ,    1  ,     2     ,     3   ,    4   ,   5   ,   6  ,   7
 */
private mapping members		= ([]),
		known_guilds	= ([]),
		guild_props	= ([]),
		nov_lvl		= ([]),
		visions		= ([]),
		expel		= ([]),
		texts		= ([]);

private string  *elders		= ({}),
		*friends	= ({}),
		*enemies	= ({}),
		*accepted	= ({}),
		*friend_guilds	= ({}),
		*enemy_guilds	= ({}),
		*hopefuls	= ({}),
		*named		= ({}),
		*blocked	= ({}),
        *blocked_guilds = ({});

private int closed;

private static string *gm_list, *vis_list;
private static object *alive = ({ }), *timers = ({ });
private static mapping punished_str = U_PUNISHED_STR;

private int remove_member(mixed whom);


private void
clog(string str)
{
    LOG_EVENT(str);
}

public int
valid_who(mixed whom)
{
    if (objectp(whom))
    {
	if (!query_interactive(whom))
	    return 0;

	whom = whom->query_real_name();
    }

    if (strlen(whom))
    {
	if (SECURITY->query_wiz_level(whom))
	    return 0;

	if (extract(whom, -2) == "jr")
	    return 0;

	return 1;
    }

    return 0;
}

/* Checks if 'who' can begin the Guru / Tornu quest. */
public int
valid_guru(object who)
{
    string name, sph;

    /* Have to be a member. */
    if (!objectp(who) || !IS_MEMBER(who))
	return 0;

    /* Already solved the guru quest. */
    if (who->test_bit("Avenir", GUILD_GROUP, TRAINING))
	return -1;

    name = who->query_real_name();

    /* Have to be in the system. */
    if (!members[name] || !strlen(sph = members[name][0]))
	return 0;

    /* Cannot be in training or duty spheres. */
    if ((sph == SPH_TRAINING) || (sph == SPH_DUTY))
	return 0;

    /* Need to have a minimum guildstat. */
    if (who->query_stat(SS_OCCUP) < 90)
	return 0;

#if 0
    /* Should the quest be closed, check for wizhood */
    if (!who->query_wiz_level() && !wildmatch("*jr", who->query_name()))
	return 0;
#endif

    /* Can quest! */
    return 1;
}

/*
 * How long has the person been idle?
 * -1  Player no longer exists!
 *  0  Player is in the game
 * num seconds since last login
 */
public int
idle_time(string name)
{
    object finger;
    int login_time;

    if (find_player(name))
	return 0;

    if (!SECURITY->exist_player(name))
	return -1;

#if 0
    /*
     * Skip this part, it's not used presently
     */
    finger = SECURITY->finger_player(name);
    login_time = finger->query_login_time();
    finger->remove_object();

    return time() - login_time;
#else
    return 1;
#endif
}

/*
 * Run through the member list and remove any players that
 * do no longer exist from the list.
 */
private void
cleanup(void)
{
    foreach(string who: m_indexes(members))
    {
	if (idle_time(who) == -1)
	    remove_member(who);
    }
}

/*
 * Load the Ogre Raiders attack room.
 * This room controls ogre raids.
 */
private void
raiders(void)
{
    OGRE_ATTACK->teleldensanka();
}

public int
update_gm_list(void)
{
    gm_list = SECURITY->query_guild_masters(OCC_SHORT);
    return 1;
}

public int
update_vis_list(void)
{
    if (file_size(VISIONS) != -2)
    {
	vis_list = ({ });
	return 0;
    }

    vis_list = filter(get_dir(VISIONS),
	&operator(<=)('a') @ &operator([])(,0));

    if (!sizeof(vis_list))
	return 0;

    sort_array(vis_list);
    return 1;
}

static void
create_object(void)
{
    reset_euid();

    set_name("guild");
    set_short("Union Guild Master");

    start_avtime();

    /* Restore saved variables. */
    restore_object(QY);

    set_alarm(itof(90 + random(DAY)), 0.0, raiders);
    set_alarm(300.0, itof(DAY + random(DAY * 3)), cleanup);

    update_gm_list();
    update_vis_list();
}

/*
 * For objects to be notified of time events.
 */
public void
notify_time(object ob)
{
    if (objectp(ob) && member_array(ob, timers) == -1)
	timers += ({ ob });
}

/*
 * Send and filter Avenir time events to listeners.
 */
static void
avenir_time_callout(int year, int week, int day, int hour)
{
    timers = filter(timers, &->avenir_time(year, week, day, hour));
}

// all members currently logged in...
public int
add_present_member(object who)
{
    alive += ({ who });
    return 1;
}

public object *
query_present_members(void)
{
    alive = filter(alive, objectp);
    return secure_var(alive);
}

public int
close_guild(int num = 1)
{
    object co;
    string cname;

    if (num == closed)
	return -1;

    closed = num;
    save_object(QY);

    if (living(co = calling_object()))
	cname = co->query_cap_name();
    else
	cname = file_name(co);

    LOG_ERR("The Union was "+ (num ? "closed" : "opened") +" by "+ cname);
    return closed;
}

public int
open_guild(void)
{
    return close_guild(0);
}

public int
query_guild_closed(void)
{
    return closed;
}

private string
get_name(mixed whom)
{
    if (objectp(whom))
	return whom->query_real_name();
    else if (stringp(whom))
	return lower_case(whom);
    else
	return "";
}

public string *
gm_list(void)
{
    return secure_var(gm_list);
}

public int
gmaster(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    return (member_array(name, gm_list) != -1);
}

public string *
member_list(void)
{
    return m_indexes(members);
}

public string *
elder_list(void)
{
    return secure_var(elders);
}

public string *
accepted_list(void)
{
    return secure_var(accepted);
}

public string *
enemy_list(void)
{
    return secure_var(enemies);
}

public string *
friend_list(void)
{
    return secure_var(friends);
}

public string *
named_list(void)
{
    return secure_var(named);
}

public string *
enemy_guild_list(void)
{
    return secure_var(enemy_guilds);
}

public string *
friend_guild_list(void)
{
    return secure_var(friend_guilds);
}

public string *
expel_list(void)
{
    return m_indexes(expel);
}

public string *
blocked_list(void)
{
    return secure_var(blocked);
}

public string *
blocked_guild_list(void)
{
    return secure_var(blocked_guilds);
}

public int
query_is_member(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    return sizeof(members[name]);
}

public int
query_is_elder(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    return (member_array(name, elders) != -1);
}

/*
 * FRIEND
 */

public int
add_friend(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (query_is_member(name))
	return 0;

    if (idle_time(name) == -1)
	return 0;

    if (member_array(name, friends) != -1)
	return 0;

    friends += ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is declared a graceful ally of the Union");

    return 1;
}

public int
remove_friend(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, friends) == -1)
	return 0;

    friends -= ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is no longer a friend of the Union.");

    return 1;
}

private int
sort_out_the(string str1, string str2)
{
    if (str1 == str2)
	return 0;

    str1 = lower_case(str1);
    str2 = lower_case(str2);

    sscanf(str1, "the %s", str1);
    sscanf(str2, "the %s", str2);

    if (str1 < str2)
	return -1;
    else if (str1 > str2)
	return 1;
    else
	return 0;
}

public string *
query_all_major_guilds_sorted(void)
{
    string *kg = (known_guilds["occ"] |
		  known_guilds["lay"] |
		  known_guilds["race"]);
    
    return sort_array(kg, sort_out_the);
}

public string *
query_all_major_guilds(void)
{
    string *kg = (known_guilds["occ"] |
		  known_guilds["lay"] |
		  known_guilds["race"]);
    
    return secure_var(kg);
}


public int
add_friend_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, query_all_major_guilds()) == -1)
	return 0;

    if (member_array(str, friend_guilds) != -1)
	return 0;

    if (member_array(str, enemy_guilds) != -1)
	return 0;

    friend_guilds += ({ str });
    save_object(QY);

    clog(CAP(str) + " is declared to be a friendly guild");
    return 1;
}

public int
remove_friend_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, friend_guilds) == -1)
	return 0;

    friend_guilds -= ({ str });
    save_object(QY);

    clog(CAP(str) + " is no longer a friendly guild.");
    return 1;
}

private int
member_of_friend_guild(object who)
{
    foreach(string guild : friend_guilds)
    {
	if (GMEMBER_APPARANT(who, guild))
	    return 1;
    }

    return 0;
}

public int
query_friend(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, friends) != -1)
	return 1;

    if (objectp(who) && member_of_friend_guild(who))
	return 1;

    return 0;
}

/*
 * ENEMY
 */

public int
add_enemy(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (query_is_member(name))
	return 0;

    if (idle_time(name) == -1)
	return 0;

    if (member_array(name, enemies) != -1)
	return 0;

    enemies += ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is declared a mortal enemy of the Union");

    return 1;
}

public int
remove_enemy(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, enemies) == -1)
	return 0;

    enemies -= ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is no longer an enemy of the Union.");

    return 1;
}

public int
add_enemy_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, query_all_major_guilds()) == -1)
	return 0;

    if (member_array(str, enemy_guilds) != -1)
	return 0;

    if (member_array(str, friend_guilds) != -1)
	return 0;

    enemy_guilds += ({ str });
    save_object(QY);

    clog(CAP(str) + " is declared to be an enemy guild");
    return 1;
}

public int
remove_enemy_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, enemy_guilds) == -1)
	return 0;

    enemy_guilds -= ({ str });
    save_object(QY);

    clog(CAP(str) + " is no longer an enemy guild");
    return 1;
}

private int
member_of_enemy_guild(object who)
{
    foreach(string guild : enemy_guilds)
    {
	if (GMEMBER_APPARANT(who, guild))
	    return 1;
    }

    return 0;
}

public int
query_enemy(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, enemies) != -1)
	return 1;

    if (objectp(who) && member_of_enemy_guild(who))
	return 1;

    return 0;
}

/*
 * ACCEPTED
 */

public int
add_accepted(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (query_is_member(name))
	return 0;

    if (member_array(name, accepted) != -1)
	return 0;

    if (idle_time(name) == -1)
	return 0;

    accepted += ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) +" was accepted for membership in the Union");

    return 1;
}

public int
remove_accepted(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (member_array(name, accepted) == -1)
	return 0;

    accepted -= ({ name });
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) +" is no longer accepted for membership");

    return 1;
}

public int
query_accepted(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    return (member_array(name, accepted) != -1);
}

/*
 * HOPEFUL
 */

public string *
hopeful_list(void)
{
    return secure_var(hopefuls);
}

public int
add_hopeful(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (query_is_member(name))
	return 0;

    if (idle_time(name) == -1)
	return 0;

    if (member_array(name, hopefuls) != -1)
	return 0;

    hopefuls += ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is recognized as a Union Hopeful");

    return 1;
}

public int
remove_hopeful(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, hopefuls) == -1)
	return 0;

    hopefuls -= ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is no longer a Union Hopeful");

    return 1;
}

public int
query_hopeful(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    return (member_array(name, hopefuls) != -1);
}

/*
 * NOVICES
 */

public int
add_nov_lvl(mixed whom, string how_much)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    nov_lvl[name] = how_much;
    save_object(QY);

    if (valid_who(name))
	clog(CAP(name) + " is novice level: "+ how_much);

    return 1;
}

public int
query_nov_lvl(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    return nov_lvl[name];
}

public int
remove_nov_lvl(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (!nov_lvl[name])
	return 0;

    m_delkey(nov_lvl, name);
    save_object(QY);

    if (valid_who(name))
	clog(CAP(name) + " had novice level cleared");

    return 1;
}

/*
 * NAMED
 */

/*
 * Function name:  add_named
 * Description:    Keeps a list of all who were ever Named
 *                 even those who have left or were purged.
 * Arguments:
 * Returns:
 */
public int
add_named(mixed who)
{
    string name = get_name(who);

    if (!sizeof(members[name]))
	return 0;

    if (member_array(name, named) != -1)
	return 0;

    named += ({ name });
    m_delkey(nov_lvl, name);

    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " was Named");

    return 1;
}

public int
query_named(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    return (member_array(name, named) != -1);
}

public int
remove_named(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, named) == -1)
	return 0;

    named -= ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is no longer Named");

    return 1;
}

public int
add_member(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (pointerp(members[name]))
    {   /* Expand array as-needed */
	while(sizeof(members[name]) < M_SIZEOF)
	    members[name] += ({ 0 });

	if (!mappingp(visions[name]))
	    visions[name] = ([ ]);

	return -1;
    }

    /* Initialize the member mapping for this player */
    members[name] = ({ DEFAULT_SPHERE, time(), 0, 0, 0, 0, 0, 0 });
    visions[name] = ([ ]);

    friends  -= ({ name });
    hopefuls -= ({ name });
    accepted -= ({ name });

    m_delkey(expel, name);
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) + " entered the Union");

    return 1;
}

/*
 * Remove the player from the member list.
 * All the lists, in fact.
 */

public int
remove_member(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]) && !sizeof(expel[name]))
	return 0;

    m_delkey(members, name);
    m_delkey(nov_lvl, name);
    m_delkey(visions, name);
    m_delkey(expel,   name);

    elders -= ({ name });

    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) + " was removed from the Union");

    return 1;
}

/*
 * ELDERS
 */

public int
add_elder(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    if (member_array(name, elders) != -1)
	return 0;

    elders += ({ name });
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) + " has risen to become an Elder");

    return 1;
}

public int
remove_elder(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (member_array(name, elders) == -1)
	return 0;

    elders -= ({ name });
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) + " lost the position of Elder");

    return 1;
}

/*
 * EXPELLED
 */

public int
add_expelled(mixed who, mixed by_whom)
{
    string name = get_name(who), from = get_name(by_whom);

    if (!strlen(name))
	return 0;

    if (sizeof(expel[name]))
	return 0;

    if (!sizeof(members[name]))
	return 0;

    expel[name] = secure_var(members[name]);
    m_delkey(members, name);
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) +" was declared to be expelled by "+ CAP(from));

    return 1;
}

public int
remove_expelled(mixed who, mixed by_whom)
{
    string name = get_name(who), from = get_name(by_whom);

    if (!strlen(name))
	return 0;

    if (!sizeof(expel[name]))
	return 0;

    members[name] = secure_var(expel[name]);
    m_delkey(expel, name);
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) +" had the expulsion lifted by "+ CAP(from));

    return 1;
}

public mixed *
query_expelled(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return ({ });

    if (!sizeof(expel[name]))
	return ({ });

    return secure_var(expel[name]);
}

/*
 * BLOCKED
 */

public int
add_blocked(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (query_is_member(name))
	return 0;

    if (idle_time(name) == -1)
	return 0;

    if (member_array(name, blocked) != -1)
	return 0;

    blocked += ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is declared 'persona non grata'");

    return 1;
}

public int
remove_blocked(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, blocked) == -1)
	return 0;

    blocked -= ({ name });
    save_object(QY);

    if (valid_who(who))
	clog(CAP(name) + " is no longer `persona non grata`");

    return 1;
}

private int
member_of_blocked_guild(object who)
{
    foreach(string guild : blocked_guilds)
    {
	if (GMEMBER_APPARANT(who, guild))
	    return 1;
    }

    return 0;
}

public int
query_blocked(mixed who)
{
    string name = get_name(who);

    if (!strlen(name))
	return 0;

    if (member_array(name, blocked) != -1)
	return 1;

    if (objectp(who) && member_of_blocked_guild(who))
	return 1;

    return 0;
}

public int
add_blocked_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, query_all_major_guilds()) == -1)
	return 0;

    if (member_array(str, enemy_guilds) != -1)
	return 0;

    if (member_array(str, friend_guilds) != -1)
	return 0;

    if (member_array(str, blocked_guilds) != -1)
	return 0;

    blocked_guilds += ({ str });
    save_object(QY);

    clog(CAP(str) + " is declared to be a blocked guild");
    return 1;
}

public int
remove_blocked_guild(string str)
{
    if (!strlen(str))
	return 0;

    if (member_array(str, blocked_guilds) == -1)
	return 0;

    blocked_guilds -= ({ str });
    save_object(QY);

    clog(CAP(str) + " is no longer a blocked guild");
    return 1;
}

/*
 * function: leave
 * This function takes care of everything we need
 * to take care of when the player leaves the guild
 * (whether he is kicked out, leaves voluntarily,
 * or changes to a forbidden race)
 * It is possible to leave in a number of ways, but
 * this function should always be called from each
 * leaving fun.
 */
public void
leave(object who)
{
    int result;
    string cname;
    object token, co = calling_object();

    if (living(co))
	cname = co->query_cap_name();
    else
	cname = file_name(co);

#ifdef VERBOSE
    clog("Leave was called in LIST for " +
	who->query_cap_name() + " by " + cname);
#endif

    if (valid_who(who))
	clog(who->query_name() +" is no longer one with the Shadows");

    /* Clear the guild stat, redo prefs */
    who->set_guild_pref(SS_OCCUP, 0);
    who->clear_guild_stat(SS_OCCUP);

    /* Remove accepted bit */
    who->clear_bit(GUILD_GROUP, ACCEPTED_BIT);

    /* Remove the various Union skills. */
    who->remove_skill(OCC_LEVEL);

    who->remove_skill(SS_SWAY);
    who->remove_skill(SS_SLASH);
    who->remove_skill(SS_FLING);

    who->remove_skill(US_PRIDE);
    who->remove_skill(US_GRACE);
    who->remove_skill(US_PURITY);
    who->remove_skill(US_DIGNITY);

    /* If player starts in the guild change that */
    if (who->query_default_start_location() == HOME)
	who->set_default_start_location(who->query_def_start());

    /* Get rid of the guild token */
    if (objectp(token = present(TOKEN_ID, who)))
	token->crumble();
    /* Get rid of any elder notebook */
    if (objectp(token = present("av_e_folio", who)))
	token->dust();
    /* Get rid of the voice notebook */
    if (objectp(token = present("av_v_notebook", who)))
	token->dust();
    /* Get rid of the combat veil */
    if (objectp(token = present("_union_scarf", who)))
    {
	token->remove();
	token->do_shred();
    }

    /* Take away soul and shadow */
    who->remove_cmdsoul(OCC_SOUL);
    who->update_hooks();

    who->setup_skill_decay();

    remove_member(who);

    /* If this is false, then the shadow is already gone, typically
     * as a result of failing the query_guild_keep_player() test.
     */
    if (!who->query_guild_member_occ())
	return;

    /* No problem removing the shadow. */
    if (who->remove_guild_occ())
	return;

    /* Failed to remove the shadow, should be a rare occurance. */
    LOG_ERR("ERR "+who->query_name() +
	" failed to have the shadow removed.");

    who->catch_tell("There is a problem.\nYour shadow "+
	"glows a malicious red and will not leave you.\n"+
	"Leave a bug report for the wizards.\n");
}

/*
 * Function:    Remove
 * Description: Expel a player from the Guild.
 * Arguments:   The player to remove.
 */
public void
remove(object who)
{
    string cname;
    object co = calling_object();

    if (living(co))
	cname = co->query_cap_name();
    else
	cname = file_name(co);

#ifdef VERBOSE
    clog(who->query_cap_name() +
	" logged on and was expelled by " + cname);
#endif

    /* Hurt him, but don't kill him */
    who->catch_tell("You feel all your strength leaving "+
	"you, you fall to the ground in despair.\n"+
	"A terrible agony shoots through your eyes!\n");

    tell_room(ENV(who), QCTNAME(who) +" falls to "+
	HIS(who) +" knees, and all the blood drains "+
	"from "+ HIS(who) +" face.\n", who, who);

    who->heal_hp(-(who->query_hp()));
    who->add_mana(-(who->query_max_mana()));
    who->add_fatigue(-(who->query_max_fatigue()));

    leave(who);
}

/*
 * SPHERES
 */

public string
query_union_sphere(mixed whom)
{
    string name = get_name(whom);
    mixed info = members[name];

    if (!sizeof(info))
	return DEFAULT_SPHERE;

    return (string)info[M_SPHERE];
}

public int
set_union_sphere(mixed whom, string to_sphere)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    members[name][M_SPHERE] = to_sphere;
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) + " had sphere changed to: "+ to_sphere);

    return 1;
}

/*
 * Convert the members mapping (of the format:
 *      name : ({ sphere, ... })
 * to a mapping of all the people in the spher, of format:
 *    sphere : ({ name1, name2, ... })
 *
 * Useful for PO aliases, etc.
 */
public mapping
sphere_members(void)
{
    mapping sph = ([]);

    foreach(string who, mixed info : members)
    {
	if (!sizeof(info))
	    continue;

	if (sph[info[M_SPHERE]])
	    sph[info[M_SPHERE]] += ({ who });
	else
	    sph[info[M_SPHERE]]  = ({ who });
    }

    return sph;
}

private int
add_single_union_message(mixed whom, string str)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    if (!sizeof(members[name][M_MSGS]))
    {
	members[name][M_MSGS] = ({ str });
	save_object(QY);
	return 1;
    }

    if (member_array(str, members[name][M_MSGS]) != -1)
	return 0;

    while(sizeof(members[name][M_MSGS]) >= MAX_GUILD_MESSAGES)
	members[name][M_MSGS] -= ({ members[name][M_MSGS][0] });

    members[name][M_MSGS] += ({ str });
    save_object(QY);

    if (valid_who(whom))
	clog(CAP(name) +" msg added: "+ str);

    return 1;
}

public int
add_union_message(mixed whom, string str)
{
    int sz;
    string *recip = ({});

    if (stringp(whom))
    {
	if (whom == "all")
	    recip = m_indexes(members);
	else if (add_single_union_message(whom, str))
	    return 1;
	else
	    recip = sphere_members()[lower_case(whom)];

	if (!(sz = sizeof(recip)))
	    return 0;

	while(sz--)
	    add_single_union_message(recip[sz], str);

	return 1;
    }

    if (!(sz = sizeof(whom)))
	return 0;

    while (sz--)
	add_single_union_message(whom[sz], str);

    return 1;
}

/*
 * Administrative function
 */

public int
clear_message_buffer(void)
{
    foreach(string who : m_indexes(members))
    {
	write("Wiping out messages for: " + who + "\n");
	members[who][M_MSGS] = 0;
    }

    save_object(QY);
    clog("Messages buffers for all members wiped");

    return 1;
}

public string *
get_union_messages(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    if (!sizeof(members[name][M_MSGS]))
	return ({ });

    whom = members[name][M_MSGS];
    members[name][M_MSGS] = 0;

    save_object(QY);
    return whom;
}

/*
 * For testing
 */

public string
joined_when(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return "(bad name)";

    mixed info = members[name];
    return ctime(info[M_JOINED]);
}

public int
add_known_guild(string name, string type)
{
    if (!strlen(name))
	return 0;
    else if (!sizeof(known_guilds[type]))
	known_guilds[type] = ({ name });
    else if (member_array(name, known_guilds[type]) != -1)
	return 0;
    else

	known_guilds[type] += ({ name });
    known_guilds[type] -= ({ 0 });

    save_object(QY);
    clog("Added known guild: ["+ type +"] "+ name);

    return 1;
}

public int
rem_known_guild(string type, string name)
{
    if (!strlen(type) || !strlen(name))
	return 0;

    if (!sizeof(known_guilds[type]))
	return -1;


    if (member_array(name, known_guilds[type]) == -1)
	return -2;

    known_guilds[type] -= ({ name });

    save_object(QY);
    clog("Removed known guild: ["+ type +"] "+ name);

    return 1;
}

public mixed
query_known_guilds(string type)
{
    if (!strlen(type))
	return secure_var(known_guilds);
    else
	return secure_var(known_guilds[type]);
}

/*
 * PUNISHMENT
 */

/*
 * Add a certain indices punishment bit to whom's punishment bits.
 */
public int
add_union_punishment(mixed whom, int type)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    int pun = members[name][M_PUNISH];

    if (pun & type)
	return 0;

    members[name][M_PUNISH] = (pun |= type);
    save_object(QY);

    return 1;
}

/*
 * Remove a certain punishment bit to whom's punishment bits.
 *
 */
public varargs int
remove_union_punishment(mixed whom, int type)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    int pun = members[name][M_PUNISH];

    /* No second arg: remove the entire punishment */
    if (type == 0)
    {
	members[name][M_PUNISH] = 0;
	save_object(QY);
	return 1;
    }

    /* Remove punishment selectively based on the type passed in */
    if (type & members[name][M_PUNISH])
    {
	members[name][M_PUNISH] ^= type;
	save_object(QY);
	return 1;
    }

    return 0;
}

/*
 * Get the punished bits for "whom"
 */
public int
query_union_punished_level(mixed whom)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    return members[name][M_PUNISH];
}

/*
 * Function name: punish_list
 * Description:   returns an array of all Union members who
 *                are currently being punished
 * Arguments:     none
 * Returns:       the array of player names
 */
public string *
punish_list(void)
{
    return filter(m_indexes(members), query_union_punished_level);
}

/*
 * Return the "unpacked" punished bits in the form of an array
 */
private int *
query_union_punished_bits(mixed whom)
{
    int *ret = ({ }),
     p_level = query_union_punished_level(whom);

    foreach(int pun: m_indexes(punished_str))
    {
	if (p_level & pun)
	    ret += ({ pun });
    }

    return ret;
}

public string
query_union_punished_string(mixed whom)
{
    string *tmpstrs = ({ });
    int *types = query_union_punished_bits(whom);

    if (!sizeof(types))
	return 0;

    foreach(int pun : types)
	tmpstrs += ({ punished_str[pun] });

    if (!sizeof(tmpstrs))
	return 0;

    return COMPOSITE_WORDS(tmpstrs);
}

public string *
query_union_punished_strings(mixed whom)
{
    string *tmpstrs = ({ });
    int *types = query_union_punished_bits(whom);

    if (!sizeof(types))
	return 0;

    foreach(int pun : types)
	tmpstrs += ({ punished_str[pun] });

    return tmpstrs;
}

/*
 * MEMBER OPTIONS
 */

/*
 * Set and query union member optional bits.
 */
public int
set_union_option(mixed whom, int option, int state)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    int opts = members[name][M_OPTS];

    if (state)
    {
	if (!(opts & option))
	    opts |= option;
    }
    else
    {
	if (opts & option)
	    opts ^= option;
    }

    members[name][M_OPTS] = opts;
    save_object(QY);
    return 1;
}

public int
query_union_option(mixed whom, int option)
{
    string name = get_name(whom);

    if (!sizeof(members[name]))
	return 0;

    return (members[name][M_OPTS] & option);
}

/*
 * VISIONS
 */

/*
 * Return a sorted array of vision files.
 */
public string *
query_vision_list(string str)
{
    return secure_var(vis_list);
}

/*
 * Return un-modified 'visions' mapping.
 */
public mapping
get_union_visions(void)
{
    return secure_var(visions);
}

/*
 * Query all visions assigned to 'whom'.
 * This is unfiltered.
 */
public mapping
query_union_visions(mixed whom)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    return visions[name];
}

/*
 * Filter the list of visions for 'whom'
 * and return the oldest pending.
 */
public string
query_union_vision(mixed whom)
{
    string vision, name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (!m_sizeof(visions[name]))
	return 0;

    /* Mappings with integer keys are inherently
     * sorted in ascending order.
     */
    foreach(int when, string what: visions[name])
    {
	m_delkey(visions[name], when);

	if (((MONTH + when) > time()) &&
	    (member_array(what, vis_list) != -1))
	{
	    vision = what;
	    break;
	}
    }

    save_object(QY);
    return vision;
}

/*
 * Assign vision 'str' to 'whom'.
 */
public int
assign_vision(mixed whom, string str)
{
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (member_array(str, vis_list) == -1)
	return 0;

    if (!mappingp(visions[name]))
    {
	visions[name] = ([ time() : str ]);
	save_object(QY);
	return 1;
    }

    /* Re-adding at bottom */
    foreach(int val, string vis: visions[name])
    {
	if (vis == str)
	    m_delkey(visions[name], val);
    }

    visions[name][time()] = str;
    save_object(QY);
    return 1;
}

/*
 * Clear the assigned visions list for 'whom'.
 */
public int
clear_union_visions(mixed whom)
{
    if (stringp(whom) && whom == "all")
    {
	foreach(string who: m_indices(visions))
	    visions[who] = ([]);

	save_object(QY);
	return 1;
    }

    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    visions[name] = ([]);
    save_object(QY);
    return 1;
}

/*
 * Remove vision 'str' from the pending list for 'whom'.
 */
public int
remove_vision(mixed whom, string str)
{
    int flag;
    string name = get_name(whom);

    if (!strlen(name))
	return 0;

    if (!m_sizeof(visions[name]))
	return 0;

    foreach(int val, string vis: visions[name])
    {
	if (vis != str)
	    continue;

	m_delkey(visions[name], val);
	flag++;
    }

    save_object(QY);
    return flag;
}

/*
 * TEXTS
 */

public string *
get_union_texts(void)
{
    return secure_var(texts);
}

public string *
query_union_texts(void)
{
    return m_indexes(texts);
}

public string
query_union_text(string str)
{
    if (!strlen(str))
	return "";

    str = lower_case(str);

    if (sizeof(texts[str]) != 2)
	return "";

    return texts[str][1];
}

public string
query_union_text_desc(string str)
{
    if (!strlen(str))
	return "";

    str = lower_case(str);

    if (sizeof(texts[str]) != 2)
	return "";

    return texts[str][0];
}

public int
change_union_text(string str, string what)
{
    if (!strlen(str))
	return 1;

    if (!strlen(what))
	return 2;

    str = lower_case(str);

    if (sizeof(texts[str]) != 2)
	return 3;

    texts[str][1] = what;
    save_object(QY);
    return 0;
}

public int
add_union_text(string str, string desc, string what)
{
    if (!strlen(str))
	return 1;

    if (!strlen(desc))
	return 2;

    if (!strlen(what))
	return 3;

    str = lower_case(str);

    if (sizeof(texts[str]))
	return 4;

    texts[str] = ({ desc, what });
    save_object(QY);
    return 0;
}

public int
rem_union_text(string str)
{
    if (!strlen(str))
	return 1;

    str = lower_case(str);

    if (!sizeof(texts[str]))
	return 2;

    m_delkey(texts, str);
    save_object(QY);
    return 0;
}

/*
 * PROPS
 */

/*
 * Function name: guild_add_prop
 * Description:   Add a misc prop to the guild
 * Arguments:     prop - the name of the property
 *                val - the value of the property
 */
public void
guild_add_prop(string prop, mixed val)
{
    guild_props[prop] = val;
    save_object(QY);
}

public mixed
guild_query_prop(string prop)
{
    return guild_props[prop];
}

/* stat_object gives some general info on the Union */
public string
stat_object(void)
{
    int num;
    string str;

    str = "~~~~~~* "+
	"Special information on the Union of the Warriors of Shadow"+
	" *~~~~~~\n";
    str += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" +
	"~~~~~~~~~~~~~~~~~\n";

    if (sizeof(gm_list))
    {
	str += "Guild Master"+ (sizeof(gm_list) > 1 ? "s: " : ": ") +
	    COMPOSITE_WORDS(map(gm_list, capitalize)) + ".\n";
    }
    else
    {
	str += "There is no Guild Master assigned at present.\n";
    }

    num = sizeof(elders);
    if (num > 0)
    {
	str += "The "+ (num > 1 ? "Elders of the Union are" :
	    "only Elder of the Union is") + ": " +
	    COMPOSITE_WORDS(map(elders, capitalize)) + ".\n";
    }
    else
    {
	str += "There are no Elders at present.\n";
    }

    string *arr = sort_array(map(m_indexes(members), capitalize));

    str += "\nThere are currently "+ m_sizeof(members) +
	" members of the Union:\n\n";
    str += sprintf("    %-#75s", implode(arr, "\n"));

#define HIC(x, y)  HANGING_INDENT(COMPOSITE_WORDS(y), x, 70)

    str += "\n\nUnion Spheres:\n\n";
    {
	mapping m_sph = sphere_members();
	string *sphs = sort_array(m_indexes(m_sph));
	int ix = -1, sz = sizeof(sphs);

	while(++ix < sz)
	{
	    str += sprintf("%' '-11s: %s", capitalize(sphs[ix]),
		HIC(13, sort_array(map(m_sph[sphs[ix]], capitalize))));
	}
    }
    str += "\n";

    /* Additional information for the eyes of the guildmaster */
    if (gmaster(this_player()))
    {
	str += "Hopeful  : " +
	    HIC(12, sort_array(map(hopefuls, capitalize)));
	str += "Accepted : " +
	    HIC(12, sort_array(map(accepted, capitalize)));
	str += "Expelled : " +
	    HIC(12, sort_array(map(expel_list(), capitalize)));
	str += "Friends  : " +
	    HIC(12, sort_array(map(friends, capitalize)));
	str += "Enemies  : " +
	    HIC(12, sort_array(map(enemies, capitalize)));
	str += "Blocked  : " +
	    HIC(12, sort_array(map(blocked, capitalize)));
	str += "Friend Guilds : " +
	    HIC(17, sort_array(friend_guilds));
	str += "Enemy Guilds  : " +
	    HIC(17, sort_array(enemy_guilds));
    }
    str += "\n";

    if (closed)
    {
	str += "The Union is currently CLOSED to training, "+
	    "joining, and leaving.\nDo 'Call "+ file_name(TO) +
	    " open_guild' to open it again.\n";
    }
    else
    {
	str += "The Union is currently OPEN to training, "+
	    "joining, and leaving.\nCall "+file_name(TO) +
	    " close_guild' to shut everything down.\n";
    }

    str += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" +
	"~~~~~~~~~~~~~~~~~\n";

    return str;
}

/*
 * lib/stone.h contains variables and functions specific to
 * the functioning of the Union sphere guild object located
 * at: obj/stone.c
 */
#include "lib/stone.h"
