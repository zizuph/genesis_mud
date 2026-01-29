
/*
 * The Post Office of rhe Halflings guild
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

#include "halflings.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>

inherit GUILD_ROOMS;
inherit "/d/Genesis/lib/post";

void reset_room()
{
    ::reset_room;
}

void 
create_guild_room()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    setuid();
    seteuid(getuid());

    set_short("Post Office");
    set_long("This is the post office of the Halflings. From here, Halflings " +
        "can send and receive messages from all over the world. A plaque " +
        "is attached to a wall with instructions for you to read.\n");

    add_cmd_item(({"plaque", "sign"}),"read","@@read_sign@@");

    reset_room();

    add_exit(HALFGLD_DIR + "rm_train", "south");
}

void 
init()
{
    ::init();
    post_init();
}

void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
    post_leave_inv(obj, to);
}

string
read_sign()
{
    return "\n\n"+
    "\t+---------------------------------------------------+\n"+
    "\t|                                                   |\n"+
    "\t|   These are some of the basic commands available. |\n"+
    "\t|   You should examine the mail reader for more     |\n"+
    "\t|   commands.                                       |\n"+
    "\t|                                                   |\n"+
    "\t|    * from [new]   List all [unread] headers       |\n"+
    "\t|    * read         Start up the mail reader        |\n"+
    "\t|                   command mode                    |\n"+
    "\t|    * read <msg>   Read message number <msg>       |\n"+
    "\t|                   from your mailbox               |\n"+
    "\t|    * mail <name>  Mail to player(s) <name>        |\n"+
    "\t|                                                   |\n"+
    "\t+---------------------------------------------------+\n\n";
}
