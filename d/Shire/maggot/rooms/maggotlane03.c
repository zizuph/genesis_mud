
/* 
	*A lane just outside Maggot's farm house and barn in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define PROP_Y			"_found_y_bead"
#define PROP_R			"_found_r_bead"
#define BRACE_PROP 		"_finding_bracelets_beads"
#define LOOK_ONE		"_checked_hedge_once"
#define LOOK_TWO		"_checked_lane_found_grass"
#define LOOK_THREE		"_checked_grass_once"

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";

public void
create_area_room()
{
	areadesc = "rutted lane";
	area = "somewhere in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	
	extraline = "The lane is bordered by low hedges. Everywhere you look you see well-tended fields, evidence of the skilled farmers that inhabit the area. To the north stands a single story farm house with an orderly yard. A gate stands between the house and the lane.";
	
	add_item(({"hedge", "hedges"}), "@@look_hedge");
	add_item(({"fields"}), "Very orderly fields and meadows, " +
	"the farmers around here tend their fields with care.\n");
	add_item(({"lane", "road", "path", "ruts"}), "@@look_lane");
	add_item(({"house", "farmhouse", "farm house"}), "The house is only a single story and very " +
	"short, reminiscent of hobbit holes one might see in other areas of " +
	"the Shire. From here it looks very clean and orderly.\n");
	add_item(({"ground"}), "Here on the lane, the ground is hard " +
	"packed dirt and pebbles, with wild grass growing in spots.\n");
	add_item(({"wild grass", "grass"}), "@@look_grass");
	add_item(({"yard"}), "It is well-kept and cut short. A few trees " +
	"line the fringe of the yard.\n");
	add_item(({"tree", "trees"}), "The trees are green and small, " +
	"almost shrub-like.\n");
	add_item(({"gate"}), "It is a small wooden gate, opened, leading " +
	"north into the yard.\n");
	add_item(({"fringe"}), "Trees line the yard's fringe.\n");
	
	set_room_tell_time(90);
	add_room_tell("A thrush alights on the hedge.");
	add_room_tell("Clouds pass by overhead, temporarily blocking " +
	"the sun.");
	add_room_tell("Sounds of activity can be heard coming from inside " +
	"the house.");
	add_room_tell("Barking can be heard in the distance.");
	
	add_exit(ROOM_DIR + "maggotlane02b", "east");
	add_exit(ROOM_DIR + "maggotlane04", "west");
	add_exit(ROOM_DIR + "maggotyard01", "north");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

string look_hedge()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The hedges are not very tall, no more than two feet high, but are very thickly leaved and dark green. They are well laid, bordering the lane on both sides.\n";
	}
	
	if(TP->query_prop(PROP_Y))
	{
		return "The hedges are not very tall, no more than two feet high, but are very thickly leaved and dark green. They are well laid, bordering the lane on both sides.\n";
	}
	
	if(!TP->query_prop(LOOK_ONE))
	{
		TP->add_prop(LOOK_ONE, 1);
		return "The hedges are not very tall, no more than two feet high, but are very thickly leaved and dark green. They are well laid, bordering the lane on both sides. Hmm...Something catches your eye near the hedge. Perhaps you need a closer look.\n";
	}
	
	if(TP->query_prop(LOOK_ONE))
	{
		TP->remove_prop(LOOK_ONE);
		return "Nope... Guess it was nothing, just a small rock.\n";
	}
}

string look_lane()
{
	if(TP->query_prop(PROP_Y))
	{
		return "It is rutted, most likely due to carts and wagons passing through. Wild grass is growing between the ruts and on either side of the lane.\n";
	}
	
	if(!TP->query_prop(BRACE_PROP))
	{
		return "It is rutted, most likely due to carts and wagons passing through. Wild grass is growing between the ruts and on either side of the lane.\n";
	}
	
	if(TP->query_prop(LOOK_TWO))
	{
		return "It is rutted, most likely due to carts and wagons passing through. Wild grass is growing between the ruts and on either side of the lane. Something in the grass catches your eye.\n";
	}
	
	if(!TP->query_prop(LOOK_TWO))
	{
		TP->add_prop(LOOK_TWO, 1);
		return "It is rutted, most likely due to carts and wagons passing through. Wild grass is growing between the ruts and on either side of the lane. Something in the grass catches your eye.\n";
	}
}

string look_grass()
{
	if(TP->query_prop(PROP_Y))
	{
		return "It's just common grass growing on various spots on the lane.\n";
	}
	
	if(!TP->query_prop(BRACE_PROP))
	{
		return "It's just common grass growing on various spots on the lane.\n";
	}
	
	if(TP->query_prop(LOOK_TWO))
	{
		TP->add_prop(LOOK_THREE, 1);
		TP->remove_prop(LOOK_TWO);
		return "It's just common grass growing on various spots on the lane, but you are certain now that you see something in the grass. Maybe you should take a closer look.\n";
	}
	
	if(TP->query_prop(LOOK_THREE))
	{
		TP->remove_prop(LOOK_THREE);
		TP->add_prop(PROP_Y, 1);
		TP->add_prop(PROP_R, 1);
		clone_object("/d/Shire/maggot/obj/bead_y.c")->move(TP);
		clone_object("/d/Shire/maggot/obj/bead_r.c")->move(TP);
		return "Yes! You knew you saw something! Two small beads were nestled in a tuft of grass at the edge of the lane. You quickly pick them up.\n";
	}
}
