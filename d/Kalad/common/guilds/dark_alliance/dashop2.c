inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/guilds/dark_alliance/dastore2"
object ob1;

/* 
 * /d/Kalad/common/guilds/dark_alliance/rshop2.c
 * Purpose    : Armory for the riders guild
 * Located    : riders guild hall
 * Created By : mhyrkhaan 2-20-97
 * Modified By: 
 */
void
create_room()
{
   config_default_trade();
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("The Shining blade");
   set_long("This is the Shining Blade, the Armoury for the Dark "+
   "Alliance. Along the walls you see various weapons and armours "+
   "hanging. Behind a large wooden counter, stands a shadowy "+
   "dark-elf, ready to help you. There is a large sign above the "+
   "counter.\n");
   INSIDE;
   add_item(({"large sign","sign"}),"A large sign hung above the "+
   "counter.\n");
   add_exit(COMMON(guilds/dark_alliance/dastore2), "west", "@@wiz_check",-1,-1);
   add_exit(COMMON(guilds/dark_alliance/rtrain), "north",0,0);
   ob1 = clone_object(COMMON(guilds/dark_alliance/dezzin));
   ob1 -> move_living("xxx", TO);
   
   INSIDE;
}
void
init()
{
   ::init();
   init_shop();
   AA(do_collar,order);
}

int
wiz_check()
{
   if(TP->query_wiz_level())
      return 0;
   write("The shadowy dark-elf stands in the doorway, growling at you.\n");
   say(QCTNAME(TP) + " tries to go west but is stopped by the shadowy darkl-elf.\n");
   return 1;
}
