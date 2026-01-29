/* Tyr delivery office */
 
/* /d/Genesis/delivery/example_office.c
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 06/07/95
 * Updated the sign and exit Damaris 5/2001
 * Updated the sign and fixed my update of the exit. Damaris 02/2006
 */
 
#include "/d/Genesis/delivery/delivery.h"
 
#pragma save_binary
#pragma strict_types
 
inherit DELIVERY_OFFICE;
inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std"; 
#include "defs.h"


public string
delivery_poster()
{
	return ("           +----------------------------------------+\n"+
	"           |             Delivery Office            |\n"+
	"           |----------------------------------------|\n"+
	"           |                                        |\n"+
	"           | To earn a few coins and some general   |\n"+
	"           | experience. 'ask for a delivery tour'. |\n"+
	"           |                                        |\n"+
	"           | Deliver the packet you receive to it's |\n"+
	"           | destination where you will also receive|\n"+
	"           | the payment.                           |\n"+
	"           |                                        |\n"+
	"           | Use 'deliver packet' to deliver your   |\n"+
	"           | packet at it's destination.            |\n"+
	"           |                                        |\n"+
	"           | 'return packet' is for packets which   |\n"+
	"           | are not destined for this office and   |\n"+
	"           | which do not have this office set as   |\n"+
	"           | origin.                                |\n"+
	"           +----------------------------------------+\n");
}
void
reset_room()
{
	reset_office();
}
 
string
the_last_room()
{
	return (this_player()->query_prop(LIVE_O_LAST_ROOM));
}
 
void
create_room()
{
	::create_room();
	set_short("the Traders' Hall of Tyr");
	set_office("the Traders' Hall of Tyr",6);
	set_long("This warehouse is a chaotic mix of frenzied activity "+
	"and absolute calm. Scurrying traders work swiftly to load up "+
	"their beasts of burden with the more valuable cargo, while "+
	"boxes of yesterday's forgotten trinkets collect dust in the "+
	"corner. A dirt-caked sign leans haphazardly against a broken "+
	"inix howdah.\n");
	add_item(({"poster","sign"}), &delivery_poster());
	add_item(({"howdah","inix howdah","broken inix howdah","broken howdah"}),
	"It appears the inix it was attached to decided to scratch "+
	"its back on a rocky outcropping. The rider's blood-stains "+
	"can still be made out.\n");
	add_item(({"boxes","box","trinkets","trinket","yesterday's forgotten trinkets","forgotten trinkets"}),
	"Perhaps someone will offer you a few coins to haul it out "+
	"of here.\n");
	add_item("dust","Life is filled with such constant thrills.\n");
	add_item(({"traders","trader","scurrying traders"}),
	"They seem to busy to take much notice of interlopers.\n");
	add_item(({"beasts","beast","beasts of burden"}),
	"Erdlu, crodlu, inix, mekillots, and more exotic animals: "+
	"Anything that can carry a weight is pressed into service.\n");
	add_item(({"cargo","valuable cargo"}),
	"A shame you won't see any.\n");
	add_exit("@@the_last_room@@","leave",0,1,0);
}
int
do_read(string str)
{
	if (str != "sign")
	{
		notify_fail("Read what?\n");
		return 0;
	}
	write("A sun-bleached human female interupts you: 'I wouldn't "+
	"advise that my friend. The last person caught reading that "+
	"sign was dragged away by an invisible Templar.\n");
	return 1;
} 
void
init()
{
	/* give the commands for the office */
	init_office();
	::init();
	add_action(do_read, "read");
}
