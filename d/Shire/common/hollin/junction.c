#include "valley.h"

create_valley() {
    set_short("Junction");
    set_long("A junction. A green valley lies to the south, a cleft to the "+
	     "west, and to the north a small dark opening to a cave. Above "+
	     "the entrance is something peculiar! A small woodcutted sign "+
	     "hangs there, having some strange characters you never saw "+
	     "before. The sign is bolted to the mountain. ");
    add_item(({"junctions","valley","cleft","opening","cave"}),
	    "Well, it looks inviting for adventure.\n");
    add_item(({"sign","chars","characters","entrance"}),
	     "I'm terribly sorry that I cannot tell you what it is, but "+
	     "maybe it is only a sign telling what valley lies south of "+
	     "you?!?\n");
    NORTH("slide");
    WEST("valley");
    SOUTH("marvel");
}

init() {
    ::init();
    add_action("my_read","read");
}
		  
my_read(string str) {
    if(!str) {
	notify_fail("Read what?\n");
	return 0;
    }
    if(str == "sign" || str == "chars" || str == "characters") {
	write("You cannot read them, due to the strange letters.\n");
	return 1;
    }
}
