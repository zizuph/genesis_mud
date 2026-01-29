/* File: /d/Shire/common/trollsh/shaws2.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/



create_shawrom()
{

    set_short("West in the Trollshaws");
    set_extraline("You are northwest on a ridge filled with " +
        "bushes and small spruce trees. There is a slope leading " +
        "north into a dense pine forest and paths that lead east " +
        "and south.\n");

 	EAST("shaws5");
	SOUTH("shaws1");
	NORTH("shaws3");
}
