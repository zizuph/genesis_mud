inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("garnet", "garnets", "orange-red", 369, 
        GEM_SOMEWHAT_COMMON, 4, 8);
    set_long("@@default_gem_long@@  The garnet is a hard, "+
        "durable, and brilliant gemstone that is well-known "+
        "for its size and clarity. Garnet can be found in "+
        "nearly every shade of colour except blue.\n");

}


