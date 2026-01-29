inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("emerald", "emeralds", "lucent", 4321,
        GEM_VERY_RARE, 2, 3);
    set_long("@@default_gem_long@@  Emerald is a variety "+
        "of the mineral beryl, and in its green colour, "+
        "one of the most highly prized of all gems.  The "+
        "finest-quality emeralds have the colour of new "+
        "grass, an almost pure spectral green, with a "+
        "very faint tint of blue.\n");
}


