inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define EXIT1 EVENDIM_DIR + "ev4","southeast",0,1
#define EXIT2 EVENDIM_DIR + "ev6","northwest",0,1

void
create_er_room()
{
    area = "in";
    areaname = "the hills of Evendim";
    land = "the Shire";
    areatype = 1;
    areadesc = "valley between rolling hills";
    grass = "blue-green";
    extraline = "Here the track bends away from the river "+
      "in a sort of valley pass between the larger hills.  The "+
	"track leads northwest and southeast.";
    add_item(({"track","river"}),
	     "The track is barely noticeable in the  blue-green grass, "+
	     "but ever and anon it bends towards the river to the "+
	     "southeast.\n");
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
