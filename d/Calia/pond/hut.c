
inherit "/std/room";
#include "pond.h"
#include <stdproperties.h>
#include <macros.h>

int net;

void
reset_room()
{
	net = 1;
}

create_room() {

			
		
	set_short("An old, dilapidated boathouse");
	set_long("You are inside an old building that was once "+
		"apparently used to store fishing and boat "+
		"implements. There is a slight odor of damp rotting "+
		"wood and dead fish. A dim light filters in through "+
		"a hole in the roof. In one corner is piled a heap "+
		"of junk.\n");

	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_INSIDE,1);
	reset_room();

	add_item((({"junk", "heap", "heap of junk"})),
		("It looks like just old broken fishing poles, and other "+
		"fishing paraphernalia, long abandoned.\n"));
	add_item((({"walls", "ceiling", "floor", "corner"})),
		("The walls and ceiling of this hut are made of "+
		"wood, rather rotten now. The floor is packed dirt "+
		"covered with mold and fish scales. In one corner "+
		"is a heap of old junk. There are no windows here.\n"));
	add_item("hole",
		"There is a hole in the roof, which lets in a "+
		"little light. It is high above your head, and "+
		"you can't reach it.\n");


	add_exit(FPATH+"edge_pond.c", "out", 0,0);
	add_prop(OBJ_S_SEARCH_FUN, "find_net");
	add_prop(OBJ_I_SEARCH_TIME, 5);
}

string
find_net(object searcher, string str)
{

	object n;

if (net)
	{
if ((str=="junk")||(str=="heap")||(str=="heap of junk"))
	{
	seteuid(getuid(TO));
	n = clone_object(NET);
	n->move(TP);
	net = 0;
	TP->add_prop(PLAYER_I_FOUND_NET,1);
	tell_room(environment(TP),QCTNAME(TP)+" found something "+
		"in the junk.\n", ({TP}));
	return "You find an old net.\n";
	}
		else
		return "You find nothing of interest there.\n";
	}
	else
	return "You find nothing of interest there.\n";
}
