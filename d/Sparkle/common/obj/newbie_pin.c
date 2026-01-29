/*
 * /d/Genesis/start/newbie/newbie_pin.c
 *
 * A pin for newbies and newbie helpers to wear.
 * Lucius, 05/2005
 * Configured by Tapakah, 01/06/2005
 */
#pragma no_shadow
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#define TP  this_player()

/* A unique name for the pin. */
#define UNIQUE        "Genesis::newbie::pin"
/* A property for the helper */
#define LIVE_I_NEWBIE_HELPER "_live_i_newbie_helper"
/* The cutoff stat average for what is a newbie */
#define STAT_LIMIT    30
/* Convience macro to differentiate between newbie and helper. */
#define IS_NEWBIE(x)  ((x)->query_average_stat() < STAT_LIMIT)
/* This is the delay for the recall ability. */
#define DELAY         5.0
/* Our logged abilities go here: */
#define LOG_NTELL     "/d/Genesis/log/NEWBIE_TELL"
#define LOG_RECALL    "/d/Genesis/log/NEWBIE_RECALL"

/* Check this for restricted usage. */
#undef RESTRICT    ("/d/Genesis/log/NEWBIE_RESTRICTED")

#define POSTER        "/d/Genesis/start/newbie/poster"
#define HELPER_FILE "/d/Genesis/start/newbie/helpers"
#define HELPER_LOG  "/d/Genesis/log/NEWBIE_HELPER"

static private int alarm, newbie;

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("pin");
    add_name(UNIQUE);
    set_adj("newbie");
    set_short("newbie pin");
    set_long("You should not be seeing this.\n");

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

public varargs string
long(string str, object fobj)
{
    if (strlen(str))
	return ::long(str, fobj);

    if (IS_NEWBIE(environment()))
    {
	str = "This is the official Genesis Newbie Pin.\n\n"+
	    "This pin will allow you to obtain help from those other "+
	    "players who have designated themselves as helpers. By "+
	    "wearing this pin, you will have a few exclusive commands "+
	    "available for your use. They are detailed below:\n\n"+
	    "  * nlist  - This command will list any newbie helpers that\n"+
	    "             are awake and looking to help.\n"+
	    "  * ntell  - This command will allow you to speak with other\n"+
	    "             newbies and the newbie helpers. All conversations\n"+
	    "             are logged so keep it appropriate.\n"+
	    "  * home   - This command will allow you to return home should\n"+
	    "             you find yourself completely lost. However, you \n"+
	    "             will find yourself quite fatigued after and if\n"+
	    "             you move about, the magic won't work.\n";
    }
    else
    {
	str = "This is the official Genesis Newbie Helper Pin.\n\n"+
	    "This pin will allow you to more easily help those players "+
	    "which are new to Genesis and considered 'newbies'. By wearing "+
	    "this pin, you will have a few exclusive commands available "+
	    "for your use. They are detailed below:\n\n"+
	    "  * nlist  - This command will list any newbies that are awake\n"+
	    "             and looking for your help.\n"+
	    "  * ntell  - This command will allow you to speak with newbies\n"+
	    "             and the other newbie helpers. All conversations\n"+
	    "             are logged so keep it appropriate.\n"+
	    "  * break  - This command will break the pin.\n";
    }

    return str;
}

private int
check_restricted(void)
{
#ifdef RESTRICT
    if (!RESTRICT->query_restricted(environment()->query_real_name()))
	return 0;

    environment()->catch_tell("\nThe Genesis Administration has deemed "+
	"you no longer worthy of holding the "+ short() +" and it soon "+
	"disappears in a puff of smoke.\n\n");

    set_alarm(1.0, 0.0, remove_object);
    return 1;
#endif
}

private int
check_newbie(void)
{
    if (!newbie)
	return 0;

    if (IS_NEWBIE(environment()))
	return 0;

    if (environment()->query_prop(LIVE_I_NEWBIE_HELPER))
        return 0;
    
    environment()->catch_tell(
	"\nYou have grown enough to no longer be considered "+
	"a newbie. As such, your "+ short() +" shall be removed "+
	"and we invite you to continue on as a newbie helper.\n\n");
    
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
	write("By wearing the pin, you advertise your request "+
	    "for help to others.\n");
    }
    else
    {
	write("By wearing the pin, you advertise your willinging "+
	    "to help out others.\n");
    }

    return 0;
}

