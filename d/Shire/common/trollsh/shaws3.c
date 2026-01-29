/* File: /d/Shire/common/trollsh/shaws3.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"


create_shawrom()
{
    set_short("Northwest in the Trollshaw pine forest.");
    set_extraline(
	 "You are in a dense pine forest in the Trollshaws. "
	+"The trees are tall and thick, so you can barely see the sky. "
        +"The shadows from the trees all around you make this place "
	+"rather spooky. It all makes you feel very unsafe. The forest "
	+"floor is scattered with sprigs and cones. To the north and west "
	+"the forest is so dark and gloomy you choose not to go there. ");

    EAST("shaws6");
    SOUTH("shaws2");
    
    /* just putting in a link to the new eastroad -Vadiem */
    /* add_exit( ER_DIR + "vroad2n.c","west",0,2); */

}
