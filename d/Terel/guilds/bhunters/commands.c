/*
 commands for bounty hunters guild, 
  by Udana 05/06
 */

#include <cmdparse.h>
#include <macros.h>
#include "./bhunters.h"
#include "/d/Terel/include/Terel.h"

int get_help(string a)
{
	if(a == "hunters")
	{
		write("Not ready yet.\n");
		return 1;
	}
	return 0;
}

int list_hunters()
{
	write("Not ready yet.\n");
	return 1;
}

int list_bounties()
{
	OFFICE->teleledningsanka();
	string *bounties = OFFICE->get_bounties();
	if(!sizeof(bounties))
	{
		write("All bounties have been claimed, you'll need to wait for new to show up.\n");
		return 1;
	}
	write(implode(bounties, "    "));
	return 1;
}

int list_sth(string a)
{
	if(a == "bounties" || a == "rewards")
		return list_bounties();
	if(a == "hunters")
		return list_hunters();
	notify_fail("List what?\n");
	return 0;
}

int trap_here(string a)
{
	string trap_name;
	notify_fail("Set what trap?\n");
	if(!strlen(a))
		return 0;
	parse_command(a, ({}), "%w [trap] ", trap_name);
	if(!stringp(TRAP_FILES[trap_name]))
		return 0;
	TP->set_trap(TRAP_FILES[trap_name]);
	return 1;
}