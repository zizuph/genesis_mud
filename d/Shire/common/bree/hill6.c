#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{
    set_short("At the end of the road on Bree-Hill.");
    set_long(
	    "You have reached an end to the road. There is a house "+
	    "right east and one more south of here. A small sign has been "+
	    "put on the wall of the house here. The house looks magnificent "+
	    "and is rather large of size. There is a huge Oak tree standing next "+
	    "to the house here and It looks very old but somehow queer. The grassy "+
	    "fields can be seen even better from here. North there are some trees "+
	    "covering you view in that direction.\n");

    add_exit(STAND_DIR + "house1", "enter", 0);
    add_exit(STAND_DIR + "hill5", "west", 0);
    add_exit(STAND_DIR + "hill5s", "south", 0);

    add_item(({"tree","oak"}),
	    "The oak tree looks very odd. It is huge and thick, and somehow it looks "+
	    "like there is eyes on the tree, staring at you!! It is not bent like old "+
	    "trees usually is. You wonder why it looks so odd and strange.\n");

    add_item(({"house"}),
	    "This house is build by humans, that is easy to see. But the garden is so beautiful "+
	    "and it is almost like if the hobbits have been there and worked on it. The door "+
	    "is of solid Oak and you can not possibly break in that door.\n");

    add_item(({"fields"}),
	    "The fields east and north of Bree is vast areas. There is not as many trees "+
	    "on the plains as it used to be in the earlier years. Only grass there as far "+
	    "the eye can see.\n");

    add_item(({"sign"}), "@@sign_long");

}

init()
{ ::init();
    add_action("do_read", "read");

}

do_read(str)
{
    if (str == "sign" || str == "small sign");
    {
	write(sign_long());
	return 1;
    }
}

sign_long()
{
    return "The sign reads: Here is something we dont know yet quite!.\n";
}
