/*
*  by Amelia, for use in the Light Forest
*/
inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "room_tell.c"
private int found;

void
reset_room()
	{
	found = 0;
	}
void
create_room()
{
	reset_room();
	set_short("The light forest");
	set_long("A large oak tree appears suddenly in the middle of the "+
		"way, causing the path to diverge into two branches.  "+
		"Although the foliage is denser, sunlight still "+
		"diffuses through the leaves.  It is warm and peaceful "+
		"here.\n");
	add_item((({"foliage"})),
		("The bushes are closer together, and the trees are "+
		"becoming larger.  This must be an older part of the "+
		"forest.\n"));
	add_item((({"bush", "bushes"})),
		("Mulberry and wildrose bushes grow in abundance here.\n"));
	add_item((({"tree", "oak tree", "oak", "large oak tree"})),
		("It is a large oak tree with spreading branches, "+
		"very old from its size.  Its bark is gnarled "+
		"and there appears to be a small hole in the trunk.\n"));
	add_item((({"hole", "small hole"})),
		("The dark hole looks just large enough to be the home of "+
		"some small animal.  Hmm...it looks interesting though...\n"));
	add_item((({"path"})),
		("The path is divided here, due to the large tree in "+
		"the way.\n"));

	set_tell_time(60);
	add_tell("Far away you can barely hear the sound of croaking "+
		"frogs.\n");
	add_tell("A mockingbird sings in the tree overhead.\n");
	add_tell("A large bumblebee buzzes right past your ear.\n");
	add_exit((FPATH+"forest_E_3a"),"northwest", 0,0);
	add_exit((FPATH+"forest_E_7a"), "southeast", 0, 0);
	add_exit((FPATH+"forest_E_5a"), "northeast", 0,0);

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE,0);
}

void
enter_inv(object ob, object from)
{
	start_room_tells();
	add_action("get_gem", "search");
	::enter_inv(TP, TO);
}

void
leave_inv(object ob, object to)
{
	remove_alarm(tell_alrm);
}

int
get_gem(string str)
	{
	object obj;

	if ((str=="hole") && (!found))
	{
	obj = clone_object(FPATH + "gem.c");
	obj->move(this_player());
	write("You search the hole in the tree.\n");
	write ("You found a gem!\n");
	found = 1;
	return 1;
	}
	else
	if ((str=="hole")&& found)
	{
		write("You search the hole in the tree.\n");
		write("Whatever was here, is gone now.\n");
		return 1;
	}
	else
		return 0;
}
