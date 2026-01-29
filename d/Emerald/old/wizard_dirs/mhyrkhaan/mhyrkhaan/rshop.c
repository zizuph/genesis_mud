inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/wild/pass/goblin/guild/riders/rstore"
object ob1;

/* 
 * /d/Kalad/common/wild/pass/goblin/guild/riders/rshop.c
 * Purpose    : Store for the riders guild
 * Located    : riders guild hall
 * Created By : mhyrkhaan 2-20-97
 * Modified By: 
 */
void
create_room()
{
   config_default_trade();
   set_money_greed_sell(95);
   set_money_greed_buy(95);
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);
   set_short("Gregor's supply shop");
   set_long("This is Gregor's Rider Supply. Along the "+
   "walls you see various weapons and armours hanging. Behind "+
   "a large wooden counter, stands a muscular dwarf, ready to "+
   "help you. There is a large sign above the counter, and a "+
   "poster on the wall.\n");
   INSIDE;
   add_item(({"large sign","sign"}),"A large sign hung above the "+
   "counter.\n");
   add_item("poster","a old torn paper poster, it has words on it.\n");
   add_cmd_item("poster","read","The poster reads: You may also <order> a "+
   "collar for your Warwolf here. Use 'order <metal type> for "+
   "<warwolf's name>'. You may select from the folowing types: "+
   "gold, silver or steel collars. You can name you "+
   "wolf anything you want, if you choose something profane, or "+
   "rude, you will be in BIG trouble. Example: 'order silver "+
   "for bob'. Collars are FREE, paid for from our loyal looting "+
   "brothers and sisters or the Red Fang.\n");
   add_exit(CPASS(goblin/guild/riders/rstore), "north", "@@wiz_check",-1,-1);
   add_exit(CPASS(goblin/guild/riders/rhall), "south",0,0);
   ob1 = clone_object(CPASS(goblin/guild/riders/owner.c));
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
   write("The muscular dwarf in the doorway, growling at you.\n");
   say(QCTNAME(TP) + " tries to go west but is stopped by the muscualr "+
   "dwarf.\n");
   return 1;
}

int
do_collar(string str)
{
    string stype;
    string wname;
    sscanf(str,"%s for %s",stype,wname);
    switch(stype)
    {
        case "gold":
            stype = "gold-studded";
        break;
        case "silver":
            stype = "silver-studded";
        break;
        case "steel":
            stype = "steel-studded";
        break;
        default:
            NF("No such metal type.\n");
            return 0;
    }
    ob1 = clone_object(CPASS(goblin/guild/riders/wcollar));
    ob1->set_wolfname(wname);
    ob1->set_type(stype);
    ob1->move(TP);
    write("You got a "+ob1->short()+", give it to your warwolf, and "+
    "it will wear it.\n");
    return 1;
}
   