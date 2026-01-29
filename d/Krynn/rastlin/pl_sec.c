/*
 * /std/player_sec.c
 *
 * This is the security part of the old player.c.
 *
 * This file is statically inherited by player_pub to ensure the
 * protection of all lower level routines.
 */

#pragma save_binary

inherit "/std/living";

#include "/std/player/savevars_sec.c"	/* Variables saved to player file */
#include "/std/player/quicktyper.c"
#include "/std/player/cmd_sec.c"
#include "/std/player/getmsg_sec.c"
#include "/std/player/death_sec.c"
#include "/std/player/querys_sec.c"
#include "/std/player/pcombat.c"

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <money.h>
#include <std.h>
#include <stdproperties.h>
#ifndef OWN_STATUE
#include <living_desc.h>
#endif

#define LINKDEATH_TIME 180.0 /* three minutes */
#define LOGIN_OBJECT   "/secure/login"

/*
 * Global variable. It is not saved.
 */
private static int    ld_alarm;  /* The alarm used when a player linkdies */
private static int do_skill_decay = 0; /* Flag to control skill decay */

#ifdef RELAY_HOST
/*
 * Global variable. It is not saved.
 */
private static string real_host; /* name o/t real host in case of a relay */

/*
 * Function name: query_real_host
 * Description  : If a player is using a relay, this will return the
 *                real host name of the player.
 * Returns      : string - the real host-name of the player.
 */
public nomask string
query_real_host()
{
    return real_host;
}
#endif

/*
 * Prototypes
 */
void new_init();
void load_auto_obj(string *load_arr);
int load_recover_list(string pl_name, string *recover_arr);
void load_auto_shadow(string *load_arr);
static void init_saved_props();
static nomask void decay_skills();

/*
 * Function name: query_def_start
 * Description:   Return the default starting location of the player type
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public string
query_def_start() { return DEFAULT_START; }

/*
 * Function name: query_orig_stat
 * Description:   Return the default starting stats of a player
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public int *
query_orig_stat() 
{
    int i, *list;

    list = ({});
    i = -1;
    while(++i < SS_NO_STATS)
    {
	list += ({ 1 });
    }
    return list;
}

/*
 * Function name: query_orig_learn
 * Description:   Return the default starting stats of a player
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public int *
query_orig_learn() 
{
    int i, *list;

    list = ({});
    i = -1;
    while(++i < SS_NO_EXP_STATS)
    {
	list += ({ 100 / SS_NO_EXP_STATS });
    }
    return list;
}

#ifndef NO_ALIGN_TITLE
/*
 * Function name: query_new_al_title
 * Description:   Return the default starting title of a player
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public string
query_new_al_title()
{
    return "neutral";
}
#endif NO_ALIGN_TITLE

/*
 * Function name: fixup_screen
 * Description:   Restore the players screen width. Normally called
 *                during login.
 */
public nomask void
fixup_screen()
{
    int width = query_prop(PLAYER_I_SCREEN_WIDTH);

    if (!width)
	width = 80;
    set_screen_width(width);
}

/*
 * Function name: add_prop_player_i_screen_width
 * Description:   Autodetect when a player's screen width is modified
 *                and notify the game driver. Do not allow VBFC values.
 * Arguments:     val: The new property value
 */
public nomask int
add_prop_player_i_screen_width(mixed val)
{
    if (!intp(val))
	return 1;
    if (val)
	set_screen_width((int)val);
    else
	set_screen_width(80);
    return 0;
}

/*
 * Function name:   setup_skill_decay()
 * Description:     setup the skill decay flag.
 */
public nomask void
setup_skill_decay()
{
    if (query_wiz_level())
	return;

    do_skill_decay = 1;
    set_alarm(5.0, 0.0, decay_skills);
}

/*
 * Function name:   query_skill_decay
 * Description:     Gives back the skill decay status
 * Returns:         The skill decay status
 */
public nomask int
query_skill_decay()
{
    return do_skill_decay;
}

/*
 * Function name: get_train_max
 * Description:   Return the max value of a skill that a trainer trains.
 * Arguments:     skill - the skill to be examined.
 *                ob - the object defining the skill
 * Returns:       See above.
 */
static nomask int
get_train_max(int skill, mixed ob)
{
    int rval = 0;

#ifdef LOG_BAD_TRAIN
    if (catch(rval = ob->sk_query_max(skill, 1)))
	log_file(LOG_BAD_TRAIN, ctime(time()) + ": " + ob + "\n");
#else
    catch(rval = ob->sk_query_max(skill, 1));
#endif

    return rval;
}

