/*
 * The functions contained herein were completely re-written from scratch
 * as was the MANAGER object itself.  The old design, to put it frankly,
 * sucked, and sucked pretty damned hard.  So I have re-written things
 * to be more robust and effective and efficient.  It should also be
 * much simpler to add future functionality now.
 *
 * Unfortunately, do to horrendous design flaws in the original guild
 * there is absolutely no way to track the current membership of the
 * guild.  And it's far far to late to add it in a few years later without
 * closing the guild and requiring everyone rejoin.
 *
 * The above disclaimer is simply there if your wondering why some of
 * the functions rely on hit & miss routines.
 *
 *    --= Lucius Kane
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <std.h>
#include <composite.h>
#include "/d/Cirath/common/mobber.h"

public int
query_prevent_snoop() { return 1; }

public void
reset_room()
{
    if (!present("board", TO))
	clone_object(GLAD_ROOM+"counbord")->move(TO);

    bring_room_mob("cilops", GLAD_NPC+"cylops", 1);
}

public int
create_room()
{
    setuid(); seteuid(getuid());

    set_short("overseer sanctum");
    set_long("   This stone chamber is cold and hard, like the ones who "
      +"use it: The Overseers of the Gladiators. "
      +"Shelves with records line one wall, while near "
      +"another is the nest of a gigantic insect, but otherwise "
      +"there is little adornment.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({ "shelf", "shelves", "records", "record" }),
      "There are records on the comings and goings of the "+
      "Gladiators of Athas.\n");
    add_item("nest", "It is made of discarded refuse found in the "+
      "guild, including broken weapons, discarded betting chits, and "+
      "even the occasional skeleton.\n");
    add_item(({ "hexagon"}), "Its solidly built and rather ugly "+
      "but serves its purpose well.\n");
    add_item(({"scratch", "scratches"}), "They seem to spell out the "+
      "words 'help powers'. What could it mean?\n");

    add_exit(GLAD_ROOM+"counrcpt", "west", 0, 1);

    LOAD_ERR("/d/Cirath/athas/gladiator/npc/brutus");
    reset_room();
}

/*
 * This function controls listing and removing of those that have
 * attacked the GM npc 'brutus'.  This is needed as there are automatic
 * punishments involved in attacking him.
 */
public int
func_brutus(string str)
{
    string name, *arr;

    if (!strlen(str))
	return NF("Syntax: brutus <list> [name] | brutus <rem> <name>\n");

    sscanf(str, "%s %s", str, name);
    switch(str)
    {
    case "list":
	if (strlen(name))
	{
	    if (!sizeof(arr = MANAGER->query_brutus_attacker(name)))
	    {
		str = "No one has attacked Brutus by that name.\n";
		break;
	    }

	    str = capitalize(name) + ": "+ COMPOSITE_WORDS(arr) + "\n";
	}
	else
	{
	    int ix = -1, sz;

	    arr = m_indexes(MANAGER->query_brutus_attacker(0));
	    sz = sizeof(arr = sort_array(arr));

	    if (sz == 0)
	    {
		str = "No one has attacked Brutus recently.\n";
		break;
	    }

	    str = 0;
	    while(++ix < sz)
		func_brutus("list "+ arr[ix]);
	}
	break;

    case "rem":
	if (!strlen(name))
	{
	    str = "Syntax: brutus <list> [name] | brutus <rem> <name>\n";
	    break;
	}

	if (MANAGER->remove_brutus_attacker(name))
	{
	    str = capitalize(name) + " removed from the list.\n";
	    WRITE_LOG(LOG_BRUTUS, TP, ": " + str);
	}
	else
	{
	    str = "Unable to remove '"+ capitalize(name) +"' from "+
	    "the list.\n";
	}
	break;

    default:
	str = "Syntax: brutus <list> [name] | brutus <rem> <name>\n";
	break;
    }

    if (strlen(str))
	write(str);

    return 1;
}

/*
 * This function is for the High Overser to control the lesser overseer
 * positions.  Demote, Appoint, etcetera.
 */
