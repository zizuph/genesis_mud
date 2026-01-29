/* 
* Post Office in the Tower of Wayreth.
* By Rastlin 950523
* Kendermore Post Office - Gwyneth, May 1999
*/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit KENDERMORE_OUT;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
    set_short("A dusty post office");
    set_long("@@long_descr");

    add_exit(KROOM + "street16.c", "west", 0);
    add_exit(KROOM + "pigeon_coop.c", "southwest", 0);
    add_item(({"table", "tables", "dusty tables"}), "There are quills, " + 
        "paper and inkpots chained to the tables.\n");
    add_item("roof", "There is no roof!\n");
    add_item(({"inkpots", "inkpot", "paper", "quill", "quills"}), "You can " + 
        "use them to write mail.\n");
}

string
long_descr()
{
    return(tod_descr() + season_descr() + "A few dusty tables decorate the " + 
        "room, but it doesn't look used very often. The room has been " + 
        "mostly built, well except for the roof, a minor oversight by " + 
        "kender standards.\n");
}

void
init()
{
    object mr;

    ::init();
    
    if (!interactive(TP))
        return;

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
