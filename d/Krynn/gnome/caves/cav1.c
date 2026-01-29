inherit "/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <wa_types.h>

void
create_room()
{
	LIGHT;
	INSIDE;
	set_short("A rough cave");
	set_long("This is a rough cave. A foul smell of decay is in the "
		+ "air all around you. A green moss sheds a dim "
		+ "illumination into the dark caves ahead.\n");
	
	add_item("moss", "The moss covers part of the walls. You touch it "
		+ "and realize that a bit sticks to your fingers. They "
		+ "also shine green now.\n");
	add_cmd_item("moss", ({"get", "take", "grab", "pick"}),
		"@@get_moss");
	add_cmd_item("hands with moss", "cover", "@@get_moss");
	add_exit(TDIR + "cave2", "south", 0, 3);
	add_exit(CAVES + "cav2", "north", "@@not_yet", 3);
	add_prop(ROOM_I_NO_CLEANUP, 1);
}

string
check_for_sign()
{
	return P("Gnomish_Sign", TO)->check_for_text();
}

int
not_yet()
{
	write("The caves ahead look dangerous. You should wait for "
		+ "a Krynn wizard to have a look first.\n");
	say(QCTNAME(TP) + " tries to go north but fails.\n");
	if(P("Gnomish_Sign", TO))
		write("You obviously didn't read the sign!\n");
	return 1;
}

string
get_moss()
{
	object obj;
	
	if(obj = TP->query_armour(TS_LHAND))
		return "Remove the " + C(obj->query_name()) + " first.\n";
	if(obj = TP->query_armour(TS_RHAND))
		return "Remove the " + C(obj->query_name()) + " first.\n";
	if(P("moss_light", TP))
		return "Your hands are still covered with moss.\n";
	
	write("You cover your hands with the shiny moss.\nThey now shed "
		+ "considerable illumination.\n");
	clone_object(OBJ + "moss_light")->move(TP);
	say(QCTNAME(TP) + " covers " + POSSESSIVE(TP) + " hands with "
		+ "the moss.\n");
	return "";
}
