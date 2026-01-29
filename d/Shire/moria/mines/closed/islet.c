#include "defs.h"

object key;

CONSTRUCT_ROOM
{
    set_short("On an islet");
    set_long(
	"You are standing on an islet in the middle of the subterrean lake. "+
	"From here you can paddle either to the east or the west.\n");
    add_item(({"islet", "room", "ground"}),
	"The islet is quite small, in fact on about 4 meters in diameter. "+
	"The ground consists of smooth sand.");
    add_item("sand",
	"The sand is not thick, and you could probably search into it with "+
	"your bare hands.");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    reset();
}

RESET_ROOM
{
    if (!key)
	key = clone_object(MORIA_OBJ+"key");
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

do_search(object tp, string what)
{
    if (!key || (random(3) && what!="sand"))
	return "Your search revealed nothing of interest.\n";
    key -> move(TO);
    key = 0;
    return "You found something!!\n";
}


string
from_raft_desc()
{
    return
	"You are sitting on a raft by a little islet in the middle of "+
	"a dark subterrean lake. You could leave the raft here, or row "+
	"to the eastern or western shore.\n";
}

int allowed_dir(string str) { return str=="west"||str=="w"||str=="east"||str=="e"; }
int is_lake_room()   { return 1; }

int
row(object boat, string way)
{
    if (!way||way==""|| (way[0..0]!="w" && way[0..0]!="e"))
	return notify_fail("Which shore? The east or the west?\n:"+way+":\n");

    if (way[0..0]=="e")
	way = "east";
    else if (way[0..0]=="w")
	way = "west";
    else
	way = "west";

    write("You start rowing towards the "+way+"ern shore!\n");
    tell_room(TO,
	QCTNAME(TP)+" starts rowing towards the "+way+"ern shore.\n");

    if (way == "west")
	boat->move(THIS_DIR+"lake_w");
    else
	boat->move(THIS_DIR+"lake_e");

    return 1;
}
