/* File: /d/Shire/common/trollsh/shaws2.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/



create_shawrom()
{

    set_short("West in the Shaws");
    set_extraline(
	 "You are northwest on a ridge filled with bushes and small spruces. "
	+"There is a slope leading down to the north into a dense pine "
	+"forest. Should you choose that direction though, you would leave "
	+"this calm ridge that runs east from here. ");

 	EAST("shaws5");
	SOUTH("shaws1");
	NORTH("shaws3");
}
