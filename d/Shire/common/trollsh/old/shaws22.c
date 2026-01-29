// File: /d/Shire/common/trollsh/trollsh22.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw. Along a path");
    add_my_desc("Here the shaws grow terribly dense. "
	+"Several spruces and sturdy bushes makes this place very narrow. " 
	+"You find several exits out here. West and east along a path, "
    +"southwest and southeast between spruces and bushes.\n");

    add_item(({"path"}),"There is a path here, going in a east-west direction. \n");
    
    add_exit(STAND_DIR + "shaws21", "east");
    add_exit(STAND_DIR + "shaws23", "west");
    add_exit(STAND_DIR + "shaws24", "southwest");
    add_exit(STAND_DIR + "shaws16", "southeast");    
}
