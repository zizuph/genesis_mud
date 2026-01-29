inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("spinel", "spinels", "violet", 369, 
        GEM_SOMEWHAT_COMMON, 4, 7);
    set_long("@@default_gem_long@@  The spinel is a hard, "+
        "brilliant stone with a wide colour range. In its "+
        "red and blue shades it is often difficult to "+
        "distinguish spinel from ruby and sapphire. More "+
        "abundant and thus less costly than its precious "+
        "counterparts, this pale violet spinel is a fine "+
        "gemstone in its own right.\n");
}


