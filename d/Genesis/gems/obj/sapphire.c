inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("sapphire", "sapphires", "blue", 2345, 
        GEM_RARE, 2, 4);
    set_long("@@default_gem_long@@  Sapphire is a gem "+
        "of great value, brilliance, and durability. The "+
        "finest sapphires are the blue variety, clear and "+
        "neither too pale nor too dark. It also comes in "+
        "other colours, especially yellow and pink, and "+
        "some beautiful shades of green. Like ruby, it is "+
        "a variety of corundum, second only to diamond in "+
        "hardness.\n");
}


