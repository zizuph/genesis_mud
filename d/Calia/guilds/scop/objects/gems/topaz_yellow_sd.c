inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of topaz", "shards of topaz", "yellow", 173, 
        GEM_RARE, 4, 5);
    set_long("@@default_gem_long@@  The shard is from a hard, "+
        "brilliant stone with a fine colour range. This, its "+
        "wonderfully clear yellow colour, is very rare and "+
        "expensive, and should not be confused with the "+
        "yellow quartz known as citrine.\n");
    add_name("shard");
    add_pname("shards");
    add_name("topaz");
    add_pname("topazes");
    add_name("topaz shard");
    add_pname("topaz shards");
    add_name("yellow_topaz_shard");
    add_name("yellow_shard_topaz");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "topaz";
}


