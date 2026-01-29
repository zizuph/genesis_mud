/* Pendant for Avenir wizards */
/* updated 12/19/98 to add an Avenir 'time' ability */

#pragma strict_types

inherit "/std/armour";
#include "/d/Avenir/common/common.h"
#include <std.h>

#define PATH ("/sys/global/filepath")

#define PID     "_avenir_pendant_wiz_object"
#define FIX     "-*- Fixed"

void create_armour()
{
    set_name("pendant");
    add_name(PID);
    set_short("carved ebony pendant");
    set_long("It is a small, delicately engraved pendant, a perfect "
      +"circle with a hole in the center.\n'help pendant' gives "
      +"some commands.\n");

    set_at(A_NECK);
    set_ac(0);
    set_af(TO);

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, 1);
}

static void check(object who)
{
    if(SECURITY->query_wiz_dom(who->query_real_name()) != "Avenir")
    {
	who->catch_msg("The pendant fades away.\n");
	remove_object();
	return;
    }

    setuid();
    seteuid(getuid(who));

    set_this_player(who);
    wear_me();

    who->catch_msg("You prepare yourself for another busy day of "
      +"coding for the Sybarites.\n");
    return;
}

mixed wear()
{
    write("You wear the " + short() + " upon your left breast.\n");
    say(QCTNAME(TP) + " wears a " + short() + " upon "
      + POSSESS(TP) + " left breast.\n");
    return 1;
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(living(to))
	set_alarm(1.0, 0.0, &check(to));
}

string query_auto_load()
{
    return MASTER;
}

string query_recover()    { return 0; }

/*
 * Let's only have one at a time...
 */
varargs int move(object to, int sub)
{
    if(present(PID, to) && ENV(TO) != to)
    {
	set_alarm(0.0, 0.0, remove_object);
	return 5;
    }

    return ::move(to, sub);
}

static int logfix(string str)
{
    string file, *foo, log = "", filename, *listing, tmppath, tmpentry, tmpstr, *tmparray,
    comment = "", type, *exploded, report;
    int    i, index, tofix = -1, com_index;

    NF("Syntax: logfix <bug/typo/idea> <keywords> [-c comments]\n");
    if(!strlen(str))
	return 0;

    foo = explode(str, " ");

    if((com_index = member_array("-c", foo)) != -1)
    {
	for(i=com_index + 1;i<sizeof(foo);i++)
	{
	    comment += foo[i] + " ";
	}

	foo = foo[0 .. com_index-1];
    }

    if(foo[0] == "bug" || foo[0] == "bugs")
	filename = "/d/Avenir/log/bugs";
    else if(foo[0] == "idea" || foo[0] == "ideas")
	filename = "/d/Avenir/log/ideas";
    else if(foo[0] == "typo" || foo[0] == "typos")
	filename = "/d/Avenir/log/typos";
    else
	return 0;

    type = foo[0];

    foo -= ({ foo[0] });

    if(!sizeof(foo))
	return 0;

    seteuid(getuid());

    /* This is so we can read logs > 50kb */
    while(file = read_file(filename, index, 200))
    {
	index += 201;
	log += file;
    }

    NF("Failed. Cannot read the file: " + filename + "\n");
    if(!strlen(log))
	return 0;

    exploded = explode(log, "\n\n");
    listing = ({ });


    /* Construct an array of separate log reports. This   */
    /* extra parsing is necessary since people sometimes  */
    /* double-space their log reports (thus exploding     */
    /* on the string "\n\n" is not quite enough).         */
    for(i=0;i<sizeof(exploded);i++)
    {
	if(!strlen(report))
	    report = exploded[i];
	else if(!wildmatch("*??? * /d/Avenir/* (?*)\n*", exploded[i]))
	{
	    report += "\n\n" + exploded[i];
	}
	else
	{
	    listing += ({ report });
	    report = exploded[i];
	}

    }

    if(strlen(report))
	listing += ({ report });

    write("[" + sizeof(listing) + " " + type + " reports to date]\n");
    if(sizeof(listing) > (MAX_ARRAY_SIZE - 50))
	write("WARNING: number of listings in " + filename + " is approaching "
	  + MAX_ARRAY_SIZE + " (MAX_ARRAY_SIZE). 'logfix' will not work "
	  + "on the file once this size is reached.\n");

    for(i = (sizeof(listing) - 1) ; i >= 0; i--)
    {
	for(index = 0; index < sizeof(foo); index++)
	{
	    if(!wildmatch("*"+foo[index]+"*", listing[i]))
		break;
	    else if(index == sizeof(foo) - 1)
		tofix = i;
	}

	if(tofix > -1)
	    break;
    }

    NF("Failed. Could not find the keyword(s): "+COMPOSITE_WORDS(foo)+".\n");
    if(tofix < 0)
	return 0;

    write("Found the log file:\n"+listing[tofix]+"\n");


    tmparray = explode(listing[tofix], "\n");
    tmpstr = tmparray[0];
    tmparray -= ({ tmpstr });

    /* tmpstr strips the noprmal header, and gets re-assigned */
    /* to a string with just the date                         */
    tmpstr = implode(explode(tmpstr, " ")[0 .. 2], " ");

    tmpentry = "On " + tmpstr + " you wrote:\n> " + implode(tmparray, "\n> ") + "\n";

    /*
	 tmppath = SECURITY->query_wiz_path(TP->query_real_name()) + "/open/logifx.tmp";
     */

    tmppath = "/d/Avenir/log/logfix.tmp";

    NF("Failed. That log file has already been fixed.\n");
    if(wildmatch("*"+FIX+"*", listing[tofix]))
	return 0;

    listing[tofix] += "\n" + FIX + " by " + TP->query_name() + ", "
    + extract(ctime(time()), 4, 15);

    if(strlen(comment))
	listing[tofix] += ": " + comment;

    log = implode(listing, "\n\n");

    NF("Failed. Could not remove " + filename + "\n");
    if(!rm(filename))
	return 0;

    NF("Failed. Could not write back to " + filename + "\n");
    if(!write_file(filename, log + "\n\n"))
	return 0;

    write("Success. Fixed that entry.\n");

    if(rm(tmppath) || file_size(tmppath) <= 0)
    {
	if(write_file(tmppath, tmpentry))
	    write("The fixed entry has been saved to " + PATH->reduce_to_tilde_path(tmppath)
	      + ".\n");
    }

    return 1;
}

