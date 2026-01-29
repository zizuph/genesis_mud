inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"
#define MAILREADER	"/d/Genesis/obj/mail_reader"

string messages;
int new_mail;

create_room() 
{
    set_short("The Post Office");
    set_long(break_string(
"This is truly an amazing place.  From this room you can reach any player " +
"anywhere in the game.  Thieves (and others) can be informed of your plans " +
"ahead of time, if you wish.  This is the best invention for planning " +
"dastardly deeds since explosives.\n", 78) +
"Commands are:\n" +
"     read              Read your mail.\n" +
"     mail <name>       Mail to player <name>.\n" +
"     from              List all headers.\n");

    add_exit(G_ROOMS + "ghall2", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

void
init() 
{
    object reader;
    ::init();

    reader = clone_object(MAILREADER);
    if (!reader) {
	write("No mailreader is available at this time.\n");
	return;
    }
    reader->move(this_player());
}

leave_inv(ob, to) {
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}

query_mail(silent) {
    string name, new, sp;

    name = lower_case(call_other(this_player(), "query_name"));
    if (!restore_object("d/Genesis/post_dir/" + name) || messages == "")
       return 0;
    if (silent) return 1;
    new = ""; sp = "    ";
    if (new_mail) {
	new = " NEW";
	sp = "";
    }
    write("\n"+
        "     +-------------------------------------------------------+\n"+
        "     ! There is" + new + " mail for you in Sparkle post office. "+
        sp +"    !\n"+
        "     ! (North end of the road just inside the village gate.) !\n"+
        "     +-------------------------------------------------------+\n");
    return 1;
}


