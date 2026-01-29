#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"
#define VOTING_BOX      VOBJ + "voting_box"
#define ADMIN "/d/Krynn/solamn/vin/knight/admin/admin.c"
#define GUILDMASTERS ({ "Aridor", "Morrigan" })

inherit FOREST_IN;

string messages;
int new_mail;

void
create_flotsam_room()
{
    set_short("The Post Office");
    set_long("A few desks fill this otherwise plain room. On "+
      "the desks are writing utencils and paper on which to write "+
      "letters. You notice a few Knights doing just that, and "+
      "make a mental note to keep quiet, so as not to disturb them. "+
      "A small plaque is fastened to one wall.\n");

    add_item(({ "desk", "desks"}), "The desks are there to be sat at if "+
      "you want to write a letter to someone.\n");
    add_item(({"small plaque","plaque"}),"The small plaque has words on it.\n");
    add_cmd_item(({"plaque","words","small plaque"}),"read",
      "The following aliases are available here to mail to:\n" +
      "Grandmaster           : The Grand Master of the Knights.\n" +
      "Conclave              : All current conclave members and the Grand Master.\n"+
      "Rose                  : The Rose conclave and council.\n" +
      "Sword                 : The Sword conclave and council.\n" +
      "Crown                 : The Crown conclave and council.\n" +
      "Council               : All members of the Knight conclave "+
      "and councils and the Grand Master.\n" +
      "Guildmaster           : The guildmaster of the Knights.\n");
    add_exit(FROOM + "startroom", "north");
}

void
init()
{
    object mr;
    string ro = (ADMIN)->query_conclave("rose"),
    sw = (ADMIN)->query_conclave("sword"),
    cr = (ADMIN)->query_conclave("crown"),
    gm = (ADMIN)->query_grandmaster();
    string *rose = (ADMIN)->query_assistants(5),
    *sword = (ADMIN)->query_assistants(4),
    *crown = (ADMIN)->query_assistants(3);
    string *conclave = ({ }),
    *council;
    if (ro && stringp(ro) && ro != "")
	conclave += ({ ro });
    if (sw && stringp(sw) && sw != "")
	conclave += ({ sw });
    if (cr && stringp(cr) && cr != "")
	conclave += ({ cr });
    if (gm && stringp(gm) && gm != "")
	conclave += ({ gm });
    council = conclave;
    ::init();
    mr = clone_object("/secure/mail_reader");
    if (gm && stringp(gm) && gm != "")
	mr->set_alias("grandmaster", ({ gm }));
    if (conclave)
	mr->set_alias("conclave", conclave);
    if (rose && sizeof(rose))
    {
	mr->set_alias("rose", rose);
	council += rose;
    }
    if (sword && sizeof(sword))
    {
	mr->set_alias("sword", sword);
	council += sword;
    }
    if (crown)
    {
	mr->set_alias("crown", crown);
	council += crown;
    }
    if (council && sizeof(council))
	mr->set_alias("council", council);
    if (GUILDMASTERS)
	mr->set_alias("guildmaster", GUILDMASTERS);
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
