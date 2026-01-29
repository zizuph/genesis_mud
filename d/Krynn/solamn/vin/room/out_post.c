/*
 * Post Office in VK
 * By Teth, Dec 7 1996
 */

#include "../local.h"

inherit IN_BASE;

#define MAILREADER_ID   "_reader_"
#define MAILREADER      "/secure/mail_reader"

public void
create_vin_room()
{
    set_short("Vingaard Keep Post Office");
    set_long("This is the general Vingaard Keep post office. " +
        "Members of the general populace and the militia use " +
        "this office for the handling of their daily mail. People " +
        "both send and read mail through the services of this " +
        "office. An exit leads east back to the street.\n");
    AI(({"ceiling","floor","wall"}),"It is made of cold hard stone. " +
        "No comforts are made available here for people to dilly-" +
        "dally and chat.\n");
    AI("walls","They are made of cold hard stone, nothing too " +
        "interesting.\n");
    AI(({"cold stone","stone","hard stone","cold hard stone"}),
        "It is dull-grey, perhaps volcanic in origin.\n");

    AE(VROOM + "es4", "east", 0);
}

void
init()
{
    object reader;

    ::init();

    if (!present(MAILREADER_ID, TP))
    {
        reader = clone_object(MAILREADER);
        reader->move(TP, 1);
    }
}

public void
leave_inv(object ob, object to)
{
    object reader;

    ::leave_inv(ob, to);

    reader = present(MAILREADER_ID, ob);

    if (reader)
        reader->remove_object();
}
                                          


