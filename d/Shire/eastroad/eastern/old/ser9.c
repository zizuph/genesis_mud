#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 ERE_DIR + "ser8","northwest",0,1
#define EXIT2 ERE_DIR + "ser10","southeast",0,1

string *herbs;


create_er_room()
{
   int i;
   
   area = "west of";
   areaname = "the River Bruinen";
   land = "Eriador";
   areatype = 7;
   areadesc = "grassy path";
   grass = "green";
   
   
   
    extraline ="The trees provide some nice shade and make the "+
      "path very pleasant to walk along.  You can make out that "+
      "path continues to the northeast and to the southwest.";
    add_item(({"grass","grassy path","path"}),"The grass is green "+
      "and feels cool under your feet.  It looks healthy and there "+
      "are some things growing in it.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
    set_search_places(({"grass","path","ground"}));
   
   
}
reset_room()
{
   ::reset_room();
}
   
