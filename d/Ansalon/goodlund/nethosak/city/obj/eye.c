inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("eye", "eyes", "shimmering", 0, 
        GEM_VERY_RARE, 0, 0); 
    set_name("_ansalon_magic_gem_");
    add_name("_holy_eye_quest_");
    set_long("This is a shimmering red eye. Perhaps it "+
             "can fit into a statue.\n"); 

}