/*
 * Function name: query_decay_skill
 * Description:   Return 1 if a skill should be decayed, 0 if not.
 * Arguments:     list - the list of objects defining the skill train max
 *                skill - the skill to be examined.
 * Returns:       See above.
 */
static nomask int
query_decay_skill(mixed list, int skill)
{
    int *sklist, i, sz, max, sk;

    /* Load all trainers first */
    /*list->teleledningsanka();*/

    /* Check the contents */
    sklist = ({ }) + map(list, &get_train_max(skill, ));
        if (sizeof(SS_SKILL_DESC[skill]))
	    sk = SS_SKILL_DESC[skill][4];
        else
	    sk = 0;
    sklist += ({ (sk > 0 ? sk : MIN_SKILL_LEVEL) });

    for (i = 0, max = 0, sz = sizeof(sklist) ; i < sz ; i++)
	        if (max < sklist[i])
		    max = sklist[i];

    return (query_base_skill(skill) > max);
}

static nomask void
loadall(mixed list, mixed obs, int *skills)
{
    int i, sz;
    
    if (sizeof(list))
    {
	list[0]->teleledningsanka();
	list = exclude_array(list, 0, 0);
	set_alarm(0.0, 0.0, &loadall(list, obs, skills));
    }
    else
    {
	/* Find out what skills need decay */
	skills = filter(skills, &query_decay_skill(obs, ));
	
	/* Do decay */
	if (sizeof(skills))
	{
	    for (i = 0, sz = sizeof(skills) ; i < sz ; i++)
		set_skill(skills[i], query_base_skill(skills[i]) - 1);
	}
	else
	    do_skill_decay = 0;
    }
}

/*
 * Function name: decay_skills
 * Description:   Do skill decay in the player
 *                Call this function ONLY if it's necessary, as when
 *                entering the game or entering/leaving a guild as
 *                it's a bit costly.
 */
static nomask void
decay_skills()
{
    mixed obs;
    mixed otmp;
    int *skills, i, sz;

    /* Added to stop the problems with decay. /Glindor */
    /* return; Removed by Rastlin */

    /* Only do this on the proper interval, and wizards pass by, of course */
    if (query_decay_time() < SKILL_DECAY_INTERVAL ||
	query_wiz_level())
	return;

    /* Reset the time for next call. */
    reset_decay_time();

    /* Get the list of trainer objects */
    obs = ({});
    otmp = this_object()->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    obs -= ({ 0 });

    /* Filter all relevant skills */
    skills = filter(query_all_skill_types(), &operator(>)(99999));

    loadall(obs, obs, skills);
}

/*
 * Function name: enter_game
 * Description:   Enter the player into the game
 * Arguments:	  pl_name: Name of the player
 * Security:
 *           This function must only be called from "/secure/login"
 */
