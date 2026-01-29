/*
 * Post Office in the Tower of Wayreth.
 *
 * By Rastlin 950523
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_tower_room()
{
    set_short("Post Office");
    set_long("You are standing in a small room with strong magical " +
	"power flowing all around you. This is the post " +
	"office of the Tower of Wayreth. Here you will be able to send " +
	"a mail and read your own mail. A small plaque is " +
	"attached to the east wall.\n");

    add_item(({"small plaque","plaque"}),"There are words on it.\n");

    add_cmd_item(({"plaque","words","small plaque"}),"read",
	"The following aliases are available here to mail to:\n" +
	"Conclave              : All current conclave members.\n" +
	"Guildmaster           : The guildmaster(s) of the Wizards " +
        "of High Sorcery.\n");


    add_exit(WTOWER + "study", "north", 0);
}

void
init()
{
    object mr;
    string *conclave = ({ });

    ::init();

    mr = clone_object("/secure/mail_reader");

    if(WOHS_MANAGER->query_is_council_black())
      conclave += ({ WOHS_MANAGER->query_is_council_black() });
    if(WOHS_MANAGER->query_is_council_red())
      conclave += ({ WOHS_MANAGER->query_is_council_red() });
    if(WOHS_MANAGER->query_is_council_white())
      conclave += ({ WOHS_MANAGER->query_is_council_white() });

    if (sizeof(conclave))
        mr->set_alias("conclave", conclave);

    if (sizeof(WIZ_GUILDMASTER))
        mr->set_alias("guildmaster", WIZ_GUILDMASTER);

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
	  "post office in the Tower of Wayreth.\n\n");

   return 1;
}                                                


