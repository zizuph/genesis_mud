#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Western shore of a dark subterranean lake");
    set_long(
	"This is an opening by the Western Shore.\n"+
	"In the east you can see a dark and sinister subterranean lake. "+
	"It is obviously impossible to swim across, though it might be "+
	"interesting to see what might be upon that islet in the middle of "+
	"the lake. There is quite a good walk-way leading into the mountain "+
	"in the north.\n");
    add_item("shore", "It is quite short, so you could not walk around the "+
	"lake.");
    add_item(({"lake", "water"}),
	"Hmm, when thinking of what evil might lurk underneath this cursed "+
	"lake you would not like to swim in it.");
    add_item(({"islet","holm"}),
	"This islet, or holm, stands there as an unreachable island in the "+
	"midst of the lake. You must have a boat or a raft to get there.");
    add_item(({"opposite shore","opening", "passage"}),
	"From here it is hard to tell features, but it seems like you could "+
	"continue further into a passage there.");
    add_item(({"walkway","exit"}),
	"The walkway seems to lead north into a round chamber.");
    NORTH("roundchb");
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
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
	"You have landed on the western shore of the dark lake. "+
	"From here you could leave the raft, or you could try "+
	"to paddle the raft to the islet in the middle of the lake "+
	"in the east.\n";
}


int allowed_dir(string str) { return str=="east"||str=="e"; }
int is_lake_room()   { return 1; }

string query_true_verb() 
{
    string verb = query_verb();
    
    if (verb == "e" || verb == "east")
	return "paddle east";
    if (verb == "w" || verb == "west")
	return "paddle west";
    return verb;
}

int
row(object boat, string dir)
{
    write("You start to "+query_true_verb()+" towards the islet!\n");
    tell_room(TO,
	QCTNAME(TP)+" starts "+query_verb()+"ing towards the islet.\n");

    (THIS_DIR+"islet")->short();

    boat->move(find_object(THIS_DIR+"islet"));
    write("You land safely by the islet.\n");
    tell_room(THIS_DIR+"islet",
	QCTNAME(TP)+" paddles towards the islet and lands safely.\n");
    return 1;
}
