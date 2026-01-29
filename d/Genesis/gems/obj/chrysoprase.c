inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("chrysoprase", "chrysoprases", "green", 288, 
        GEM_SOMEWHAT_COMMON, 28, 36);
    set_long("@@default_gem_long@@  This chrysoprase is a "+
        "translucent, bright green variety of chalcedony. "+
        "It sometimes has a yellowish tint when held to the "+
        "light, creating a golden glow within the apple-green "+
        "stone.\n");
}

