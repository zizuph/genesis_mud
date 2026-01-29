inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("pearl", "pearls", "white", 432, 
        GEM_SOMEWHAT_RARE, 2, 4);
    set_long("@@default_gem_long@@  This lustrous, "+
        "finely-tinted bead is found in oysters and other "+
        "bivalve shellfish. Pearls come in a range of "+
        "colours, from white to pink, orange, and black. "+
        "They are valued for their perfect roundness and "+
        "elegant simplicity\n");

}


