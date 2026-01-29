inherit "/d/Kalad/room_std";
inherit "/d/Emerald/common/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/caravan/shop/perfume_store"
object ob1;
void
/* by Antharanos */
create_room()
{
   config_default_trade();
   set_money_greed_sell(0);
   set_money_greed_buy(95);
   set_money_give_max(0);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 1;
   set_short("The Perfume Shop");
   set_long("You are inside the Perfume Shop.\n"+
      "The walls about you enclose a moderately large-sized room, which "+
      "is decorated with a myriad variety of motifs, all concerning flowers. "+
      "There is no seat or bench for you to rest upon here, however at the far "+
      "end of the room is a polished redwood counter, behind which is a "+
      "small opening, leading to another room. A large plaque hangs in front "+
      "of the counter.\n");
   add_item(({"walls","wall"}),"The walls, along with the rest of the "+
      "room are beautifully decorated in myriad images of flowers of every "+
      "variety.\n");
   add_item(({"flowers","flower"}),"You can see several flowers, among "+
      "them are roses, violets, lilies and so on.\n");
   add_item(({"motifs","motif"}),"A plethora of flowers of every inkling you can imagine.\n");
   add_item(({"polished redwood counter","polished counter","redwood counter","counter"}),
      "A finely-grained set of wood, it firmly blocks the way west, except "+
      "for one spot where a small hinged door allows passage behind it.\n");
   add_item(({"small hinged door","small door","hinged door","door"}),
      "It is the only way behind the counter, other than jumping over the "+
      "counter...\n");
   add_item(({"small opening","opening"}),"A doorway that leads west.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_exit(CVAN(shop/perfume_store),"west", "@@wiz_check",-1,-1);
   add_exit(CVAN(caravan/s1),"east",0,-1,-1);
   ob1 = clone_object("/d/Kalad/common/caravan/npc/perfumer");
   ob1 -> move_living("xxx", TO);
   INSIDE;
}
plaque()
{
   return "This shop only sells perfumes, we do not buy perfumes or any "+
   "other types of items.\n";
}
void
init()
{
   ::init();
   init_shop();
}
int
wiz_check()
{
   if (TP->query_wiz_level())
      return 0;
   write("The effeminite slender human places a hand on your chest and pushes "+
      "you away from her store room.\n");
   say(QCTNAME(TP) + " tries to go west but is gently but firmly pushed "+
      "away by the effeminite slender human.\n");
   return 1;
}
int
do_read(string str)
{
   return 0;
}
int shop_hook_allow_sell(object ob)
{
   if(ob->id("_Kabal_perfume_shop"))return 1;
   return 0;
}
int
do_sell(string str)
{
   TP->catch_msg("This shop only sells perfumes.\n");
   return 1;
}
