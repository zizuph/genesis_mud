/*
	*Base room with descriptions and rtells for Maggot's fields
	*Altrus, March 2005
*/

#include "/d/Shire/sys/defs.h";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
inherit AREA_ROOM;

//adds the plant and ground descriptions for the fields in this area
void set_add_field()
{
	add_item(({"turnip", "turnips", "crops"}),"These white " +
	"turnips are quite large, obviously the product of a " +
	"skilled farmer.\n");
	add_item(({"field", "turnip field"}),"The field is fairly " +
	"brimming with turnips. The ground here is a dark brown, " +
	"very fertile.\n");
	add_item(({"ground", "soil", "dirt"}),"Your foot sinks " +
	"slightly into the rich soil. There are footprints in the " +
	"dirt.\n");
	add_item(({"footprints"}),"Beside your own prints, there " +
	"are what looks like the footprints of a hobbit and at " +
	"least one very large dog.\n");
	
	set_no_herbs(); //an orderly hobbit-tended field wouldn't have weeds ;)
}

//adds the row descriptions for the southernmost field rooms
void set_add_rows_south()
{
	add_item(({"row"}), "This is a row of orderly planted " +
	"turnips. There are more rows north of here.\n");
	add_item(({"rows"}), "The other rows are north of here, " +
	"if want to see them why don't you head that way?\n");
}

//adds the row descriptions for the northernmost field rooms
void set_add_rows_north()
{
	add_item(({"row"}), "This is a row of orderly planted " +
	"turnips. There are more rows south of here.\n");
	add_item(({"rows"}), "The other rows are south of here, " +
	"if want to see them why don't you head that way?\n");
}

//adds the row descriptions for the middle field rooms
void set_add_rows_middle()
{
	add_item(({"row"}), "This is a row of orderly planted " +
	"turnips. There are more rows north and south of here.\n");
	add_item(({"rows"}), "The other rows are north and south " +
	"of here. Try heading in the direction you want to walk.\n");
}
//adds the tree descriptions for the field rooms near trees
void set_add_trees()
{
	add_item(({"tree", "trees", "grove"}),"The grove of " +
	"trees comes right up to the edge of the field. The trees " +
	"are deciduous, with leaves of green in varying shades.\n");
	add_item(({"leaves", "foliage"}),"The foliage of the " +
	"trees is an amazing variety of green hues.\n");
}

//adds the room tells for the fields
void set_add_rtells()
{
	set_room_tell_time(90+random(15));
	add_room_tell("Loud barking can be heard nearby.");
	add_room_tell("A crow circles overhead.");
	add_room_tell("Clouds pass by overhead, temporarily blocking " +
	"the sun.");
	add_room_tell("A slight breeze blows across the fields.");
	add_room_tell("Dark clouds pass overhead, threatening rain.");
}
