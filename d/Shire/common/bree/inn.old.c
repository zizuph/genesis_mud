inherit "/d/Shire/room";
inherit "/lib/trade";
inherit "/d/Genesis/delivery/office";
#include "/d/Genesis/delivery//delivery.h"

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

/* Prototype */
void reset_room();

static object barliman, nob, bob;

void
create_room()
{
  config_default_trade();
  set_short("The Prancing Pony");
set_office("the Prancing Pony in Bree",3);
  set_long(break_string(
    "You have entered Bree's and the hobbits' great pride, the largest "+
    "and biggest inn in miles around: The Prancing Pony. You see a red "+
    "banner on the wall above a counter. There is a drawing of a golden "+
    "horse, or perhaps even a golden pony, standing on its hind-legs "+
    "waving its front-legs in the air. On that same wall, next to the "+
    "banner, there is a pricelist.  A sign hangs above the counter. "+ 
    "East is a dim room.\n",70));
  add_item("sign","The sign has writing on it.\n");
  add_cmd_item("sign","read","The sign reads:\nHere you may:\n"+
  "<ask for a delivery tour> To get a delivery task.\n"+
  "<deliver>  To deliver an assigned task.\n"+
  "<return>  To return a failed delivery.\n");
  add_item("mirror", "@@mirror_desc");  /* in innkeeper's right hand */
  add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
  add_item("counter", "It's made out of wood. There is a man standing "+
                      "behind it.\n");
  add_item("wall", "It's used to secure the inn from wind and rain.\n");
  add_item("banner", "It's made out of some kind of tissue.\n");
  add_item(PRICELIST_ID, "@@pricelist_desc");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); /* We want the bar open at all times. Screw Realism */
  add_exit(BREE_DIR + "inn_yard", "south");
   add_exit(BREE_DIR + "front_room","west");
   add_exit(BREE_DIR + "innroom","east",0,1);
 
  set_alarm(1.0, 0.0, reset_room);
}

string
mirror_desc()
{
  if (!barliman || !present(barliman)) 
    return "You find no mirror.\n";
  return "The mirror reflects the pricelist on the wall.\n"+
         "You are having a hard time reading the prices this way.\n";
}

string
pricelist_desc()
{
  return "\nDrinks:\n\n"+
    "1. 'A nice cold beer' ............   20 cc\n"+
    "2. 'A pint of ale' ...............   50 cc\n"+
    "3. 'A glass of red wine ..........   80 cc\n"+
    "4. 'A tiny bit of prime liquor ...  180 cc\n"+
    "\nSnacks:\n\n"+
    "5. 'A bag of cookies' ............  15 cc\n"+
    "6. 'A ham sandwich' ..............  40 cc\n"+
    "\nMeals:\n\n"+
    "7. 'Some wabbit stew' ............  75 cc\n"+
    "8. 'Steak a la maison' ...........  160 cc\n"+
    "9. 'Fantastic feast in a bag'.......210 cc\n\n"+
    "10. A night's stay in the inn........144 cc\n\n\n";
}

void
reset_room()
{
  if (!barliman)
    barliman = clone_object(BREE_DIR + "npc/butterbur");
  if (!present(barliman,this_object()))
    barliman->move(this_object());
  if (!bob)
  {
    bob = clone_object(BREE_DIR + "npc/bob_nob");
    bob->monster_is_bob();
    bob->move(this_object());
  }
  if (!nob)
  {
    nob = clone_object(BREE_DIR + "npc/bob_nob");
    nob->monster_is_nob();
    nob->move(this_object());
  }
}

void
init()
{
  init_office();
  ::init();

  add_action("do_read", "read", 0);
  add_action("do_buy","buy",0);
  add_action("do_buy","order",0);
}

int
do_read(string str)
{
  if (!str)
    return 0;
  if (member_array(str, PRICELIST_ID) == -1)
    return 0;
  write(pricelist_desc());
  return 1;
}

