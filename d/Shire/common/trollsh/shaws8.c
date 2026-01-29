/* File: /d/Shire/common/trollsh/shaws8.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/


create_shawrom()
{

    set_short("In the Trollshaw");
    set_extraline("You are in the middle of the Trollshaws. To the east and "
	+"northeast you can see a small ridge. There are many bushes "
	+"here which prevent your moving as freely as you would "
	+"like in this frightening wood. To the north the brush "
	+"seems to grow even denser. To the northeast a slope leads "
	+"up to a ridge while to the southwest you would enter "
	+"a rather spooky pine forest. It seems to be possible "
	+"to go south as well. ");


  
	NORTH("shaws9");
	SOUTHWEST("shaws6");
	NORTHEAST("shaws13");
	SOUTH("shaws7");
    
}
