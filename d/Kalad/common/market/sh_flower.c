[30m±[1m[37;47m‡[0m[30mÉÿ
[30m
[1m[37;47m
[1m[37;47m
inherit "/d/Emerald/common/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/market/flower_store"
object ob1;
void
/* by Cyric */
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
   set_short("The Flowerseller's Shop");
   set_long("You are inside the Flowerseller's Shop.\n"+
      "As you step into this tent the sweet smell "+
      "of flowers wafts to your nose, calming you. "+
       "This is clearly the local florist. Flowers of "+
      "every variety and hue sit in buckets of water on the "+
       "floor. There is a sign dangling precariously over  "+
      "your head from a rope in the middle of the tent.\n");
   add_item(({"flowers","flower"}),"The proprieter of this "+
        "shop must be a skilled gardener, as there seem to "+
        "be all varieties of flowers here, even some you "+
        say(QC   TP->catch_msg("This shop doesn't buy a
