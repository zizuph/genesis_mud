/*
	*Base room with descriptions and rtells for 
	*a small forest area near Maggot's farm
	*Altrus, March 2005
*/

#include "/d/Shire/sys/defs.h";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";

//adds the plant and ground descriptions for the fields in this area
void set_add_forest()
{
	add_item(({"thicket"}), "You are standing in a dense thicket of trees.\n");
	add_item(({"breaks", "field", "fields"}), "The fields seen through " +
	"the breaks in the trees appear to be filled with turnips.\n");
	add_item(({"turnip", "turnips"}), "From this distance it is hard " +
	"to tell, but the turnips look quite large.\n");
	add_item(({"trees", "tree"}), "The trees are deciduous, the " +
	"foliage a healthy green.\n");
	add_item(({"foliage", "leaves"}), "The leaves range in size, " +
	"from smaller than a length of a finger to twice the size of a " +
	"hand.\n");
	add_item(({"undergrowth", "bushes"}), "There is not much to " +
	"speak of, just a few bushes growing near the bases of the trees.\n") +
	add_item(({"growth", "lichen", "fungal growth"}), "Lichen grows " +
	"on the trees in abundance; mushrooms litter the forest floor.\n");
	add_item(({"mushroom", "mushrooms"}), "These mushrooms are " +
	"small, hardly worth even a snack.\n");
	add_item(({"ground", "floor", "forest floor", "soil"}), "The ground is " +
	"soft, and pleasantly cool. The soil is dark, nearly black, and " +
	"appears quite fertile.\n");
}

//adds the room tells for the fields
void set_add_rtells_forest()
{
	set_room_tell_time(90+random(15));
	add_room_tell("Loud barking can be heard nearby.");
	add_room_tell("A cricket chirps loudly.");
	add_room_tell("A rustling can be heard in the leaves overhead.");
	add_room_tell("A slight breeze blows in the treetops.");
	add_room_tell("A shrill whistle breaks the silence.");
}
