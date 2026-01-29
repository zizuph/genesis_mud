/**********************************************************************
 * - room8.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"
#include "fireplace.c"
#include "seating.c"

void
create_khalakhor_room()
{
	object coffer;
	set_short("a quiet room");
	set_long("\n   The fireplace in the northern wall is quite "+
	"striking with skillfully carved white molding making up a "+
	"substantial mantle. Between the door and the fireplace is "+
	"a special holder for a fireplace poker and a coffer for "+
	"holding other items. The room is quite spacious with many "+
	"items filling the room so to give it a relaxing atmosphere. ");
	
	add_item(({"window"}),
	"There is a single window placed in the western wall with "+
	"a light covering.\n");
	add_item(({"light covering", "covering", "curtain"}),
	"This light covering is draped softly over the window to "+
	"obscure some of the light.\n");
	add_item(({"light"}),
	"Light gently cascades from the window along with the "+
	"brass lanterns.\n");
	
	add_item(({"log", "logs"}),
	"There are logs piled in a fireboax next to the fireplace.\n");
	add_item(({"firebox"}),
	"The firebox is squared and abundantly filled with logs.\n");
	add_item(({"box"}),
	"Which box do you wish to examine? The firebox or the coffer.\n");
	add_item(({"holder", "special holder"}),
	"A poker is resting in a special holder next to the fireplace "+
	"so you may stoke the fire.\n");
	add_item(({"poker", "fireplace poker"}),
	"This poker is used to stoke up the fire nicely.\n");
	add_item(({"fireplace"}),
	"The fireplace is in the northern wall and is quite "+
	"striking with skillfully carved white molding.\n");
	add_item(({"fire", "flames", "flame"}),
	"The fire dances along the logs giving warmed and light to "+
	"the area.\n");
	add_item(({"mantle"}),
	"The skillfully carved molding makes quite a striking mantle.\n");
	add_item(({"molding", "white molding"}),
	"The molding is white and skillfully carved to present a "+
	"striking contrast to the fireplace.\n");
	add_item(({"wooden floor", "floor", "flooring"}),
	"The flooring is made from joined planks of polished wood.\n");
	add_item(({"wood", "polished wood"}),
	"Some of the wood used here is highly polished and in very "+
	"good condition.\n");
	add_item(({"ceiling"}),
	"The ceiling is open with beams running crossways and isn't "+
	"really much to look at.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from wooden panels.\n");
	add_item(({"lanterns", "lantern", "brass lantern", "brass lanters"}),
	"These lanterns are made from brass and etched glass. They "+
	"are highly polished and not a speck of dust can be found on "+
	"their surface. They add to the d�cor of the hallway and give "+
	"subtle but adequate lighting to the area.\n");
	add_item(({"cushion", "cushions"}),
	"The cushions are vibrant and plush with gold and emerald "+
	"threads woven in intricate patterns.\n");
	add_item(({"bed", "plush bed", "four poster bed"}),
	"This in an elaborate four poster bed with plush bedding "+
	"that beckons to be laid upon or even sit on it's edge.\n");
	add_item(({"skin", "rug", "animal skin"}),
	"This animal skin rug spreads out before the fire invitingly. "+
	"It is quite soft and appealing to lay upon.\n");
	add_item(({"bedding"}),
	"The bedding is soft and quite plush.\n");
	
	add_item(({"north wall", "northern wall", "north"}),
	"There is a fireplace in that direction.\n");
	add_item(({"south wall", "southern wall", "south"}),
	"There is a four poster bed in that direction.\n");
	add_item(({"east wall", "eastern wall", "east"}),
	"There is a window in that direction.\n");
	add_item(({"west wall", "western wall", "west"}),
	"There is a door in that direction.\n");	
	
	coffer=clone_object(IOBJ + "coffer");
	coffer->move(TO);

	add_my_desc(seat_desc, this_object());
	add_my_desc(laying_desc, this_object());
	add_my_desc(people_desc, this_object());
	
	add_door_exit(IOBJ + "door8", "hall4", "west");
	
	add_fail("auto", "A wall stops you.\n");
	
}

public void
init()
{
	::init();
	init_fire();
	init_seat();

}
