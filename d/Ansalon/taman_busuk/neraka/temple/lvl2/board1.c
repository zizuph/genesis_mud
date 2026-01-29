/* This room is supposed to be the main boardroom for the PoT
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    ::create_temple_room();

     set_short("The board room");
    set_long("This room is very bare and empty except for one large board " +
        "on the opposite side of the room from the entrance. Beside it is " +
        "a small wooden holder and a quill hanging from a delicate chain.  "+
        "A small sign is here.\n");

    add_item(({"quill"}), "Made of the feather of a griffon and fastened " +
        "in the small wooden holder, it is an instrument of writing " +
        "to use when scribing notes on the board.\n");
    add_item(({"small wooden holder", "small holder", "wooden holder",
        "holder"}), "It is an unadorned and practical holder for the " +
        "quill that has been fastened in a chain to it.\n");
    add_item(({"delicate chain", "chain"}), "Each ring in the metal " +
        "chain is about the diameter of a ring that only a child " +
        "could bear. It keeps the quill to the small wooden holder.\n");

   add_item(({"sign","small sign"}),
       "The sign reads:\n  To take over for an inactive guild leader, "+
       "use <assume leadership>.\n");

   add_cmd_item(({"sign","small sign"}),
       "read",
       "The sign reads:\n  To take over for an inactive guild leader, "+
       "use <assume leadership>.\n");

   setuid();
    seteuid(getuid());

    clone_object(GUILDDIR + "obj/guild_board")->move(this_object());

    add_exit( LVLTWO + "library.c", "northeast" );
}

int
assume(string str)
{
    object who = this_player();

    if (!strlen(str) || !(str == "leadership")) {
        notify_fail("Assume leadership?\n");
        return 0;
    }

    if (!GUILD_ADMIN->check_replace_leader(who)) {
        notify_fail("You are unable to assume leadership.  The current guild leader "+
            "must have not logged in for 22 days for someone else "+
            "to take over.\n");
        return 0;
    }

    write("You assume leadership of the Priesthood of Takhisis!\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("assume","assume");
}
