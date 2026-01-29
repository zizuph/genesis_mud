inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of moonstone", "shards of moonstone", "lambent", 22, 
        GEM_SLIGHTLY_COMMON, 3, 5);
    set_long("@@default_gem_long@@  The shard is from an opalescent "+
        "pearly-blue semi-precious stone. Its name is derived "+
        "from the billowy, floating light effect produced when "+
        "it is moved. It is the perfect hardness for carving, "+
        "and requires very little polishing to produce a lustrous "+
        "sheen.\n");
    add_name("shard");
    add_pname("shards");
    add_name("moonstone");
    add_pname("moonstones");
    add_name("moonstone_shard");
    add_name("moonstone shard");
    add_pname("moonstone shards");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");
    
    // Need to properly set the gem name
    gem_name = "moonstone";
}
