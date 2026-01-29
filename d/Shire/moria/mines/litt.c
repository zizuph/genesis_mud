#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Wing of Literature");
    set_long("You're in the Wing of Literature. On the wall there is an "+
	     "inscription in the tongue of elves. There is a little hole "+
	     "to the west, and a bigger to the east.\n");
    add_item(({"wall","inscription"}),"Perhaps read it?");
    add_item("hole",
	     "The one to the west is 6 feet wide, and the eastern about "+
	     "10 feet.");
    add_item(({"grey book","book","gray book"}),
	     "The grey book is jammed tightly into the cracks of the wall.");
    add_item("cracks","The cracks are where the wall has shifted over time.");

    EXIT("mjunc","west");
    EXIT("longr1","east");
}    

init() {
    ::init();
    add_action("my_read","read");
    add_action("do_pull","pull");
    add_action("do_pull","pry");
}

my_read(str) {
    if (!str) {
	notify_fail("Read what?\n");
	return 0;
    }
    if (str == "wall" || str == "inscription") {
	write("The inscription says:\n"+
	      "             Gilthoniel a Elbereth!\n"+
	      "             O menel Palan-Diriel\n"+
	      "             le nallon si di'nguruthos!\n"+
	      "             a tiro nin, Fanuilos!\n"+
	      "You notice a grey book hidden in the wall.\n");
	tell_room(ETP, QCTNAME(TP)+ " reads the inscriptions.\n", TP);
	return 1;
    }
}

int
do_pull(string str)
{
    notify_fail("Pull what?\n");
    if(!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
		       "[the] [grey] 'book' 'from' [the] 'wall' / 'crack'"))
	{
	    write("Pull what from where?\n");
	    return 1;
	}

    FIXEUID;
    
    write("You pull the grey book from the wall and read:\n");

    write(read_file(MORIA_DIR + "doc/bombir_book.txt"));

    say(QCTNAME(TP)+ " reads a grey book and puts it back.\n");
    write("You put the book back where it came from.\n");
    
    return 1;
}
