inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/include/deities.h"

void
create_gems()
{
    config_gems("ruby", "rubies", "star", 4123, GEM_VERY_RARE, 2, 4);
    
    set_long("@@default_gem_long@@ Ruby is the red variety of the mineral "+
        "corundum. Though it may range in colour from a yellowish red "+
        "to a deep red-violet, the most highly valued colour is a pure "+
        "spectral red with the faintest hint of blue. The star ruby is "+
        "a rarer form of the gem. Star rubies and sapphires show a "+
        "bright six-legged star in the dome of their cabochon. The stars "+
        "are formed by light reflecting off tiny inclusions in the stone. "+
        "Many cultures attribute this unique formation to be the "+
        "result of divine influence, including in Sybarus where such "+
        "star jewels are said to have been touched by Nitikas.\n");
            
    add_prop(NITIKAS_OFFERING, 1);   
}
