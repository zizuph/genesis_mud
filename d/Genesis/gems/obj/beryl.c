inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("beryl", "beryls", "yellow", 400, 
        GEM_SLIGHTLY_RARE, 3, 5);
    set_long("@@default_gem_long@@ Beryl is a lustrous, "+
        "transparent family of gemstones, including emerald "+
        "and aquamarine. It is colourless in its pure form, "+
        "but is also found in green, yellow, pink, and blue. "+
        "The rarest and most expensive is the red beryl.\n");

}


