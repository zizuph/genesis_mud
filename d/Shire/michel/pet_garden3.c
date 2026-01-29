inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
inherit "/d/Shire/lib/herbsearch.c";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

void
create_room()
{
   set_short("a garden");
   set_long("You stand in a garden, surrounded by the "+
   "wonderful smells of herbs all around. "+
   "The bushes here are really thick, and could contain "+
   "many things.\n");

   add_item(({"bushes","thick bushes","really thick bushes"}),
   "You can't tell from here if there's anything under them.\n");

   add_exit(MICH_DIR + "pet_garden2","west",0,1);
   add_exit(MICH_DIR + "pet_garden4","east",0,1);


    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"bush","bushes","thick bushes"}));
    add_herb_file(HERB_DIR + "lianor_berry");

}
