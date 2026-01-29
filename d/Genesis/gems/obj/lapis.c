inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("lapis lazuli", "lapis lazulis", "blue", 576, 
        GEM_SOMEWHAT_RARE, 2, 3);
    set_long("@@default_gem_long@@  Lapis Lazuli is a "+
        "semi-precious gemstone with a vivid blue hue. "+
        "It is opaque, with areas of lighter blue and "+
        "spider-silk fine veins of pyrite. In antiquity, "+
        "this stone was called sapphire.\n");
}


