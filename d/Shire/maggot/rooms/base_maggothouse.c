/*
	*Base file holding the observables and rtells for Maggot's house
	*Altrus, March 2005
*/

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";	

//adds observable items for Maggot's yard
void set_add_house()
{
	add_item(({"ceiling"}), "It is very low, barely six feet " +
	"from the floor.\n");
	add_item(({"walls", "wall"}), "The walls are whitewashed " +
	"and clean. They are decorated with various paintings and " +
	"small shelves. Sconces on the walls shed light here.\n");
	add_item(({"floor"}), "The floors are spotlessly clean, " +
	"not a speck of dust mars the wooden surface.\n");
	add_item(({"sconces", "sconce"}), "They contain " +
	"beeswax candles, filling the room with a pleasant smell.\n");
	add_item(({"candle", "candles", "beeswax candle", "beeswax candles"}), "They " +
	"fill the room with a pleasant smell.\n");
	add_item(({"paintings"}), "Just a couple framed canvases " +
	"depicting scenes of hobbit life.\n");
	add_item(({"shelves"}), "They are holding a few vases filled " +
	"with wild and garden flowers.\n");
	add_item(({"flowers"}), "The flowers look a little dry.\n");
}

//adds rtells for Maggot's yard
void set_add_rtells_house()
{
	set_room_tell_time(120+random(15));
	add_room_tell("Barking can be heard outside.");
	add_room_tell("From a nearby room someone shouts: 'Oh dear! Where did I put the salt!'");
	add_room_tell("You can hear someone yelling in a nearby room: 'Who took my mixing bowl! Oh, there it is!'");
	add_room_tell("Bang! Sounds like someone is busy in the kitchen.");
}

