/*
 *	/d/Gondor/ithilien/emyn-arnen/obj/scabbard_master.c
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 * 	Master object to keep track of scabbards.
 *
 *	Olorin, 22-Feb-97.
 *
 *	Modification log:
 *      30-Jul-1997, Olorin: Added the 'purge' command.
 */
#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define SCABBARD_SAVE		"/d/Gondor/log/scabbard_save"
#define SCABBARD		(ITH_DIR + "emyn-arnen/obj/scabbard")
#define CELLAR			(ITH_DIR + "emyn-arnen/palace/cellar")

public string  list_owners(int active = 0);

string *Owner = ({ });

public void
create_gondor()
{
    set_short("control room");
    set_long(BSN("The control room for scabbards from the treasury " +
		 "in the house of Hurin in Emyn Arnen."));

    add_exit("/d/Gondor/workroom", "gondor", 0, 0, 0);
    add_exit(ITH_DIR + "emyn-arnen/palace/cellar", "cellar", 0, 0, 0);

    if (file_size(SCABBARD_SAVE + ".o") > 0)
	restore_object(SCABBARD_SAVE);

    add_cmd_item("owners", "list", &list_owners(0));
    add_cmd_item( ({ "playing", "players", "present", "active", }),
        "list", &list_owners(1)); 
    add_cmd_item( ({ "lost", "losers", "loser", }),
        "list", &list_owners(2)); 
}

public mixed
query_owner(mixed who)
{
    if (!who)
	return secure_var(Owner);

    if (objectp(who))
	who = who->query_real_name();
    else if (stringp(who))
	who = LOW(who);

    return member_array(who, Owner);
}

public void
remove_owner(mixed who)
{
    int     il = 1;
    object  co;
    string  msg = "";

    if (objectp(who))
	who = who->query_real_name();
    else if (stringp(who))
	who = LOW(who);
    else
	return;

    if (!strlen(who))
	return;

    // security:
    if (MASTER_OB(previous_object()) != SCABBARD)
    {
	if (objectp(TI))
	    msg = TI->query_name();
	else
	    while (objectp(co = calling_object(--il)))
		msg += file_name(co) + ": " + calling_function(il) +
		    "\n";
	msg += " called remove_owner for " + who + " in " + MASTER +
	    ". " + ctime(time()) + ".\n";
	log_file("scabbard", msg);
	return;
    }

    Owner -= ({ who });
    save_object(SCABBARD_SAVE);
}

public void
check_owner(mixed who)
{
    if (objectp(who))
	who = who->query_real_name();
    else if (stringp(who))
	who = LOW(who);
    else
	return;

    if (!strlen(who))
	return;

    // To prevent double adding of a name:
    if (member_array(who, Owner) > -1)
        return;

    Owner += ({ who });
    save_object(SCABBARD_SAVE);
}

public int
check_restore(mixed who)
{
    object  player;

    if (objectp(who))
	who = who->query_real_name();
    else if (stringp(who))
	who = LOW(who);
    else
	return 0;

    if (query_owner(who) < 0)
	return 0;
    if (!objectp(player = find_player(who)))
	return 0;
    if (objectp(present("_emyn_arnen_scabbard", player)))
	return 0;
    if (!player->test_bit("Gondor", MORGUL_GROUP,
			 ANGMAR_STANDARD_BIT))
	return 0;
    return 1;
}

static string
is_playing(string name)
{
    object  player;

    if (objectp(player = find_player(name)))
    {
	if (!objectp(present("_emyn_arnen_scabbard", player)))
	{
	    if (check_restore(player))
		return name + " (R)";
	    return name + " (-)";
	}
	return name + " (*)";
    }
    return name;
}

public string
list_owners(int active = 0)
{
    string *list = ({ }) + Owner,
            msg;

    sort_array(list);
    // copy the sorted list to the Owner array:
    Owner = ({ }) + list;
    save_object(SCABBARD_SAVE);

    if (active)
    {
        list = filter(list, objectp @ find_player);
        if (active > 1)
            list = filter(list, not @ objectp @
                &present("_emyn_arnen_scabbard", ) @ find_player); 
    }
    list = map(list, capitalize @ is_playing);
    //    list = map(list, capitalize);

    if (!sizeof(list))
        msg = "There is no player of the requested category.";
    else
        msg = COMPOSITE_WORDS(list) + ".";
    write(BSN(msg));

    return "";
}

