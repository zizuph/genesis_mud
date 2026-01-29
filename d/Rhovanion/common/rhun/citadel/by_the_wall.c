
inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("By the citadel wall");
    set_long("You stand on the eastern side of a tall, menacing "+
	"black wall.  It is made of some shiny black stone, though you don't "+
    "know its origins, and stretching up for almost ten "+
 	"meters.  The wall "+
	"looks quite thick, and strong, and you can understand "+
	"why the citadel which stands behind it has stood for so "+
	"long.  You may pass beneath the wall, through the citadel "+
	"gates, by moving westward, or take up the path of a wide "+
        "dirt road which dead-ends here off to the east.  "+
	"\n");

    AE(RHUN+"citadel/gate","west");
    AE(RHUN+"roads/section10/v","east");

}

