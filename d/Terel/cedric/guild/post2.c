#pragma save_binary

inherit "/std/room.c";
inherit "/d/Genesis/lib/post";

#include <std.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: Post Office
 * This room is like any other post office in the game.
 * Cedric 1/93
 */


int
check_enter()
{
    if (MEMBER(TP()))
    {
	return 0;
    }
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

public void
create_room()
{
    set_short("Guild postoffice");
    set_long(break_string("You are in the guild post office. This is a "+
	     "place of great magic! From here you can reach people with a "+
	     "written message, all over the world! Quite amazing.\n",76)+
        get_std_use());
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GUILD + "nice", "west", 0);
    add_exit(GUILD + "dorm", "southeast", check_enter);
}

init()
{
    ::init();
    post_init();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    post_leave_inv(ob, to);
}

public void
mail_message(string new)
{
    write("\n" +
	  "-------------------------------------------------------------\n" +
          "There is " + new + "mail for you in the post office of the Minstrels.\n" +
	  "-------------------------------------------------------------\n");
}

public void
add_aliases(object reader)
{
    string *members, *gms, *cycle;
    string security = SECURITY;

    setuid();
    seteuid(getuid());

    cycle = MEMBER_MANAGER->query_council_members();
    reader->set_alias("cycle", cycle);

    gms = SECURITY->query_guild_masters(GUILD_SHORT_NAME);
    reader->set_alias("guildmaster", gms);

    members = MEMBER_MANAGER->query_all_guild_members();
    dump_array(members);
    members = filter(members, &security->exist_player());
    dump_array(members);
    reader->set_alias("minstrels", members);
}
