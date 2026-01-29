/*  -*- LPC -*-  */
#include "defs.h"

int opened;

void add_stuff();
CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");
    
    set_short("An off-partitioned room");
    set_long("This is a partitioned room in the eastern "+
	     "part of the Dirty Department. There is a table "+
	     "made of rock here@@desc_table@@");
    add_item("table", "@@exa_table@@");
    WEST("clampass");
    opened = 0;
    add_stuff();
    add_prop(ROOM_I_HIDE, -1);
}

RESET_ROOM {
    remove_exit("down");
    opened = 0;
    add_stuff();
}

string
desc_table()
{
    if (!opened)
	return (" that dominates the room.");
    else
	return ". It is pushed aside, "+
	    "leaving a passage steeply down some stairs.";
}

init() {
    ::init();
    add_action("my_down","down");
    add_action("my_down","d");
    add_action("my_move","move");
    add_action("my_move","push");
}

my_move(str) 
{
    if (!str) {
	notify_fail(CAP(query_verb())+" what?\n");
	return 0;
    }
    if (str == "the table" || str == "table") {
	if(present("cave troll"))
	    return notify_fail("The troll won't let you do that.\n");
	if (opened)
	    return notify_fail("But, it's already opened!\n");
	write("You push the table aside!\n");
	say(QCTNAME(TP) + " pushes the table aside.\n");
	opened = 1;
	return 1;
    }
}

my_down() 
{
    if (!opened)
	return 0;
    this_player()->move_living("down", THIS_DIR + "lair/stair0");
    return 1;
}

string
exa_table() 
{
    if (opened)
	return "There are some stairs going down into the darkness!";
    else 
	return "Wonder what it might be good for??";
}

void
add_stuff()
{
    object troll1, troll2, bigtroll;
    
    if (!present("cave troll"))
    {
	troll1 = clone_object("/d/Shire/moria/npc/cavetroll");
	troll1->move(this_object());
	
	troll2 = clone_object("/d/Shire/moria/npc/cavetroll");
	troll2->move(this_object());
	
	bigtroll = clone_object("/d/Shire/moria/npc/bigtroll");
	bigtroll->move(this_object());
    }
}
