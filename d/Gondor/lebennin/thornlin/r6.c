#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("dusty");
    set_whereis("in");
    set_crop("wheat");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");

    set_extraline("The road is running from east to west. On both sides "
      + "of the road are farming fields. Far to the north the mountains "+
      "of the Ered Nimrais are rising.");

    add_item(({"field","fields"}),"On the nearst field north of here you "+ 
      "see "+crop+" growing.\n");

    add_item(({"mountain", "mountains", "white mountains", "ered nimrais", }),
      BSN("Beyond the fields north of the road the White Mountains of "
	+ "Gondor, the Ered Nimrais, can be seen in the distance. The caps "
	+ "of the mighty mountains are covered by snow."));

    add_exit(THORN_DIR + "r5","west",0,1);
    add_exit(THORN_DIR + "r7","east",0,1);
    add_exit(THORN_DIR + "f7","north",0,2);
    add_exit(THORN_DIR + "f2","south",0,2);

}
