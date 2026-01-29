/*
 * /d/Genesis/start/newbie/newbie_pin.c
 *
 * A pin for newbies and newbie helpers to wear.
 * Lucius, 05/2005
 * Configured by Tapakah, 01/06/2005
 * Changed so that wizards can listen to the line, Altrus, 10/12/2005
 * Do not use write() in remove(). Mercade, 21 April 2007
 * Re-coded f_break() and re-did check_restricted(). Lucius, 25 OCT 2007
 * Cleanup, Mercade, 13 December 2007
 * Set newbie level to wanderer, fixed "No Helpers" bug, Petros, March 2008
 * Removed wizard juniors from the list, Petros, March 2008
 * Use the PLAYER_I_NEWBIE_HELPER property for who list, Petros, March 2008
 * Update text to make it clearer to newbies, Petros, May 2009
 * 10/08/22 Lavellan Fixed a typo 
 * Grr.. Logs should cycle. Mercade, 28 March 2013.
 * Added <nrules> to clarify guidelines for useage. Gorboth, November 2013
 * Added <nhistory> to allow people to review the prior 10 messages. Petros, January 2015
 * The <nrules> command  was not visible for newbies, fixed now, Cherek, January 2017
 * Added functionality to <nignore> people on the line, Gorboth, April 2017
 * Added max message length, Cotillion, April 2017
 * Prevented <home> from working when in/fresh from combat, Shanoga, May 2019
 * <home> works in combat for players that are still in tutorial, Shanga, May 2019
 */
#pragma no_shadow
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <files.h>
#include <language.h>
#include <log.h>
#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "newbie.h"

#define TP      this_player()
#define TO      this_object()
#define ENV     environment

/* This is the delay for the recall ability. */
#define DELAY         5.0


#define NBAN_AGE        (86400 * 100) /* 100 days */ 
#define NTELL_MIN_AGE  (10 * 60)
#define NTELL_INTERVAL 15    /* Seconds between ntell */
#define NTELL_BURST     3    /* Token bucket size */ 
#define NTELL_LENGTH   (80 * 3) /* Max message length */
#define REPEAT_DELAY   60
#define REPEAT_LIMIT    4
#define NHISTORY_SIZE  20

int tokens = NTELL_BURST;
int token_update_time = time();

static private int alarm, newbie, removing;
string *texts = ({ });
string *history = ({ });
string *Ignored = ({ });

public mixed  query_ignored() { return Ignored; }

public string
long_description()
{
    if (SD_IS_NEWBIE(ENV()))
    {
	return "This is the official Genesis Newbie Pin.\n\n"+
	    "This pin will allow you to obtain help from those other "+
	    "players who have designated themselves as helpers. By "+
	    "wearing this pin, you will have a few exclusive commands "+
	    "available for your use. They are detailed below:\n\n"+
	    "  * nlist        - This command will list any newbie helpers that\n"+
	    "                   are awake and looking to help.\n"+
	    "  * ntell <text> - This command will allow you to speak with newbies\n"+
	    "                   and the other helpers.\n"+
	    "                      Example Usage: ntell please help!\n"+
	    "                   Note that all conversations are recorded so keep \n"+
	    "                   it appropriate.\n"+
            "  * nignore      - This command will block messages from someone\n"+
            "                   who you no longer wish to hear on the line.\n"+
            "  * nhistory     - This command allows you to review the most recent \n" +
            "                   conversation on the newbie line.\n"+
            "  * nrules       - Rules for the ntell line (important!)\n"+            
	    "  * home         - This command will allow you to return home should\n"+
	    "                   you find yourself completely lost. However, you \n"+
	    "                   will find yourself quite fatigued afterwards.\n"+
	    "                   If you move about, the magicks will not work.\n";
    }
    else
    {
	return "This is the official Genesis Newbie Helper Pin.\n\n"+
	    "This pin will allow you to more easily help those players "+
	    "which are new to Genesis and considered 'newbies'. By wearing "+
	    "this pin, you will have a few exclusive commands available "+
	    "for your use. They are detailed below:\n\n"+
	    "  * nlist        - This command will list any newbies that are awake\n"+
	    "                   and looking for your help.\n"+
	    "  * ntell <text> - This command will allow you to speak with newbies\n"+
	    "                   and the other helpers.\n"+
	    "                      Example Usage: ntell please help!\n"+
	    "                   Note that all conversations are recorded so keep \n"+
	    "                   it appropriate.\n"+
            "  * nignore      - This command will block messages from someone\n"+
            "                   who you no longer wish to hear on the line.\n"+
            "  * nhistory     - This command allows you to review the most recent \n" +
            "                   conversation on the newbie line.\n"+
            "  * nrules       - Rules for the ntell line (important!)\n"+
            "  * nban         - Ban a newbie from using the line. This command\n"+
            "                   is only available to helpers who are at least\n"+    
            "                   100 days old. Note: Only ban newbies in extreme\n"+
            "                   cases, for example those who take part in spamming,\n"+ 
            "                   harassment, and/or continuous violations of ntell\n"+   
            "                   rules.\n"+            
	    "  * break pin    - This command will break the pin.\n";
    }
}

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("pin");
    add_name(PIN_UNIQUE_ID);
    set_adj("newbie");
    set_short("newbie pin");
    set_long(long_description);

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    config_wearable_item(A_CHEST, 1, 99, this_object());
}

