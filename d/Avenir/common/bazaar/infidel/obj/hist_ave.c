inherit "/std/scroll";
#include "../infidel.h"

public void
create_scroll(void)
{
    set_name(({"vellum","scroll"}));
    set_adj(({"aged","well-worn"}));

    set_long("This is an aged vellum scroll from times long "+
	"past. It is apparent that it has been handled many times "+
	"for it is well-worn but has also clearly been carefully "+
	"tended to and preserved.\n");
    
    set_file(OBJ + "hist_ave.scroll");
}

