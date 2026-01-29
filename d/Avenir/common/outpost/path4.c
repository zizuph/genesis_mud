// file name: d/Avenir/common/outpost/path4.c
// creator(s):  Kazz    Jan '95
// last update: Boriska, Sep 95 added rider NPC
//              Cirion, Feb 96, removed the rider until something more
//                suitable can be found
// purpose:     final tunnel room, leading southeast to the fort cavern.
// note:
// bug(s):
// to-do:  

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

static object rider;

/*
void
reset_room() {
  if (!objectp(rider)) {
    rider = clone_object(OUTPOST + "mon/rider");
    rider->equip_me();
    rider->move(this_room());
  }
}
 */

void
create_room()
{
        SHORT("Tunnel by cavern");
	LONG("The tunnel ends to the southeast where a lit cavern can be "+
	     "seen. To the north west, the tunnel continues slightly "+
	     "uphill into darkness.\n" );

	add_exit(OUTPOST + "cave1","southeast",0);  // to fort cavern
	add_exit(OUTPOST + "path3","northwest",0);  // toward pier

	add_item(({"cavern"}),
		 "You can't see much except the cavern floor and shadows.\n");
	add_item(({"cavern floor"}),
		 "You will see better to the southeast.\n" );
	add_item(({"shadows"}),
		 "The shadows seem to be made by a slightly moving "+
		 "light source.\n" );

	ADD_TUNNEL_ITEMS;
		
	IN;
/*
	reset_room();
 */

} // create_room()

