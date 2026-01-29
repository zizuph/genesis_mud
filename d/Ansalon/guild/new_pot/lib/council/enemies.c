/* Lucius @ Genesis - Aug 2016
 *
 * Neraka Enemies code
 */
#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

#include "../../guild.h"

#define ATTACKERS "/d/Ansalon/taman_busuk/neraka/admin/attackers"

public mapping
query_enemies_commands(void)
{
    return ([ "enemies" : "handle_enemies" ]);
}

public int
check_enemy(string arg)
{
    mixed *data = ATTACKERS->query_single_enemy(lower_case(arg));

    arg = capitalize(arg);

    if (!sizeof(data))
    {
	write("\""+ arg +"\" is not an enemy of the Holy City.\n");
	return 1;
    }

    write(sprintf("%14s: %-20s // %s\n",
	    arg, ctime(data[0])[4..], data[2]));

    return 1;
}

public int
list_enemies(string arg)
{
    arg = lower_case(arg);

    if (!strlen(arg))
    {
	string *names = ATTACKERS->query_enemy_list();

	if (!sizeof(names))
	{
	    write("There are no known enemies of the Holy City.\n");
	    return 1;
	}

	write("These are enemies of the Holy City:\n" +
	    sprintf("  %-#76s\n", implode(map(names, capitalize), "\n")));

	return 1;
    }

    mapping enemies = ([]);

    if (arg == "full")
	enemies = ATTACKERS->query_enemy_list(1);
    else if (arg == "all")
	enemies = ATTACKERS->query_all_enemies();
    else
	return notify_fail("Enemies list [all | full]?\n");


    if (!m_sizeof(enemies))
    {
	write("There are no known enemies of the Holy City.\n");
	return 1;
    }

    write(" These are the enemies of the Holy City:\n\n"+
	sprintf("%14s: %|20s //   Description\n%'-'76s\n",
	    "Name", "Last Attack", ""));

    foreach(string name: sort_array(m_indexes(enemies)))
    {
	mixed data = enemies[name];

	write(sprintf("%14s: %-20s // %s\n",
		capitalize(name), ctime(data[0])[4..], data[2]));
    }
    return 1;
}

public int
remove_enemy(string arg)
{
    string who, why;

    if (!parse_command(arg, ({}), "%w 'because' / 'for' %s", who, why))
    {
        notify_fail("Enemies remove <who> [because] <why>?\n");
        return 0;
    }

    if (strlen(why = implode(explode(why, " "), "")) < 5)
    {
	write("You must provide more of a reason than that.\n");
	return 1;
    }

    who = lower_case(who);
    arg = ATTACKERS->remove_attacker(who, why);
    
    if (arg == "Ok.\n")
    {
	GUILD_ADMIN->log(this_player(), "council", capitalize(who) +
                " was removed as an enemy. ["+ why +"]");

	write("You remove " + capitalize(who) +
	    " as an enemy of the Holy City.\n");
    }
    else
    {
	write("Error encountered: "+ arg);
    }

    return 1;
}

public int
handle_enemies(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
	return 0;

    notify_fail("Enemies list [all | full]\n" +
       "Enemies	check <who>?\n" +
       "Enemies	remove <who> [because] / [for] <why>?\n");

    if (!strlen(arg))
	return 0;

    string *arr = explode(arg, " ");

    if (sizeof(arr) < 2)
	arg = "";
    else
	arg = implode(arr[1..], " ");

    switch(arr[0])
    {
    case "list":
	return list_enemies(arg);
    case "check":
	return check_enemy(arg);
    case "remove":
	return remove_enemy(arg);
    default:
	return 0;
    }
}
