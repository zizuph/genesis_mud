/*
 * /d/Genesis/login/ghost_player
 *
 * This player file is used when a player logging in does not have a valid
 * player file.
 *
 *    There can be three different reasons for not having a player_file:
 *
 *       1 - If this is a new character, then manage the creation process.
 *
 *       2 - The players racefile is not loadable, a new body must be
 *           choosen.
 *
 *       3 - The players racefile is not a legal playerfile, a new body
 *           must be choosen.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/player_pub";

#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include "login.h"

#define DEATH_BADGE "death_badge"

static private int	time_out_alarm;	/* The id of the alarm */
static private string	rhost;		/* The real host */

/*
 * This is for skill preparation
 */
int skill_coins;

/*
 * Prototypes
 */
public void ghost_start();
void next_query();
void ask_player();
static void check_identity1(string id);

/*
 * Function name: time_out
 * Description  : Remove this object if it has been idle too long.
 */
void
time_out()
{
    write("Time out\n");
    remove_object();
}

/*
 * Function name:   legal_player
 * Description:     This is called from the master object to check that
 *                  a specific player object is legal. This is used to
 *		    decide if restore_object / save_object in /players
 *		    is possible.
 * Arguments:       ob: The object to check
 * Returns:         True for legal player object
 */
nomask public int
legal_player(object ob)
{
    string m;
    mapping r;

    m =  MASTER_OB(ob);

    if (m == MASTER)
	return 1;

    r = RACEMAP;
    if (member_array(m, m_values(r)) >= 0)
	return 1;

    return 0;
}

/*
 * Function name:  enter_new_player
 * Description:    This is the function called from the login object.
 *                 It is responsible for initialising the correct actions
 *		   to be performed.
 */
public nomask void
enter_new_player(string name, string pass)
{
    if (!interactive(this_object()))
    {
	write("I'm linkdead, bye bye!\n");
	remove_object();
	return;
    }

    /*
     * Prevent intrusion into more privileged players
     */
    if (!previous_object() ||
    	(MASTER_OB(previous_object()) != "/secure/login"
	&& MASTER_OB(previous_object()) != MASTER))
    {
	log_file("SECURITY", "enter_new_player() called from " +
	    file_name(previous_object()) + "\n");
	remove_object();
	return;
    }

    set_name(name);
    seteuid(0);

    rhost = query_ip_name(this_object());

    /*
     * Check if the player exist
     */
    if (!SECURITY->load_player())
    {
	seteuid(getuid(this_object()));
	set_player_file(MASTER);

	/* This can never be a valid password, so we use this to trigger
	 * internal call.
	 */
	if (pass != "")
	{
	    set_password(pass);
	}

	/*
         * name'jr' is a wizard helper if it is not an old player
         */
	if (wildmatch("*jr", name))
	{
	    write("\nOk, you say you're a wizard. Let's see if it's true.\n" +
		  "And do remember: Max two helpers per wizard!\n");
	    write("\nInput your wizard name: ");
	    input_to(check_identity1, 0);
            time_out_alarm = set_alarm(1200.0, 0.0, time_out);
	    return;
	}

#ifdef Genesis
	/*
         * Is the mud open to new players ?
         */
	if (file_size(LOGIN_NO_NEW) > 0)   
	{
	    cat(LOGIN_NO_NEW);
	    log_file("REFUSED_ENTRY", ctime(time()) + ": " + name + "\n");
	    remove_object();
	    return;
	}
#endif	

	write("Creating a new player.\n");
	log_file("CREATE_PLAYER", ctime(time()) + " " + query_name() +
	    " (" + query_ip_name(this_object()) + ")\n", -1);
	set_ghost(GP_NEW);
	cat(LOGIN_FILE_NEW_PLAYER_INFO);

	ask_player();  /* Some questions are still needed */
	return;
    }
    seteuid(getuid(this_object()));

    /*
     * Is this a normal CDlib player with a bad playerfile ?
     */
    if (query_player_file() != MASTER)
    {
	set_ghost(GP_BODY | GP_DEAD);
	set_player_file(MASTER);
	write("You have a bad body and will have to choose a new.\n");
    }
    ghost_start();
}

/*
 * Get the password of the old wizard.
 */
