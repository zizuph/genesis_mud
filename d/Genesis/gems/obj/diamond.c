inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("diamond", "diamonds", "glittering", 6048,
        GEM_VERY_RARE, 1, 2);
    set_long("@@default_gem_long@@  Diamond is a rare, "+
        "brilliant gem of incredible hardness and dura"+
        "bility.  Its most common colour is the clear "+
        "white, but on rare occasions it can be found in "+
        "others such as blue, black, and yellow.\n");
}


