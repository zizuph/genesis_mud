inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("carnelian", "carnelians", "red", 288, 
        GEM_SOMEWHAT_COMMON, 26, 38);
    set_long("@@default_gem_long@@  Carnelian is a reddish "+
        "variety of chalcedony, ranging from pink to red and "+
        "orange-red, with lacy swirls of milky-white quartz. "+
        "It is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable.\n");
}

