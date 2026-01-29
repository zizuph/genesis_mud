/*
 * The actors club central room.
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <std.h>

#include "actor.h"

static nomask int do_invite(string str);
static nomask int do_deride(string str);
static nomask int do_remove(string str);
static nomask int do_laud(string str);
static nomask int do_honour(string str);
static nomask int do_restore(string str);
static nomask int do_resign(string str);
static nomask int do_apply(string str);
static nomask int do_list(string str);
static nomask int do_read(string arg);
static nomask int do_review(string arg);

/*
 * Name:	create_room
 * Desc:	Create the room
 */
public nomask void
create_room()
{
    setuid();
    seteuid(getuid());
    
    set_short("A barely lit room");
    set_long("  You are standing in a barely lit room. It is mostly empty except for a fine carpet and a bookcase. This is the room where the members of the Actors Club gather to discuss the world and the behaviour of people.\n  The members haven't bothered to decorate it much since they aren't here too often. They are busy spending their time exploring the world.\n\n");

    add_item(({"carpet", "rug"}), "It is an ancient carpet, donated by the creator of this room.\n");

    add_item(({"bookcase", "bookshelf"}), "The wooden bookcase contains but one single book.\n");

    add_item(({"book", "volume"}), "A leather-bound volume with a white smiling actors mask on the front cover, and a black sad mask on the back.\n");

    add_exit("/d/Genesis/clubs/rpg/ac_script", "east", "@@enter_test", 1, "@@can_see_exit");
    add_exit("/d/Genesis/clubs/rpg/ac_club", "south");

    add_prop(OBJ_S_WIZINFO, "An archwizard or member of the Genesis domain has full access to all commands in the Actors Club. However, before using ANY of these commands it is necessary to read the help texts found by typing 'read book' in this room. Failure to do so might upset the workings of the club. Also please keep in mind that the club is intended to function with as little wizard interference as possible.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

/*
 * Name:	init
 * Desc:	Add commands to those who should have them
 */
public nomask void
init()
{
    int wiz = IS_WIZ(TP);
    
    add_action(do_read, "read");
    add_action(do_read, "open");
    add_action(do_apply, "apply");

    if (QUERY_LEVEL(TP) >= 0 || IS_WIZ(TP))
	add_action(do_list, "list");

    if (QUERY_LEVEL(TP) >= 0)
    {
	add_action(do_restore, "restore");
	add_action(do_resign, "resign");
    }

    if (QUERY_LEVEL(TP) >= MEMBER_RANK)
    {
	add_action(do_invite, "invite");
	add_action(do_deride, "deride");
	add_action(do_laud, "laud");
	add_action(do_honour, "honour");
    }

    if (QUERY_LEVEL(TP) == ADMIN_RANK)
    {
	add_action(do_review, "review");
	add_action(do_remove, "remove");
    }

    ::init();
}

/*
 * Name:	do_read
 * Desc:	Read the book
 * Args:	arg - what to read
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_read(string arg)
{
    string	*args;
    int		wiz = IS_WIZ(TP);

    if (!strlen(arg))
	return notify_fail("Read what?\n");
	    
    args = explode(arg, " ");

    if (args[0] != "book" &&
	args[0] != "volume")
	return notify_fail(capitalize(query_verb()) + " what?\n");

    if (query_verb() == "open")
    {
	write("The book is open for anyone to read.\n");
	return 1;
    }

    if (sizeof(args) > 1)
	arg = implode(args[1..], " ");
    else
	arg = "";
    
    if (wiz || CHECK_MEMBER(TP))
    {
	switch (lower_case(arg))
	{
	case "":
	    TP->more(AC_HELP + "index", 1);
	    break;
	    
	case "access":
	case "deride":
	case "emotes":
	case "honour":
	case "index":
	case "invite":
	case "laud":
	case "list":
	case "ooc":
	case "rank":
	case "resign":
	case "remove":
	case "restore":
	case "review":
	case "roleplay":
	case "rules":
	case "symbol":
	    TP->more(AC_HELP + arg, 1);
	    break;

	default:
	    write("You can't find that chapter in the book.\n");
	    break;
	}
    }
    else
	TP->more(AC_HELP + "general", 1);

    return 1;
}

/*
 * Name:	do_resign
 * Desc:	Resign from the club
 * Args:	str - what to resign from
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_resign(string str)
{
    object ob;
    int wiz = IS_WIZ(TP);

    if (wiz || CHECK_MEMBER(TP) != 1)
	return 0;
    
    if (str != "from the club")
	return notify_fail("Resign from what?\n");
    
    if (TP->query_prop(LEAVE_PROP))
    {
	TP->remove_prop(LEAVE_PROP);
	write("Your resignation from the club has been accepted.\n");
	tell_room(this_object(), QCTNAME(TP) + " resigns from the Actors Club.\n", TP);
	ob = present(AC_TOKEN, TP);
	if (objectp(ob))
	    ob->remove_object();
	AC_CENTRAL->do_remove_member(TP->query_real_name(), REASON_RESIGN);
    }
    else
    {
	TP->add_prop(LEAVE_PROP, 1);
	write("Please type 'resign from the club' again for confirmation.\n");
    }
    return 1;
}

/*
 * Name:	do_invite
 * Desc:	Invite someone to the club
 * Args:	str - who to invite
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_invite(string str)
{
    object pl;
    string name;
    int wiz = IS_WIZ(TP);

    if (!wiz && CHECK_MEMBER(TP) != 1)
	return 0;

    if (!strlen(str) ||
	sscanf(str, "%s to the club", name) != 1)
	return notify_fail("Invite whom?\n");

    name = lower_case(name);
    if (!objectp(pl = find_player(name)) || !present(pl, this_object()))
    {
	write(capitalize(name) + " must be present for this to be possible.\n");
	return 1;
    }

    if (present(AC_TOKEN, pl))
    {
	TP->catch_msg(QCTNAME(pl) + " is " +
	      "already a member.\n");
	return 1;
    }

    if (CHECK_MEMBER(pl))
    {
	TP->catch_msg(QCTNAME(pl) + " is a member, but has lost " +
	      pl->query_possessive() + " symbol. " +
	      capitalize(pl->query_pronoun()) + " should do 'restore' here instead.\n");
	return 1;
    }

    if (SECURITY->query_wiz_rank(name) != WIZ_MORTAL)
    {
	TP->catch_msg("Unfortunately " + QCTNAME(pl) + " is a wizard. Wizards are considered to be permanently OOC and thus not suitable as members of the Actors Club.\n");
	return 1;
    }
	
    TP->command("$snap");

    TP->catch_msg("You have invited " + QCTNAME(pl) + " to the Actors Club.\n");
    pl->catch_msg(QCTNAME(TP) + " invited you to become an Actor.\n");
    TP->add_prop(INVITE_PROP, name);
    return 1;
}

/*
 * Name:	do_apply
 * Desc:	Apply for membership
 * Args:	str - apply for what
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_apply(string str)
{
    mixed people;
    string name, *nlist;
    int i, invnum, sz, req, nwiz, wiz = IS_WIZ(TP);

    if (wiz || CHECK_MEMBER(TP))
	return 0;

    if (str != "for membership")
	return notify_fail("apply where?\n");

    people = filter(all_inventory(this_object()), interactive);
    sz = sizeof(people);
    name = TP->query_real_name();

    for (nlist = ({}), i = invnum = nwiz = 0 ; i < sz ; i++)
    {
	wiz = IS_WIZ(people[i]);
	if ((wiz || CHECK_MEMBER(people[i])) &&
	    people[i]->query_prop(INVITE_PROP) == name)
	{
	    nlist += ({ people[i]->query_real_name() });
	    nwiz += IS_WIZ(people[i]);
	    invnum += INVITE_MOD[QUERY_LEVEL(people[i])];
	}
    }

    req = AC_CENTRAL->query_expelled(name) ? INVITE_MIN * 2 : INVITE_MIN;

    if (!nwiz && invnum < req)
    {
	write("Unfortunately you haven't been invited by a sufficient number of members (" + req + ") to be accepted.\n");
	return 1;
    }

    for (i = 0 ; i < sz ; i++)
	if (CHECK_MEMBER(people[i]) &&
	    people[i]->query_prop(INVITE_PROP) == name)
	    people[i]->remove_prop(INVITE_PROP);
				  
    tell_room(this_object(), "A small symbol appears in " +
	      LANG_POSS(QCTNAME(TP)) + " hand. " +
	      capitalize(TP->query_pronoun()) +
	      " attaches it to " + TP->query_possessive() + " clothes.\n",
	      TP);

    TP->catch_msg("A small symbol appears in your hand. You attach it " +
		  "to your clothes, on a visible place.\n");

    AC_CENTRAL->add_member(TP->query_real_name(), nlist);

    clone_object(AC_SYMBOL)->move(TP);

    return 1;
}

/*
 * Name:	do_deride
 * Desc:	Deride someone
 * Args:	str - deride who
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_deride(string str)
{
    object pl, ob;
    string name, *nlist;
    mixed people;
    int i, demnum, sz, wiz = IS_WIZ(TP);

    if (!wiz && !CHECK_MEMBER(TP))
	return 0;

    if (!wiz && QUERY_LEVEL(TP) < MEMBER_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[MEMBER_RANK] + " and higher.\n");

    name = lower_case(str);
    if (!objectp(pl = find_player(name)) || !present(pl, this_object()))
    {
	write(capitalize(name) + " isn't present, which is bad form, but that's ok anyway.\n");
#ifdef 0
	write(capitalize(name) + " must be present for this to be possible.\n");
	return 1;
#endif
    }

    if (!CHECK_MEMBER_N(name))
    {
	write(capitalize(name) + " is not a member of the club.\n");
	return 1;
    }

    if (TP->query_real_name() == name)
    {
	write("You can't propose to deride yourself, silly!\n");
	return 1;
    }

    if (!wiz && QUERY_LEVEL_N(name) > QUERY_LEVEL(TP))
    {
	write("You can't propose to deride someone of higher rank than yourself.\n");
	return 1;
    }
    
    TP->command("$snap");

    TP->catch_msg("You have declared your intent to deride " + capitalize(name) + " from the Actors Club.\n");
    tell_room(this_object(), QCTNAME(TP) + " proposes to deride " + capitalize(name) + ".\n", TP);
    
    TP->add_prop(DEMOTE_PROP, name);

    people = filter(all_inventory(this_object()), interactive);
    sz = sizeof(people);

    for (nlist = ({}), i = demnum = 0 ; i < sz ; i++)
    {
	if ((wiz || CHECK_MEMBER(people[i])) &&
	    people[i]->query_prop(DEMOTE_PROP) == name)
	{
	    nlist += ({ people[i]->query_real_name() });
	    demnum += DEMOTE_MOD[QUERY_LEVEL(people[i])];
	}
    }

    if (!wiz && demnum < DEMOTE_MIN)
	return 1;

    for (i = 0 ; i < sz ; i++)
	if (CHECK_MEMBER(people[i]) &&
	    people[i]->query_prop(DEMOTE_PROP) == name)
	    people[i]->remove_prop(DEMOTE_PROP);

    sz = AC_CENTRAL->demote_member(name, nlist);

    if (sz < 0)
	tell_room(this_object(), capitalize(name) + " has been expelled from the Actors Club.\n");
    else
	tell_room(this_object(), capitalize(name) + " has been derided to the rank of " + AC_RANK_NAMES[sz] + ".\n");

    if (objectp(pl))
    {
	if (sz < 0)
	{
	    ob = present(AC_TOKEN, pl);
	    if (objectp(ob))
		ob->remove_object();
	    pl->catch_msg("You have been expelled from the Actors Club.\n");
	}
	else
	    pl->catch_msg("You have been derided to the rank of " + AC_RANK_NAMES[sz] + " in the Actors Club.\n");
    }

    return 1;
}

/*
 * Name:	do_remove
 * Desc:	Remove someone from the club
 * Args:	str - remove who
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_remove(string str)
{
    object pl, ob;
    string name, *nlist;
    mixed people;
    int i, demnum, sz, wiz = IS_WIZ(TP);

    if (!wiz && !CHECK_MEMBER(TP))
	return 0;
    
    if (!wiz && QUERY_LEVEL(TP) != ADMIN_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[ADMIN_RANK] + ".\n");

    name = lower_case(str);
    pl = find_player(name);

    if (!CHECK_MEMBER_N(name))
    {
	write(capitalize(name) + " is not a member of the club.\n");
	return 1;
    }

    if (TP->query_real_name() == name)
    {
	write("You can't propose to remove yourself, silly!\n");
	return 1;
    }

    AC_CENTRAL->remove_member(name, TP->query_real_name());

    tell_room(this_object(), capitalize(name) + " has been removed from the Actors Club.\n");

    if (objectp(pl))
	pl->catch_msg("You have been expelled from the Actors Club.\n");

    return 1;
}

/*
 * Name:	do_review
 * Desc:	Review a log
 * Args:	str - which log to review
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_review(string str = "")
{
    int wiz = IS_WIZ(TP);
    string *logs, name, cmd;

    if (!wiz && !CHECK_MEMBER(TP))
	return 0;

    if (!wiz && QUERY_LEVEL(TP) != ADMIN_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[ADMIN_RANK] + ".\n");

    switch (str)
    {
    case "":
    case "list":
	write("The following members are available for review:\n" + implode(map(sort_array(get_dir(EMOTE_LOG)), capitalize), ", ") + "\n");
	return 1;
	break;

    case "history":
	TP->more(AC_LOG, 1);
	return 1;
	break;

    default:
	logs = explode(str, " ");
	if (sizeof(logs) > 1)
	{
	    cmd = logs[0];
	    name = lower_case(logs[1]);
	    
	    if (file_size(EMOTE_LOG + name) < 0)
	    {
		write("The review file \"" + name + "\" does not exist.\n");
		return 1;
		break;
	    }

	    if (wildmatch(name + "*", name))
	    {
		write("Hehe, no, you can't mess with your own records, sneeky little bugger you!\n");
		return 1;
		break;
	    }

	    switch (cmd)
	    {
	    case "copy":
		rm (EMOTE_LOG + name + ".copy");
		write_file(EMOTE_LOG + name + ".copy", read_file(EMOTE_LOG + name));
		write("The review file \"" + name + "\" has been copied.\n");
		rm (EMOTE_LOG + name);
		break;
		
	    case "remove":
		rm (EMOTE_LOG + name);
		write("The review file \"" + name + "\" has been removed.\n");
		break;
		
	    default:
		write("Unknown review command \"" + cmd + "\".\n");
		break;
	    }
	    return 1;
	}
	else
	    name = lower_case(str);
	break;
    }

    if (file_size(EMOTE_LOG + name) < 0)
    {
	write("The review file \"" + name + "\" does not exist.\n");
	return 1;
    }

    TP->more(EMOTE_LOG + name, 1);

    return 1;
}

/*
 * Name:	do_laud
 * Desc:	Laud someone 
 * Args:	str - whom to laud
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_laud(string str)
{
    object pl, ob;
    string name, *nlist;
    mixed people;
    int i, promnum, sz, wiz = IS_WIZ(TP);

    if (!wiz && !CHECK_MEMBER(TP))
	return 0;

    if (!wiz && QUERY_LEVEL(TP) < MEMBER_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[MEMBER_RANK] + " and higher.\n");

    name = lower_case(str);
    if (!objectp(pl = find_player(name)) || !present(pl, this_object()))
    {
	write(capitalize(name) + " must be present for this to be possible.\n");
	return 1;
    }

    if (!CHECK_MEMBER(pl))
    {
	write(capitalize(name) + " is not a member of the club.\n");
	return 1;
    }

    if (TP->query_real_name() == name)
    {
	write("You can't propose to laud yourself, silly!\n");
	return 1;
    }

    if (QUERY_LEVEL(pl) >= MAX_RANK)
    {
	write(capitalize(name) + " already has achieved the highest rank in the club.\n");
	return 1;
    }
    
    if (!wiz && QUERY_LEVEL(pl) >= QUERY_LEVEL(TP))
    {
	write("You can't propose to laud someone of higher or equal rank to yourself.\n");
	return 1;
    }

    TP->command("$snap");

    TP->catch_msg("You have declared your intent to promote " + capitalize(name) + " in the Actors Club.\n");
    tell_room(this_object(), QCTNAME(TP) + " proposes to promote " + capitalize(name) + ".\n", TP);
    
    TP->add_prop(PROMOTE_PROP, name);

    people = filter(all_inventory(this_object()), interactive);
    sz = sizeof(people);

    for (nlist = ({}), i = promnum = 0 ; i < sz ; i++)
	if ((wiz || CHECK_MEMBER(people[i])) &&
	    people[i]->query_prop(PROMOTE_PROP) == name)
	{
	    nlist += ({ people[i]->query_real_name() });
	    promnum += PROMOTE_MOD[QUERY_LEVEL(people[i])];
	}

    if (!wiz && (promnum < PROMOTE_MIN))
	return 1;

    for (i = 0 ; i < sz ; i++)
	if (CHECK_MEMBER(people[i]) &&
	    people[i]->query_prop(PROMOTE_PROP) == name)
	    people[i]->remove_prop(PROMOTE_PROP);

    sz = AC_CENTRAL->promote_member(name, nlist);

    tell_room(this_object(), capitalize(name) + " has been promoted to the rank of " + AC_RANK_NAMES[sz] + ".\n");

    pl->catch_msg("You have been promoted to the rank of " + AC_RANK_NAMES[sz] + " in the Actors Club.\n");

    return 1;
}

/*
 * Name:	do_honour
 * Desc:	Honour someone
 * Args:	str - whom to honour
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_honour(string str)
{
    object pl, ob;
    string name, *nlist;
    mixed people;
    int i, promnum, sz, wiz = IS_WIZ(TP), thesp = 0;

    if (!wiz && !CHECK_MEMBER(TP))
	return 0;

    if (!wiz && QUERY_LEVEL(TP) < MEMBER_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[MEMBER_RANK] + " and higher.\n");

    name = lower_case(str);
    if (!objectp(pl = find_player(name)) || !present(pl, this_object()))
    {
	write(capitalize(name) + " must be present for this to be possible.\n");
	return 1;
    }

    if (!CHECK_MEMBER(pl))
    {
	write(capitalize(name) + " is not a member of the club.\n");
	return 1;
    }

    if (TP->query_real_name() == name)
    {
	write("You can't propose to honour yourself, silly!\n");
	return 1;
    }

    if (QUERY_LEVEL(pl) == HONOURED_RANK)
    {
	write(capitalize(name) + " already is an honoured member of the club.\n");
	return 1;
    }
    
    TP->command("$snap");

    TP->catch_msg("You have declared your intent to honour " + capitalize(name) + " in the Actors Club.\n");
    tell_room(this_object(), QCTNAME(TP) + " proposes to honour " + capitalize(name) + ".\n", TP);
    
    TP->add_prop(HONOUR_PROP, name);

    people = filter(all_inventory(this_object()), interactive);
    sz = sizeof(people);

    for (nlist = ({}), i = promnum = 0 ; i < sz ; i++)
	if ((wiz || CHECK_MEMBER(people[i])) &&
	    people[i]->query_prop(HONOUR_PROP) == name)
	{
	    nlist += ({ people[i]->query_real_name() });
	    promnum += PROMOTE_MOD[QUERY_LEVEL(people[i])];
	    if (QUERY_LEVEL(people[i]) == ADMIN_RANK)
		thesp++;
	}

    if (!wiz && (promnum < HONOUR_MIN))
	return 1;

    if (!wiz && thesp == 0)
	return 1;

    for (i = 0 ; i < sz ; i++)
	if (CHECK_MEMBER(people[i]) &&
	    people[i]->query_prop(HONOUR_PROP) == name)
	    people[i]->remove_prop(HONOUR_PROP);

    sz = AC_CENTRAL->promote_member(name, nlist);

    tell_room(this_object(), capitalize(name) + " has been awarded the rank of " + AC_RANK_NAMES[sz] + ".\n");

    pl->catch_msg("You have been awarded the rank of " + AC_RANK_NAMES[sz] + " in the Actors Club.\n");

    return 1;
}

/*
 * Name:	do_list
 * Desc:	List member records
 * Args:	str - which records to list
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_list(string str)
{
    int wiz = IS_WIZ(TP);

    if ((!wiz && CHECK_MEMBER(TP) != 1))
	return notify_fail("List what?\n");

    switch (str)
    {
    case "members":
	AC_CENTRAL->list_members(TP, 0);
	break;

    case "removed":
	AC_CENTRAL->list_members(TP, 1);
	break;

    case "expelled":
	AC_CENTRAL->list_members(TP, 2);
	break;

    case "all":
	AC_CENTRAL->list_members(TP, 0);
	write("\n");
	AC_CENTRAL->list_members(TP, 1);
	write("\n");
	AC_CENTRAL->list_members(TP, 2);
	break;

    default:
	return notify_fail("List what? Members, removed, expelled or all?\n");
    };

    return 1;
}

/*
 * Name:	do_restore
 * Desc:	Restore a symbol, or change old for new
 * Args:	str - restore what
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_restore(string str)
{
    object ob;

    if (CHECK_MEMBER(TP) != 1)
	return 0;
    
    if (objectp(ob = FIND_SYMBOL(TP)))
    {
	write("You replace your symbol with a new one.\n");
	ob->remove_object();
	clone_object(AC_SYMBOL)->move(TP);
    }
    else
    {
	write("You attach a new symbol to your clothes.\n");
	clone_object(AC_SYMBOL)->move(TP);
    }
    
    return 1;
}

/*
 * Name:	enter_inv
 * Desc:	Enter the room
 * Args:	to - Entering where
 *		from - Entering from where
 */
public nomask void
enter_inv(object to, object from)
{
    int wiz = IS_WIZ(TP);
    
    if (wiz || CHECK_MEMBER(TP))
	set_alarm(1.0, 0.0, &write("\nYou experience a feeling of belonging.\n\n"));
    else
	set_alarm(1.0, 0.0, &write("\nYou feel a have an odd feeling of intruding on something, or someone.\n\n"));
    ::enter_inv(to, from);
}

/*
 * Name:	enter_test
 * Desc:	Check to see if you can enter
 * Returns:	1 - failure, 0 - success
 */
public nomask int
enter_test()
{
    int		wiz = IS_WIZ(TP);
    
    if (!wiz && !CHECK_MEMBER(TP))
    {
	write("There is no obvious exit east.\n");
	return 1;
    }

    tell_room(this_object(), QCTNAME(TP) + " makes a gesture at the east wall, which then becomes transparent for a second or so, allowing " + TP->query_objective() + " to pass through.\n", TP);
    return 0;
}

/*
 * Name:	can_see_exit
 * Desc:	Can you see the exit, or not?
 * Returns:	1 - failure, 0 - success
 */
public nomask int
can_see_exit()
{
    int		wiz = IS_WIZ(TP);

    if (!wiz && !CHECK_MEMBER(TP))
	return 1;

    return 0;
}

/*
 * Name:	
 * Desc:	
 * Args:	
 * Returns:	
 */
