#pragma save_binary

inherit "/d/Shire/room";
inherit "/d/Shire/lib/inn.c";
#include "/d/Shire/common/defs.h"
#include "hobbit.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define TOB_DIR   HOBGLD_DIR + "tobacco/" 

static object innkeeper;
void add_stuff();
void reset_room();

void
create_shire_room()
{

    configure_shire_inn();
    set_short("The Ploughed Field");
    set_long("You have entered a small inn, known as the Ploughed Field.  "+ 
      "Chairs and tables litter this inn whose purpose is to serve the "+
      "Adventuresome Hobbits their food and drink. "+
      "A pricelist, or menu is posted to the wall.\n");

    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a hobbit standing "+
      "behind it.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(HOBGLD_DIR + "hall", "northwest");
    add_exit(HOBGLD_DIR + "libraryroom","southwest");
    reset_room();
}

string
pricelist_desc()
{
    return "\nDrinks:\n"+
    " 1. 'A fresh delicous beer' ............   10 cc\n"+
    " 2. 'A pint of red ale' ................   25 cc\n"+
    " 3. 'A glass of brandywine' ............   40 cc\n"+
    " 4. 'A shot of Gamwich whiskey' ........   90 cc\n"+
    "\nSnacks:\n"+
    " 5. 'A cracker' ........................   10 cc\n"+
    " 6. 'A turkey sandwich' ................   21 cc\n"+
    "\nMeals:\n"+
    " 7. 'A vegetable soup' .................   38 cc\n"+
    " 8. 'A beef stew' ......................   54 cc\n"+
    " 9. 'A large t-bone' ...................  120 cc\n"+
    "10. 'A roast chicken' ..................  350 cc\n"+
    "\nTobacco:\n"+
    "11. 'Longbottom leaf tobacco' ..........  15 cc\n"+
    "12. 'Old Toby tobacco' .................  35 cc\n"+
    "13. 'Southern star tobacco' ............  50 cc\n"+
    "14. 'Tobacco pouch' ....................  75 cc\n\n";
}

void
reset_room() 
{
    if (!innkeeper) innkeeper = clone_object(HOBGLD_DIR + "innkeeper");
    if (!present(innkeeper)) innkeeper->move(this_object());
    set_alarm(0.4,0.0,"add_stuff");
}

init() {
    ::init();
    add_action("do_read", "read", 0);
    init_shire_inn();
}

do_read(str)
{
    if (!str) return 0;
    if (member_array(str, PRICELIST_ID) == -1) return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str)
{
    if (!innkeeper || !present(innkeeper)) {
	notify_fail("There is no one here to buy anything from.\n"+
	  "The innkeeper has been killed!\n");
	return 0;
    }
    return ::do_order(str);
}

mixed *
get_order(string str1)
{
    int price;
    object order;

    switch (str1) {
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
	price = 10;
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
	price = 25;
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
	price = 40;
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
	price = 90;
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
	price = 10;
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
	price = 21;
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
	price = 38;
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
	price = 54;
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
	price = 120;
	break;

    case "medley": case "chicken": case "roast chicken": case "10":
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
	price = 556;
	break;
    case "tobacco": case "longbottom leaf": case "longbottom leaf tobacco": case "11":
	order = clone_object(TOB_DIR +"tob_longbottom");
	price = 15;
	break;
    case "old toby": case "old toby tobacco": case "12":
	order = clone_object(TOB_DIR +"tob_oldtoby");
	price = 35;
	break;
    case "southern star": case "southern star tobacco": case "13":
	order = clone_object(TOB_DIR +"tob_star");
	price = 50;
	break;
    case "tobacco pouch": case "pouch": case "14":
	order = clone_object(TOB_DIR + "tob_pouch");
	price = 75;
	break;
    }
    return (({order}) + ({price}));
}


void
add_stuff()
{
    object hobbit1, hobbit2, hobbit3;
    if(!present("billyjoe"))
    {
	hobbit1 = clone_object(HOBBITMAKER);
	hobbit1->set_power(140);
	hobbit1->set_type(CITIZEN);
	hobbit1->add_name("billyjoe");
	hobbit1->move(TO);
    }

    if(!present("bobbysue"))
    {
	hobbit2 = clone_object(HOBBITMAKER);
	hobbit2->add_name("bobbysue");
	hobbit2->set_power(85);
	hobbit2->set_type(CITIZEN);
	hobbit2->move(TO);
    }

    if(!present("bobbybilly"))
    {
	hobbit3 = clone_object(HOBBITMAKER);
	hobbit3->add_name("bobbybilly");
	hobbit3->set_type(ELDER);
	hobbit3->set_power(95);
	hobbit3->move(TO);
    }

}