public int
func_lesser(string str)
{
    int slot;
    object who;
    string arg, *arr;

    if (!strlen(str))
	return NF("Usage: lesser <appoint | demote> <name> [position]\n");

    if (sscanf(lower_case(str), "%s %s", str, arg) != 2)
	return NF("Usage: lesser <appoint | demote> <name> [position]\n");

    switch(str)
    {
    case "appoint":
	arr = explode(arg, " ");
	if (sizeof(arr) != 2)
	{
	    str = "Usage: lesser appoint <who> <position>\n";
	    break;
	}

	if ((slot = member_array(arr[1], OVERSLOTS[1..])) == POS_NONE)
	{
	    str = "That is not a valid Lesser Overseer position.\n";
	    break;
	}

        slot++;

	if (strlen(QUERY_OVERSEER(slot)))
	{
	    str = "That Overseer position is already taken.\n";
	    break;
	}

if(!objectp(who = find_player(arr[0])))
{
  str = capitalize(arr[0]) + " is not present in the realms.\n";
  break;
}

//	if (!objectp(who = present(arr[0], environment(TP))))
//	{
//	    str = capitalize(arr[0]) +" is not present.\n";
//	    break;
//	}

	if (!IS_MEMBER(who))
	{
	    str = capitalize(arr[0]) +" is not a Gladiator.\n";
	    break;
	}

	if (QUERY_OVERSEER(who) != POS_NONE)
	{
	    str = capitalize(arr[0]) +" already holds an Overseer "+
	    "position.\n";
	    break;
	}

	if (!ADD_OVERSEER(who->query_real_name(), OVERSLOTS[slot]))
	{
	    str = "An unknown error occured, please make a report.\n";
	    break;
	}

	str = "You appoint '"+ capitalize(arr[0]) +" to the "+
	capitalize(OVERSLOTS[slot]) +" Overseer position.\n";

	WRITE_LOG(LOG_LESSER, TP, ": "+ str);

	tell_object(who, "You have been appointed to the "+
	  capitalize(arr[1]) +" position by "+
	  TP->query_the_name(who) +".\n");

	/* Reset the cuirasse */
	who = present(CUIR_ID, who);
	who->remove_adj(who->query_adj());
	who->configure_cuirasse();
	break;

    case "demote":

if(!objectp(who = find_player(arg)))
{
  str = capitalize(arg) + " is not present in the realms.\n";
  break;
}

//	if (!objectp(who = present(arg, environment(TP))))
//	{
//	    str = capitalize(arg) +" is not present.\n";
//	    break;
//	}

	if (!IS_MEMBER(who))
	{
	    str = capitalize(arg) +" is not a Gladiator.\n";
	    break;
	}

	if ((slot = QUERY_OVERSEER(who)) == POS_NONE)
	{
	    str = capitalize(arg) +" does not hold an Overseer "+
	    "position.\n";
	    break;
	}

	if (!REM_OVERSEER(who->query_real_name()))
	{
	    str = "An unknown error occured, please make a report.\n";
	    break;
	}

	if (who == TP)
	{
	    str = "You retire your position of High Overseer.\n";
	}
	else
	{
	    str = "You demote '"+ capitalize(arg) +"' from the "+
	    capitalize(OVERSLOTS[slot]) +" Overseer position.\n";
	    tell_object(who, TP->query_The_name(who) +" has stripped "+
	      "you of your Overseer position.\n");
	}

	WRITE_LOG(LOG_LESSER, TP, ": "+ str);

	/* Reset the cuirasse */
	who = present(CUIR_ID, who);
	who->remove_adj(who->query_adj());
	who->configure_cuirasse();
	break;

    default:
	str = "Usage: lesser <appoint | demote> <name> [position]\n";
	break;
    }

    if (strlen(str))
	write(str);
    return 1;
}

/*
 * This function handles viewing of the various logs.
 * For now, all Overseers have access to the logs.
 */
public int
func_logs(string str)
{
    int mored;
    string *arr;

    if (!strlen(str))
    {
	return NF("Available logs are:\n  "+
	  "join, quit, lesser, punish, brutus\n");
    }

    arr = explode(str, " ");
    if ((sizeof(arr) == 2) && (arr[1] == "more"))
	mored = 1;

    switch(arr[0])
    {
    case "join":
	str = LOG_JOIN;
	break;

    case "quit":
	str = LOG_QUIT;
	break;

    case "lesser":
	str = LOG_LESSER;
	break;

    case "punish":
	str = LOG_PUNISH;
	break;

    case "brutus":
	str = LOG_BRUTUS;
	break;

    default:
	write("That does not appear to be a valid logfile.\n");
	return 1; break;
    }

    if (file_size(str) == -1)
    {
	write("That logfile appears to not contain any data at "+
	  "the present time.\n");
	return 1;
    }

    if (mored)
	this_player()->more(read_file(str));
    else
	tail(str);

    return 1;
}

/*
 * This function handles punishemnts.  Listing, adding, removing, etcetera.
 * Only the High Overseer may invoke some of these.
 * Only the High Overseer may punish Lesser Overseers.
 */
