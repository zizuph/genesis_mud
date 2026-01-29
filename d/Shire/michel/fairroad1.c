inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "wisegarden","south"
#define EXIT2 MICH_DIR + "fairroad2","east"
#define EXIT3 MICH_DIR + "gamroad1","west"



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
    extraline = "The path through this field leads to the Fair Field, where "+
    "the Midsummer's Fair is held every seven years.  White picket fences "+
    "separate the grey gravel path from the green lawns of the residents here. "+
    " West is the main road of Michel Delving, and east will take you to the "+
    "Fair Field.  South is a house with a garden in front.";

    add_item(({"field","fair field","fair"}),
      "This field is green and rolling like the Fair Field, only not lined with "+
      "tall slender willow trees.\n");

    add_item(({"fence","fences","white picket fences","picket fences"}),
      "The fences are freshly painted and in good order.\n");

    add_item(({"path","grey path","grey gravel path"}),
      "The path is made of crushed stones, probably from a nearby mill.\n");

    add_item(({"lawn","lawns","green lawns","green lawn"}),
      "Those who live here maintain their lawns beautifully.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
}
