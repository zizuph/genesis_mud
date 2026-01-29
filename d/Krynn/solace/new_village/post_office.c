/*
 * Post Office of Solace
 *
 * By Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "local.h"

inherit SOLINROOM;

#define MAILREADER_ID   "_reader_"
#define MAILREADER      "/secure/mail_reader"

public void
create_solace_room()
{
    set_short("The post office");
    set_long("You are standing inside a rather large wooden building. " +
	     "It is the local post office, where you are able to send " +
	     "and read your mail. On the far side is a wooden plaque " +
	     "attached to the wall.\n");

    add_item("plaque", "There are words on it, maybe you should read it.\n");

    add_cmd_parse("[the] [wooden] 'plaque'", "read",
		 "The following alias is available here to mail to:\n" +
		 "  conclave              : The Wizards of High Sorcery leadership.\n" +
		 "  responsible           : The wizard responsible for " +
		 "Solace.\n");

    add_exit(TDIR + "bridge_walk14", "north");
}

void
init()
{
    object reader;
    string *conclave = ({ });

    ::init();

    if(WOHS_MANAGER->query_is_council_black())
      conclave += ({ WOHS_MANAGER->query_is_council_black() });
    if(WOHS_MANAGER->query_is_council_red())
      conclave += ({ WOHS_MANAGER->query_is_council_red() });
    if(WOHS_MANAGER->query_is_council_white())
      conclave += ({ WOHS_MANAGER->query_is_council_white() });

    if (!present(MAILREADER_ID, TP))
    {
        reader = clone_object(MAILREADER);
        reader->set_alias("responsible", RESPONSIBLE);
        if (sizeof(conclave))
            reader->set_alias("conclave", conclave);
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
                                          