static void
check_identity2(string p, string id)
{
    object wiz;

    write("\n");
    remove_alarm(time_out_alarm);

    if (!objectp(wiz = find_player(id)))
    {
	wiz = SECURITY->finger_player(id);
    }

    if (!(wiz->match_password(p)))
    {
	if (wiz->query_finger_player())
	{
	    wiz->remove_object();
	}

	write("Wrong password!\n");
	remove_object();
	return;
    }
    log_file("HELPER", ctime(time()) + ": " +
	capitalize((wiz->query_real_name())) + " -> " +
	query_name() + "\n", -1);

    write("Copying your wizards email address.\n");
    set_mailaddr(wiz->query_mailaddr());
    if (wiz->query_finger_player())
    {
	wiz->remove_object();
    }

    set_ghost(GP_NEW);
    ghost_start();
}

/*
 * Get the name of the old wizard and check out the identity.
 */
static void
check_identity1(string id)
{
    remove_alarm(time_out_alarm);

    if (!strlen(id))
    {
	write("No name entered.\n");
	remove_object();
	return;
    }

    if (!(SECURITY->query_wiz_rank(id)))
    {
	write(capitalize(id) + " is not a wizard.\n");
	remove_object();
	return;
    }

    write("Input your wizard password: ");
    input_to(&check_identity2(, id), 1);
    time_out_alarm = set_alarm(1200.0, 0.0, time_out);
    return;
}

/*****************************************************************
 *
 * The questions to ask an entirely new player, which is not handled
 * in the configuration process.
 *
     Ask for email adress

 */
static string   *new_queries;

/*
 * Function name: ask_player
 * Description:   Ask some questions of new players
 */
static void
ask_player()
{
    new_queries = ({ "dummy", "q_mail" });
    next_query();
    return;
}

/*
 * Function name: end_query
 * Description:   
 * Return:        
 */
static void
end_query()
{
    ghost_start();
}

/*
 * Function name: next_query
 * Description:   Asks the next question of the user interactively.
 */
void
next_query()
{
    remove_alarm(time_out_alarm);
    while (1)
    {
	if (sizeof(new_queries) < 2)
	    return end_query();	/* does not return */
	new_queries = slice_array(new_queries, 1, sizeof(new_queries));
	if (call_other(this_object(), new_queries[0] + "_pretext"))
	{
            time_out_alarm = set_alarm(1200.0, 0.0, time_out);
	    input_to(new_queries[0]);
	    return;
	}
    }
}

/*
 * Function name: again_query
 * Description:   Asks the same question again.
 */
static void
again_query()
{
    if (call_other(this_object(), new_queries[0] + "_pretext"))
    {
	input_to(new_queries[0]);
	return;
    }
    next_query();
}


int
q_mail_pretext()
{
    /*
     * Do not ask if there is already an email
     */
    if (query_mailaddr())
	return 0;
    write("Please enter your email address (or 'none'): ");
    return 1;
}

/*
 * Function:    q_mail
 * Description: This function is called using input_to, and sets the
 *              email adress of this player.
 */
static void
q_mail(string maddr)
{
    set_mailaddr(maddr);
    next_query();
}

/*
 * Here we start the actual configuration routine
 */
public void
ghost_start()
{	
    remove_alarm(time_out_alarm);
    if (!query_race_name())
    {
	set_race_name("newbie");
	save_me(0); /* Only needed if you are a firstimer isn't it? */
    }
    if (this_player() != this_object())
	set_this_player(this_object());

    /*
	We now have a correct .o file
    */
    write("\nEntering the hall of the bodies in waiting...\n\n");
    enter_game(query_real_name(), "");
}

void
start_player()
{
    if (!sizeof(this_object()->query_cmdsoul_list()))
    {
	this_object()->add_cmdsoul("/d/Genesis/cmd/soul_cmd_ghost");
	this_object()->add_cmdsoul("/d/Genesis/cmd/misc_cmd_ghost");
    }
    ::start_player();
}

public string
query_default_start_location()
{
    if (query_ghost() & GP_BODY)
	return "/d/Genesis/login/bodies";
    else if (query_ghost() & GP_MANGLE)
	return "/d/Genesis/login/mangle";
    else if (query_ghost() & GP_FEATURES)
	return "/d/Genesis/login/features";
    else if (query_ghost() & GP_SKILLS)
	return "/d/Genesis/login/skills";
    else if (query_ghost() == 0)
	return RACESTART[this_object()->query_race_name()];
    /*
     * Should not happen
     */
    return "/d/Genesis/login/bodies";
}