public nomask int
enter_game(string pl_name)
{
    string      fname;
    string	*souls;
    int 	il, size;
    int		lost_money;
    object 	ob;

    if (MASTER_OB(previous_object()) != "/secure/login" &&
	MASTER_OB(previous_object()) != LOGIN_NEW_PLAYER)
    {
	write("Bad login object: " + file_name(previous_object()) + "\n");
	return 0;
    }

#ifdef RELAY_HOST
    real_host = previous_object()->query_relay();
#endif

    if (SECURITY->check_inherit("/std/player_sec", this_object()))
    {
	remove_object();
	return 0;
    }
    set_name(pl_name);

    fixup_screen();
    ::set_adj(({}));		/* No adjectives and no default */
    new_init();             	/* All variables to default condition */

    seteuid(0);
    if (!SECURITY->load_player())
    {
	return 0;
    }
    seteuid(query_wiz_level() ? pl_name : getuid(this_object()));
    set_adj(0);			/* Set the adjectives as loaded */

    add_name(query_race_name());
    if (query_wiz_level())
	add_name("wizard");

    /* Make some sanity things to guard against old and patched .o files
    */
    set_m_out(query_m_out());
    set_m_in(query_m_in());
    set_mm_out(query_mm_out());
    set_mm_in(query_mm_in());
    set_learn_pref(query_learn_pref(-1));

    /* People might have inconsistent acc_exp in guildstats, we must guard
       against it.
    */
    il = query_exp();
    this_object()->add_exp(1, 1);
    if (query_exp() < il)
    {
	il -= query_exp();
	this_object()->add_exp(il);
    }
    else
	this_object()->add_exp(-1, 1);

    set_login_time();
    set_login_from();

    set_living_name(pl_name);
    cmd_sec_reset();
    player_save_vars_reset();
    
    acc_exp_to_stats();   /* Setup our current stats */

    if (query_temp_start_location() &&
	SECURITY->check_temp_start_loc(query_temp_start_location()) >= 0)
    {
	catch(move_living(0, query_temp_start_location()));
	set_temp_start_location(0);
    }

    if (!environment(this_object()))
    {
	if (!query_default_start_location() ||
	    (!query_wiz_level() && SECURITY->
		check_def_start_loc(query_default_start_location()) < 0))
	    set_default_start_location(query_def_start());
	catch(move_living(0, query_default_start_location()));
    }

    /*
     * Let players start even if their start location is bad
     */
    if (!environment(this_object()) && !query_wiz_level())
	if (catch(move_living(0, query_def_start())))
	{
	    /*
	     * If this start location is corrupt too, then destruct the player
	     */
	    write("PANIC, your starting locations are corrupt!!\n");
	    destruct();
    	}

    /* Set some default properties */
    add_prop(PLAYER_I_MORE_LEN, 20);
    /* Restore the bits */
    unpack_bits();

    if ((query_wiz_level()) && (environment(this_object())))
	write("Starting in:" + file_name(environment(this_object())) + "\n");

    init_saved_props();

    /* Non wizards should not have a lot of command souls
     */
    if (!query_wiz_level())
    {
	souls = query_cmdsoul_list();
	if (sizeof(souls))
	{
	    il = -1;
	    size = sizeof(souls);
	    while(++il < size)
	    {
		remove_cmdsoul(souls[il]);
	    }
	}
    }

    if (!m_alias_list)
	m_alias_list = ([]);

    /* Start him up */
    if (query_autoshadow_list())
	load_auto_shadow(query_autoshadow_list());
    if (query_auto_load())
	load_auto_obj(query_auto_load());
    if (query_recover_list())
	if (load_recover_list(pl_name, query_recover_list()) == 0)
	    set_recover_list(({}));

    /* Set up skill decay now that the guild shadows are loaded
     * Do a first decay as well, making it a bit more frequent for
     * people who log on/off/on all the time
     */
    setup_skill_decay();
     
    /* Start him up 
     */
    this_object()->start_player();
    query_combat_object()->cb_configure();
    
    /* Non wizards should not have a lot of tool souls
     */
    if (!query_wiz_level())
    {
	souls = query_tool_list();
	if (sizeof(souls))
	{
	    il = -1;
	    size = sizeof(souls);
	    while(++il < size)
	    {
		this_object()->remove_toolsoul(souls[il]);
	    }
	}
    }

    if ((lost_money = query_tot_value()) > 0)
    {
	tell_object(this_object(), "You find " + lost_money +
			" coppers of your lost money.\n");
    	MONEY_ADD(this_object(), lost_money);
    }
    add_prop(PLAYER_I_LASTXP, query_exp());

    return 1;
}

/*
 * Function name: init_saved_props
 * Description  : Add the saved properties to the player.
 */
static void
init_saved_props()
{
    int index = -1;
    int size = ((sizeof(SAVE_PROPS) < sizeof(saved_props)) ?
	sizeof(SAVE_PROPS) : sizeof(saved_props));

    while(++index < size)
    {
	if (saved_props[index])
	{
	    add_prop(SAVE_PROPS[index], saved_props[index]);
	}
	else
	{
	    remove_prop(SAVE_PROPS[index]);
	}
    }

    saved_props = 0;
}

/*
 * Function name: open_player
 * Description  : This function may only be called by SECURITY or by the
 *                login object to reset the euid of this object.
 */
public nomask void
open_player()
{
    if ((previous_object() == find_object(SECURITY)) ||
	(MASTER_OB(previous_object()) == "/secure/login"))
	seteuid(0);
}

/*
 * Function name: fix_saveprops_list
 * Description  : Before the player is saved, this function is called to
 *                store several properties into an array that will be
 *                saved in the player file.
 */
nomask public int
fix_saveprop_list()
{
    int i, size;

    /* Fix the saved_props list before save */
    saved_props = ({ });
    i = -1;
    size = sizeof(SAVE_PROPS);
    while(++i < size)
    {
	saved_props += ({ query_prop(SAVE_PROPS[i]) });
    }
}

