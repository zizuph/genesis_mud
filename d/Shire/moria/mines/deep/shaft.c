#include "defs.h"

CONSTRUCT_ROOM {
    set_short("In a steep shaft");
    set_long(
	"You are climbing in a steep shaft. The shaft continues "+
	"further down and looks rather dangerous. You can not "+
	"continue without the aid of climbing equipment. In the east "+
	"there is a narrow hole.\n");
    add_item(({"shaft","walls"}), "It is very steep, almost vertical.");
    add_item("hole","You seem to be able to squeeze into it.");
    EXIT("mjunc","up");
    EXIT("eelpass","east");
}
