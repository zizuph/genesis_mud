inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of pearl", "shards of pearl", "white", 44, 
        GEM_SOMEWHAT_RARE, 2, 4);
    set_long("@@default_gem_long@@  The shard is from "+
	     "a lustrous and finely-tinted bead, found in oysters and other "+
	     "bivalve shellfish. Pearls come in a range of "+
	     "colours, from white to pink, orange, and black. "+
	     "They are valued for their perfect roundness and "+
	     "elegant simplicity\n");
    add_name("shard");
    add_pname("shards");
    add_name("pearl");
    add_pname("pearls");
    add_name("shard_of_pearl");
    add_name("pearl_shard");
    add_name("white_pearl_shard");
    add_name("shard_pearl");
    add_name("pearl shard");
    add_pname("pearl shards");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "white pearl";
}


