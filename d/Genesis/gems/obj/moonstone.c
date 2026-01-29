inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("moonstone", "moonstones", "lambent", 216, 
        GEM_SLIGHTLY_COMMON, 28, 46);
    set_long("@@default_gem_long@@  Moonstone is an opalescent "+
        "pearly-blue semi-precious stone. Its name is derived "+
        "from the billowy, floating light effect produced when "+
        "it is moved. It is the perfect hardness for carving, "+
        "and requires very little polishing to produce a lustrous "+
        "sheen.\n");
}
