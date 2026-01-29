inherit "/d/Shire/room";
inherit "lib/trade";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

static object innkeeper;

create_room() {

   object infoman;
  config_default_trade();
  set_short("The Small Hole");
  set_long(break_string(
    "You have entered a small inn. In the tradition of the hobbits it is "
    + "underground in a small hill. The doors are all round as are the few "
    + "windows. The air is filled with smoke coming from the numerous "
    + "pipes being smoked by the hobbits. You almost have trouble finding "
    + "the innkeeper in the dark room. One the wall you can see a pricelist. \n", 70));

  add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
  add_item("counter", "It's made out of wood. There is a hobbit standing "+
                      "behind it.\n");

  add_item(PRICELIST_ID, "@@pricelist_desc");

  add_prop(ROOM_I_INSIDE,1);
  add_exit(STAND_DIR + "md1", "leave");
 
   infoman = clone_object("/d/Shire/common/hobbiton/npc/info_man");
   infoman->move(TO);
  reset_room();
}

pricelist_desc()
{
  return "\nDrinks:\n\n"+
    " 1. 'A nice cold beer' .............   20 cc\n"+
    " 2. 'A pint of ale' ................   50 cc\n"+
    " 3. 'A glass of red wine' ..........   80 cc\n"+
    " 4. 'A tiny bit of prime liquor' ...  180 cc\n"+
    "\nSnacks:\n\n"+
    " 5. 'A bag of cookies' .............   21 cc\n"+
    " 6. 'A ham sandwich' ...............   42 cc\n"+
    "\nMeals:\n\n"+
    " 7. 'A veggie delight' .............   65 cc\n"+
    " 8. 'Some wabbit stew' .............  109 cc\n"+
    " 9. 'Steak a la maison' ............  239 cc\n"+
    "10. 'The big meat medley' ..........  556 cc\n\n";
}

reset_room() {
  if (!innkeeper) innkeeper = clone_object(NPC_DIR + "innkeeper_hob");
  if (!present(innkeeper)) innkeeper->move(this_object());
}

init() {
  ::init();
  add_action("do_read", "read", 0);
  add_action("do_buy","buy",0);
  add_action("do_buy","order",0);
}

do_read(str)
{
  if (!str) return 0;
  if (member_array(str, PRICELIST_ID) == -1) return 0;
  write(pricelist_desc());
  return 1;
}

