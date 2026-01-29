/* File: /d/Shire/common/trollsh/trollsh25.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"


create_shawrom()
{

    set_short("Deep in the Trollshaws on a ridge.");
    set_extraline("You find yourself northwest on a small ridge. "
	+"There are many spruces scattered around this place and several bushes makes "
	+"this place quite constricted.  Going east and south would take you "
	+"to another part of this ridge, while there are several paths "
        +"leading down from the ridge to the west, "
        +"nortwest and to the northeast. ");

add_item(({"path","paths"}),"There are four paths here, all leading down from this ridge. \n");
		   


    WEST("shaws24");
    SOUTH("shaws13");
    EAST("shaws16");
    NORTHWEST("shaws23");
    NORTHEAST("shaws21");
}
