inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("alexandrite", "alexandrites", "vivid", 4321,
        GEM_EXTREMELY_RARE, 1, 2);
    set_long("@@default_gem_long@@  Alexandrite is a very "+
        "rare and unique variety of chrysoberyl.  When viewed "+
        "in natural sunlight, it appears green to the eye, "+
        "but in incandescent light is red.  It is one of the "+
        "most sought-after and expensive of gemstones.\n");
}


