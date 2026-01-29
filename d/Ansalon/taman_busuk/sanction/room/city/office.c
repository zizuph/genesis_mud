#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/guild/dragonarmy/guild.h"

inherit SANCINROOM;

string read_sign();

object clerk;

reset_sanction_room()
{
    if(!objectp(clerk))
    {
	clerk = clone_object(SNPC + "clerk");
	clerk->move(TO);
    }
}

void
create_sanction_room()
{
    set_short("Inside a military dispatch office.\n"+
      "A recruitment poster is tacked onto a wall here");
    set_long("@@long_descr");

    add_item(({"requisitions","orders","directives","requests",
	"reports","records"}),
      "Various military transcripts find themselves orderly " +
      "piled up on desks, pinned to boards or filed away here.\n");
    add_item(({"harried staff","staff","officers"}),
      "A harried staff of office employees of the dragonarmy " +
      "work around the clock with speedy efficiency to keep " +
      "track of the vast expansion of the Dragon Empire.\n");
    add_item(({"poster","recruitment poster"}),
      "A recruitment poster has been tacked on the wall " +
      "here.\n");

    add_cmd_item("poster","read","@@read_poster");


   add_item(({"sign","small sign"}),
       "@@read_sign");

   add_cmd_item(({"sign","small sign"}),
       "read",
       "@@read_sign");

    add_exit(SCITY + "yard","west",0);
    add_exit(SCITY + "po","south","@@enter_po");
    add_exit(SCITY + "archive","east","@@enter_archive");

    reset_sanction_room();
}

int
enter_archive()
{
    if(objectp(clerk) && (E(clerk) == TO) &&
      TP->query_alignment() > -100)
    {
	clerk->command("say Hey! Keep away from there!");
	write("The busy clerk stops you from entering " +
	  "the archive to your east.\n");
	say(QCTNAME(TP)+ " is stopped from going east by "+
	  "the busy clerk.\n");
	return 1;
    }
    return 0;
}

int
enter_po()
{
    if(TP->query_dragonarmy_occ_member() ||
       TP->query_guild_member("Priests of Takhisis") ||
       TP->query_wiz_level())
    {
	write("You pass into the main dispatch office.\n");
	return 0;
    }
    write("Only members of the dragonarmy may enter the " +
      "main dispatch office!\n");
    return 1;
}

string
read_sign()
{
    if (!TP->query_dragonarmy_occ_member())
        return "You are unable to read the sign.\n";

    return "The sign reads:  To take over for an inactive General, "+
       "use <assume command>.\n";
}

string
read_poster()
{

    write("\n"+


      "    ------------------------------------------------\n"+
      "   /                                               |\n"+
      "   |  *                                        *   |\n"+
      "   |                                               |\n"+
      "   |             RECRUITING NOW!                   |\n"+
      "   |                                               |\n"+
      "   |                                               |\n"+
      "   |      With the return of Takhisis, Queen of    |\n"+
      "   |      Darkness, with her children the fabled   |\n"+
      "   |      dragons once again spreading their shadow|\n"+
      "   |      over the lands of Ansalon, armies gather |\n"+
      "   |      in a bid for conquest and glory in Her   |\n"+
      "   |      name.                                    |\n"+
      "   |      For the mighty, the strong, and the      |\n"+
      "   |      cunning, a place may be found amongst    |\n"+
      "   |      Her glorious ranks. Inquire here at the  |\n"+
      "   |      clerk for more details.                  |\n"+
      "   |                                               |\n"+
      "   |                                               |\n"+
      "   |      Presently recruiting:                    |\n"+
      "   |          The Red Dragonarmy.                  |\n"+
      "   |          The Blue Dragonarmy.                 |\n"+
      "   |                                               |\n"+
      "   |   *                                       *   |\n"+
      "   |_______________________________________________|\n"+
      "\n");
    return "";
}

string
long_descr()
{
    return "This small office is the second home to a " +
    "rather harried staff of officers. Military requisitions, " +
    "orders, directives, requests and reports are received, " +
    "recorded and filed here with speedy efficiency.  "+
    "A small sign is posted.\n" +
    "A recruitment poster is tacked onto a wall here.\n";
}

int
assume(string str)
{
    if (!TP->query_dragonarmy_occ_member())
    {
        notify_fail("You are no Dragonarmy member!\n");
        return 0;
    }

    // Must be officer rank or higher to assume command
    if(TP->query_dragonarmy_promotions() < 2)
    {
        notify_fail("Only officers can assume command of the " +
            "Dragonarmies!\n");
        return 0;
    }
    
    if (!strlen(str) || !(str == "command")) {
        notify_fail("Assume command?\n");
        return 0;
    }

    if (!MANAGER->check_replace_leader(TP)) {
        notify_fail("You are unable to assume command.  "+
            "The current General "+
            "must have not logged in for 14 days for someone else "+
            "to take charge.\n");
        return 0;
    }

    write("You assume command as General of the "+
        capitalize(TP->query_dragonarmy_division())+" Dragonarmy!\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(assume, "assume");
}
