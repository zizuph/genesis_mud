/* post.c made by Nick
 * adjustments to the new mailreader by Aridor, 09/94
 *
 * Modification log:
 *   - Aug 27, 2018: Added no-scry protection in guild (Gorboth)
 */

#include "guild.h"

inherit ROOM_BASE

#include <stdproperties.h>

#define MAILCHECKER "/secure/mail_checker"
#define MAILREADER_ID     "_reader_"

string messages;
int new_mail;

void
create_thief_room()
{
    set_short("The private chamber");
    set_long("You are in the private chamber of the Cabal of Hiddukel. " +
	     "Here you can send private notes to other thieves and " +
	     "blackmail other players. Also you can read those notes " +
	     "you received from others. To contact the guildmaster of " +
	     "the Cabal, send mail to 'guildmaster'. Use 'rsend ringleader' " +
	     "if you want to get in contact with the Ringleader of the Cabal. " +
	     "Use 'rread' to read any messages from the Ringleader.\n@@check_rmail@@");
    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    INSIDE;
    LIGHT;
    add_exit(GUILDR + "start", "south");
}

void
init()
{
    object mr;
    ::init();
    ADA("send");
    ADD("send","blackmail");
    ADA("rread");
    ADA("rsend");
    mr = clone_object("/secure/mail_reader");
    mr->set_alias("guildmaster", GUILDMASTERS);
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
   write("\n" +
        "There is" + new + " mail for you in the " +
	"mail chamber in the Cabal of Hiddukel.\n");
   return 1;
}

string
check_rmail()
{
    if (POSTMASTER->has_mail(TP))
      return "\nYou have mail from the Ringleader, please use the 'rread' command!\n";
    return "";
}

int
rread(string str)
{
    int num;
    mixed flag;

    if (!MEMBER(TP) && member_array(TP->query_name(),GUILDMASTERS) < 0)
      return 0;
      
    NF("Rread what?\n");
    if (!str || str == "")
      return POSTMASTER->check_mail(TP);

    if (sscanf(str,"%d %s",num,flag) == 2)
      return POSTMASTER->read_mail(TP,num,flag);
    
    if (sscanf(str,"%d",num) == 1)
      return POSTMASTER->read_mail(TP,num,0);

    return 0;
}

int
rsend(string str)
{
    if (!MEMBER(TP) && member_array(TP->query_name(),GUILDMASTERS) < 0)
      return 0;
      
    NF("Rsend to who?\n");
    if (L(str) != "ringleader")
      return 0;

    return POSTMASTER->send_mail(TP,"ringleader");
}

int
send(string str)
{
    return TP->command("mail " + str);
}