/*
 * Function name: save_player
 * Description  : This function actually saves the player object.
 * Arguments    : string pl_name - the name of the player
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
save_player(string pl_name)
{
    if (!pl_name)
	return 0;

    pack_bits();
    seteuid(getuid(this_object()));
    save_object(PLAYER_FILE(pl_name));
    seteuid(getuid(this_object()));

    /* Discard the props again */
    saved_props = 0;
    return 1;
}

/*
 * Function name: load_player
 * Description  : This function actually loads the player file into the
 *                player object.
 * Arguments    : string pl_name - the name of the player.
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
load_player(string pl_name)
{
    int ret;
   
    if (!pl_name)
	return 0;

    seteuid(getuid(this_object()));
    ret = restore_object(PLAYER_FILE(pl_name));
    seteuid(0);
    return ret;
}

/*
 * Function name: actual_linkdeath
 * Description  : This function is called when the player actually linkdies.
 *                If the player is in combat, this will be delayed, or else
 *                it is called directly.
 */
static nomask void
actual_linkdeath()
{
#ifdef OWN_STATUE
    OWN_STATUE->die(this_object());
#else   
    tell_room(environment(), LD_STATUE_TURN(this_object()), ({ }) );
#endif OWN_STATUE

    set_linkdead(1);
}

/*
 * Function name: linkdie
 * Description  : When a player linkdies, this function is called.
 */
nomask public void
linkdie()
{
    if (previous_object() != find_object(SECURITY))
    {
	return;
    }

    if (objectp(query_attack()))
    {
	tell_room(environment(), QCTNAME(this_object()) +
	    " looses touch with reality.\n", ({ this_object() }) );

	ld_alarm = set_alarm(LINKDEATH_TIME, 0.0, "actual_linkdeath");
    }
    else
    {
	actual_linkdeath();
    }
}

/*
 * Function name: revive
 * Description  : When a player revives from linkdeath, this function is
 *                called.
 */
nomask public void
revive()
{
    if (MASTER_OB(previous_object()) != LOGIN_OBJECT)
    {
	return;
    }

    if (!get_alarm(ld_alarm))
    {
	set_linkdead(0);

#ifdef OWN_STATUE
	OWN_STATUE->revive(this_object());
#else	
	tell_room(environment(), QCTNAME(this_object()) + " " +
	    STATUE_TURNS_ALIVE + ".\n", ({ this_object() }) );
#endif OWN_STATUE

	player_save_vars_reset();
	save_vars_reset();
    }
    else
    {
	tell_room(environment(), QCTNAME(this_object()) +
	    " gets in touch with reality again.\n", ({ this_object() }) );

	remove_alarm(ld_alarm);
	ld_alarm = 0;
    }
}

/*
 * Function name: load_auto_obj
 * Description  : Loads all autoloaded objects
 * Arguments    : string *load_arr - the array of objects to load.
 */
nomask static void
load_auto_obj(string *load_arr)
{
    string file, argument, *parts;
    object ob;
    int	   il, size;

    if (!load_arr || !sizeof(load_arr))
	return;

    il = -1;
    size = sizeof(load_arr);
    while(++il < size)
    {
	if (!stringp(load_arr[il]))
	{
	    write("Aotoload array element " + il + " corrupt.\n");
	    continue;
	}

	if (sscanf(load_arr[il], "%s:%s", file, argument) != 2)
	{
	    file = load_arr[il]; argument = 0;
	}
	if (!stringp(file))
	{
	    write("Auto load string corrupt: " + load_arr[il] + "\n");
	    continue;
	}
	if (LOAD_ERR(file))
	    continue;
	if (!objectp(find_object(file)))
	    continue;
	catch(ob = clone_object(file));
	if (argument)
	{
	    if (catch(ob->init_arg(argument)))
	    {
		ob->remove_object();
		continue;
	    }
	}
	ob->move(this_object());
    }
}

/*
 * Function name: load_recover_list
 * Description:   Loads all recoverable objects.
 * Arguments:	  pl_name - the player name,
 *		  recover_arr - The array of objects to recover
 */
