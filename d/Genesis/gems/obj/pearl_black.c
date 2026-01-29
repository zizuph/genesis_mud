inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("pearl", "pearls", "black", 1728, 
        GEM_RARE, 2, 4);
    set_long("@@default_gem_long@@  This bead is black "+
        "as the underdark. It is lustrous and perfectly "+
        "round, making it a very rare and very expensive "+
        "pearl.\n");

}


