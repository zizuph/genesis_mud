#include "valley.h"

int amount;

create_valley() {
    amount = 1000;
    set_short("Marvelous greenhouse valley!!");
    set_long("You are in the marvelous greenhouse valley!!\n"+
	     "In a natural cleft someone, probably elves, have made a bulging "+
	     "greenhouse, or more a garden. All kinds of herbs and plants "+
	     "grow around here, and the smell is fresh and clear, though "+
	     "somewhat hot. It's even a small waterfall here, and the "+
	     "artistic decoration makes this some garden of Eden. The valley "+
	     "stretches out of sight to the south and to the north a path "+
	     "leads out of the valley. ");
    add_item(({"valley","cleft","greenhouse","garden"}),
	     "It's a wonder how the elves managed to make such a nice "+
	     "place so far up in the mountains.\n");
    add_item(({"herbs","plants","smell"}),
	     "The plants and herbs create a wonderful aura.\n");
    add_item("waterfall",
	    "Perhaps drink the water?\n");
    add_item("decoration",
	    "Wow, this must be the next thing to Eden!\n");
    NORTH("junction");
    SOUTH("greenh");
}

reset_valley() {
    amount = 1000;
}

init() {
    ::init();
    add_action("my_drink","drink");
}

my_drink() {
    int h;
    
    h = random(100)*amount/1000;
    if(!h) {
	write("Hmm. The water tastes somewhat non-tasty.\n");
	say(QCTNAME(TP)+" drinks from the waterfall.\n");
	return 1;
    }
    write("Ahh, what a refresh!\n");
    this_player()->heal_hp(h);
    amount -= h;
    return 1;
}
