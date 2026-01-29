inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("quartz", "quartzes", "rose", 12, 
        GEM_EXTREMELY_COMMON, 66, 88);
    set_long("@@default_gem_long@@  Quartz, perhaps the most "+
        "common mineral to occur in crystalline form, is also "+
        "beautiful and affordable. It can be found in all "+
        "colours of the spectrum, in both transparent and "+
        "opaque forms.\n");
}
