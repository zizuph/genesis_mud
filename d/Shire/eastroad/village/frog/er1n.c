inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 ER_DIR + "village/frog/er1","south",0,1
#define EXIT2 ER_DIR + "village/frog/er2n","north",0,1


void
create_room()
{
   int i;
   string *herbs;
   
   area = "passing through"; /* Distance from areaname */
   areaname = "Frogmorton";
   land = "the Shire";
   areatype = 10;
   areadesc = "village";
   grass = "green";
   
   extraline = "This is a major village along the eastroad as "+
   "not many Shire villages can brag about having a bank, post office and shop. "+
   "Apparently the hobbits here are trying to attract travelers "+
   "to their commercial enterprizes. However this has taken "+
   "a toll on the villagers so they have hired guards to protect "+
   "them from the ever increasing number of rowdy strangers visiting "+
   "the village.";
   
   add_item (({"frogmorton","village of frogmorton"}),"This village "+
      "is somewhat larger than most other Shire villages. The "+
      "villagers seem to be trying to turn it into a commercial "+
      "center to take advantage of the traffic along eastroad.\n");
   
   
	add_exit(EXIT1);
	add_exit(EXIT2);

   herbs = ({HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))],
         HERBS[random(sizeof(HERBS))]});
   
   for(i = 0; i < sizeof(herbs); i++)
   add_herb_file(herbs[i]);
   add_prop(OBJ_S_SEARCH_FUN,"herb_search");
   add_prop(OBJ_I_SEARCH_TIME,8);
   
   set_search_places(({"hills","hill","grass","plain","plains","ground"}));
   
   make_the_room();
}
reset_room()
{
   ::reset_room();
   set_searched(0);
}

