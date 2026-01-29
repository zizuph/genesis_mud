#include "forest.h"

create_forest()
{
    set_short("By the river");
    set_long(
	"You are standing on the bank of a large river to the southeast "+
	"and east. It bends slowly from the north to the southwest here, and by "+
	"the river there is a small track you could follow. In all the "+
	"other direction you could go, but then you would end up in the "+
	"surronding forest. On the other side you notice no forest, merely"+
	"damp marshes.\n");
    add_item(({"river","greyflood"}),
	"It is quite wide and you wouldn't like to try to swim there..\n");
    add_item(({"bank","track"}),
	"The track by the river bank leads in the northeast-southwest "+
	"direction.\n");
    add_item(({"marshes","march","other side", "river"}),
	"Well, surely this might be a delta of another river into the "+
	"river.\n");

    SOUTHWEST("f0202");
    //WEST("f0203");
    NORTHWEST("f0204");
    NORTH("f0304");
    //NORTHEAST("f0404");
}