public mixed
remove()
{
    if (check_restricted())
	return "";

    if (newbie)
    {
	write("By removing the pin, you no longer advertise "+
	    "needing help.\n");
    }
    else
    {
	write("By removing the pin, you no longer advertise "+
	    "your presence for those seeking help.\n");
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

private int
check_available(object who)
{
    if (objectp(present(UNIQUE, who)->query_worn()))
	return !who->query_wiz_level();
    else
	return 0;
}

void
log_me(string helper, string action)
{
  write_file(HELPER_LOG,ctime(time()) + " " + helper + " " + action + "\n");
}

mapping
read_helperfile()
{
  return restore_map(HELPER_FILE);
}

void
write_helperfile(mapping helper)
{
  save_map(helper,HELPER_FILE);
}
int
delete_helper(string entry)
{
  mapping helper;
  
  helper = read_helperfile();
  if(helper[entry]) {
    helper = m_delete(helper,entry);
    write_helperfile(helper);
    write("You are not on the list anymore. What a pity!\n");
    log_me(entry, "unlisted");
  }
  else 
    write("You are not on the list!\n");
  return 1;

}
/*
 * Nlist: This allows newbies to get a list of awake and active helpers
 *        and for helpers to get a list of awake and seeking newbies.
 *        There is not cost for using this feature.
 */
public int
f_nlist(string str)
{
    int ix, size;
    object *newb, *help;

    if (check_restricted())
	return 0;

    if (!objectp(wearer))
	return 0;

    if (strlen(str))
	return notify_fail("There is no argument to nlist.\n");

    newb = filter(users() - ({ TP }), check_available);

    if (!(size = sizeof(newb)))
    {
	if (newbie)
	{
	    write("Sadly, there are no helpers awake to assist you.\n");
	    return 1;
	}
	else
	{
	    write("There aren't any newbies seeking help at the moment.\n");
	    return 1;
	}
    }

    help = filter(newb, &operator(<)(STAT_LIMIT) @ &->query_average_stat());
    newb -= help;

    if (newbie)
    {
	if (sizeof(help))
	{
	    write(sprintf(" --- Newbie Helpers:\n\n%-#75s\n\n",
		    implode(map(help, &->query_name()), "\n")));
	}

	if (sizeof(newb))
	{
	    write(sprintf(" --- Fellow Newbies:\n\n%-#75s\n\n",
		    implode(map(newb, &->query_name()), "\n")));
	}
    }
    else
    {
	if (sizeof(newb))
	{
	    write(sprintf(" --- Active Newbies:\n\n%-#75s\n\n",
		    implode(map(newb, &->query_name()), "\n")));
	}

	if (sizeof(help))
	{
	    write(sprintf(" --- Fellow Helpers:\n\n%-#75s\n\n",
		    implode(map(help, &->query_name()), "\n")));
	}
    }

    return 1;
}

/*
 * Ntell:  This allows newbies and helpers to speak to each other.
 *         All communications are logged and there is no cost to use.
 */
public int
f_ntell(string str)
{
    object *whom;
    
    if (check_restricted())
        return 0;

    if (!objectp(wearer))
	return 0;

    if (!strlen(str))
	return notify_fail("What are you trying to say?\n");

    if (sizeof(whom = filter(users(), check_available)) <= 1)
    {
	write("There is nobody else to hear your message.\n");
	return 1;
    }

    whom->catch_tell(sprintf("<Newbie> %s: %s\n",
	    capitalize(TP->query_real_name()), str));

#ifdef LOG_NTELL
    write_file(LOG_NTELL,
	sprintf("%s %-11s: %s\n", ctime(time()),
	    capitalize(TP->query_real_name()), str));
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

    if (!objectp(who))
	return;

    if (last != environment(who))
    {
	TP->catch_tell("Your movement has caused the magics to "+
	    "cease and you fail to be returned home.\n");
	return;
    }

    TP->move_living("shimmering then fading away", where, 1, 0);
    TP->add_fatigue(-(TP->query_max_fatigue()));

    TP->catch_tell("\nThe magicks leaving you feeling extrememly fatigued, "+
	"it would be a good idea to find something to eat and drink when "+
	"you've recovered some.\n\n");

#ifdef LOG_RECALL
    write_file(LOG_RECALL,
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
    if (check_restricted())
	return 0;

    if (!objectp(wearer))
	return 0;

    if (!newbie)
	return 0;

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
    if (str == file_name(environment(TP)))
    {
	write("You are already at your starting location!\n");
	return 1;
    }

    write("You feel yourself beginning to fade.. remember to "+
	"hold still or the magic will go awry.\n");

    alarm = set_alarm(DELAY, 0.0, &do_recall(TP, str, environment(TP)));
    return 1;
}

public int
f_break(string str)
{
  string what;
  object poster;
  
  if (!str) {
    notify_fail("Break what? The pin?\n");
    return 0;
  }
  if (sscanf(str,"%s",what) == 1)
    if(what == "pin") {
      write("The pin breaks into small shatters.\n");
      if (poster = find_object(POSTER))
	delete_helper(TP->query_name());
      remove_object();
      return 1;
    }
    else
      notify_fail("Break what? The pin?\n");

  return 0;
}
public void
init(void)
{
    ::init();

    if (TP != environment())
	return;

    if (check_restricted())
	return;

    add_action( f_nlist, "nlist" );
    add_action( f_ntell, "ntell" );
    add_action(  f_home, "home"  );
    add_action( f_break, "break" );
    if (IS_NEWBIE(environment()))
    {
	newbie = 1;
	set_alarm(5.0, 0.0, wear_me);
    }
    else
    {
	add_adj("helper");
	set_short("newbie helper pin");
    }
}