public void
remove_object(void)
{
    if (alarm)
	remove_alarm(alarm);

    ::remove_object();
}

public int
is_restricted(string name)
{
    if (file_size(RESTRICT) < 5)
        return 0;

    string *whom = explode(read_file(RESTRICT), "\n");
    string pattern = sprintf("^[%s%s]%s$", capitalize(name[0..0]), 
            name[0..0], name[1..]);

    if (!sizeof(regexp(whom, pattern)))
        return 0;

    return 1;
}

private int
check_restricted(void)
{
#ifdef RESTRICT
    if (removing)
	return 1;

    if (!is_restricted(ENV()->query_real_name()))
        return 0;

    /*
    ENV()->catch_tell("\nThe Genesis Administration has deemed "+
	"you no longer worthy of holding the "+ short() +". It disappears "+
	"in a puff of smoke.\n\n");

    set_alarm(0.0, 0.0, remove_object);
    removing = 1;
    */
    return 1;
#else
    return 0;
#endif
}

private int
check_newbie(void)
{
    if (!newbie)
	return 0;

    if (SD_IS_NEWBIE(ENV()))
	return 0;

    if (ENV()->query_prop(PLAYER_I_NEWBIE_HELPER))
        return 0;
    
    ENV()->catch_tell(
	"\nYou have grown enough to no longer be considered "+
	"a newbie. As such, your "+ short() +" shall be removed. "+
	"We invite you to continue on as a newbie helper.\n\n");
    
    set_alarm(1.0, 0.0, remove_object);
    return 1;
}

public mixed
wear(object ob)
{
    if (check_restricted())
	return "";

    if (newbie)
    {
	write("By wearing the pin, you advertise your desire "+
	    "to be helped by others.\n");
    }
    else
    {
	write("By wearing the pin, you advertise your willingness "+
	    "to help out others.\n");
	TP->add_prop(PLAYER_I_NEWBIE_HELPER, 1);
    }

    return 0;
}

public mixed
remove(object ob)
{
    object player = query_worn();

    if (check_restricted())
	return "";

    if (!player)
        return 0;

    /* During remove() never use write as this_player() isn't known. */
    if (newbie)
    {
	player->catch_tell("By removing the pin, you no longer advertise "+
	    "needing help.\n");
    }
    else
    {
	player->catch_tell("By removing the pin, you no longer advertise "+
	    "your presence for those seeking help.\n");
	TP->remove_prop(PLAYER_I_NEWBIE_HELPER);
    }

    return 0;
}

public string
query_recover(void)
{
    return (string)0;
}

