inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 GREEN_DIR + "vill1","northeast",0,1
#define EXIT2 GREEN_DIR + "path2","northwest",0,1



void
create_er_room()
{
   int i;
   string *herbs;

   area = "outside of";
   areaname = "Greenfields";
   land = "the Shire";
   areatype = 2;
   areadesc = "field";
   grass = "green";

   extraline = "This twisty path leads through very jagged hills.  The "+
   "path gets twistier to the northwest and smooths out as it reaches "+
   "an intersection to the northeast.";

   add_item(({"path","twisty path"}),"The path makes a narrow curve "+
   "here in the jagged hills, leading northwest and northeast.\n");

   add_item(({"hills","hill","bushes","bush"}),
   "The hills themselves, while steep, look very rich and full of life.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);


   herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
   set_search_places(({"bushes","bush","field","fields","ground","grass"}));
 
}
reset_room()
{
  set_searched(0);
}


