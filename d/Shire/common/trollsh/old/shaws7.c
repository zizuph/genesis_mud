/* File: /d/Shire/common/trollsh/shaws7.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/


create_shawrom()
{

    set_short("Some kind of clearing in the Trollshaw");
    set_extraline(
	 "While there is dense brush all over the shaw, "
	+"this place seems to be almost without bushes. Only a few of them "
	+"grow here. This place can't really be called a clearing, though, since "
	+"the pine trees are blocking all visibility to the sky. To the north "
 +"the vegetation appears to be only slightly heavier.  "
	+"Walking along the small path going up the slope to the northeast would "
	+"take you atop a ridge to the east. In the opposite direction, to the "
	+"southwest, there is another ridge. A small path leads up there. ");


    NORTHEAST("shaws12");
    SOUTHWEST("shaws5");
    NORTH("shaws8");

}
