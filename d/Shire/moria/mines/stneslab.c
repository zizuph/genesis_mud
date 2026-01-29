#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("On a large stone-slab");
    set_long(
	"You are standing on a flat landing made by a large slab of stone. "+
	"A cool draft arrives from the west from where a giant dark cave "+
	"opens. To the east there is a half-open door towards a little "+
	"room. An archway continues north from here, and in the south "+
	"you could go to a little hole in the ground.\n");
    add_item(({"landing","slab","slab of stone", "stone-slab"}),
	"The slab is amazingly in colours red and green. You would guess "+
	"that this is a piece of marble collected by the dwarves and placed "+
	"here.");
    add_item("draft", "Seems to come from the dark cave in the west.");
    add_item("cave", "Perhaps you should go there and find out?");
    add_item("archway", "It leads northwards.");
    add_item("door", "On the door there is placed a little sign.");
    add_item("sign", "Perhaps read it?");
    add_call("read", "[the] [little] 'sign' [on] [the] [door]", "do_read");
    NORTH("archway");
    add_exit(THIS_DIR + "shop", "east");
    SOUTH("byhole");
    WEST("lake_e");
}

int
do_read(string str)
{
    write("The sign states:\n" +
	  "   \"Ugluk Dumwa's Pawnshop and Antiques\"\n"+
	  "Somehow you understand that this once was a "+
	  "shop used by the Dwarves under the Mountain, "+
	  "but that a thefty Orc have started new " +
	  "business here.\n");
    say(QCTNAME(TP) + " reads the sign on the door.\n");
    return 1;
}

int
chk_it()
{
    tell_room(TO,
        "Ugluk Dumwa arrives with a snearing grin.\n" +
        "Ugluk grins: Stupid mortals, haven't time.\n" +
        "Ugluk hisses: I have to see what I have stolen...\n" +
        "Ugluk cackles evilly.\n" +
        "Ugluk leaves east through the door.\n" +
        "Ugluk shouts: Come back when I am done!\n");
    return 1;
}
