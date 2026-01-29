#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Genesis/delivery/office";

#include "local.h"
#include H_MAKER
#include "/d/Genesis/delivery/delivery.h"

#define PRICELIST_ID ({"pricelist","list","sign","menu","prices"})

static object innkeeper;
object hobbit1, hobbit2, hobbit3;

void add_stuff();

void
create_room()
{

   configure_shire_inn();
   set_short("The Stonebows Inn");
   set_long("The Stonebows Inn is small but well-equipped "+
	    "for things that the throat thirsts after or the stomach "+
	    "pines for. At the far end of the room, the small "+
	    "counter situated beneath a large, hand-lettered pricelist. "+
	    "There is a plaque on the wall. Chairs and tables are available, but "+
	    "it is well not to sit too heavily in them since "+
	    "the entire inn is suspended from the bridge.\n");

   add_item(({"chair","chairs","table","tables"}),
	    "The chairs and tables have had rather rough treatment by "+
	    "the guests but most seem intact.\n");
   add_item(({"counter","counters"}),
	    "The counter is made of two shipping crates with an old "+
	    "round hobbitish door placed atop them.\n");

   add_item(PRICELIST_ID, "@@pricelist_desc");
   
   add_prop(ROOM_I_INSIDE,1);
   add_exit(EAST_R_DIR + "stonebows","out");
   reset_shire_room();

    set_office("The Stonebows Inn of the Shire", 3);

    add_cmd_item("plaque","read","The plaque reads:\nHere you may:\n"+
      "<deliver>  To deliver an assigned task.\n"+
      "<return>  To return a failed delivery.\n");



}

string
pricelist_desc()
{
  return "\nDrinks:\n\n"+
    " 1. A fresh delicous beer . . . . . . .   20 cc\n"+
    " 2. A pint of red ale . . . . . . . . .   50 cc\n"+
    " 3. A glass of brandywine . . . . . . .   80 cc\n"+
    " 4. A glass of mild whiskey . . . . . .  175 cc\n"+
    "\nSnacks:\n\n"+
    " 5. A cracker . . . . . . . . . . . . .   18 cc\n"+
    " 6. A turkey sandwich . . . . . . . . .   40 cc\n"+
    "\nMeals:\n\n"+
    " 7. A vegetable soup. . . . . . . . . .   75 cc\n"+
    " 8. A beef stew . . . . . . . . . . . .  100 cc\n"+
    " 9. A large t-bone. . . . . . . . . . .  235 cc\n"+
    "10. A roast chicken . . . . . . . . . .  650 cc\n\n";
}

void
reset_shire_room() 
{
    if(!innkeeper) innkeeper = clone_object(ER_NPC + "stone_keeper");
    if (!present(innkeeper)) innkeeper->move(this_object());
    set_alarm(0.4,0.0,"add_stuff");
    reset_office();
}

void
init() 
{
    ::init();
    add_action("do_read", "read", 0);
    init_office();
    init_shire_inn();
}

int
do_read(string str)
{
  if (!str) return 0;
  if (member_array(str, PRICELIST_ID) == -1) return 0;
  write(pricelist_desc());
  return 1;
}

int
do_order(string str) 
{

  if (!innkeeper || !present(innkeeper)) 
  {
    notify_fail("There is no one here to buy anything from.\n"+
                "The innkeeper has been killed!\n");
    return 0;
  }
  return ::do_order(str);
}

