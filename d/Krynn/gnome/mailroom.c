/* Code borrowed from Nick's Solamnic post office, altered by Grrrr */

inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <local.h>
#include <guild/guild.h>
#define MAILCHECKER     "/secure/mail_checker"
#define MAILREADER_ID   "_reader_"

string messages;
int new_mail;

void
create_room()
{
    set_short("The post office");
    set_long("This is the gnomish post office. Anyone is welcome to read "+
	     "and send mail here. You notice a sign behind the counter " +
	     "and wanted posters lining the walls.\n");
    INSIDE;
    LIGHT;
    
    add_item(({"poster", "posters"}), "@@wanted");
    add_item("sign", "@@read");
    add_cmd_item("sign", "read", "@@read");
    add_exit(STAND_DIR + "gnome/cavern9", "east", 0);
    add_exit(STAND_DIR + "gnome/living2", "west", 0);
}

void
init()
{
    object mr;
    ::init();
    mr = clone_object("/secure/mail_reader");
    mr->set_alias("guildmaster", GUILDMASTERS);
    mr->set_alias("mastergnome", ({ WIZARD_IN_CHARGE }));
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

string
wanted()
{
    string *list, str1, str2;
    int i;
    
    write("Many of the posters are old and faded, obviously of no " +
	  "interest. However, you do notice:\n\n");
    seteuid(getuid(TO));
    list = explode(read_file(STAND_DIR + "gnome/log/fight.log"), "\n");
    for (i = 0; i < sizeof(list); i++)
      {
	  sscanf(list[i], "%s %s", str1, str2);
	  write("A poster with a description of: a " + str2 + ".\n");
      }
    return "\nObviously a group of hardened criminals.\n";
}

string
read()
{
    string str;
    str = ("Welcome to the post office of the Hazardous Experiments "+
	   "division of Gnomish Industries. The commands you can use are:\n"+
	   "    read          - read your mail\n"+
	   "    mail <name>   - send a message to <name>\n" +
	   "    from          - get a list of your messages\n" +
	   "To mail the guildmaster of the race guild, or the master gnome " +
	   "of this area, send mail to 'guildmaster' or 'mastergnome', " +
	   "respectively.\n");
    return str;
}

tohelp()
{
    return "east";
}

int
query_mail(int silent)
{
    string new = "Read", str = "----";
    int mail;
    
    mail = MAILCHECKER->query_mail();
    if (!mail)
      return 0;
    if (silent)
      return 1;
    if (mail == 2) 
    {
	new = " New ";
	str = "-----";
    }
    if (mail == 3)
    {
    	new = "Unread";
	str = "------";
    }
    write("\n" +
	  "-------" + str + "--------------------------------------------------\n" +
	  "ThereIs" + new + "MailForYouInTheFantasticMailroomOnTheGroundLevelOf\n" +
	  "TheMountainWhichHasBeenSelectedToBeInhabitatedByGnomesAnd...\n" +
	  "-------" + str + "--------------------------------------------------\n\n");
   return 1;
}                                                
