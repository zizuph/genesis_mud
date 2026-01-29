inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/include/deities.h"

void
create_gems()
{
    config_gems("sapphire", "sapphires", "star", 4000, GEM_VERY_RARE, 2, 4);
    
    set_long("@@default_gem_long@@ Sapphire is a gem of great value, "+
        "brilliance, and durability. The finest sapphires are the "+
        "blue variety, clear and neither too pale nor too dark. It also "+
        "comes in other colours, especially yellow and pink, and "+
        "some beautiful shades of green. Like ruby, it is a variety "+
        "of corundum, second only to diamond in hardness. The star "+
        "sapphire is a rarer form of the gem. Star rubies and sapphires "+
        "show a bright six-legged star in the dome of their cabochon. "+
        "The stars are formed by light reflecting off tiny inclusions "+
        "in the stone. Many cultures attribute this unique formation to "+
        "be the result of divine influence, including in Sybarus where "+
        "such star jewels are said to have been touched by Nitikas.\n");
            
    add_prop(NITIKAS_OFFERING, 1);          
}
