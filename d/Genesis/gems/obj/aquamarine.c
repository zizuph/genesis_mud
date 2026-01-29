inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("aquamarine", "aquamarines", "blue-green", 436,
        GEM_SLIGHTLY_RARE, 2, 3);
    set_long("@@default_gem_long@@ Aquamarine is a member "+
        "of the beryl family, which includes emerald, but "+
        "it is more durable and less brittle than emerald. "+
        "It ranges in colour from palest blue to bluish "+
        "green to deep blue. Aquamarine is a brilliant "+
        "gemstone of excellent clarity.\n");

}


