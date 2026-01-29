inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("coral", "corals", "pink", 72, 
        GEM_VERY_COMMON, 40, 41);
    set_long("@@default_gem_long@@  Coral is an organic "+
        "gemstone taken from coral reefs in the sea. It ranges "+
        "from semi-translucent to opaque and occurs in a wide "+
        "range of colours. It is fairly soft, making it easy "+
	"to carve, and it is easily polished to a fine lustre.\n");
}
