inherit "/std/scroll.c";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_scroll()
{
    set_name("scroll");
    set_adj("blue");
    set_short("blue scroll");
    set_long("The blue scroll looks a bit weatherbeaten, but still can be "
	   + "read. It contains a strange little rhyme.\n");
    set_file(STAND_DIR + "quest_rhyme.txt");
}
