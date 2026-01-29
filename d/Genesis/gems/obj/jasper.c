inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("jasper", "jaspers", "red", 72, 
        GEM_VERY_COMMON, 50, 82);
    set_long("@@default_gem_long@@  Jasper is a multicoloured "+
        "quartz aggregate. It is opaque, compact, and occurs "+
        "in a variety of earth-toned,  vibrant colours. It is "+
        "the perfect hardness for carving, and develops a "+
        "beautiful lustre when polished.\n");
}
