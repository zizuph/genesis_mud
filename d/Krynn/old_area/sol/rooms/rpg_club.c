/*
 *
 */
#pragma strict_types

#include "local.h"

inherit "/std/room";

static void
load_board()
{
    clone_object(OBJ + "rpg_board")->move(TO);
}

public void
create_room()
{
    seteuid(getuid());
    
    set_short("A barly lit room");
    set_long("You are standing in a barly lit room. It is mostly empty " +
	     "except for the fine carpet and a bookcase. This is the room " +
	     "where the members of the RolePlaying Club gathers, to " +
	     "discuss the world and the behaviour of people. The members " +
	     "haven't bothered to decorate it since they are not here " +
	     "to often. They are instead spending their time exploring " +
	     "the world.\n");

    add_item(({"carpet", "rug"}), "It is an ancient carpet, donated by " +
	     "the creator of this room.\n");
    add_item(({"bookcase", "bookshelf"}), "It is almost empty, except for " +
	     "one book, and that one is chained to the wall.\n");

    load_board();
}

public int
do_rinvite(string str)
{
    object pl;
    
    CHECK_RPG_MEMBER

    notify_fail("Invite whom?\n");
    if (!str || !strlen(str))
	return 0;

    pl = find_player(str);
    if (!pl || !present(pl, this_object()))
	return notify_fail("The person you invite must be present.\n");

    if (present("_genesis_rpg_token_", pl))
	return notify_fail(QCTNAME(pl) + " is already a member.\n");

    this_player()->command("$snap");
    tell_room(this_object(), "A small symbol appears in " +
	      pl->query_possessive() + " hand.\n",
	      pl);

    pl->catch_msg("A small symbol appears in your hand.\n");

    clone_object(RPG_SYMBOL)->move(pl);
    return 1;
}

public void
init()
{
    add_action(do_rinvite, "rinvite");
    ::init();
}


