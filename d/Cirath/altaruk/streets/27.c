#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Giant");
    last_line("The south wall is unusualy high here." +
        " There is a gate in the middle of the wall.\n");
    
    add_item("wall", "What wall?\n");
    add_item("south wall", "The wall is higher than usual." +
        " It also semes quite new.\n");
    add_item("gate", "The wooden gate is securly closed." +
        " Through a crack in the gate you think you see a" +
        " lush garden.\n");

    add_exit("26.c", "west", 0,1,0);
}
