/* File         : /d/Terel/calathin/caravan_office.c
 * Creator      : Pasqua	
 * Date         : April 2000         
 * Purpose      : Caravan Office in Calathin
 * Related Files: 
 * Comments     : 
 * Modifications:
 */

#include "/d/Terel/include/Terel.h"

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

inherit STDROOM;

inherit "/d/Terel/std/room_tell.c";

#define CARAVAN_START SILVER_DIR + "road/road02"

public void
create_room()
{
   ::create_room();
   set_short("Caravan Office in Calathin");
   set_long("This is the Office of the Caravan. The purpose of this office " +
        "is to ordinate the paperwork and handle the administration of the " + 
	    "transportation that the merchant and his caravan have between Calathin " +
	    "and The Last. Behind the marble table in front of you, a hardworking receptionist " +
	    "is seated. A few metres behind to the left of him, is the economical assistant seated " +
	    "at a counter. A few bookcases line most of the walls in this office. Outside the " +
	    "office a black obsidian obelisk can be seen at the crowded town square.\n");

   add_exit(CALATHIN_DIR + "square3_1", "south", 0);

   set_tell_time(300 + random(300));
   add_tell("An errand boy enter the office and places a turkey pie on the table. " +
	        "The receptionist cracks a smile and says 'Thank you! could you send this " +
	        "report of successfully delivered goods to the Office in The Last' " +
            "to the boy and gives him a report before he leaves.\n");
   add_tell("The receptionist observes a card which upon inspection seems to be " +
	        "the agenda of the daily routines of the office.\n");
   add_tell("The receptionist mumbles something about the good relationship between " +
	        "Calathin and The Last.\n");
   add_tell("A caravan member arrives and leaves a report on the table. The " +
	        "receptionist seems satisfied by the recieved report and " +
	        "says 'Yet another succesful delivery of goods to us, send the " +
	        "regards of mine to the Merchant and your caravan' as he shakes the " +
	        "hand of the caravan member before he leaves.\n");

   add_item(({"table","marble table","marbletable"}),"The table is made out of " +
    	"marble that has been hewn in a regular rectangular shape. Two heaps of " +
		"papers are organized in the middle of the table and next to them on the " +
		"right a silver labeled notebook is placed.\n");
   add_item(({"bookcase","bookcases","book cases"}),"The bookcases are lining most of " +
	    "the walls in the room, they are semi full, but with all the reports coming " +
	    "in about the exported and imported goods they will surely be full soon.\n");
   add_item(({"imported goods","imported"}),"The reports with the label 'Imported' gives " +
	    "you the information that the imported goods are: gold, silver and various animal " +
	    "furs and other misc goods.\n");
   add_item(({"counter","assistant's counter"}),"Its a regular counter made out of pure oak, " + 
	    "stacks of papers with written numbers on them can be seen on the table, they dont " +
	    "seem to be very systemized by the first peek.\n");
   add_item(({"exported goods","exported"}),"The reports with the label 'Exported' gives " +
	    "you the information that the exported goods are: tools, weapons and armours.\n");
   add_item(({"papers","paper","heap of papers","heaps of papers"}),"The two heaps " +
	    "seems to be the reports of incoming and outgoing goods of Calathin.\n");
   add_item(({"notebook","silver labeled notebook","silver notebook"}),"The notebook " +
	    "is labeled in silver and it seems like the citizens of Calathin have signed " +
	    "it to show their appreciation of the new Caravan Office and the tradeline " +
	    "between Calathin and The Last.\n");
   add_item(({"wall","walls"}),"The walls are made out of stone but the outer layer of the wall " +
	    "got a newly made bonewhite wallpaper, but most of the walls are covered by the bookcases.\n");
   add_item(({"window","windows"}),"The windows are painted in silver, yet they seem really clean. " +
        "You can see the obelisk and the town square as good through them as you see through the " +
		"open entry of this office.\n");
   add_item(({"stool","stools"}),"The stools doesn't seem comfortable, but the employee here doesn't " +
	    "seem to mind that at all as they are to busy thinking about more important issues than the " +
	    "stools cosiness.\n");
   add_item(({"receptionist","hardworking receptionist"}),"The hardworking receptionist sits at his " +
	    "marble table on a stool doing the daily routines as the administrative worker at this office.\n");
   add_item(({"assistant","economical assistant"}),"The economical assistant seems to be in charge " +
	    "of counting and handling the economical values of the imported and exported goods, he seems " +
	    "like he's really busy with his work.\n");

   add_cmd_item(({"notebook","silver labeled notebook","silver notebook"}), "read","@@read_book");
   add_npc(CALATHIN_DIR + "npc/clerk");

   

}

int
read_book()
{
    write("You open the silver labeled notebook and read.\n");
	write("+------------------------------------------------------+\n");
	write("| If you like what we're doing, please sign this book! |\n");
	write("+------------------------------------------------------+\n");
	write("| - April 1st Delsanora wrote:                         |\n");
	write("|   The people from The Last rarely rest a night at my |\n");
	write("|   inn anymore, but it must be a relief for them to   |\n");
	write("|   not have to travel to Calathin and trade anymore.  |\n");
	write("|              / Delsanora from Silver Tree Inn.       |\n");
	write("+------------------------------------------------------+\n");
	write("| - April 2nd Jenna wrote:                             |\n");
	write("|   I am so thankful for the tradingline between our   |\n");
	write("|   cities.. the merchant and his caravan tips me great|\n");
	write("|   when they visit.. if you haven't tasted the food at|\n");
	write("|   our Inn yet, please come and do so!!               |\n");
	write("|              / Jenna from the Calathin Inn.          |\n");
	write("+------------------------------------------------------+\n");
	write("| - April 2nd Leah wrote:                              |\n");
	write("|   I just love that the Merchant and his caravan have |\n");
	write("|   started the goodstrading between the cities, could |\n");
	write("|   it be possible to send some shots of sinvon's up to|\n");
	write("|   that cold city up north some day?                  |\n");
	write("|              / Leah From Our Beloved Big Rock Pub!   |\n");
    write("+------------------------------------------------------+\n");
    say(QCTNAME(TP) + " studies the notebook.\n");
}

public void init()
{
        ::init();
        start_room_tells();
	//(CARAVAN_START)->caravan_block();

}
