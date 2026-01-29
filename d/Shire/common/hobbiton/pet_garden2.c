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
   "The trees here are low and stubby and there may "+
   "be some herbs underneath them.\n");

   add_item(({"trees","short trees","short stubby trees"}),
   "You can't tell from here if there's anything under them.\n");

   add_exit("/d/Shire/common/hobbiton/pet_garden","west",0,1);
   add_exit("/d/Shire/common/hobbiton/pet_garden3","east",0,1);


    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"tree","trees","stubby trees"}));
    add_herb_file(HERB_DIR + "grass");

}
