/*
 * /d/Genesis/wiz/fury.c
 *
 * This room is the master room controlling the fury of Genesis. It can be
 * summoned to kill a player for punishment.
 *
 * Copyright (C) Stas van der Schaaf - November 12 1995
 *               Mercade @ Genesis
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <std.h>

/*
 * Global variable.
 *
 * fury_map = ([ (string)target : ({ (string)wizard, (string)reason }) ])
 * fury_npc = ([ (string)target : (object)attacking fury ])
 */
static private mapping fury_map = ([ ]);
static private mapping fury_npc = ([ ]);
static private int     alarm_id = 0;

/*
 * Prototype.
 */
static int fury(string str);
static void fury_alarm();

#define FURY_FILE ("/d/Genesis/wiz/fury")
#define FURY_NPC  ("/d/Genesis/wiz/fury_npc")
#define FURY_LOG  ("fury")
#define INDEX_WHO (  0  )
#define INDEX_WHY (  1  )
#define DELAY     (300.0)

/*
 * Function name: create_room
 * Description  : This function is called to create this room.
 */
static void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("the Genesis Fury room");
    set_long(break_string("Here, in this empty space, the fury of Genesis " +
	"is controlled. The wrath of the fury may be called on a player " +
	"if he or she deserves it. The ghostly fury will attack its prey " +
	"and fight it until the player dies. Only archwizards and keepers " +
	"may call on the fury of Genesis this way. To control the fury, " +
	"the following commands are possible:", 75) + "\n" +
	"    fury list\n" +
	"    fury add <name> <reason>\n" +
	"    fury remove <name>\n" +
	break_string("Note that the reason will be printed to the target " +
	"of the fury when it first attacks and when the player examines " +
	"the fury. It should be a complete sentence including the period or " +
	"exclamation mark.", 75) + "\n");

    fury_map = restore_map(FURY_FILE);

    if (m_sizeof(fury_map))
    {
	alarm_id = set_alarm(DELAY, DELAY, fury_alarm);
    }
}

/*
 * Function name: init
 * Description  : This function links the command 'fury' to people who
 *                enter this room.
 */
void
init()
{
    add_action(fury, "fury");
}

/*
 * Function name: fury
 * Description  : This function contains the code for the command 'fury'. In
 *                the long description you shall find the arguments possible
 *                to this command.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
static int
fury(string str)
{
    string name = this_player()->query_real_name();
    string *args;
    int    index;
    int    index2;
    int    size;
    int    size2;
    string *tmp;

    if (!strlen(str))
    {
	notify_fail("No argument to fury.\n");
	return 0;
    }

    if ((SECURITY->query_wiz_rank(name) < WIZ_ARCH) &&
		!SECURITY->query_team_member("aop", name) && (str != "list"))
    {
	notify_fail("You have no access to the fury.\n");
	return 0;
    }

    args = explode(str, " ");

    switch(args[0])
    {
    case "add":
	if (sizeof(args) < 3)
	{
	    notify_fail("Syntax: fury add <name> <reason>\n");
	    return 0;
	}

	args[1] = lower_case(args[1]);
	if (pointerp(fury_map[args[1]]))
	{
	    notify_fail("Fury already called on " + capitalize(args[1]) +
		" by " + capitalize(fury_map[args[1]][INDEX_WHO]) + ".\n");
	    return 0;
	}

	fury_map[args[1]] = ({ name, implode(args[2..], " ") });
	save_map(fury_map, FURY_FILE);

	if (objectp(find_player(args[1])))
	{
	    fury_npc[args[1]] = clone_object(FURY_NPC);
	    fury_npc[args[1]]->fury_start(args[1],
		fury_map[args[1]][INDEX_WHY]);
	}
	else if (!alarm_id)
	{
	    alarm_id = set_alarm(DELAY, DELAY, fury_alarm);
	}

	args[1] = capitalize(args[1]);
	log_file(FURY_LOG,
	    ctime(time()) + " " + FORMAT_NAME(capitalize(args[1])) +
	    ": Added by " + capitalize(name) + ": " +
	    implode(args[2..], " ") + "\n");
	write("Fury added to " + args[1] + ".\n");
	return 1;

    case "list":
	if (!(size = m_sizeof(fury_map)))
	{
	    write("No players under revenge from the fury.\n");
	    return 1;
	}

	write("TARGET     : WIZARD     : REASON\n");

	args = sort_array(m_indices(fury_map));
	index = -1;
	while(++index < size)
	{
	    tmp = explode(break_string(FORMAT_NAME(capitalize(args[index])) +
		": " +
		FORMAT_NAME(capitalize(fury_map[args[index]][INDEX_WHO])) +
		": " + fury_map[args[index]][INDEX_WHY], 78), "\n");
	    str = tmp[0] + "\n";

	    if (sizeof(tmp) > 1)
	    {
		tmp = explode(break_string(implode(tmp[1..(sizeof(tmp) - 1)],
		    " "), 53), "\n");

		index2 = -1;
		size2 = sizeof(tmp);
		while(++index2 < size2)
		{
		    str += "                          " + tmp[index2] + "\n";
		}
	    }

	    write(str);
	}

	return 1;

    case "remove":
	if (sizeof(args) != 2)
	{
	    notify_fail("Syntax: fury remove <name>\n");
	    return 0;
	}

	args[1] = lower_case(args[1]);
	if (!pointerp(fury_map[args[1]]))
	{
	    notify_fail("The fury has not be called on " +
		capitalize(args[1]) + ".\n");
	    return 0;
	}

	if (objectp(fury_npc[args[1]]))
	{
	    fury_npc[args[1]]->fury_removed(args[1]);
	    fury_npc = m_delete(fury_npc, args[1]);
	}

	fury_map = m_delete(fury_map, args[1]);
	save_map(fury_map, FURY_FILE);

	if (!m_sizeof(fury_map))
	{
	    remove_alarm(alarm_id);
	    alarm_id = 0;
	}

	args[1] = capitalize(args[1]);
	log_file(FURY_LOG,
	    ctime(time()) + " " + FORMAT_NAME(args[1]) + ": Removed by " +
	    capitalize(name) + ".\n");
	write("Fury removed from " + args[1] + ".\n");
	return 1;

    default:
	notify_fail("Invalid subcommand '" + args[0] + "' to fury.\n");
	return 0;
    }

    write("FATAL in fury(). Please report this.\n");
    return 1;
}

/*
 * Function name: fury_alarm
 * Description  : Each five minutes this module will check whether there
 *                are players that are under the wrath of the fury.
 */
