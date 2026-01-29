// File: /d/Shire/common/trollsh/trollsh21.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw. Along a path.");
    set_extraline("Here the shaws grow terribly dense. "
	+"Many spruces and thick bushes makes this place very narrow."
	+"You find several exits out of here. West and east along a path and "
        +"southwest and southeast between spruces and bushes. ");

add_item(({"path"}),"There is a path here, going in a east-west direction. \n");

    
    EAST("shaws20");
    WEST("shaws22");
    SOUTHWEST("shaws25");
    SOUTHEAST("shaws19");
}
