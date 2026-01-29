#include "rom.h"

create_rom()
{
    set_short("Circular crack");
    set_long("@@long_desc@@\n");

    add_item(({"crack", "cave", "opening"}),
	"You see nothing special.\n");

    add_item(({"smell", "fire", "fireplace", "smoke", "air", "odour"}),
        "The fire seems shortly abandoned. However you feel something rotten\n"+
        "about this place, as if trolls have been here recently!\n"
    );

    add_item(({"rocks","sky"}),
	"You can only glimpse the sky above.\n");

    add_item("opening",
	"Which opening?\n");

    add_item(({"north", "north opening"}),
	"It leads out to clearer air.\n");

    add_item(({"east", "east opening", "bigger room"}),
	"Yikes, there is a smell coming from there! Probably trolls!\n");

    add_item(({"boulders", "north", "north exit"}),
	"@@exa_boulders@@\n");

    add_item(({"wall", "walls"}),
	"The walls are made of stone.\n");

    add_item("button",
	"The button might be pressed.\n");

    add_exit(STAND_DIR+"big_hole","north","@@chk_exit");

    EAST("round_room");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(OBJ_I_SEARCH_TIME, 8);
    add_prop(OBJ_S_SEARCH_FUN,	"search");

    add_cmd_item("button", ({ "push", "press" }), "@@press_button");
}

int blocked() {
    return call_other(STAND_DIR+"big_hole", "boulders_block_exit");
}

string
exa_boulders() {
    if(blocked())
	return
	    "A whole lot of large boulders is blocking the north exit. "+
	    "Obviously, someone have accidentily stepped on the trap outside "+
	    "Now, how on earth are you going to get out of here!";
    else
	return
	    "The northern exit leads out into a big hole.";
}

int
chk_exit()
{
    if(blocked()) {
	write("You can't go north from here!\n"+
	    "A lot of boulders have blocked the exit out of here!!\n");
	return 1;
    } else
	return 0;
}

string
long_desc()
{
    string str =
	"You're in a semidark, almost circular crack in the mountain.\n"+
	"A decayed fireplace is here and a scent of smoke is in the air! "+
	"To the east there is an irregular opening to a bigger room";

    if(call_other(STAND_DIR+"big_hole", "boulders_block_exit"))
	str +=
	    ", but to the north, where there used to be an opening, "+
	    "you notice that it is blocked by huge boulders!! ";
    else
	str += " and to the north an opening. ";

    str +=
	"The odour is remarkable. It smells almost like rotten meat.. "+
	"Slabs of rocks over you almost make this a cave, with just a glimpse "+
	"of sky above.";

    return str;
}

string
search(object tp, string str)
{
    if(str=="wall"||str=="walls"||str=="here"||str=="room"||str=="button")
	return "Your search reveals a button hidden in the wall!!\n";
    else
	return 0;
}

press_button()
{
    write("You press the button on the wall.\n");
    if(blocked())
	call_other(STAND_DIR+"big_hole", "reset_boulders");
    return 1;
}