/*
 * Function name: stats_to_acc_exp
 * Description:   Translates the current base stats into acc_exp. This is used
 *                used when getting stats from a body.
 */
public nomask void
stats_to_acc_exp()
{
    ::stats_to_acc_exp();
}

public void
set_exp(int e)
{
    ::set_exp(e);
}

public void
set_exp_combat(int e)
{
    ::set_exp_combat(e);
}

public void
update_acc_exp()
{
    ::update_acc_exp();
}

/*
 * Function name: damn_stubborn_object
 * Description  : This function is apparently needed to get rid of objects
 *                that refuse to destruct the first time.
 */
void
damn_stubborn_object()
{
    set_alarm(1.0, 0.0, damn_stubborn_object);
    destruct();
}    

/*
 * Now the configuration is ready, and we want to swap to the correct
 * playerfile. 
 */
public int
ghost_ready()
{
    string plfile;
    object ob, badge;
    int wizlev;

    if (query_ghost())
    {
	write("You still have things to do before entering the world.\n");
	return 0;
    }
    plfile = RACEMAP[query_race_name()];
    if (!plfile)
    {
	write("You cannot be a " + query_race_name() + 
	      ", choose a new body!\n");
	set_ghost(GP_BODY | GP_DEAD);
	enter_new_player(query_real_name(), "");
	return 0;
    }

    ob = clone_object(plfile);
    if (!ob)
    {
	write(capitalize(query_race_name()) + 
	      " is a faulty race. Choose a new body!\n");
	set_ghost(GP_BODY | GP_DEAD);
	enter_new_player(query_real_name(), "");
	return 0;
    }	
    
    /* 
     * Prepare the new player object. We must change:
     *      We should have the correct souls.
     *      We should have the correct playerfile.
     */
    exec(ob, this_object());
    if (badge = present(DEATH_BADGE, this_object()))
	badge->move(ob, 1);

    set_player_file(plfile);
    this_object()->transmsg_reset();
    set_default_start_location(RACESTART[this_object()->query_race_name()]);
    save_me(0);

    /*
     * Add a property to show that the player has just been created. 
     */
    ob->add_prop("just_created", 1); 

    /*
     * Enter the game and load the save file
     */
    if (!ob->enter_game(query_real_name(), ""))
    {
	write(capitalize(query_race_name()) + 
	      " is an illegal race. Choose a new body!\n");
	set_ghost(GP_BODY | GP_DEAD);
	enter_new_player(query_real_name(), "");
	return 0;
    }

    ob->update_hooks();
    ob->save_me(0);

    /* Notify security of the fact that a new player enters the game.
     * Let the wizards know a new player logged in.
     */
    SECURITY->notify(ob, 0);

    /*
     * Now if we hammer hard enough it probably goes away
     */
    set_alarm(1.0, 0.0, damn_stubborn_object);
    remove_object();
    destruct();
}

/*
 * Function name: 
 * Description:   Called by a player object that is a ghost and needs to
 *		  be reincarnated.
 */
public void
reincarnate_me()
{
    object pl, gh, n, p, ob;

    pl = previous_object();
    if (!interactive(pl) || !pl->query_ghost())
	return;
    pl->set_ghost(GP_BODY | GP_DEAD);
    pl->set_temp_start_location(0);
    pl->save_me(0);

    /* This makes the real hostname carry on to the new player object
    */
    rhost = query_ip_name(pl);

  /* Without this uid/euid setting, this file does not have permission */
  /* to clone a copy of itself */
    setuid();
    seteuid(getuid());

    gh = clone_object(MASTER);
    exec(gh, pl);
    if (ob = present(DEATH_BADGE, pl))
	ob->move(gh, 1);

    gh->set_bit_array(pl->query_bit_array());
    n = pl->query_real_name();
    SECURITY->do_debug("destroy", pl);
    gh->enter_new_player(n);
}

public string
query_race()
{
    return "ghost";
}

/*
 * Set and query the skill coins
 *
 */
public void
set_skill_coins(int c)
{
    skill_coins = c;
}

public int
query_skill_coins()
{
    return skill_coins;
}
