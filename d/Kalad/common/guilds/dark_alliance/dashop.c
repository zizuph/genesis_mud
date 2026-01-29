inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"
#define STORE_ROOM "/d/Kalad/common/guilds/dark_alliance/dastore"
object ob1;

/* 
 * /d/Kalad/common/guilds/riders/rshop.c
 * Purpose    : Store for the riders guild
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
   set_short("Alliance supply shop");
   set_long("This is the supply shop for the Dark Alliance. Along the "+
   "walls you see various backpacks and lamps hanging. Behind "+
   "a large wooden counter, stands a muscular dwarf, ready to "+
   "help you. There is a large plaque above the counter, and a "+
   "poster on the wall.\n");
   INSIDE;
   add_item("poster","a old torn paper poster, it has words on it.\n");
   add_cmd_item("poster","read","The poster reads: Riders may also <order> a "+
   "collar for their Warwolf here. Use 'order <metal type> for "+
   "<warwolf's name>'. You may select from the folowing types: "+
   "gold, silver or steel collars. You can name you "+
   "wolf anything you want, if you choose something profane, or "+
   "rude, you will be in BIG trouble. Example: 'order silver "+
   "for bob'. Collars are FREE, paid for from our loyal looting "+
   "brothers and sisters of the Dark Alliance, or by our trusted "+
   "friends of the Red Fang.\n");
   add_item("plaque","@@plaque");
   add_cmd_item("plaque","read","@@plaque");
   add_exit(COMMON(guilds/dark_alliance/dastore), "north", "@@wiz_check",-1,-1);
   add_exit(COMMON(guilds/dark_alliance/dahall), "south",0,0);
   ob1 = clone_object(COMMON(guilds/dark_alliance/owner));
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
    ob1 = clone_object(COMMON(guilds/dark_alliance/wcollar));
    ob1->set_wolfname(wname);
    ob1->set_type(stype);
    ob1->move(TP);
    write("You got a "+ob1->short()+", give it to your warwolf, and "+
    "it will wear it.\n");
    return 1;
}
plaque()
{
   return "This store only sells items, we do not pay for any items you "+
   "attempt to sell here.\n";
}
do_read(string str)
{
   return 0;
}
int shop_hook_allow_sell(object ob)
{
   if(ob->id("_Kabal_equip_shop"))return 1;
   return 0;
}
do_sell(string str)
{
   TP->catch_msg("This shop only sells equipment.\n");
   return 1;
}
   