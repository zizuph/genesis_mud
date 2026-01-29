#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err5","northeast",0,2
#define EXIT2 ERE_DIR + "err13","south",0,2
#define EXIT3 ERE_DIR + "err21","west",0,2

void
create_er_room()
{

    area = "in";
    areaname = "a ravine";
    land = "Eriador";
    areatype = 5;
    areadesc = "path";
    grass = "green";

    extraline = "Climbing over and moving through the "+
    "rocks and boulders in this ravine is not "+
    "easy. At the top of the ravine, dark trees seem to be "+
    "the only vegatation in the area. Steep paths rising to the "+
    "the top of the ravine are west and south.";



    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
}
