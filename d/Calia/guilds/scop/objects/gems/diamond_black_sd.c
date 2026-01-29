inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of diamond", "shards of diamond", "black", 635,
        GEM_EXTREMELY_RARE, 1, 2);
    set_long("@@default_gem_long@@ The shard is from a dark and " +
	     "ominous black gem. Rather than reflecting light, " +
	     "it seems to shine with a "+
	     "brilliance of its own. Also known as carbonados it is "+
	     "a rare type of diamond and quite valuable.\n");
    add_name("shard");
    add_pname("shards");
    add_name("diamond");
    add_pname("diamonds");
    add_name("black diamond");
    add_pname("black diamonds");
    add_name("black_diamond_shard");
    add_name("black diamond shard");
    add_pname("black diamond shards");
    add_name("diamond shard");
    add_name("shard_diamond");
    add_name("black_shard_diamond");
    add_pname("diamond shards");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "black diamond";
}
