inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("topaz", "topazes", "yellow", 1728, 
        GEM_RARE, 6, 10);
    set_long("@@default_gem_long@@  The topaz is a hard, "+
        "brilliant stone with a fine colour range. This, its "+
        "wonderfully clear yellow colour, is very rare and "+
        "expensive, and should not be confused with the "+
        "yellow quartz known as citrine.\n");
}


