/*
 * Added delivery office to inn
 * -- Finwe, Nov 2005
 */

#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE
#include "/d/Genesis/delivery/delivery.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit SHIRE_ROOM;
inherit INN_LIB;
inherit "/d/Genesis/delivery/office";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

static object innkeeper, hob, hob2, hob3, dwarf, hob4;
void add_stuff();

void
create_shire_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    object infoman;
    set_short("The Pipe and Fork Inn");
    set_long(
      "You have entered the Pipe and Fork. In the tradition of the hobbits it is "
      + "underground in a small hill. The doors are all round as are the few "
      + "windows. The air is filled with smoke coming from the numerous "
      + "pipes being smoked by the hobbits. You almost have trouble finding "
      + "the innkeeper in the dark room. On the wall you can see a pricelist. "
      + "West is a room separated from the main inn by curtains.\n");

    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a hobbit standing "+
      "behind it.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(MICH_DIR  + "gamroad4", "northeast");
    add_exit(MICH_DIR + "kitchen","west");

    infoman = clone_object(MICH_DIR + "npc/info_man");
    infoman->move(TO);
    reset_shire_room();

// delivery office info
    set_office("Pipe and Fork Inn of Michel Delving", 3);
    add_cmd_item("plaque","read","The plaque reads:\nHere you may:\n\n"+
        "\t<ask for a delivery tour> To get a delivery task.\n"+
        "\t<deliver>  To deliver an assigned task.\n"+
        "\t<return>  To return a failed delivery.\n");


    configure_shire_inn();
}

string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
    " 1. 'A nice cold beer' .............   20 cc\n"+
    " 2. 'A pint of ale' ................   50 cc\n"+
    " 3. 'A glass of red wine' ..........   80 cc\n"+
    " 4. 'A stout whiskey' ..............  180 cc\n"+
    "\nSnacks:\n\n"+
    " 5. 'A bag of cookies' .............   21 cc\n"+
    " 6. 'A ham sandwich' ...............   42 cc\n"+
    "\nMeals:\n\n"+
    " 7. 'A veggie delight' .............   65 cc\n"+
    " 8. 'Some rabbit stew' .............  109 cc\n"+
    " 9. 'Well cooked steak' ............  239 cc\n"+
    "10. 'The big meat medley' ..........  556 cc\n";
//    "11. 'Pot of chocolate' ............. 60 cc\n\n";
}
void
reset_shire_room()
{
    if (!innkeeper) innkeeper = clone_object(COMMON_NPC + "innkeeper_hob");
    if (!present(innkeeper)) innkeeper->move(this_object());
    set_alarm(2.0,0.0,"add_stuff");
    reset_office();
}

void
add_stuff()
{
    if(!hob)
    {
	hob = clone_object(HOBBITMAKER);
	hob->set_type(CITIZEN);
	hob->set_power(150);
	hob->move(TO);
    }
    if(!hob2)
    {
	hob2 = clone_object(HOBBITMAKER);
	hob2->set_type(MAIDEN);
	hob2->set_power(100);
	hob2->move(TO);
    }
    if(!hob3)
    {
	hob3 = clone_object(HOBBITMAKER);
	hob3->set_type(MILITA);
	hob3->set_power(150);
	hob3->move(TO);
    }
    if(!hob4)
    {
	hob4 = clone_object(HOBBITMAKER);
	hob4->set_type(CITIZEN);
	hob4->set_power(60);
	hob4->move(TO);
    }
    if(!dwarf)
    {
	dwarf = clone_object(MICH_DIR + "npc/dark_dwarf");
	dwarf->move(TO);
    }
}

init() {
    ::init();
    add_action("do_read", "read", 0);
    init_shire_inn();
    init_office();
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
    if (!innkeeper || !present(innkeeper)) {
	notify_fail("There is no one here to buy anything from.\n"+
	  "The innkeeper has been killed!\n");
	return 0;
    }
    return ::do_order(str);
}

mixed
get_order(string str1)
{
    object order;
    int price;

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
    case "whiskey": case "stout whiskey": case "4":
	order = clone_object("/std/drink");
	order->set_name("whiskey");
	order->set_pname("whiskeyss");
	order->set_short("stout whiskey");
	order->set_pshort("stout whiskeys");
	order->set_adj("stout");
	order->set_long("The smell of this powerful whiskey nearly knocks you down.\n");
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

    case "stew": case "rabbit stew": case "rabbit stew": case "8":
	order = clone_object("/std/food");
	order->set_name("stew");
	order->set_pname("stews");
	order->set_short("rabbit stew");
	order->set_pshort("rabbit stews");
	order->set_adj(({"rabbit", "rabbit"}));
	order->set_long("This is some delicious looking rabbit stew "+
	  "with chunks of taters and carrots and beans drowning in a "+
	  "thick, brown gravy.\n");
	order->set_amount(250);
	order->add_prop(OBJ_I_WEIGHT, 200);
	order->add_prop(OBJ_I_VOLUME, 300);
	order->add_prop(HEAP_S_UNIQUE_ID,"rabbit stew");
	price = 109;
	break;

    case "steak": case "well cooked steak": case "9":
	order = clone_object("/std/food");
	order->set_name("steak");
	order->set_pname("steaks");
	order->set_short("well grilled steak");
	order->set_pshort("well grilled steaks");
	order->set_adj(({"well", "grilled"}));
	order->set_long("Juices ooze from this nice, thick steak "+
	  "as it steams slightly, fresh from the grill.\n");
	order->set_amount(375);
	order->add_prop(OBJ_I_WEIGHT, 400);
	order->add_prop(OBJ_I_VOLUME, 300);
	order->add_prop(HEAP_S_UNIQUE_ID,"well grilled steak");
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
/*
    case "chocolate": case "pot": case "pot of chocolate": case "11":
        order = clone_object("/d/Shire/common/obj/chocolate");
        price = 60;
        break;
*/
    }
    return ({order}) + ({price});
}
