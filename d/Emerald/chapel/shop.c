inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>
#include "chapel.h"
#include "/d/Emerald/sys/paths.h"

void
create_room()
{
   set_short("Wedding accessories shop");
   set_long("   You step into a room where lovely "+
      "wedding gowns and accessories, as well as impeccable tuxedos are proudly on display. "+
      "The closet set into the back wall is filled with fresh flower "+
      "wedding bouquets.  A smiling couple waits quietly out of the "+
      "way, ready to help if needed. Behind them, on the wall, is a small sign.\n\n");
   
   add_item("couple","The couple consists of "+
      "a tailor and a seamstress.\n");
   add_item("tailor","The tailor waits patiently off to the side, ready to help the groom when needed.\n");
   add_item("seamstress","The seamstress is stylishly dressed "+
      "and ready to help fit any female patrons.\n");
   add_item(({"case", "back wall", "bouquets", "bouquets"}),
      "The bouquets are kept in a glass case "+
      "along the back wall.  Perfectly preserved from the time of "+
      "cutting until they are needed, they are incredibly beautiful "+
      "and well worth the price.\n");
   add_item(({"dress", "clothes", "tuxedo", "veil", "train"}),
      "The clothes are all made of the finest "+
      "materials.  They seems to want you to run your  "+
      "fingers over them and feel their luxuriousness.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(CHAPEL_DIR + "rectory", "west");
   add_exit(CHAPEL_DIR + "store", "north", "@@wiz_check@@");
   
   config_default_trade();
   set_store_room(CHAPEL_DIR + "store");
}

void
init()
{
   ::init();
   init_shop();
}

int
shop_hook_allow_sell(object ob)
{
   NF("This shop is for wedding accessories only.  Sorry.\n");
   return ob->wedding_stuff();
}

int
shop_hook_bought_items(object *arr)
{
   int i;
   
   for (i=0 ; i<sizeof(arr) ; i++)
   if (!arr[i]->id("bouquet"))
      if (arr[i]->for_bride())
      TP->catch_msg("The seamstress quickly fits the " +
      arr[i]->query_short() + " to your exact " +
      "specifications.\nThe fit is absolutely " +
      "perfect!\n");
   else
      TP->catch_msg("The tailor quickly fits the " +
      arr[i]->query_short() + " to your exact " +
      "specifications.\nThe fit is absolutely " +
      "perfect!\n");
   return ::shop_hook_bought_items(arr);
}

int
do_read(string arg)
{
   NF("Read what?\n");
   if (arg != "sign")
      return 0;
   
   write("" +
      "You can try these instructions: \n" +
      "    buy dress for gold and get copper back\n" +
      "    buy dress for gold coins\n" +
      "    sell dress for copper coins\n" +
      "    sell all  - will let you sell all wedding items except for\n" +
      "                those you wear.\n" +
      "    sell all! - will let you sell ALL items you have, well\n" +
      "                at least the droppable wedding items.\n" +
      "    If you want a list of all available in the store, the\n" +
      "    correct syntax is: list\n" +
      "");
   return 1;
}