public void
cellar_restore(object who)
{
    int     il;
    object  co,
            scabbard;
    string  name = who->query_name(),
            msg;

    // security:
    if (MASTER_OB(previous_object()) != CELLAR)
    {
	if (objectp(TI))
	    msg = TI->query_name() + " (" + file_name(previous_object())
		+ ") ";
	else
	    while (objectp(co = calling_object(--il)))
		msg += file_name(co) + ": " + calling_function(il) +
		    "\n";
	msg += " called cellar_restore for " + name + " in " + MASTER +
	    ". " + ctime(time()) + ".\n";
	log_file("scabbard", msg);
	return;
    }

    if (check_restore(who))
    {
	scabbard = clone_object(SCABBARD);
	write("As you enter the cellar, you step onto " +
	      (CAN_SEE_IN_ROOM(TP) ? LANG_ADDART(scabbard->short()) :
	       "something") + ".\n");
	if (scabbard->move(TP))
	{
	    if (scabbard->move(ENV(TP)))
		scabbard->move(ENV(TP), 1);
	}
	else
	    write("You stoop down and pick it up.\n");
	log_file("scabbard", "Scabbard restored to " +
		 TP->query_name() + ". " + ctime(time()) + ".\n");
    }
}

private int
restore(string who)
{
    int     rank = SECURITY->query_wiz_rank(TI->query_real_name());
    object  player,
            scabbard;

    if (rank < WIZ_STEWARD)
	return 0;
    if (((rank == WIZ_LORD) || (rank == WIZ_STEWARD)) &&
	(SECURITY->query_wiz_dom(TI->query_real_name()) != "Gondor"))
	return 0;

    if (!strlen(who))
    {
	NFN("Restore the scabbard to whom?");
	return 0;
    }

    if (!objectp(player = find_player(LOW(who))))
    {
	NFN("No player " + who + " found!");
	return 0;
    }

    if (!player->test_bit("Gondor", MORGUL_GROUP,
			  ANGMAR_STANDARD_BIT))
    {
	write("The scabbard may not be returned to " +
	      player->query_name() + ", since " +
	      player->query_pronoun() + 
	      " did not solve the quest!\n");
	return 1;
    }

    if (member_array(player->query_real_name(), Owner) < 0)
    {
	write(player->query_name() + " has no right to have a " +
	      "scabbard restored, since " + player->query_possessive()
	      + " was not lost due to a bug!\n");
	return 1;
    }

    if (objectp(scabbard = present("_emyn_arnen_scabbard", player)))
    {
        write(player->query_name() + " already has " +
            LANG_ADDART(scabbard->query_name()) + "!\n");
        return 1;
    }

    if ((scabbard = clone_object(SCABBARD))->move(player))
    {
	write(player->query_name() + " cannot carry the " +
	      scabbard->short() + "!\n");
	scabbard->remove_object();
    }
    else
    {
	write("You return the " + scabbard->short() + " to " +
	      player->query_name() + ".\n");
	player->catch_tell(TP->query_name() + " gives you " +
			   LANG_ADDART(scabbard->short()) + 
			   ", restoring your loss.\n");
	log_file("scabbard", "Scabbard restored by " +
		 TP->query_name() + " to " +
		 player->query_name() + ". " + ctime(time()) + ".\n");
    }
    
    return 1;
}

private int
purge(string arg)
{
    int     rank = SECURITY->query_wiz_rank(TI->query_real_name()),
            old;

    if (rank < WIZ_STEWARD)
	return 0;
    if (((rank == WIZ_LORD) || (rank == WIZ_STEWARD)) &&
	(SECURITY->query_wiz_dom(TI->query_real_name()) != "Gondor"))
	return 0;

    if (strlen(arg))
    {
	NFN("Purge what?");
	return 0;
    }

    old = sizeof(Owner);
    Owner = filter(Owner, &SECURITY->exist_player());
    save_object(SCABBARD_SAVE);

    write("The list of owners has been purged of players who do not exist anymore.\n" +
	  "Of " + old + " names, " + (old - sizeof(Owner)) + " have been removed.\n");
    return 1;
}
    
public void
init()
{
    int      rank;

    ::init();

    if (SECURITY->query_wiz_rank(TI->query_real_name()) < WIZ_STEWARD)
	return;

    add_action(restore, "restore");
    add_action(purge,   "purge");
}