int qcheck(string str)
{
    string file, *foo, new = "";
    string start_date;
    int    i, index;

    NF("Check to see which quests who has completed?\n");
    if(!strlen(str))
	return 0;

    str = CAP(str);

    seteuid(getuid());

    while(file = read_file("/d/Avenir/log/quest/quests", index, 100))
    {
	index += 100;

	if(!file)
	    continue;

	/* Obtain the first date in the log */
	if(!strlen(start_date) && strlen(file) > 24)
	    start_date = file[0 .. 23];


	foo = explode(file, "\n");

	for(i=0;i<sizeof(foo);i++)
	    if(wildmatch("*"+str+"*", foo[i]))
	    {
		if(i+1 >= sizeof(foo))
		    new += implode( ({ foo[i] }), "\n") + "\n";
		else
		    new += implode( ({ foo[i], foo[i+1] }), "\n") + "\n";
	    }
    }

    NF(str + " has completed no quests in Avenir after " + start_date + ".\n");
    if(!strlen(new))
	return 0;

    NF("Return string was too long. Are you sure you used the "
      +"player's name as the argument, and not something like 'quest'?\n");
    if(strlen(new) > 8000)
	return 0;

    write(str + " has completed the following Avenir quests after "
      + start_date + ":\n");
    write(new);
    return 1;
}

static int map(string str)
{
    string  where = file_name(ENV(TP)),
    *brk;

    seteuid(getuid(TP));

    brk = explode(where, "/");

    brk[sizeof(brk)-1] = "MAP";

    where = implode(brk, "/");

    if(file_size(where) < 0)
    {
	brk[sizeof(brk)-1] = "map";
	where = implode(brk, "/");
    }

    brk -= ({ brk[sizeof(brk)-1] });

    if(file_size(where) < 0)
    {
	write("No map file for " + implode(brk, "/") + "/\n");
	return 1;
    }

    write("**-Map file for " + implode(brk, "/") + "/-**\n");
    setuid();
    seteuid(getuid());

    if(!cat(where))
	write("Seems that you have no read-access here.\n");

    return 1;
}

int avtime(string str)
{
    setuid();
    seteuid(getuid());

    "/d/Avenir/inherit/avenir_time"->start_avtime();
    tell_object(environment(this_object()), "It is now the "+ 
      "/d/Avenir/inherit/avenir_time"->get_time_text() +
      ".\n");
    return 1;
}
int help(string str)
{
    if(str == "logfix")
    {
	write("Syntax: logfix <bug/typo/idea> <keyword(s)>\n"
	  +" This will put in an entry at the end of a cetrain bug "
	  +" or typo entry saying that you have fixed it. <keyword(s)> can "
	  +" be any words in the certain entry you want to fix. Simplest would "
	  +" be the player who made the entry and the date the entry was made, "
	  +" such as:"
	  +" logfix bug Nikklaus Aug 12\n"
	  +" The keyword search works from the bottom up, so if you just "
	  +" want to fix the last bug report that Kithkanan entered:"
	  +" logfix bug Kithkanan\n"
	  +" will work fine.\n");
	return 1;
    }

    if(str != "pendant")
    {
	return 0;
    }

    write("The following commands are available for the pendant:\n"
      +"   avtime    - Get the Avenir/Sybarus time.\n"
      +"   logfix    - log that you fixed a bug/idea/typo.\n"
      +"   map       - see the map of the room you are standing in.\n"
      +"   qcheck    - check to see what quests someone has done in Avenir.\n");
    return 1;
}

void init()
{
    ::init();

    add_action(map, "map");
    add_action(help, "help");
    add_action(logfix, "logfix");
    add_action(qcheck, "qcheck");
    add_action(avtime, "avtime");
}
