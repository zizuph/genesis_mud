/* Created by Macker 11/2/94 */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit ICEINROOM;

object bozak;

void
reset_icewall_room()
{
	if(!bozak)
	{
		bozak = clone_object(SPLAINS_L + "bozak.c");
		bozak->set_color("white");
		bozak->move(TO);
	}	
	return;
}

void create_icewall_room() {
   set_short("Storage Room");
   set_long("This is a large room with shelves on every wall. " +
		"This room was obviously a storage room at one " +
		"time, but now it appears to be empty.\n");
   add_item("shelves", "They line every wall in the room from " +
		"top to bottom. They look like they could support " +
		"quite a bit of weight, but right now they are empty.\n");

	/*Perhaps give them something if they search the shelves?*/
   add_exit(ICE_CAST2_R+"main_hall","east");

   reset_icewall_room();
}