mixed *
get_order(string str)
{
  object order;
  int price;

  switch (str) 
  {
    case "beer": case "cold beer": case "nice cold beer": case "1":
      order = clone_object("/std/drink");
      order->set_name("beer");
      order->set_pname("beers");
      order->set_short("fresh delicious beer");
      order->set_pshort("fresh delicious beers");
      order->set_adj(({"fresh", "delicious"}));
      order->set_long("A very fresh, delicious beer, brewed for the "+
		      "Adventuresome Hobbits to aid them in their journeys.\n");
      order->set_soft_amount(110);
      order->set_alco_amount(8);
      order->add_prop(OBJ_I_WEIGHT, 220);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 20;
      break;

    case "ale": case "pint": case "red ale": case "2":
      order = clone_object("/std/drink");
      order->set_name(({"ale", "pint", "red ale"}));
      order->set_pname(({"ales", "pints", "red ale"}));
      order->set_short("pint of red ale");
      order->set_pshort("pints of red ale");
      order->set_long("The pint of red ale looks inviting.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(14);
      order->add_prop(OBJ_I_WEIGHT, 54);
      order->add_prop(OBJ_I_VOLUME, 54);
      price = 50;
      break;
    case "wine": case "brandywine": case "glass of brandywine": case "3":
      order = clone_object("/std/drink");
      order->set_name(({"wine","brandywine","glass"}));
      order->set_pname(({"wines","brandywines","glasses"}));
      order->set_short("glass of brandywine");
      order->set_pshort("glasses of brandywine");
      order->set_long("This brandywine is reddish brown in color, "+
      "reflecting its blend of brandy with wine, thus the name.\n");
      order->set_soft_amount(90);
      order->set_alco_amount(18);
      order->add_prop(OBJ_I_WEIGHT, 20);
      order->add_prop(OBJ_I_VOLUME, 20);
      price = 80;
      break;
    case "whiskey": case "gamwich whiskey": case "4":
      order = clone_object("/std/drink");
      order->set_name("whiskey");
      order->set_pname("whiskeys");
      order->set_short("gamwich whiskey");
      order->set_pshort("gamwich whiskeys");
      order->set_adj("gamwich");
      order->set_long("Gamwich is famous for its strong, but foul-tasting "+
       "whiskey.\n");
      order->set_soft_amount(50);
      order->set_alco_amount(30);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 100);
      price = 180;
      break;
    case "cracker": case "5":
      order = clone_object("/std/food");
      order->set_name("cracker");
      order->set_pname("crackers");
      order->set_short("cracker");
      order->set_pshort("crackers");
      order->set_long("This is a lightly toasted cracker.\n");
      order->set_amount(100);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 200);
      order->add_prop(HEAP_S_UNIQUE_ID,"cookies");
      price = 21;
      break;
    case "sandwich": case "turkey sandwich": case "6":
      order = clone_object("/std/food");
      order->set_name("sandwich");
      order->set_pname("sandwiches");
      order->set_short("turkey sandwich");
      order->set_pshort("turkey sandwiches");
      order->set_adj("turkey");
      order->set_long("It looks worth a try.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 80);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"ham sandwich");
      price = 40;
      break;
    
    case "soup": case "vegetable soup": case "7":
      order = clone_object("/std/food");
      order->set_name("soup");
      order->set_pname("soups");
      order->set_short("vegetable soup");
      order->set_pshort("vegetable soups");
      order->set_adj("vegetable");
      order->set_long("This soup is made of carrots, onions, "+
      "cabbage, potatoes and celery.\n");
      order->set_amount(190);
      order->add_prop(OBJ_I_WEIGHT,250);
      order->add_prop(OBJ_I_VOLUME,350);
      order->add_prop(HEAP_S_UNIQUE_ID,"veggie delight");
      price = 75;
      break;

    case "stew": case "beef stew": case "8":
      order = clone_object("/std/food");
      order->set_name("stew");
      order->set_pname("stews");
      order->set_short("beef stew");
      order->set_pshort("beef stews");
      order->set_adj(({"beef"}));
      order->set_long("This is some delicious looking beef stew "+
        "with chunks of taters and carrots and beans drowning in a "+
        "thick, brown gravy.\n");
      order->set_amount(250);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"wabbit stew");
      price = 100;
      break;
    
    case "steak": case "t-bone": case "large t-bone": case "9":
      order = clone_object("/std/food");
      order->set_name(({"steak","t-bone"}));
      order->set_pname(({"steaks","t-bones"}));
      order->set_short("large t-bone steak");
      order->set_pshort("large t-bone steaks");
      order->set_adj(({"large", "t-bone"}));
      order->set_long("Juices ooze from this nice, thick steak "+
        "as it steams slightly, fresh from the grill.\n");
      order->set_amount(375);
      order->add_prop(OBJ_I_WEIGHT, 400);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"nice juicy steak");
      price = 235;
      break;
   
    case "chicken": case "roast chicken": case "big roast chicken": case "10":
      order = clone_object("/std/food");
      order->set_name("chicken");
      order->set_pname("chickens");
      order->set_short("roast chicken");
      order->set_pshort("roast chickens");
      order->set_adj(({"whole","roast"}));
      order->set_long("This whole roast chicken "+
      "is sizzling hot and golden-brown. Yum!\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,750);
      order->add_prop(OBJ_I_VOLUME,900);
      order->add_prop(HEAP_S_UNIQUE_ID,"magic meat medley");
      price = 650;
      break;
  }

  return (({order}) + ({price}));
}


void
add_stuff()
{
   if(!hobbit1)
   {
     hobbit1 = clone_object(HOBBITMAKER);
     hobbit1->set_type(CITIZEN);
     hobbit1->set_power(125);
     hobbit1->move(TO);
    }

   if(!hobbit2)
   {
     hobbit2 = clone_object(HOBBITMAKER);
     hobbit2->set_type(MAIDEN);
     hobbit2->set_title("the Barmaiden of the Stonbows Inn");
     hobbit2->set_power(75);
     hobbit2->move(TO);
    }

   if(!hobbit3)
   {
     hobbit3 = clone_object(HOBBITMAKER);
     hobbit3->set_type(MILITA);
     hobbit3->set_power(140);
     hobbit3->move(TO);
    }

}
