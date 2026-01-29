inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 BB_DIR + "buroad11","east",0,1
#define EXIT2 BB_DIR + "buroad14","west",0,1
#define EXIT3 BB_DIR + "burrow2_1","south",0,1

string *herbs;


void
create_room()
{
    int i;

    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "grassy path";

    extraline = "You are on a small path just outside of a small burrow. "+
    "The burrow is to the south of you, or you can continue walking along "+
    "the path.  If you go to the west, you will find some other burrows, "+
    "and if you go to the east, you will end up on the main road in "+
    "Bucklebury.";

    add_item(({"path","grassy path"}),"The path is quite well used, but "+
      "is still just a path.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    herbs = ({HERBS[random(sizeof(HERBS))],
      HERBS[random(sizeof(HERBS))],
      HERBS[random(sizeof(HERBS))]});

    for(i = 0; i < sizeof(herbs); i++)
    add_herb_file(herbs[i]);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);

    set_search_places(({"grass","ground","path","grassy path"}));


    make_the_room();
}


