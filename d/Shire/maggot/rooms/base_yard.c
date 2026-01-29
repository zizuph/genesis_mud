/*
	*Base file holding the observables and rtells for Maggot's yard
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
void set_add_yard()
{
	add_item(({"flower garden", "garden"}), "The flower garden is " +
	"quite orderly, with a variety of plants, in a variety of colors. " +
	"Fragrances from the garden fill the air.\n");
	add_item(({"flower", "flowers", "plants"}), "There are too many different "+
	"kinds of flowers to count, creating a blanket of colors around the " +
	"outside of the house.\n");
	add_item(({"house"}), "The house is only a single story and very short, " +
	"reminiscent of hobbit holes one might see in other areas of the Shire.\n");
	add_item(({"barn", "old barn"}), "It is slightly higher than the house, faded red in " +
	"color. Sounds of animals can be heard coming from within.\n");
	add_item(({"yard"}), "The grass is kept very short, trimmed at the edges " +
	"near the garden. Trees line the yard.\n");
	add_item(({"trees", "small trees"}), "They are small, almost shrubs. Their foliage is very " +
	"green.\n");
	add_item(({"foliage", "leaves"}), "The leaves are a healthy shade of green.\n");
}

//adds rtells for Maggot's yard
void set_add_rtells_yard()
{
	set_room_tell_time(120+random(15));
	add_room_tell("Clouds pass by overhead, temporarily blocking the sun.");
	add_room_tell("Sounds of activity can be heard coming from inside the house.");
	add_room_tell("Barking can be heard in the distance.");
	add_room_tell("A small butterfly floats past on a breeze.");
	add_room_tell("Grunting and scuffling can be heard from the barn nearby.");
}

