inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("tourmaline", "tourmalines", "pink", 6420, 
        GEM_EXTREMELY_RARE, 6, 13);
    set_long("@@default_gem_long@@  This is a very rare "+
        "colour of the brilliant tourmaline gemstone, a "+
        "lovely, clear rose-pink that is very appealing "+
        "to the eye. Larger, unoccluded pink tourmalines "+
        "are more highly valued than diamonds of the same "+
        "size.\n");

}


