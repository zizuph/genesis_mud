/* post.c made by Nick
* adjustments to the new mailreader by Aridor, 09/94
*/

#include "../../guild.h"
#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"
#define VOTING_BOX      VOBJ + "voting_box"

inherit IN_BASE;

string messages;
int new_mail;

void
create_vin_room()
{
    set_short("The Study");
    set_long("You are in the study of the Solamnian Knights. " +
        "This is where members of the guild receive and send " +
        "correspondence. Instead of rock, the entire room is " +
        "covered with hardwood, which was most likely placed over " +
        "the rock. A small plaque is fastened to one wall.\n");

    AI("walls","They are covered with hardwood.\n");
    AI(({"floor","ceiling","wall"}),"It is covered with a varnished " +
        "hardwood.\n");
    AI("varnish","The varnish is most likely shellac, a beetle derivative.\n");
    AI(({"wood","hard wood","hardwood"}),"The wood is definitely " +
        "birch, light in colour with the occasional wisp of red.\n");
    AI("birch","Most likely from the forests surrounding Palanthus is its " +
        "origin.\n");
    AI(({"small plaque","plaque"}),"The small plaque has words on it.\n");
    ACI(({"plaque","words","small plaque"}),"read",
        "The following aliases are available here to mail to:\n" +
    "Grandmaster           : The Grand Master of the Knights.\n" +
        "Conclave              : All current conclave members and the Grand Master.\n" +
        "Rose                  : The Rose conclave and council.\n" +
        "Sword                 : The Sword conclave and council.\n" +
        "Crown                 : The Crown conclave and council.\n" +
        "Council               : All members of the Knight conclave "+
        "and councils and the Grand Master.\n" +
        "Guildmaster           : The guildmaster of the Knights.\n");
    AE(VROOM + "north_hallway", "east", 0);
    clone_object(VOTING_BOX)->move(TO);
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
    {
      conclave += ({ ro });
      rose += ({ ro });
    }
    if (sw && stringp(sw) && sw != "")
    {
      conclave += ({ sw });
      sword += ({ sw });
    }
    if (cr && stringp(cr) && cr != "")
    {
      conclave += ({ cr });
      crown += ({ cr });
    }
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
        council += rose;
        mr->set_alias("rose", rose);
    }
    if (sword && sizeof(sword))
    {
        council += sword;
        mr->set_alias("sword", sword);
    }
    if (crown)
    {
        council += crown;
        mr->set_alias("crown", crown);
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

int
query_mail(int silent)
{
    string new;
    int mail;

    mail = MAILCHECKER->query_mail();
    if (!mail)
        return 0;
    if (silent)
        return 1;
    new = "";
    if (mail == 2)
        new = " NEW";
    if (mail == 3)
        new = " unread";
    write("\nWelcome Knight of Solamnia!\n\n" +
        "There is" + new + " mail for you in the " +
        "post office in Vingaard Keep.\n");
    return 1;
}

