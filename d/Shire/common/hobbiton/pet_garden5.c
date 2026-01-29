inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

void add_stuff();
void reset_room();

create_room()
{
   set_short("a garden ");
   set_long("You stand in a garden, surrounded by the "+
   "wonderful smells of herbs all around. "+
   "Nothing is here but some tall grass growing "+
   "up from the ground.\n");

   add_item(({"grass","ground","tall grass"}),
   "You can't tell from here if there's anything in there.\n");

   add_exit("/d/Shire/common/hobbiton/pet_garden4","west",0,1);


    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass","ground","tall grass"}));
    add_herb_file(HERB_DIR + "parsley");


   reset_room();
}
void
reset_room()
{
    add_stuff();
}

void add_stuff()
{
   object rock,rock2,rock3,rock4;

   if(!present("rocks"))
   {
   rock = clone_object("/d/Shire/common/hobbiton/obj/smallrock");
   rock->move(TO);

   rock2 = clone_object("/d/Shire/common/hobbiton/obj/smallrock");
   rock2->move(TO);

   rock3 = clone_object("/d/Shire/common/hobbiton/obj/smallrock");
   rock3->move(TO);

   rock4 = clone_object("/d/Shire/common/hobbiton/obj/smallrock");
    rock4->move(TO);

   }

}
