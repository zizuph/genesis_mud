inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("chalcedony", "chalcedonies", "striped", 144, 
        GEM_COMMON, 40, 67);
    set_long("@@default_gem_long@@  This chalcedony is a "+
        "variety of banded quartz. It is usally opaque and "+
        "banded with a variety of colours that create a "+
        "beautiful surreal landscape for the eye. It is a "+
        "lustrous, medium-hard stone, easily cut and polished, "+
        "but durable.\n");
}
