/*

   Diamond. Post Office

    mail.c
    ------
    Coded .........: May 1997
    By ............: Kentari

    Latest Update .: May 1997
    By ............: Kentari 

 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <money.h>

inherit IN_BASE;

#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_dim_room()
{
    set_short("Post Office");
    set_long("This is the post office of the Diamond City, where you " +
	"can easily invite your friends to take part in the festivities, " +
	"wherever they may happen to be in the realms. There is a note " +
	"subtly hanging on the wall. Here you will be able to send " +
	"and read your own mail. A small plaque and a poster are " +
	"hanging on the wall.\n");

    add_item(({"small plaque","plaque"}),"There are words on it.\n");
    AI(({"note","subtle note","hanging","hanging note"}),
	"It simply reads: 'What are you waiting for, INVITE YOUR " +
	"FRIENDS!!'\n      Not so subtle after all.\n");
    ACI("note","read","It simply reads: 'What are you waiting for, " +
	"INVITE YOUR FRIENDS!!'\n       Not so subtle after all.\n");
    AI("poster","The poster reads:\n\nMessenger pigeons! 99 copper " +
	"coins each!\n\n");

    ACI("poster","read","The sign reads:\n\nMessenger pigeons! 99 " +
	"copper coins each!\n\n");
    add_cmd_item(({"plaque","words","small plaque"}),"read",
		 "The following aliases are available here to mail to:\n" +
		 "Tapmaster           : The creator and supervisor(s) of Diamond Isle.\n");

    add_exit(DIROOM + "nw2", "southeast", 0);
}

void
init()
{
    object mr;

    ::init();
    ADA("buy");

    mr = clone_object("/secure/mail_reader");

    if (sizeof(TAPMASTERS))
        mr->set_alias("tapmaster", TAPMASTERS);

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
	  "post office of Diamond City.\n\n");

   return 1;
}                                                

buy(str)
{
    object pig,who;
    NF("Buy what did you say?\n");
    if (!str || (str != "pigeon"))
        return 0;

    NF("You cannot pay the price!\n");
    if (!MONEY_ADD(TP, -99))
        return 0;   
    write("You make your purchase, and suddenly a pigeon flies inside " +
	"and lands on your shoulder, gets ready to poop on you, and is " +
        "promptly stopped and put into your inventory.\n");
    say(QCTNAME(TP) + " catches a pigeon as it flies in from outside.\n");

    who = TP;
    pig = clone_object(DINPC + "pigeon");
    pig->set_owner(who);
    pig->move(who);
    return 1;
}