int
do_buy(string str) 
{
  object order;
  string str1, str2, str3;
  int *arr, price, silent, i;

  if (!str)
  {
    notify_fail("Buy 'item' with 'type of money' and get 'type of money'.\n");
    return 0;
  }
  if (!barliman || !present(barliman))
  {
    notify_fail("There is no-one here to buy anything from.\n"+
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
  switch (str1)
  {
    case "beer":
    case "cold beer":
    case "nice cold beer":
    case "1":
      order = clone_object("/std/drink");
      order->set_name("beer");
      order->set_pname("beers");
      order->set_short("nice cold beer");
      order->set_pshort("nice cold beers");
      order->set_adj(({"nice", "cold"}));
      order->set_long("You couldn't imagine what would refresh you more.\n");
      order->set_soft_amount(110);
      order->set_alco_amount(4);
      order->add_prop(OBJ_I_WEIGHT, 220);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 20;
      break;

    case "ale":
    case "pint":
    case "pint of ale":
    case "2":
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

    case "wine":
    case "red wine":
    case "glass of wine":
    case "3":
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

    case "liquor":
    case "prime liquor":
    case "4":
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

    case "cookies":
    case "bag of cookies":
    case "bag":
    case "5":
      order = clone_object("/std/food");
      order->set_name("cookies");
      order->set_pname("cookies");
      order->set_short("bag of cookies");
      order->set_pshort("bags of cookies");
      order->set_long("These are some delicious looking brownies.\n");
      order->set_amount(50);
      order->add_prop(OBJ_I_WEIGHT, 50);
      order->add_prop(OBJ_I_VOLUME, 100);
      add_prop(HEAP_S_UNIQUE_ID,"heaps o cookies");
      price = 15;
      break;

    case "sandwich":
    case "ham sandwich":
    case "6":
      order = clone_object("/std/food");
      order->set_name("sandwich");
      order->set_pname("sandwiches");
      order->set_short("ham sandwich");
      order->set_pshort("ham sandwiches");
      order->set_adj("ham");
      order->set_long("It looks tasty enough to risk a bite.\n");
      order->set_amount(130);
      order->add_prop(OBJ_I_WEIGHT, 80);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"heaps o sandwiches");
      price = 38;
      break;

    case "stew":
    case "wabbit stew":
    case "rabbit stew":
    case "7":
      order = clone_object("/std/food");
      order->set_name("stew");
      order->set_pname("stews");
      order->set_short("wabbit stew");
      order->set_pshort("wabbit stews");
      order->set_adj(({"wabbit", "rabbit"}));
      order->set_long("Yummy chunks of bunny meat floating in a greasy broth.\n");
      order->set_amount(200);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"heaps o stew");
      price = 75;
      break;

    case "steak":
    case "steak a la maison":
    case "8":
      order = clone_object("/std/food");
      order->set_name("steak");
      order->set_pname("steaks");
      order->set_short("nice juicy steak");
      order->set_pshort("nice juicy steaks");
      order->set_adj(({"nice", "juicy"}));
      order->set_long("A steaming, delicious steak, done to perfection.\n");
      order->set_amount(300);
      order->add_prop(OBJ_I_WEIGHT, 250);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"heaps o steak");
       order->add_prop("_steak_for_doggie", 1);
      price = 160;
      break;


    case "feast":
    case "fantastic feast":
    case "9":
      order = clone_object("/std/food");
      order->set_name("feast");
      order->set_pname("feasts");
      order->set_short("fantastic feast");
      order->set_pshort("fantastic feasts");
      order->set_adj("fantastic");
      order->set_long("A feast in a bag, meant for travellers.\n");
      order->set_amount(350);
      order->add_prop(OBJ_I_WEIGHT, 300);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"heap o feasts");
      price = 210;
      break;

    case "key":
    case "night's stay":
    case "10":
      order = clone_object(BREE_DIR + "obj/inn_key");
      price = 144;
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
    say(QCTNAME(this_player())+" and " + QCTNAME(barliman)+" exchange "+
      "some coins.\n");
  }
  else say(QCTNAME(this_player())+" gives "+QCTNAME(barliman)+" some "+
    "money.\n");
  write("The innkeeper hands you "+order->short()+".\n");
  say(QCTNAME(barliman)+" hands "+QCTNAME(this_player())+" "+
    order->short()+".\n"); 
  if (order->move(this_player())) {
    write("You drop the " + order->short() + " on the floor.\n");
    say(QCTNAME(this_player())+" drops a " + order->short()+" on the "+
      "floor.\n");
    order->move(this_object());
  }
  return 1;
}
