inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("turquoise", "turquoise", "oval", 144, 
        GEM_COMMON, 7, 13);
    set_long("@@default_gem_long@@  An opaque gemstone of "+
        "moderate hardness, turqoise can be blue or green "+
        "and any shade between. This one is the highly-pleasing "+
        "blue-green colour webbed with fine veins of copper "+
        "and pyrite. It is usually cut very simply and polished "+
        "to a high sheen.\n");
}
