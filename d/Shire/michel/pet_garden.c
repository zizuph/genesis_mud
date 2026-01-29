inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
inherit "/d/Shire/lib/herbsearch.c";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

void
create_room()
{
   set_short("a garden outside a cottage");
   set_long("You stand in a wonderful smelling herb garden, filled with "+
   "smells of all kinds- sweet, sensual and pleasant. "+
   "The cottage to your west is not well painted here, it seems "+
   "like someone decided that half a job was simpler than "+
   "the whole. A row of slim green bushes forms the border between here and "+
   "the rest of the garden.\n");

   add_exit(MICH_DIR + "pet_garden2","east",0,1);

    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"bush","bushes","slim bushes"}));
    add_herb_file(HERB_DIR + "huckleberry");

}
init()
{
    ::init();
    add_action("do_enter","enter");
}

int
do_enter(string str)
{
   if (str == 0)
   {
     write("Enter what?\n");
     return 1;
     }


   if (str != "window")
   {
     write("You try to enter the "+str+" but fail.\n");
   say(QCTNAME(TP)+ " tried to enter a "+str+", but didn't quite make it.\n");
   return 1;
     }

   write("You enter the window and go back to the cottage.\n");
   say(QCTNAME(TP)+ " leaves through the window.\n");
   TP->move_living("M",MICH_DIR + "petunia_house",1);
   return 1;


}
