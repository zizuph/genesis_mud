/*
 * drow/race/soul.c
 *
 * The guild soul for the drow racial guild.
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma save_binary
#pragma strict_types

#include "guild.h"
#include <cmdparse.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/cmd/std/command_driver";
/* Our commands.c is slightly different then the mudlibs. */
inherit (P_FAERUN_LIB + "commands");

/* For adding 'emotion' messages to players descs */
#ifndef SOULDESC
#  define SOULDESC(x)	(this_player()->add_prop("_live_s_soulextra", (x)))
#endif

public int
query_cmd_soul(void)
{
    return 1;
}

public string
get_soul_id(void)
{
    return "drow_layman";
}

/*
 * Add commands in alpha order by category.
 * Function names should be prefixed as follows:
 *    f_  == General command function
 *    e_  == Guild emotes.
 */
public mapping
query_cmdlist(void)
{
    return ([
	"dlhelp" : "f_dlhelp",
    ]);
}

/*
 * This is used constantly, so simplify its usage.
 */
#define OBERROR(str) if (!sizeof(oblist)) { \
	    if (strlen(parse_msg)) { write(parse_msg); return 1; } \
	    return notify_fail(str);  }


/*************************************************************************
 * C O M M A N D S
 */

/* Used to parse and display the helpfiles. */
public int
f_dlhelp(string str)
{
    string file;

    setuid();
    seteuid(getuid());

    if (!strlen(str))
	str = "index";
    else
	str = lower_case(str);

    file = sprintf("%s%s", GUILD_HELP, str);
    if (file_size(file) > 0)
	return TI->more(read_file(file), 0);

    write("Unfortunaly, there is no help on that subject.\n");
    return 1;
}

public void
do_sign(object me, object who, string str)
{
    if (!CAN_SEE_IN_ROOM(who) || !CAN_SEE(who, me))
	return;

    if ((IS_DROW(who) && who->query_skill(SS_LANGUAGE) > 49) ||
      (random(who->query_skill(SS_LANGUAGE) +
	  who->query_stat(SS_WIS) / 2) > 150))
	who->catch_tell(me->query_The_name(who) +
	  " signs in the Silent Language: " +str + "\n");
    else
    {
	who->catch_tell(me->query_The_name(who) +
	  " performs an intricate series of gestures with " +
	  this_player()->query_possessive() + " hands.\n");
	return 0;
    }
    return 1;
}

public int
e_dlsign(string str)
{
    int size; 
    object *whom, *other;

    if (!strlen(str))
    {
	notify_fail("Sign what in the Silent Language?\n");
	return 0;
    }

    if (TP->query_skill(SS_LANGUAGE) < 50)
    {
	write("You are not skilled enough in foreign languages " +
	  "to be able to use the Silent Language.\n");
	return 1;
    }

    if (TP()->query_option(OPT_ECHO))
	write ("You sign in the Silent Language: "+ str +"\n");
    else
	write ("Ok.\n");

    whom  = filter(all_inventory(ENV(TP)), query_interactive) - ({ TP });
    other = filter(whom, &->query_wiz_level());
    whom -= wiz;

    wiz->catch_tell(TP->query_name() +
	" signs in the Silent Language: "+ str +"\n");

    other = filter(whom, &operator(==)(GUILD_NAME) @
			 &->query_guild_name_lay());
    whom -= other;

    size = sizeof(whom);
    while(--size)
	do_sign(TP, whom[size], str);

    return 1;
}
