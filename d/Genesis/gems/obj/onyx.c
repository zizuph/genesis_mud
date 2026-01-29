inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("onyx", "onyxes", "black", 216, 
        GEM_SLIGHTLY_COMMON, 5, 9);
    set_long("@@default_gem_long@@  Onyx is a black variety "+
        "of chalcedony, often one solid colour, but usually "+
        "banded with white, red, or green chalcedony as well. "+
        "It is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable.\n");
}

