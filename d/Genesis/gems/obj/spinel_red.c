inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("spinel", "spinels", "red", 864, 
        GEM_SOMEWHAT_RARE, 4, 7);
    set_long("@@default_gem_long@@  The spinel is a hard, "+
        "brilliant stone with a wide colour range. In this, its "+
        "astonishing crimson shade, it is difficult to distinguish "+
        "from ruby, save that its colouration makes it look "+
        "more like a ruby than the real one. Hardier and more "+
        "abundant than its precious counterpart, the red spinel "+
        "is an exquisite gemstone in its own right.\n");
}