do_buy(str) {
  object order;
  string str1, str2, str3;
  int *arr, price, silent, i;

  if (!str) {
    notify_fail("Buy 'item' with 'type of money' and get 'type of money'.\n");
    return 0;
  }
  if (!innkeeper || !present(innkeeper)) {
    notify_fail("There is no one here to buy anything from.\n"+
                "The innkeeper has been killed!\n");
    return 0;
  }
  if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3) {
    str3 = "";
    if (sscanf(str, "%s with %s", str1, str2) != 2) {
      str2 = "";
      str1 = str;
    }
  }
  switch (str1) {
    case "beer": case "cold beer": case "nice cold beer": case "1":
      order = clone_object("/std/drink");
      order->set_name("beer");
      order->set_pname("beers");
      order->set_short("nice cold beer");
      order->set_pshort("nice cold beers");
      order->set_adj(({"nice", "cold"}));
      order->set_long("You couldn't imagine what would refresh you more.\n");
      order->set_soft_amount(110);
      order->set_alco_amount(8);
      order->add_prop(OBJ_I_WEIGHT, 220);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 20;
      break;
    case "ale": case "pint": case "pint of ale": case "2":
      order = clone_object("/std/drink");
      order->set_name(({"ale", "pint", "pint of ale"}));
      order->set_pname(({"ales", "pints", "pints of ale"}));
      order->set_short("pint of ale");
      order->set_pshort("pints of ale");
      order->set_long("Yup. It's a pint of ale... and it's all yours.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(14);
      order->add_prop(OBJ_I_WEIGHT, 540);
      order->add_prop(OBJ_I_VOLUME, 540);
      price = 50;
      break;
    case "wine": case "red wine": case "glass of wine": case "3":
      order = clone_object("/std/drink");
      order->set_name(({"wine", "glass"}));
      order->set_pname(({"wines", "glasses"}));
      order->set_short("glass of red wine");
      order->set_pshort("glasses of red wine");
      order->set_long("You guess it's a Bordeaux from '76.\n");
      order->set_soft_amount(90);
      order->set_alco_amount(16);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 200);
      price = 80;
      break;
    case "liquor": case "prime liquor": case "4":
      order = clone_object("/std/drink");
      order->set_name("liquor");
      order->set_pname("liquors");
      order->set_short("prime liquor");
      order->set_pshort("prime liquors");
      order->set_adj("prime");
      order->set_long("Don't drink this unless you are a real boozer.\n");
      order->set_soft_amount(50);
      order->set_alco_amount(30);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 100);
      price = 180;
      break;
    case "cookies": case "bag of cookies": case "bag": case "5":
      order = clone_object("/std/food");
      order->set_name("cookies");
      order->set_pname("cookies");
      order->set_short("bag of cookies");
      order->set_pshort("bags of cookies");
      order->set_long("These are some delicious looking brownies.\n");
      order->set_amount(100);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 200);
      order->add_prop(HEAP_S_UNIQUE_ID,"cookies");
      price = 21;
      break;
    case "sandwich": case "ham sandwich": case "6":
      order = clone_object("/std/food");
      order->set_name("sandwich");
      order->set_pname("sandwiches");
      order->set_short("ham sandwich");
      order->set_pshort("ham sandwiches");
      order->set_adj("ham");
      order->set_long("It looks tasty enough to risk a bite.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 80);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"ham sandwich");
      price = 42;
      break;
    
    case "delight": case "veggie delight": case "7":
      order = clone_object("/std/food");
      order->set_name("delight");
      order->set_pname("delights");
      order->set_short("veggie delight");
      order->set_pshort("veggie delights");
      order->set_adj("veggie");
      order->set_long("This garden salad, loaded with lots of "+
        "differing kinds of veggies from local gardens and stuffed "+
        "into a light bread shell and smothered in a light cream "+
        "sauce, serves as the perfect meal for those who want "+
        "a lighter, yet filling, repast.\n");
      order->set_amount(190);
      order->add_prop(OBJ_I_WEIGHT,250);
      order->add_prop(OBJ_I_VOLUME,350);
      order->add_prop(HEAP_S_UNIQUE_ID,"veggie delight");
      price = 65;
      break;

    case "stew": case "wabbit stew": case "rabbit stew": case "8":
      order = clone_object("/std/food");
      order->set_name("stew");
      order->set_pname("stews");
      order->set_short("wabbit stew");
      order->set_pshort("wabbit stews");
      order->set_adj(({"wabbit", "rabbit"}));
      order->set_long("This is some delicious looking wabbit stew "+
        "with chunks of taters and carrots and beans drowning in a "+
        "thick, brown gravy.\n");
      order->set_amount(250);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"wabbit stew");
      price = 109;
      break;
    
    case "steak": case "steak a la maison": case "9":
      order = clone_object("/std/food");
      order->set_name("steak");
      order->set_pname("steaks");
      order->set_short("nice juicy steak");
      order->set_pshort("nice juicy steaks");
      order->set_adj(({"nice", "juicy"}));
      order->set_long("Juices ooze from this nice, thick steak "+
        "as it steams slightly, fresh from the grill.\n");
      order->set_amount(375);
      order->add_prop(OBJ_I_WEIGHT, 400);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"nice juicy steak");
      price = 239;
      break;
   
    case "medley": case "meat medley": case "big meat medley": case "10":
      order = clone_object("/std/food");
      order->set_name("medley");
      order->set_pname("medleys");
      order->set_short("big meat medley");
      order->set_pshort("big meat medleys");
      order->set_adj(({"meat","big"}));
      order->set_long("The medley is composed of several varieties "+
        "of meat, including vension, beef, and rabbit, all marinated "+
        "in Dolin's secret sauce for days while roasting in a bronze "+
        "pot over a bed of hot hickory coals. Even the largest "+
        "man to come through Michel Delving can fill up on this "+
        "collection of luscious meats, although few hobbits "+
        "from this area can even finish one.\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,750);
      order->add_prop(OBJ_I_VOLUME,900);
      order->add_prop(HEAP_S_UNIQUE_ID,"magic meat medley");
      price = 556;
      break;
  
    default:
      notify_fail("Buy 'item' with 'type of money' and get "+
                  "'type of money'.\n");
      return 0;
  }
  arr = pay(price, 0, str2, 0, 0, str3, 0);
  if (sizeof(arr) == 1) {
    if (arr[0] == 1) notify_fail("You have to give me more to choose from.\n");
    else if (arr[0] == 2) notify_fail("You don't carry that kind of money!\n");
    return 0;
  }
  write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
  if (text(exclude_array(arr, 0, NUM-1))) {
    write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    say(QCTNAME(this_player()) + " and " + QCTNAME(innkeeper) + " exchange "+
      "some coins.\n");
  }
  else say(QCTNAME(this_player()) + " gives " + QCTNAME(innkeeper) + " some "+
    "money.\n");
  write("The innkeeper hands you "+order->short()+".\n");
  say(QCTNAME(innkeeper) + " hands " + QCTNAME(this_player())+
    " "+order->short() + ".\n"); 
  if (order->move(this_player())) {
    write("You drop the " + order->short() + " on the floor.\n");
    say(QCTNAME(this_player()) + " drops a " + order->short() + " on the "+
      "floor.\n");
    order->move(this_object());
  }
  return 1;
}
