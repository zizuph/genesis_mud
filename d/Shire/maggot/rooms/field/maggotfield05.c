
/* 
	*Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_COMMON;
inherit AREA_ROOM;

#define PATH_PROP "_found_path_to_forest"

void create_area_room()
{
	areadesc = "large turnip field";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There are probably more turnips here than " +
	"in the whole of the Shire. Best not pick them, farmers " +
	"can be quite protective of their crops! You are standing " +
	"in a row of planted turnips on the south edge of " +
	"the field. A grove of trees are growing near the edge of " +
	"the field south of here.";
	
	add_item(({"tree", "trees", "grove"}),"The grove of " +
	"trees comes right up to the edge of the field. There is " +
	"dense undergrowth at the base of the trees here.\n");
	add_item(({"leaves", "foliage"}),"The foliage of the " +
	"trees is an amazing variety of green hues.\n");
	add_item(({"undergrowth"}), "The undergrowth is quite " +
	"dense here. Something about the bushes does not look " +
	"quite right though.\n");
	add_item(({"bushes", "bush"}), "These bushes are not " +
	"rooted in the ground, but look freshly cut and placed here to " +
	"cover up something. You notice odd markings on the ground.\n");
	add_item(({"markings", "odd markings", "marks", "odd marks"}), "@@exa_marks");
	add_item(({"path"}), "@@exa_path");
	
	set_add_field();
	set_add_rows_south();
	set_add_rtells();
	
	add_exit(FIELD_DIR + "maggotfield04", "east");
	add_exit(FIELD_DIR + "maggotfield06", "west");
	add_exit(FIELD_DIR + "maggotfield11", "north", 0, 3, 1);
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{   
	::init();
	add_action("follow_path", "follow");
}

string exa_marks()
{
	if(this_player()->query_skill(SS_AWARENESS)>10)
	{   
		this_player()->add_prop(PATH_PROP, 1);
		this_player()->catch_msg("There is definitely " +
		"something odd about these marks on the ground...\n" +
		"After rooting around for a moment, you discover a " +
		"path heading off into the trees! Where might it " +
		"lead if you follow it?\n");
		return "";
	}
	else
	{
		this_player()->catch_msg("After poking around " +
		"the bushes a bit, you decide that it's nothing " +
		"important and turn your attention to other things.\n");
		return "";
	}
}

string exa_path()
{
	if(this_player()->query_prop(PATH_PROP))
	{   
		this_player()->catch_msg("You can still see the path quite clearly.\n");
		return "";
	}
	else
	{
		this_player()->catch_msg("You find no path.\n");
		return "";
	}
}

int follow_path(string str)
{
	if(str == "path")
	{
		if(this_player()->query_prop(PATH_PROP))
		{    
			this_player()->catch_msg("You follow a path into the grove of trees.\n");
			say("What? " + QCTNAME(this_player()) + " is gone!\n");
			tell_room(ROOM_DIR + "maggotforest03", QCTNAME(this_player()) + " arrives.\n");
			this_player()->move_living("M", ROOM_DIR +"maggotforest03",1);
                       return 1;
		}
		
		else
		{
			this_player()->catch_msg("You don't see a " + str + " to follow.\n");
			return 1;
		}
	}
	
	else
	{
		this_player()->catch_msg("Follow what?\n");
		return 1;
	}
	return 1;
}
