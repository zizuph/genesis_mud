#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("East of a subterranean lake");
    set_long(
	"You are standing on the eastern shore of a large subterranean lake. "+
	"The lake is dark and looks deep, and somewhat out from of the shore it "+
	"seethes and boils. Yes, it looks like small glistening arms winding and "+
	"hiting the water out there. It's all trollish about this lake, and a "+
	"bath seems not very appealing! There is a small islet half way "+
	"between here and the opposite shore, where there is an opening. "+
	"Though, if you should get there, you would need a boat or a raft. "+
	"To the east, there is a huge slab of stone.\n");
    add_item("shore", "It is quite short, so you could not walk around the "+
	"lake.");
    add_item(({"lake", "water"}),
	"Hmm, when thinking of what evil might lurk underneath this cursed "+
	"lake you would not like to swim in it.");
    add_item("arms", "Difficult to tell what it is. Let's hope you'll never "+
	"come in a position to find out..");
    add_item(({"islet","holm"}),
	"This islet, or holm, stands there as an unreachable island in the "+
	"midst of the lake. You must have a boat or a raft to get there.");
    add_item(({"opposite shore","opening", "passage"}),
	"From here it is hard to tell features, but it seems like you could "+
	"continue further into a passage there.");
    add_item(({"slabs", "stone-slabs", "slabs of stone"}),
	"Perhaps go east and investigate?");
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    EAST("stneslab");
}

init()
{
    ::init();
    add_action("no_swim", "swim");
    add_action("no_swim", "enter");
    add_action("no_swim", "bathe");
    add_action("no_swim", "jump");
}

int
no_swim(string what)
{
    if (what!="in lake"&&what!="lake"&&what!="in water"&&what!="water")
	return notify_fail(CAP(query_verb())+" what?\n");

    write("No, you wouldn't dare to "+query_verb()+" into that evil dark lake!\n");
    return 1;
}

string
from_raft_desc()
{
    return
	"This is the eastern shore of a dark subterranean lake. You could "+
	"either leave the raft or row to the islet in the west.\n";
}

int allowed_dir(string str) { return str=="west"||str=="w"; }
int is_lake_room()   { return 1; }

int
row(object boat, string dir)
{
    write("You start to "+query_verb()+" towards the islet!\n");
    tell_room(TO,
	QCTNAME(TP)+" starts "+query_verb()+"ing towards the islet.\n");

    (THIS_DIR+"islet")->short();

    boat->move(find_object(THIS_DIR+"islet"));
    write("You land safely by the islet.\n");
    tell_room(THIS_DIR+"islet",
	QCTNAME(TP)+" paddles towards the islet and lands safely.\n");
    return 1;
}