nomask static int
load_recover_list(string pl_name, string *recover_arr)
{
    string          file,
                    argument,
                    *parts;
    object          ob;
    int		    il, size;

    if (!recover_arr || !sizeof(recover_arr))
	return 0;

    /* Do not restore after 2 hours */
    if (time() - file_time(PLAYER_FILE(pl_name) + ".o") > 7200)
	return 0;

    il = -1;
    size = sizeof(recover_arr);
    while(++il < size)
    {
	if (sscanf(recover_arr[il], "%s:%s", file, argument) != 2)
	{
	    file = recover_arr[il]; argument = 0;
	}
	if (!stringp(file))
	{
	    write("Recover string corrupt: " + recover_arr[il] + "\n");
	    continue;
	}
	if (LOAD_ERR(file))
	    continue;
	if (!objectp(find_object(file)))
	    continue;
	catch(ob = clone_object(file));
	if (argument)
	{
	    if (catch(ob->init_recover(argument)))
	    {
		ob->remove_object();
		continue;
	    }
	}
        write("You recover your " + ob->short() + ".\n");
	ob->move(this_object());
    }
}

/*
 * Function name: load_auto_shadow
 * Description  : Startup all the shadows that should shadow this player.
 * Arguments    : string *load_arr - the array of shadows to add.
 */
nomask static void
load_auto_shadow(string *load_arr)
{
    string file, argument;
    object ob;
    int	   il, size;

    if (!load_arr || !sizeof(load_arr))
	return;

    il = -1;
    size = sizeof(load_arr);
    while(++il < size)
    {
	if (sscanf(load_arr[il], "%s:%s", file, argument) != 2)
	{
	    write("Shadow load string corrupt: " + load_arr[il] + "\n");
	    continue;
	}
	if (LOAD_ERR(file))
	    continue;
	ob = find_object(file);
	if (!ob)
	    continue;
	ob = clone_object(file);
	if (argument)
	    ob->autoload_shadow(argument);
	else
	    ob->autoload_shadow(0);
    }
}

/*
 * Function name: new_save
 * Description:   Save this player as 'name'
 *                This is only called when new players
 *                enters the game. It makes it possible to initialize variables
 *                using the standard set_ calls.
 * Arguments:	  pl_name: Name of the player
 * Security:
 *           This function must only be called from "/secure/login" or
 *           from the object creating new players. Which inherits
 */
public nomask int
new_save(string pl_name, string pwd, string pfile)
{
    string          fname;

    if (!CALL_BY("/secure/login") &&
	!CALL_BY(LOGIN_NEW_PLAYER))
	return 0;

    write("Creating new player: " + pl_name + "\n");
    seteuid(getuid(this_object()));
    set_name(pl_name);
    set_password(pwd);
    set_player_file(pfile);
    new_init();			/* Initialize all variables on startup */

    save_object(PLAYER_FILE(pl_name));
    return 1;
}


/*
 * Function:     new_init
 * Description:  Initialises all variables to default conditions.
 */
static nomask void
new_init()
{
    int i, *ostat;

    ostat = query_orig_stat();

    i = -1;
    while(++i < SS_NO_EXP_STATS)
    {
	set_base_stat(i, ostat[i]);
    }

    stats_to_acc_exp();

    set_learn_pref(query_orig_learn());

#ifndef NO_ALIGN_TITLE
    set_al_title(query_new_al_title());
#endif NO_ALIGN_TITLE
}

/*
 * Function name: create_living
 * Description  : Called to create the player. It initializes some variables.
 */
public nomask void
create_living()
{
    player_save_vars_reset();
}

/*
 * Function name: reset_living
 * Description  : We don't want people to mask this function.
 */
public nomask void
reset_living()
{
    return;
}

/*
 * Function name:	command
 * Description:		Makes the player execute a command, If the player is a
 *			wizard then the object must have the same effective
 *			userid as the wizard being forced.
 * Arguments:		cmd: String containing the command
 * Returns:		eval_cost or '0' if unsuccessful
 */
public nomask int
command(string cmd)
{
    if (query_wiz_level() && previous_object())
    {
        if (!SECURITY->wiz_force_check(geteuid(previous_object()),
	    geteuid(this_object())))
	{
	    return 0;
	}
    }

    return ::command(cmd);
}

/*
 * Function name: id
 * Description  : Returns whether this object can be identified by a certain
 *                name. That isn't the case if the player hasn't met you
 *                while the real name is used.
 * Arguments    : string str - the name to test
 * Returns      : int 1/0 - true if the name is valid.
 */
public int
id(string str)
{
    if ((str == query_real_name()) && notmet_me(previous_object()))
    {
	return 0;
    }

    return ::id(str);
}

