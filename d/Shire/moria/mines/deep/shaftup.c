#include "defs.h"

string *ldesc;
int pos;

object rope()
{
    return THIS_DIR+"shaft1"->query_rope();
}

CONSTRUCT_ROOM
{
}

setup_pos(int p)
{
    pos = p;
    set_long("You are climbing on a "+rope()->short()+" in a deep shaft "+
	"in the Mines of Moria. You are at position: "+pos+"\n");
    set_short("In a shaft");
}