public int
func_punish(string str)
{
    int pos, pun;
    string *arr;
    mixed tmp;

    if (!strlen(str) || sizeof(arr = explode(lower_case(str), " ")) != 3)
	return NF("Usage: punish <add|rem|query> <name> <type>\n");

    if ((pun = MAP_PUN[arr[2]]) == 0)
    {
	return NF("That is not a valid punishment.  Choose from:\n  "+
	  COMPOSITE_WORDS(m_indexes(MAP_PUN)) + "\b");
    }

    if ((arr[1] == "all") && (arr[0] != "query"))
	return NF("You may only 'query' all, not 'add' nor 'rem'.\n");

    pos = QUERY_OVERSEER(TP);
    tmp = CHECK_PUNISHMENT(arr[1], pun);

    if ((arr[0] != "query") && (pun == PUN_EXPEL) && (pos != POS_HIGH))
	return NF("Only the High Overseer may 'expel'.\n");

    switch(QUERY_OVERSEER(arr[1]))
    {
    case POS_WIZ:
    case POS_HIGH:
	str = "Surely you jest, you may not punish that individual.\n";
	break;

    case POS_INT..POS_ARENA:
	if (pos != POS_HIGH)
	{
	    str = "Only the High Overseer may punish the "+
	    "Lesser Overssers.\n";
	    break;
	}
	// Fallthru
    default:
	str = 0;
	break;
    }

    if (strlen(str))
    {
	write(str);
	return 1;
    }

    switch(arr[0])
    {
    case "query":
	if (arr[1] == "all")
	{
	    if (!sizeof(tmp))
	    {
		str = "Nobody seems to be under that punishment.\n";
	    }
	    else
	    {
		str = "The following are affected by that punishment:\n"+
		sprintf("%-#78s\n", implode(map(tmp, capitalize), "\n"));
	    }
	    break;
	}
	else if(tmp > 0)
	{
	    str = capitalize(arr[1]) +" is under that punishment.\n";
	}
	else
	{
	    str = capitalize(arr[1]) +" is not under that punishment.\n";
	}
	break;

    case "add":
	if (tmp > 0)
	{
	    str = capitalize(arr[1]) +" is already under that punishment.\n";
	    break;
	}

        if (ADD_PUNISHMENT(arr[1], pun))
	{
	    str = "Punishment '"+ arr[2] +"' added to: "+
		capitalize(arr[1]) +".\n";
	    WRITE_LOG(LOG_PUNISH, TP, ": "+ str);
	}
	else
	{
	    str = "Unable to add that punishment to "+
		capitalize(arr[1]) + ".\n";
	}
	break;

    case "rem":
	if (tmp <= 0)
	{
	    str = capitalize(arr[1]) +" is not under that punishment.\n";
	    break;
	}

        if (REM_PUNISHMENT(arr[1], pun))
	{
	    str = "Punishment '"+ arr[2] +"' removed from: "+
		capitalize(arr[1]) +".\n";
	    WRITE_LOG(LOG_PUNISH, TP, ": "+ str);
	}
	else
	{
	    str = "Unable to remove that punishment from "+
		capitalize(arr[1]) + ".\n";
	}
	break;

    default:
	str = ("Usage: punish <add|rem|query> <name> <type>\n");
	break;
    }

    if (strlen(str))
	write(str);

    return 1;
}

public int
pet(string str)
{
    string *arr = ({"cilops", "cylops", "gray cilops", 
      "large gray cilops", "large cilops"});

    if (member_array(str, arr) == -1)
	return 0;

    if(!present("cilops", TO))
	return NF("The cilops doesn't seem to be around.\n");

    write("You pet the hard chitin of the cilops.\n");
    say(QCTNAME(TP)+" pets the hard chitin of the cilops.\n");
    tell_room(E(TP), "The cilops clicks its mandibles together happily.\n");
    return 1;
}

public int
func_help(string str)
{
    if (str != "powers")
	return NF("Help powers perhaps?\n");

    write(
	"The Overseers of the Gladiators of Athas have the following "+
	"powers:\n\n    Brutus, Punish, Logs, Lesser\n\nYou may not "+
	"have access to all powers, it is rank dependant.  Type the "+
	"name of each power for a brief syntaxtual help message.  More "+
	"detailed help is on the way.\n");
    return 1;
}

void
init()
{
    int pos = QUERY_OVERSEER(TP);

    ::init();

    add_action(pet, "pet");

    if (pos == POS_NONE)
	return;

    /* Only Overseers get these actions. */
    add_action(func_help, "help");
    add_action(func_punish, "punish");
    add_action(func_brutus, "brutus");
    add_action(func_logs, "logs");

    if (pos != POS_HIGH)
	return;

    /* Only the High Overseers get these actions. */
    add_action(func_lesser, "lesser");
}

