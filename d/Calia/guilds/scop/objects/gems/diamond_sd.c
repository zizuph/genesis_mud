inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of diamond", "shards of diamond", "glittering", 605,
        GEM_VERY_RARE, 1, 2);
    set_long("@@default_gem_long@@  The shard is from a rare, "+
        "brilliant gem of incredible hardness and dura"+
        "bility.  Its most common colour is the clear "+
        "white, but on rare occasions it can be found in "+
        "others such as blue, black, and yellow.\n");
    add_name("shard");
    add_pname("shards");
    add_name("diamond");
    add_pname("diamonds");
    add_name("diamond shard");
    add_pname("diamond shards");
    add_name("diamond_shard");
    add_name("shard_diamond");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "diamond";
}


