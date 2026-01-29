inherit "/d/Kalad/room_std";
inherit "/d/Emerald/common/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/market/wep_store"
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
   set_short("The Weaponsmith's Shop");
   set_long("You are inside the Weaponsmith's Shop.\n"+
      "Many examples of finely crafted weapons adorn the "+
      "walls, including some exotic ones from far lands. "+
       "The smith stands behind a display counter "+
      "polishing an already bright longsword, and beyond "+
       "him is the entrance to the store room. In front "+
      "of the case is a small plaque.\n");
   add_item(({"walls","wall"}),"The walls are hung with examples "+
        "of the weaponsmith's goods in great variety.\n");
   add_item(({"weapon","weapons"}),"These weapons are for "+
        "display purposes only. You dont think the smith will "+
        "sell them.\n");
   add_item(({"exotic weapon","exotic weapons"}),"One particular "+
        "piece which catches your eye is a wickedly curved weapon "+
        "with two blades, one extending from either end of the "+
        "centrally placed hilt.  It looks deadly but you are sure it "+
        "would be a difficult weapon to master.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_item(({"display counter","counter","display case","case"}),"A "+
        "large glass case filled with various weapons.  "+
        "Among them you see a curved black dagger, a "+
        "silvery flail, a sharp poniard, and a small axe.\n");
   add_exit(MARKET(wep_store),"north","@@wiz_check",-1,-1);
   add_exit(MARKET(m03),"south");
   ob1 = clone_object(MARKET(/npc/wepsmith));
   ob1 -> move_living("xxx", TO);
   INSIDE;
}
plaque()
{
   return "This shop deals in specialized weapons, we only buy "+
        "what we sell.\n";
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
   write("You try to walk into the closed and locked store "+
        "room door but only wind up bumping your head.  "+
        "You cant go in there.\n");
   say(QCTNAME(TP) + " tries to go north but is prevented "+
        "by the closed store room door.\n");
   return 1;
}
int
do_read(string str)
{
   return 0;
}
int shop_hook_allow_sell(object ob)
{
   if(ob->id("_Kmarket_wep_shop"))return 1;
   return 0;
}
int
do_sell(string str)
{
   TP->catch_msg("This shop only sells weapons.\n");
   return 1;
}
