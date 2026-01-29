inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of carnelian", "shards of carnelian", "red", 29, 
        GEM_SOMEWHAT_COMMON, 3, 5);
    set_long("@@default_gem_long@@  The shard is from a reddish "+
        "variety of chalcedony, ranging from pink to red and "+
        "orange-red, with lacy swirls of milky-white quartz. "+
        "It is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable.\n");
    add_name("shard");
    add_pname("shards");
    add_name("carnelian");
    add_pname("carnelians");
    add_name("carnelian_shard");
    add_name("carnelian shard");
    add_pname("carnelian shards");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "carnelian";
}

