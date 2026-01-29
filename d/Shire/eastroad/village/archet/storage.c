#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include <composite.h>
inherit SHIRE_DIR +"room";

create_room()
{
	set_short("Inside a storage room");
	set_long(
		"You are inside a rather large storage room. There are many shelves "+
		"here, filled with many rare things. @@is_saw_here@@. An unlit "+
		"torch hang above the window, which is on the eastern wall. The south"+
		"ern wall has a huge shelf standing against it. Through the window some "+
		"light shred into the room. The exit out of here is through a door facing "+
		"the west wall.\n");
	ITEM("saw", "@@check_for_saw@@");
	ITEM("axe", "@@the_axe@@");
	ITEM(({"shelf", "shelves")}, "Which shelf do you refer to? The on on the "+
		"southern wall, or the one on the northern wall?\n");
	ITEM(({"northern shelf","shelf to the north", "north shelf")}, "The shelf on "+
		"the northern wall contains @@present_axe@@ some books.\n");
	ITEM("window", "@@exa_window@@");
	ITEM("door", "The door is open, you can pass that west through it.\n");
	add_exit(ARCHET_DIR +"inside", "west", 0);
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
}

string
is_saw_here()
{
	object saw = present("_timberman_saw_");
	if (saw)
		return "There is a saw hanging on the northern wall, above the shelf there.";
	else
		return "";
}

string
check_for_saw()
{
	if (present("_timberman_saw_"))
		return "The saw looks like a common saw, used for cutting down trees.\n";
	else
		return "You find no saw here.\n";
}

string
present_axe()
{
	if (present("_timberman_axe_"))
		return "an axe and";
	else
		return "";
}

string
the_axe()
{
	if (present("_timberman_axe_"))
		return "The axe looks like a common axe used by a timberman to cut down trees.\n";
	else
		return "You find no saw here.\n";
}

string
exa_window()
{
	object *ob, *liv, opp;
	string str;

	if (LOAD_ERR(ARCHET_DIR +"yard2"))
		return "";

	opp = find_object(ARCHET_DIR +"yard2");

	if (!opp)
		return "";
	if (opp->query_prop(OBJ_I_LIGHT) <= 0)
		return "It is too dark to see anything out there.\n");

	ob = FILTER_CAN_SEE(all_inventory(opp), TP);

	if (!sizeof(ob))
		return "You look out through the window into the backyard of the cottage.";

	return "Looking out the window you can see "+COMPOSITE_WORDS(map(ob, "desc", "TO))+".";
}

string
desc(object ob)
{
	if (living(ob))
		return LANG_ADDART(ob->query_race_name());
	else
		RETURN LANG_ADDART(ob->short());
}

