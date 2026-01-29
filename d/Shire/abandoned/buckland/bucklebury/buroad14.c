inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 BB_DIR + "buroad13","east",0,1
#define EXIT2 BB_DIR + "buroad15","west",0,1
#define EXIT3 BB_DIR + "burrow3_1","south",0,1
#define EXIT4 BB_DIR + "burrow4_1","north",0,1

string *herbs;


void
create_room()
{
    int i;

    areaname  = "Bucklebury";
    land      = "Buckland";
    areatype  = 2;
    areadesc  = "grassy path";

    extraline = "The path that you are wandering along goes past some "+
    "small burrows.  There is one north of you, and another one is to the "+
    "south.  The path also continues to the east and west.";

    add_item(({"path","grassy path"}),"The path is quite well used, but "+
      "is still just a path.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
    add_exit(EXIT4);

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


