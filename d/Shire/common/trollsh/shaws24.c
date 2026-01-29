// File: /d/Shire/common/trollsh/trollsh24.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw");
    set_extraline("Here the shaws grow terribly dense. "
	+"Several spruces and sturdy bushes makes this place very narrow. "
	+"You find three exits from this place that lead north along a path, east up "
	+"to a ridge and northeast through some bushes. ");

add_item(({"path"}),"There are two paths here, one leads up to the ridge to the east, "
		   +"another one leads north.\n");

    
    NORTH("shaws23");
    EAST("shaws25");
    NORTHEAST("shaws22");

}
