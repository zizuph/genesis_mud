inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of garnet", "shards of garnet", "orange-red", 37, 
        GEM_SOMEWHAT_COMMON, 4, 8);
    set_long("@@default_gem_long@@  The shard is from a hard, "+
        "durable, and brilliant gemstone that is well-known "+
        "for its size and clarity. Garnet can be found in "+
        "nearly every shade of colour except blue.\n");
    add_name("shard");
    add_pname("shards");
    add_name("garnet");
    add_pname("garnets");
    add_name("garnet_shard");
    add_name("garnet shard");
    add_pname("garnet shards");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "garnet";
}


