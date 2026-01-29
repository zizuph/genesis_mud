inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("beryl", "beryls", "red", 4500, 
        GEM_EXTREMELY_RARE, 2, 3);
    set_long("@@default_gem_long@@ Beryl is a lustrous, "+
        "transparent family of gemstones, including emerald "+
        "and aquamarine. This particular colour of beryl is "+
        "rarer and more durable than emerald, making it a "+
        "bit more valuable.\n");
}


