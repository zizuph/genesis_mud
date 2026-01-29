/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>

inherit TEMPLE_BASE;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You stand within a small post office in the temple. Here " +
    "the members of the guild can read and write letters at their " +
    "convenience. There is a doorway to the north, leading out to " +
    "a corridor.\n";
}

void
create_neraka_room()
{
    set_short("a post office in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");

    add_item("corridor","The corridor to the north leads east to west.\n");

    reset_room();

    add_exit(NTEMPLE + "d1", "north");
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
      "You have" + new + " mail in the post office in the Temple " +
      "of Takhisis.\n\n");

    return 1;
}
