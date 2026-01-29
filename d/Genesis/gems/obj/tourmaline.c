inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("tourmaline", "tourmalines", "banded", 432, 
        GEM_SLIGHTLY_RARE, 7, 14);
    set_long("@@default_gem_long@@  This versatile "+
        "gemstone is available in every color, in every "+
        "tone, from deep to pastel and even with two or "+
        "more colors appearing in the same stone, side "+
        "by side, in distinct bands. Tourmaline is fairly "+
        "hard, durable, and brilliant.\n");

}


