inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/macros.h"
#include "/d/Shire/common/herbs/herb_list.h"

#define EXIT1 BB_DIR + "buroad10","east",0,1
#define EXIT2 BB_DIR + "burrow1_1","west",0,1

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
    "You can enter it by walking west, or you can get back onto the main "+
    "path by going east.";

    add_item(({"path","grassy path"}),"The path is quite well used, but "+
      "is still just a path.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
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


