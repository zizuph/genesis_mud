#include "forest.h"

create_forest()
{
    set_short("Along a river bend");
    set_long(
	"You are standing on the bank of a large river to the southeast. "+
	"It bends slowly from the northeast to the south here, and by "+
	"the river there is a small track you could follow. In all the "+
	"other direction you could go, but then you would end up in the "+
	"surronding forest.\n");
    add_item(({"river","greyflood"}),
	"It is quite wide and you wouldn't like to try to swim there..\n");
    add_item(({"bank","track"}),
	"The track by the river bank leads in the northeast-southwest "+
	"direction.\n");

    SOUTHWEST("f0202");
   //WEST("f0203");
    NORTHWEST("f0204");
    NORTH("f0304");
    NORTHEAST("f0404");
}
 