inherit "/d/Shire/eastroad/std/er_base.c";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 MICH_DIR + "fairfield","northeast"
#define EXIT2 MICH_DIR + "fairroad2","west"
#define EXIT3 MICH_DIR + "dondelHouse", "east"

void
create_er_room()
{
    area = "in";
    areaname = "Michel Delving";
    land = "the Shire";
    areatype = 1;
    areadesc = "field";
    grass = "green";

    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    extraline = "The path ends here at a white picket gate, separating the "+
    "lane from Fair Field.  The fresh greenness of this place is not marred "+
    "by any season or weather.  The air is sweet with the beauty of nature.  "+
    "West will lead back to the main parts of Michel Delving. ";
//You can enter the Fair Field by going east.

    add_item(({"field","fair field","fair"}),
      "The Fair Field is just beyond the white picket gate here.\n");

    add_item(({"white picket gate","gate","picket gate","latch"}),
      "The white picket gate is more for decoration than security, "+
      "its latch is probably sufficient for keeping nosy hobbits out.\n");

    add_item(({"path","grey path","grey gravel path"}),
      "The gravel path diminishes here, leaving beautiful green grass.\n");


//    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);

}
