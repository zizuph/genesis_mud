/* Carridin */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit INNER_IN;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
    set_short("Post office in the Green Quarter");
    set_long("You are standing in a post office in the Green Quarter. " +
      "The room is circular, with an exit southeast to the street.\n");

	add_prop(ROOM_I_INSIDE, 1);	

    add_exit(NOUTER + "green/g5.c","southeast");
}

void
init()
{
    object mr;

    ::init();

    mr = clone_object("/secure/mail_reader");

    mr->move(TP, 1);
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

int
query_mail(int silent)
{
    string new;
    int mail;

    mail = MAILCHECKER->query_mail();

    if (!mail) return 0;

    if (silent) return 1;

    new = "";
    if (mail == 2) new = " NEW";
    if (mail == 3) new = " unread";

    write("\n" +
      "There is" + new + " mail for you in the " +
      "nearest post office.\n\n");

    return 1;
}
