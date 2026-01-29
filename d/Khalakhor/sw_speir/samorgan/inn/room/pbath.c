/**********************************************************************
 * - pbath.c                                                        - *
 * - Public bathing area. It allows bathing (removes dirty prop) &  - *
 * - allows free emotes.                                            - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"
#include "fireplace1.c"
#include "bathing1.c"
#include "emotes.c"

public void
create_khalakhor_room()
{
	object coffer;
	object shelves;
	
	set_short("public bathing room");
	set_long("\n   Next to the archway leading back to the landing "+
	"is an inviting fire dancing within a large hearth. Logs "+
	"abundantly fill a firebox next to the fireplace with a "+
	"poker. Just across the room towards the south is a large "+
	"single window that along with a warm fireplace helps to "+
	"give an airy and relaxing atmosphere. A long set of shelves "+
	"line the western wall with a small sign with flowing script "+
	"dangling from it. Directly diagonal from the fireplace is "+
	"a small wooden coffer with a brass plaque. ");
	add_item(({"area", "spacious room", "bathing room", "room"}),
	"Next to the archway leading back to the landing is an "+
	"inviting fire dancing within a large hearth. Logs "+
	"abundantly fill a firebox next to the fireplace with a "+
	"poker. Just across the room towards the south is a large "+
	"single window that along with a warm fireplace helps to give "+
	"an airy and relaxing atmosphere. A long set of shelves line "+
	"the western wall with a small sign with flowing script "+
	"dangling from it. Directly diagonal from the fireplace is a "+
	"small wooden coffer with a brass plaque. A remarkably generous "+
	"tub dominates the center of this spacious room yet allows "+
	"space for a couple of wooden benches.\n");
	
	add_item(({"ceiling"}),
	"The ceiling is made of wooden beams.\n");
	add_item(({"floor", "flooring"}),
	"The flooring is made from highly polished wooden planks that "+
	"are seemlessly pressed together.\n");
	add_item(({"walls", "wall"}),
	"The walls are made from wood panels.\n");
	
	add_item(({"fireplace"}),
	"It is a moderate fireplace with a warm fire dancing within.\n");
	add_item(({"fire", "flame", "flames"}),
	"The fire dances with flickering flames along the logs.\n");
	add_item(({"log", "logs"}),
	"There are logs piled in a fireboax next to the fireplace.\n");
	add_item(({"firebox"}),
	"The firebox is squared and abundantly filled with logs.\n");
	add_item(({"box"}),
	"Which box do you wish to examine? The firebox or the coffer.\n");
	add_item(({"lanterns", "lantern", "brass lantern", "brass lanters"}),
	"These lanterns are made from brass and etched glass. They "+
	"are highly polished and not a speck of dust can be found on "+
	"their surface. They add to the d�cor of the landing and give "+
	"subtle but adequate lighting to the area.\n");
	add_item(({"bench", "benches"}),
	"The benches are wooden and used for sitting.\n");
	add_item(({"window"}),
	"The window adds a nice amount of warm light.\n");	
	add_item(({"attendent"}),
	"The attendent is quietly working.\n");
	
	add_item(({"bath", "tub", "bathtub", "bathing tub"}), bath_desc);
	add_my_desc(bath_desc, this_object());	

	coffer=clone_object(IOBJ + "coffer");
	coffer->move(TO);
	shelves=clone_object(IOBJ + "shelves");
	shelves->move(TO);	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	add_exit("landing", "north");
	add_fail("auto","You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");
}

void
init()
{
	::init();
	init_fire();
	init_bathing();
	init_emotes();

}
