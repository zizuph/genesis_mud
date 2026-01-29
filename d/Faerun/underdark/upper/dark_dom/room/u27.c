#include "../defs.h"

inherit STD("room");

public void
dark_dom(void)
{
    set_short("You are in a cavern somewhere in the Dark Dominion");
    set_long("You find yourself within a small cavern in the Dark Dominion. "+
	"The ceiling is looming above you, a bit higher then the tunnels you've passed. "+
	"There's curving stalagmites which seem to grow up from the limestone floor and "+
	"they occationally meet the stalactites, which has been formed over centuries " +
	"by mineralized drops of water. Together these form pillars of stones, which seem " +
	"to uphold the rough stone ceiling.\n");

    add_item(({"sides","side","irregular walls","walls","wall"}),
	"The walls are nothing but bare uncut limestone.\n");

    add_exit("u24", "southwest", check_follow);
    add_exit("u26", "west", check_follow);
    add_exit("u30", "north", check_follow);
   

 }