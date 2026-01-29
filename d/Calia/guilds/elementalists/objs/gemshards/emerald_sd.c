inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of emerald", "shards of emerald", "lucent", 720,
        GEM_VERY_RARE, 2, 3);
    set_long("@@default_gem_long@@ The shard is from a variety "+
        "of the mineral beryl, and in its green colour, "+
        "one of the most highly prized of all gems. The "+
        "finest-quality emeralds have the colour of new "+
        "grass, an almost pure spectral green, with a "+
        "very faint tint of blue.\n");
    add_name("shard");
    add_pname("shards");
    add_name("emerald");
    add_pname("emeralds");
    add_name("emerald shard");
    add_pname("emerald shards");
    add_name("emerald_shard");
    add_name("shard_emerald");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "emerald";
}