static void
fury_alarm()
{
    string *targets;
    int    size;

    if (!m_sizeof(fury_map))
    {
	remove_alarm(alarm_id);
	alarm_id = 0;
	return;
    }

    targets = m_indices(fury_map) - m_indices(fury_npc);
    size = sizeof(targets);
    while(--size >= 0)
    {
	fury_npc[targets[size]] = clone_object(FURY_NPC);
	fury_npc[targets[size]]->fury_start(targets[size],
	    fury_map[targets[size]][INDEX_WHY]);
    }

    if (m_sizeof(fury_map) == m_sizeof(fury_npc))
    {
	remove_alarm(alarm_id);
	alarm_id = 0;
    }
}

/*
 * Function name: fury_succeeded
 * Description  : This function is called by the fury when the player was
 *                killed by the fury.
 * Arguments    : string target - the target that was killed.
 */
void
fury_succeeded(string target)
{
    if ((!objectp(previous_object())) ||
	(MASTER_OB(previous_object()) != FURY_NPC))
    {
	return;
    }

    log_file(FURY_LOG,
	ctime(time()) + " " + FORMAT_NAME(capitalize(target)) + ": Killed!\n");

    fury_npc = m_delete(fury_npc, target);
    fury_map = m_delete(fury_map, target);
    save_map(fury_map, FURY_FILE);
}

/*
 * Function name: fury_interrupted
 * Description  : This function is called by the fury when the player has
 *                disconnected or quit in order to escape the fury.
 * Arguments    : string target - the target that we were fighting.
 */
void
fury_interrupted(string target)
{
    if ((!objectp(previous_object())) ||
	(MASTER_OB(previous_object()) != FURY_NPC))
    {
	return;
    }

    fury_npc = m_delete(fury_npc, target);

    if (!alarm_id)
    {
	alarm_id = set_alarm(DELAY, DELAY, fury_alarm);
    }

}

/*
 * Function name: fury_to_lunch
 * Description  : This function is called by the fury when it harasses the
 *                player some more by leaving for lunch just before killing
 *                the player.
 * Arguments    : string target - the target that we were fighting.
 */
void
fury_to_lunch(string target)
{
    if ((!objectp(previous_object())) ||
	(MASTER_OB(previous_object()) != FURY_NPC))
    {
	return;
    }

    log_file(FURY_LOG,
	ctime(time()) + " " + FORMAT_NAME(capitalize(target)) +
	": Lunch!\n");
}

/*
 * Function name: query_prevent_shadow
 * Description  : We disallow anyone to shadow us.
 * Returns      : int 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
