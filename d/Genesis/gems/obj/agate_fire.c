inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("agate", "agates", "fire", 1500, GEM_EXTREMELY_RARE, 5, 5);
    set_long("@@default_gem_long@@  This is an extremely "+
	    "rare gemstone, rarer even than diamond, though not "+
		"nearly as valuable. Ovoid in shape, this trans"+
		"lucent agate appears to contain a myriad of small "+
		"bubbles or scales, all gleaming in a rainbow of colours "+
	    "tinged with a halo of reddish gold. It looks more like "+
	    "the egg of a miniature dragon than an actual gem, "+
		"and for this reason it is highly prized.\n");
}
