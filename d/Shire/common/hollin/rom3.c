#include "lakeroom.h"

create_lakeroom() {
    set_short("NORTH end of lake");
    set_long(
	"The main path from the south turns to the east here. "+
	"However the eastern path seems to cross a slimy brooklet. "+
	"A small path continues upwards to the north. ");
    EXIT("rom4","north");
    EXIT("rom2","south");
    EXIT("rom6","east");
    add_item(({"path","brooklet"}),"Try to go there first.\n");
}