public string
query_auto_load(void)
{
    if (check_newbie() || check_restricted())
	return "";

    return MASTER + ":";
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


/*
 * Function name:        ignoring_me
 * Description  :        check to see if a player has chosen to ignore
 *                       me on the ntell line (presumably because I am being
 *                       an idiot and deserve to be ignored.)
 * Arguments    :        object who - the potential hearer of our ntell
 * Returns      :        int 1 - won't hear my ntell, 
 *                           0 - will hear my ntell
 */
public int
ignoring_me(object who)
{
    mixed   listener_pin = present(PIN_UNIQUE_ID, who);
    object  message_sender = environment(this_object());
    string *ignored_by_recipient = listener_pin->query_ignored();


    if (!listener_pin                 ||
        !interactive(message_sender)  ||
        IN_ARRAY(message_sender->query_real_name(),
                     ignored_by_recipient))
    {
        return 1; /* will not be heard by this recipient */
    }
    else
    {
        return 0; /* will be heard by this recipient */
    }
} /* ignoring_me */
        

private int
check_available(object who)
{
    if (objectp(present(PIN_UNIQUE_ID, who)->query_worn()) &&
        !ignoring_me(who))
    {
	return 1;
    }
    else
    {
	return 0;
    }
}

private int
check_available_list(object who)
{
	string name;
	if (objectp(present(PIN_UNIQUE_ID, who)->query_worn()))
	{
		name = who->query_name();
		return !who->query_wiz_level() && !wildmatch("*jr", name);
	}
	else
		return 0;
}


private int
check_ignored(object who)
{
    return IN_ARRAY(who->query_real_name(), Ignored);
}


/*
 * Nlist: This allows newbies to get a list of awake and active helpers
 *        and for helpers to get a list of awake and seeking newbies.
 *        There is not cost for using this feature.
 */
public int
f_nlist(string str)
{
    object *newbies, *helpers, *are_ignored;

    if (!objectp(wearer))
	return 0;

    if (strlen(str))
	return notify_fail("There is no argument to nlist.\n");

    newbies = filter(users() - ({ TP }), check_available_list);
    are_ignored = filter(newbies, check_ignored);
    newbies -= are_ignored;
    helpers = filter(newbies, &operator(<)(SD_AV_NEWBIE) @ &->query_average_stat());
    newbies -= helpers;

    write(" --- " + (newbie ? "Newbie" : "Fellow") + " Helpers:\n\n");
    if (sizeof(helpers))
    {
        write(sprintf("%-#75s\n\n", implode(map(helpers, &operator(+)(, "+") @ &->query_name()), "\n")));
    }
    else
    {
        write("None right now.\n\n");
    }

    write(" --- " + (newbie ? "Fellow" : "Active") + " Newbies:\n\n");
    if (sizeof(newbies))
    {
	write(sprintf("%-#75s\n\n", implode(map(newbies, &->query_name()), "\n")));
    }
    else
    {
        write("None right now.\n\n");
    }

    if (sizeof(are_ignored))
    {
        write(" --- Ignored Currently:\n\n");
        write(sprintf("%-#75s\n\n", implode(map(are_ignored, &->query_name()), "\n")));
    }

    return 1;
}

int
check_rate_limit()
{
   int interval = (time() - token_update_time) / NTELL_INTERVAL;

   if (interval > 0)
   {
	tokens = min(tokens + interval, NTELL_BURST);
	token_update_time += interval * NTELL_INTERVAL;
   }

   if (tokens > 0)
   {
   	tokens--;
	return 1; 
   }
   return 0;
}

/*
 * Ntell:  This allows newbies and helpers to speak to each other.
 *         All communications are logged and there is no cost to use.
 */
public int
f_ntell(string str)
{
    object *whom;
    string text;
    
    if (!objectp(wearer))
	return 0;

    if (!strlen(str))
	return notify_fail("What are you trying to say?\n");

    if ((this_player()->query_age() * 2) < NTELL_MIN_AGE)
        return notify_fail("You are too new to the game to ask questions. Explore a bit first.\n");

    if (strlen(str) > NTELL_LENGTH)
        return notify_fail("You can't say that much at once!\n");

    if (sizeof(whom = filter(users(), check_available)) <= 1)
    {
	write("There is nobody to hear your message.\n");
	return 1;
    }

    if (!check_rate_limit())
    {
	write("You are talking too fast, calm down.\n");
	return 1;
    }

    /* No spamming. */
    if (IN_ARRAY(str, texts) && !this_player()->query_wiz_level())
    {
	write("No point in repeating yourself, is there?\n");
	return 1;
    }
    texts += ({ str });
    texts = texts[..REPEAT_LIMIT];

    string separator = ": ";
    if (!SD_IS_NEWBIE(TP))
    {
        separator = "(+): ";
    }

    text = "<Newbie> " + capitalize(TP->query_real_name()) + separator + str;


    /* Pretend everything is OK for banned players */
    if (check_restricted()) {
        this_player()->catch_tell(text + "\n");
        return 1;
    }

    whom->catch_tell(text + "\n");

    // Get all the newbie pins so that we can write to it.
    object * listening_pins = map(whom, &present(PIN_UNIQUE_ID,));
    listening_pins->add_message_to_history(text);
    whom->gmcp_comms("newbie", capitalize(TP->query_real_name()), text);

#ifdef LOG_NTELL
    log_file(LOG_NTELL, sprintf("%s %-11s: %s\n", ctime(time()),
	    capitalize(TP->query_real_name()), str), LOG_SIZE_1M);
#endif

    return 1;
}

/*
 * This is stage 2 of recall. It does the actual movement
 * and drains the players fatigue. All successful recalls
 * are also logged.
 */
private void
do_recall(object who, string where, object last)
{
    alarm = 0;

    if (!TP->query_relaxed_from_combat() || TP->query_attack())
    {
        if (!environment(TP)->query_prop("_room_i_tutorial"))
        {
        notify_fail("You have too recently been in combat. You have to " +
            "relax before the magicks can take you home.\n");
        return 0;
        }
    }

    if (!objectp(who))
	return;

    if (last != ENV(who))
    {
	TP->catch_tell("Your movement has caused the magicks to "+
	    "cease and you fail to be returned home.\n");
	return;
    }

    TP->move_living("shimmering then fading away", where, 1, 0);
    TP->add_fatigue(-(TP->query_max_fatigue()));

    TP->catch_tell("\nThe magicks leave you feeling extremely fatigued. "+
	"It would be a good idea to find something to eat and drink when "+
	"you've recovered some.\n\n");

#ifdef LOG_RECALL
    log_file(LOG_RECALL,
	sprintf("%s: %-11s recalled from %s\n\t to %s\n", ctime(time()),
	    capitalize(TP->query_real_name()),
	    file_name(last), where));
#endif
}

/*
 * Recall:  Send a newbie to their start position.
 *          This ability will wipe their fatigue as it
 *          should be used only when hopelessly lost and
 *          they can't get help via other means.
 */
public int
f_home(string str)
{
    if (TP->query_wiz_level())
        return 0;
   
    if (check_restricted())
	return 1;

    if (!objectp(wearer))
	return 0;

    if (!newbie)
	return 0;

    if (!TP->query_relaxed_from_combat() || TP->query_attack())
    {
        if (!environment(TP)->query_prop("_room_i_tutorial"))
        {
        notify_fail("You have too recently been in combat. You have to " +
            "relax before the magicks can take you home.\n");
        return 0;
        }
    }

    if (strlen(str))
    {
	notify_fail("You don't need to have an argument to go home.\n");
	return 0;
    }

    if (alarm)
    {
	write("You are already preparing to go home.\n");
	return 1;
    }

    str = TP->query_default_start_location();
    if (str == file_name(ENV(TP)))
    {
	write("You are already at your starting location!\n");
	return 1;
    }

    write("You feel yourself beginning to fade... "+
	"remember to hold still or the magick will go awry.\n");

    alarm = set_alarm(DELAY, 0.0, &do_recall(TP, str, ENV(TP)));
    return 1;
}

private int
delete_helper(string entry)
{
    mapping helper = restore_map(HELPER_FILE);

    if (helper[entry])
    {
	write("You are not on the list anymore. What a pity!\n");
	m_delkey(helper, entry);
	setuid();
	seteuid(getuid());  
	save_map(helper, HELPER_FILE);
	log_file(HELPER_LOG, ctime(time()) + " " + entry + " unlisted.\n");

	return 1;
    }

    write("You are not on the list!\n");
    return 1;
}

public int
f_break(string str)
{
    if (str != "pin")
    {
	notify_fail("Break what, the pin?\n");
	return 0;
    }

    write("The pin breaks into small pieces.\n");
    delete_helper(TP->query_name());
    remove_object();
    return 1;
}

/* 
 * Function:    notify_newbie_helpers
 * Description: Function that gets called whenever someone with the newbie
 *              pin enters the realms. It will notify all the helpers about
 *              newbies that are now available.
 */
public void
notify_newbie_helpers(object player)
{
    if (!objectp(player))
    {
        return;
    }
    string name = player->query_real_name();
    if (!SD_IS_NEWBIE(player) 
        || player->query_wiz_level()
        || wildmatch("*jr", name))
    {
        // No notifications if the person is not a newbie, is a wizard,
        // or a junior.
        return;
    }
    
    object * helpers = filter(users() - ({ player }), check_available);
    helpers = filter(helpers, &operator(<)(SD_AV_NEWBIE) @ &->query_average_stat());
    if (sizeof(helpers))
    {
        helpers->catch_tell(sprintf("<Newbie> Your newbie pin buzzes and "
            + "alerts you that the newbie %s is now awake.\n",
            capitalize(player->query_real_name())));
    }
     
    return;
}

public int
f_nrules(string arg)
{
    this_player()->more(read_file("/d/Genesis/start/newbie/ntell_rules.txt"));
    return 1;
}

public int
f_nhistory(string arg) 
{
    if (sizeof(history) == 0)
    {
        write("You have no history of any conversation on the newbie line.\n");
        return 1;
    }
    write("Here are the recent messages on the newbie line:\n");
    foreach (string message : history)
    {
        this_player()->catch_tell(message + "\n");
    }
    write("\n");
    return 1;
}

public void
add_message_to_history(string message)
{
    history += ({ message });
    if (sizeof(history) > NHISTORY_SIZE)
    {
        history = history[(sizeof(history) - NHISTORY_SIZE)..];
    }
}


/*
 * Function name:        f_nignore
 * Description  :        Allow players to ignore people on the ntell
 *                       line who they no longer wish to hear
 * Arguments    :        string arg - what they player typed
 * Returns      :        1 - successfully ignored someone
 *                       0 - failed
 */
public int
f_nignore(string arg)
{
    object  *newbies;
    int      player_available = 0;

    if (!strlen(arg))
    {
        notify_fail("Useage: <ignore [name]> to toggle on/off ignore status.\n");
        return 0;
    }

    if (IN_ARRAY(lower_case(arg), Ignored))
    {
        Ignored -= ({ arg });

        write("You are no longer ignoring " + capitalize(arg) + ".\n");
        return 1;
    }

    newbies = filter(users() - ({ TP }), check_available_list);

    foreach(object newbie: newbies)
    {
        player_available += (lower_case(arg) == newbie->query_real_name());
    }

    if (player_available)
    {
        write("You are now ignoring " + capitalize(arg) + ". You may choose"
          + " to toggle back to hearing that person on the line again by"
          + " again using the <nignore> command with their name.\n");
        Ignored += ({ arg });

        return 1;
    }

    notify_fail("That is not the name of anyone currently using the ntell"
      + " line. You can only ignore players who are present and wearing"
      + " their pin.\n");
    return 0;
} /* f_nignore */


int
can_nban(object player)
{
    if (player->query_wiz_level())
        return 1;

    if (player->query_age() * 2 > NBAN_AGE)
        return 1;

    return 0; 
}

/*
 * Function name: n_ban
 * Description  : Ban someone from the newbie line
 * Arguments    : string name - The player
 */
public int
f_nban(string name)
{
    if (!can_nban(this_player()))
        return 0;

    notify_fail("Usage: nban <name>.\n");
    if (!strlen(name))
        return 0;

    name = lower_case(name);

    if (!this_player()->query_wiz_level()) 
    {
        object player = find_player(name);
    
        if (!objectp(player) || !SD_IS_NEWBIE(player))
        {
            notify_fail("You can only ban newbies who are online.\n");
            return 0;
        }       
    }

    if (is_restricted(name))
    {
        notify_fail(capitalize(name) + " has already been banned.\n");
        return 0;
    }

    if (!SECURITY->exist_player(name))
    {
        notify_fail("There is no such player.\n");
        return 0;
    }

    write_file(RESTRICT, sprintf("# Added by %s on %s\n%s\n", 
        capitalize(this_player()->query_real_name()), 
        ctime(time()),
        capitalize(name)));

    write("You banned " + capitalize(name) + " from using the newbie line.\n");
    return 1;
}


public void
init()
{
    ::init();

    /* Only works when we carry this pin. */
    if (TP != ENV())
	return;

    if (check_restricted())
	return;

    add_action( f_nlist,    "nlist"    );
    add_action( f_ntell,    "ntell"    );
    add_action( f_nrules,   "nrules"   );
    add_action( f_nhistory, "nhistory" );
    add_action( f_nignore,  "nignore"  );
    add_action( f_nban,     "nban"     );
 
    if (SD_IS_NEWBIE(TP))
    {
	newbie = 1;
	set_alarm(1.0, 0.0, wear_me);
        add_action( f_home,  "home"  );
    
        /* Notification of newbie logins has been removed as 
         * it provides no values at all. Newbie helpers are not
         * supposed to just randomly chat with newbies anyway. */ 
        // set_alarm(1.0, 0.0, &notify_newbie_helpers(TP));
    }
    else
    {
	add_adj("helper");
	set_short("newbie helper pin");
        add_action( f_break, "break" );
    }    
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    /* There can be only one. */
    if (sizeof(filter(all_inventory(dest), &->id(PIN_UNIQUE_ID))) > 1)
    {
        set_alarm(0.1,0.0, remove_object);
        return;
    }
}

void
log_me(string helper, string action)
{
    log_file(HELPER_LOG, ctime(time()) + " " + helper + " " + action + "\n");
}
