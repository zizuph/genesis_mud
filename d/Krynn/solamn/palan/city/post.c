/* post.c made by Nick
 * adjustments to the new mailreader by Aridor, 09/94
 */

#include "../local.h"

inherit ROOM_BASE

#define MAILREADER_ID   "_reader_"

string
query_to_jail()
{
    return "north";
}

void
create_palan_room()
{
    set_short("The Post Office");
    set_long("This is the local post office. Here you can check who you " +
	     "have mail 'from', and read the letters with 'read n', where " +
	     "n is the number of the letter. You can also send mail to " +
	     "other players with 'mail <player>'. To send mail to the " +
	     "Lord and Mayor of Palanthas and its surrounding areas, use " +
	     "'mail mayor'.\n");
    
    add_exit(ROOM + "street8", "north", 0);
}

void
init()
{
    object mr;
    ::init();
    mr = clone_object("/secure/mail_reader");
    mr->set_alias("mayor", ({ WIZARD_IN_CHARGE }));
    mr->move(this_player(), 1);
}

void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);

    reader = present(MAILREADER_ID, ob);
    if (reader)
      reader->remove_object();
}

