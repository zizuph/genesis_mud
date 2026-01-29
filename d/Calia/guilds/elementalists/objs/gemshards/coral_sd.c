inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of coral", "shards of coral", "pink", 8, 
        GEM_VERY_COMMON, 4, 5);
    set_long("@@default_gem_long@@  The shard is from an organic "+
        "gemstone taken from coral reefs in the sea. It ranges "+
        "from semi-translucent to opaque and occurs in a wide "+
        "range of colours. It is fairly soft, making it easy "+
	"to carve, and it is easily polished to a fine lustre.\n");
    add_name("shard");
    add_pname("shards");
    add_name("coral");
    add_pname("corals");
    add_name("pink coral shard");
    add_pname("pink coral shards");
    add_name("coral shard");
    add_pname("coral shards");
    add_name("pink_coral_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "coral";
}
