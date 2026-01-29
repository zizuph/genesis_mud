inherit "/d/Shire/eastroad/std/er_base";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev5","southeast",0,1
#define EXIT2 EVENDIM_DIR + "ev7","northwest",0,1

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "valley between rolling hills";
    grass = "blue-green";
    extraline = "The narrow valley pass shrinks somewhat "+
      "here as a projection of the nearest hill forces you to "+
	"go around or over it.  The only ways out are "+
	  "northwest and southeast.";
    add_item(({"projection","nearest hill"}),
	     "This projection, shaped like a tree-limb, nearly "+
	     "crosses the small valley.\n");
    add_item(({"pass","valley pass"}),
	     "The narrow pass goes between large, steep hills.\n");
    add_item(({"hills","larger hills","steep hills","hill"}),
	     "The larger hills are a deep blue at the top, from the "+
	     "blue-green grass that coats them from summit to base. "+
	     "They are too steep to climb.\n");
    add_exit(EXIT1);
    add_exit(EXIT2);
    set_noshow_obvious(1);
}
