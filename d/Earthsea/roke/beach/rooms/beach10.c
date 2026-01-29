/*
 * A beach in Roke by Ckrik, 9/2003
 */
#include "defs.h"

inherit ROKE_BEACH + "std/base_beach_sandy.c";
 
int no_pass()
{
  write("An invisible barrier has been erected here. " + 
	"It looks like you're going to have to come back " +
	"at a later date.\n");
  return 1;
}

void
create_beach()
{
    add_my_desc("A large cliff with stairs carved into it blocks " +
		"the beach to the north. Boulders chipped off the " +
		"face of the cliff lie its base.\n");
    add_item (({"beach", "rocky beach", "boulders", "boulder", "cliff"}),
        "The beach is rocky with broken boulders from the " +
        "cliff and from rocks that have come in with " +
	"the tide.\n");
    add_item("cliff",
        "The cliff towers over the beach. It " +
	"is impossible to climb over.\n");
    add_exit(ROKE_BEACH+"rooms/cliff01","up", &no_pass());
    add_exit(ROKE_BEACH+"rooms/beach09","southwest");
}
