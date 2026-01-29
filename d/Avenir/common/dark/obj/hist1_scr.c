inherit "/std/scroll.c";
#include "/d/Avenir/common/dark/dark.h"

create_scroll()
{
    set_name("scroll");
    set_adj("old");
    set_long("An old almost unreadable scroll.\n");
    
    set_file(OBJ+"hist1.scroll");
}

