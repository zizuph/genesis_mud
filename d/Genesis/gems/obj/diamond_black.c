inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("diamond", "diamonds", "black", 6348,
        GEM_EXTREMELY_RARE, 1, 2);
    set_long("@@default_gem_long@@ Dark and ominous, this gem, "+
	"rather than reflecting light, seems to shine with a "+
	"brilliance of its own. Also known as carbonados it is "+
	"a rare type of diamond and quite valuable.\n");
}
