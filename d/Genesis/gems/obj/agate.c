inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("agate", "agates", "marbled", 72, 
        GEM_EXTREMELY_COMMON, 1, 2);
    set_long("@@default_gem_long@@  This agate is a type of "+
        "chalcedony quartz that is usually grey or brown. "+
        "Partially translucent, with opaque white inclusions "+
        "that form ribbons and swirls, it is usually polished "+
        "and cut into beads.\n");
}
