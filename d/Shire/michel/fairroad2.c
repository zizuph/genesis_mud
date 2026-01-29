inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 MICH_DIR + "newtask","north",0,0,1
#define EXIT2 MICH_DIR + "fairroad3","east"
#define EXIT3 MICH_DIR + "fairroad1","west"



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
    extraline = "This path looks well used by many feet over many many years. "+
    " East is the Fair Field, well known as the site of the Midsummer's Fair "+
    "held here in Michel Delving every seven years, where the new Mayor of "+
    "the Shire is chosen.  The path continues east towards the field and west "+
    "back to the main parts of Michel Delving.  North of here, a small cottage "+
    "sits on a slight hill.";

    add_item(({"field","fair field","fair"}),
      "This field is green and rolling like the Fair Field, only not lined with "+
      "tall slender willow trees.\n");

    add_item(({"cottage","hill","small cottage","slight hill"}),
      "The cottage is painted a fresh coat of white and sits on a smoothly "+
      "sloping grass hill.  You can enter it by going north.\n");

    add_item(({"path","grey path","grey gravel path"}),
      "The path is made of crushed stones, probably from a nearby mill.\n");

    add_item(({"lawn","lawns","green lawns","green lawn"}),
      "Those who live here maintain their lawns beautifully.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);

}
