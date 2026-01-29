inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


void
create_er_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
   area = "outside of";
   areaname = "Michel Delving";
   land = "Shire";
   areatype = 2;
   areadesc = "meadow";
   grass = "green";

   extraline = "You are just steps from the tiny village of "+
     "Michel Delving, opting for the country. All around "+
     "life flourishes, in the bushes, the trees, even the "+
     "air is alive, it seems. This path will "+
   "take you back to Michel Delving or further into the wilderness. "+
   "";

   add_item(({"path","white downs","downs","entrance"}),
   "This path to the southwest leads to a burrow under "+
   "the White Downs, it looks like some sort of entrance.\n");

   add_item(({"life","bushes","trees","tree","bush","air"}),
     "The vibrance of early spring is here year-round, it seems.  "+
     "Everything seems to be growing, right before your eyes.\n");

   add_item(({"path","michel delving","village","country","wilderness"}),
     "The path you stand on leads southwest towards Michel Delving "+
     "or north, farther into the wilderness.\n");

   add_exit(MICH_DIR + "gamroad5","southwest",0,1);
   add_exit(MICH_DIR + "farmrd2","northeast",0,1);

}
