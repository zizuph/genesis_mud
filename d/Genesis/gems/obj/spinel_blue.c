inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("spinel", "spinels", "blue", 864, 
        GEM_SOMEWHAT_RARE, 4, 7);
    set_long("@@default_gem_long@@  The spinel is a hard, "+
        "brilliant stone with a wide colour range. In this, its "+
        "deep spectral-blue shade, it is difficult to distinguish "+
        "from sapphire, save that its colouration makes it look "+
        "more like a sapphire than the real one. Hardier and more "+
        "abundant than its precious counterpart, the blue spinel "+
        "is an exquisite gemstone in its own right.\n");
}


