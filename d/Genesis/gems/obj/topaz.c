inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("topaz", "topazes", "blue", 432, 
        GEM_SLIGHTLY_COMMON, 6, 10);
    set_long("@@default_gem_long@@  The topaz is a hard, "+
        "brilliant stone with a fine colour range, from "+
        "green and yellow to blue and violet, all very light, "+
        "yet vibrant. Its yellow colour is very rare and "+
        "expensive, and should not be confused with the "+
        "yellow quartz citrine.\n");
}


