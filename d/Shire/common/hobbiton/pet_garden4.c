inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_room()
{
   set_short("a garden ");
   set_long("You stand in a garden, surrounded by the "+
   "wonderful smells of herbs all around. "+
   "The trees here are not very leafy and tall. "+
   "They do not seem to have anything at all.\n");

   add_item(({"trees","tree","tall trees"}),
   "You can't tell from here if there's anything on top of them.\n");

   add_exit("/d/Shire/common/hobbiton/pet_garden3","west",0,1);
   add_exit("/d/Shire/common/hobbiton/pet_garden5","east",0,1);


    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"tree","trees","tall trees"}));
    add_herb_file(HERB_DIR + "treemushroom");

}
