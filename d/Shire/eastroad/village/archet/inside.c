#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
inherit SHIRE_DIR +"room";

create_room()
{
	set_short("At the front room of a cottage");
	set_long("You are standing in the front room of a cottage. "+
		"The front door is quite tall, and the room is about 10 by 8 feet "+
		"wide. Another door is leading into something that seems to be a "+
		"bedroom south of here, and another door seems to lead into a small "+
		"storage room just east of the hall. "+
		"Facing north there is a door which appears to be leading into the living "+
		"room. The walls is build by timber, solid timber, and it seems "+
		"like excellent craftmanship. Torches light up the hall, but some "+
		"additional light shreds throught the window when the sun is up.\n");
	add_exit(ARCHET_DIR +"cottage", "out", 0);
	add_exit(ARCHET_DIR +"bedroom", "south", 0);
	add_exit(ARCHET_DIR +"storage", "east", 0);
	add_exit(ARCHET_DIR +"living", "north", 0);
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	ITEM("walls", "The walls have been carved out of solid timber. It seems like "+
		"oak, as it is the most common wood around in this forest. The entire "+
		"cottage seems to be built of it.\n");
	ITEM(({"door", "front door"}), "The front door is about 7 feet high, and has "+
		"been made out of oak too. It is ornamented with a picture of an axe "+
		"and a saw. A small round window is in head height.\n");
	ITEM(({"bedroom","living room", "storage room"}),
		"Can't see much from here. Maybe enter into it?\n");
	ITEM(({"torch", "torches"}), "There are four torches on the walls in the hall. "+
		"They provide good light when lit, and they are connected to the wall.\n");
	ITEM("window", "The window is made out of glass. You look out of it. "+
		"@@desc_other_side@@\n");
}

string
desc_other_side()
{
	object *ob, *liv, opp;
	string str;

	if (LOAD_ERR(BREE_DIR +"archet/cottage"))
		return "";

	opp = find_object(BREE_DIR +"archet/cottage");

	if (!opp)
		return "";
	if (opp->query_prop(OBJ_I_LIGHT) <= 0)
		return "It is too dark outside to see anything.";
	
	ob = FILTER_CAN_SEE(all_inventory(opp), TP);

	if (!sizeof(ob))
		return "You can't see anything special out there, only a small garden.";

	return "On the outside you can see "+COMPOSITE_WORDS(map(ob, "desc", TO))+".";
}

string
desc(object ob)
{
	if (living(ob))
		return LANG_ADDART(ob->query_race_name());
	else
		return LANG_ADDART(ob->short());
}

