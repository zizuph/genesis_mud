// File: /d/Shire/common/trollsh/trollsh23.c */

inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw");
    set_extraline("Here the shaws grow terribly dense. "
	+"Several spruces and sturdy bushes makes this place very narrow. "
	+"There are three exits out here that lead south and east along a path "
        +"and southeast between some spruces. ");

    add_item(({"path"}),"There are two paths here.\n");

    
    SOUTH("shaws24");
    EAST("shaws22");
    SOUTHEAST("shaws25");

}
