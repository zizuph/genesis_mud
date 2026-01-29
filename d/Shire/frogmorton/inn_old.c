/*
 * The Floating Log in of Frogmorton
 * by Finwe, September 1998
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Shire/lib/inn";
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include HOBBIT_FILE
 
inherit SHIRE_ROOM;
#define PRICELIST_ID ({"pricelist","list","sign","menu","prices"})
 
static object innkeeper;
object hobbit1, hobbit2, hobbit3;
 
void add_stuff();
 
void
create_shire_room()
{
 
   configure_shire_inn();
   set_short("The Floating Log Inn");
   set_long("This is the Floating Log, one of the most famous " +
        "inns in the Shire. Hobbits always stop here on there " +
        "travels because the ale is so good and the food is " +
        "exceptional. Hobbits even make special trips here just " +
        "to enjoy the food and ale. The in always busy, but " +
        "especially in the evening when travellers stop in for " +
        "a bite to eat and to spend the night. Amongst all the " +
        "visitors here, you see hobbit darting in and out. He " +
        "must be the innkeeper. A pricelist is on the wall.\n");
 
 
   add_item(({"chair","chairs","table","tables"}),
            "The chairs and tables have had rather rough treatment by "+
            "the guests but most seem intact.\n");
   add_item(({"counter","counters"}),
            "The counter is made of two shipping crates with an old "+
            "round hobbitish door placed atop them.\n");
 
   add_item(PRICELIST_ID, "@@pricelist_desc");
 
   set_room_tell_time(30);
   add_room_tell("say A group of hobbits suddenly laugh out loud.");
   add_room_tell("say A drunk hobbit stands up on a table and does a " +
        "little jig.");
   add_room_tell("say the barkeeper runs around and fills beer mugs.\n");
   add_room_tell("say A hobbit yells for refills.");
   add_room_tell("say A drunk hobbit stumbles out of the Inn.");
   add_room_tell("say A group of weary travellers enter the Inn.");
   
   add_prop(ROOM_I_INSIDE,1);
   add_exit(FROG_DIR + "road01","out");
   reset_shire_room();
}
 
string
pricelist_desc()
{
  return "\nDrinks:\n\n"+
    " 1.  A fresh cold beer . . . . . . . .  20 cc\n"+
    " 2.  A pint of fine ale. . . . . . . .  50 cc\n"+
    " 3.  A mug of porter . . . . . . . . .  80 cc\n"+
    "\nSnacks:\n\n"+
    " 4.  A slice of bread and jam. . . . .  18 cc\n"+ 
    " 5.  A large pickle. . . . . . . . . .  25 cc\n"+
    " 6.  A butter scone. . . . . . . . . .  40 cc\n"+
    "\nMeals:\n\n"+
    " 7.  A vegetable salad . . . . . . . .  75 cc\n"+
    " 8.  A vegetable soup. . . . . . . . . 100 cc\n"+
    " 9.  A meat pie. . . . . . . . . . . . 235 cc\n"+
    "\nDesserts:\n\n"+
    "10.  A seed cake . . . . . . . . . . .  50 cc\n"+
    "11.  An apple tart . . . . . . . . . .  75 cc\n"+
    "12.  A mincemeat pie . . . . . . . . . 120 cc\n";
 
}
 
void
reset_shire_room() 
{
/*
  if(!innkeeper) innkeeper = clone_object(FNPC_DIR + "stone_keeper");
  if (!present(innkeeper)) innkeeper->move(this_object());
*/
  set_alarm(0.4,0.0,"add_stuff");
}
 
void
init() 
{
  ::init();
  add_action("do_read", "read", 0);
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
/*
 
  if (!innkeeper || !present(innkeeper)) 
  {
    notify_fail("There is no one here to buy anything from.\n"+
                "The innkeeper has been killed!\n");
    return 0;
  }
*/
  return ::do_order(str);
}
 
mixed *
get_order(string str)
{
  object order;
  int price;
 
  switch (str) 
  {
    case "beer": case "cold beer": case "fresh cold beer": case "1":
      order = clone_object("/std/drink");
      order->set_name("beer");
      order->set_pname("beers");
      order->set_short("fresh cold  beer");
      order->set_pshort("fresh cold beers");
      order->set_adj(({"fresh", "delicious"}));
      order->set_long("A large mug of freshly brewed in " +
        "Frogmorton for hobbits to enjoy.\n");
      order->set_soft_amount(110);
      order->set_alco_amount(8);
      order->add_prop(OBJ_I_WEIGHT, 220);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 20;
      break;
 
    case "ale": case "pint": case "fresh ale": 
    case "pint of fresh ale": case "2":
      order = clone_object("/std/drink");
      order->set_name(({"ale", "pint", "fresh ale", "pint of fresh ale"}));
      order->set_pname(({"ales", "pints", "fresh ale", 
        "pints of fresh ale"}));
      order->set_short("pint of fresh ale");
      order->set_pshort("pints of fresh ale");
      order->set_long("The pint of fresh ale looks rich and " +
        "delicious.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(14);
      order->add_prop(OBJ_I_WEIGHT, 54);
      order->add_prop(OBJ_I_VOLUME, 54);
      price = 50;
      break;
    
      case "porter": case "mug": case "mug of porter": case "3":
      order = clone_object("/std/drink");
      order->set_name(({"porter", "mug"}));
      order->set_pname(({"porter","mugs"}));
      order->set_short("mug of porter");
      order->set_pshort("mugs of porter");
      order->set_long("This porter is a dark beer made from " +
        "browned malt somewhere in the Shire.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(20);
      order->add_prop(OBJ_I_WEIGHT, 22);
      order->add_prop(OBJ_I_VOLUME, 22);
      price = 80;
      break;
    case "bread": case "slice": case "bread and jam": 
        case "slice of bread and jam": case "4":
      order = clone_object("/std/food");
      order->set_name(({"bread", "slice of bread", 
        "slice of bread and jam"}));
      order->set_pname(({"bread", "slices of bread", 
        "slices of bread and jam"}));
      order->set_short("slice of bread and jam");
      order->set_pshort("slices of bread and jam");
      order->set_long("This is a slice of frsh bread. It is " +
        "buttered and covered with fresh jam.\n");
      order->set_amount(100);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 200);
      order->add_prop(HEAP_S_UNIQUE_ID,"red_and_jam");
      price = 18;
      break;
    case "pickle": case "large": case "large pickle" : case "5":
      order = clone_object("/std/food");
      order->set_name(({"pickle", "large"}));
      order->set_pname(({"pickles", "large"}));
      order->set_short("large pickle");
      order->set_pshort("large pickles");
      order->set_long("It is a large cucumber, picked in brine " +
        "and aged for a couple of months. It looks crunchy.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 80);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"pickle");
      price = 25;
      break;
 
    case "butter": case "scone": case "butter scone": case "6":
      order = clone_object("/std/food");
      order->set_name(({"butter", "scone"}));
      order->set_pname(({"butter", "scones"}));
      order->set_short("butter scone");
      order->set_pshort("butter scones");
      order->set_long("It is a round piece of bread that is " +
        "covered with rich butter.\n");
      order->set_amount(200);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"scone");
      price = 40;
      break;
 
    case "vegetable": case "salad": case "vegetable salad": case "7":
      order = clone_object("/std/food");
      order->set_name(({"vegetable", "salad"}));
      order->set_pname(({"vegetable", "salads"}));
      order->set_short("vegetable salad");
      order->set_pshort("vegetable salads");
      order->set_long("It is a mixture of lettuce, carrots, " +
        "purple cabbage, and cucumbers sliced and tossed together.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 120);
      order->add_prop(HEAP_S_UNIQUE_ID,"veg_salad");
      price = 75;
      break;
    
    case "soup": case "vegetable soup": case "8":
      order = clone_object("/std/food");
      order->set_name("soup");
      order->set_pname("soups");
      order->set_short("vegetable soup");
      order->set_pshort("vegetable soups");
      order->set_adj("vegetable");
      order->set_long("This soup is made of carrots, onions, "+
        "cabbage, potatoes and celery. The vegetable are in a " +
         "rich broth of seasonings.\n");
      order->set_amount(190);
      order->add_prop(OBJ_I_WEIGHT,250);
      order->add_prop(OBJ_I_VOLUME,350);
      order->add_prop(HEAP_S_UNIQUE_ID,"veg_soup");
      price = 75;
      break;
 
   
    case  "pie": case "meat": case "meat pie": case "9":
      order = clone_object("/std/food");
      order->set_name(({"meat","pie"}));
      order->set_pname(({"meat","pie"}));
      order->set_short("meat pie");
      order->set_pshort("meat pies");
      order->set_long("This meat pie is full of chunks of brown " +
        "meat vegetables, and a thick broth. The crust is " +
        "golden brown.\n");
      order->set_amount(375);
      order->add_prop(OBJ_I_WEIGHT, 400);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"nice juicy steak");
      price = 235;
      break;
   
    case "cake": case "seed": case "seed cake": case "10":
      order = clone_object("/std/food");
      order->set_name(({"seed", "cake"}));
      order->set_pname(({"seed", "cakes"}));
      order->set_short("seed cake");
      order->set_pshort("seed cakes");
      order->set_long("This seed cake is moist and looks " +
        "delicious. Small black seeds are scattered across " +
        "the top.\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,500);
      order->add_prop(OBJ_I_VOLUME,700);
      order->add_prop(HEAP_S_UNIQUE_ID,"seed_cake");
      price = 50;
      break;
 
    case "tart": case "apple": case "apple tart": case "11":
      order = clone_object("/std/food");
      order->set_name(({"apple", "tart"}));
      order->set_pname(({"apple", "tarts"}));
      order->set_short("apple tart");
      order->set_pshort("apple tarts");
      order->set_long("This apple tart is triagular shaped. " +
        "It's covered with a white glaze and stuffed full of " +
        "apples. It's still warm from the oven.\n");
      order->set_amount(200);
      order->add_prop(OBJ_I_WEIGHT,50);
      order->add_prop(OBJ_I_VOLUME,250);
      order->add_prop(HEAP_S_UNIQUE_ID,"apple_tart");
      price = 75;
      break;
 
    case "mincemeat": case "pie": case "mincemeat pie": case "12":
      order = clone_object("/std/food");
      order->set_name(({"mincemeat", "pie"}));
      order->set_pname(({"mincemeat", "pies"}));
      order->set_short("mincemeat pie");
      order->set_pshort("mincemeat pies");
      order->set_long("This pie is a mixture of finely chopped " +
        "apples, aromatic spices, amnd chopped rabbit meat in a " +
        "broth.\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,500);
      order->add_prop(OBJ_I_VOLUME,700);
      order->add_prop(HEAP_S_UNIQUE_ID,"mincemeet_pie");
      price = 120;
      break;
 
  }
 
  return (({order}) + ({price}));
}
 
 
void
add_stuff()
{
/*
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
     hobbit2->set_title("the Barkeeper of the Floating Log");
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
*/
 
}
/*
 * The Floating Log in of Frogmorton
 * by Finwe, September 1998
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Shire/lib/inn";
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include HOBBIT_FILE
 
inherit SHIRE_ROOM;
#define PRICELIST_ID ({"pricelist","list","sign","menu","prices"})
 
static object innkeeper;
object hobbit1, hobbit2, hobbit3;
 
void add_stuff();
 
void
create_shire_room()
{
 
   configure_shire_inn();
   set_short("The Floating Log Inn");
   set_long("This is the Floating Log, one of the most famous " +
        "inns in the Shire. Hobbits always stop here on there " +
        "travels because the ale is so good and the food is " +
        "exceptional. Hobbits even make special trips here just " +
        "to enjoy the food and ale. The in always busy, but " +
        "especially in the evening when travellers stop in for " +
        "a bite to eat and to spend the night. Amongst all the " +
        "visitors here, you see hobbit darting in and out. He " +
        "must be the innkeeper. A pricelist is on the wall.\n");
 
 
   add_item(({"chair","chairs","table","tables"}),
            "The chairs and tables have had rather rough treatment by "+
            "the guests but most seem intact.\n");
   add_item(({"counter","counters"}),
            "The counter is made of two shipping crates with an old "+
            "round hobbitish door placed atop them.\n");
 
   add_item(PRICELIST_ID, "@@pricelist_desc");
 
   set_room_tell_time(30);
   add_room_tell("say A group of hobbits suddenly laugh out loud.");
   add_room_tell("say A drunk hobbit stands up on a table and does a " +
        "little jig.");
   add_room_tell("say the barkeeper runs around and fills beer mugs.\n");
   add_room_tell("say A hobbit yells for refills.");
   add_room_tell("say A drunk hobbit stumbles out of the Inn.");
   add_room_tell("say A group of weary travellers enter the Inn.");
   
   add_prop(ROOM_I_INSIDE,1);
   add_exit(FROG_DIR + "road01","out");
   reset_shire_room();
}
 
string
pricelist_desc()
{
  return "\nDrinks:\n\n"+
    " 1.  A fresh cold beer . . . . . . . .  20 cc\n"+
    " 2.  A pint of fine ale. . . . . . . .  50 cc\n"+
    " 3.  A mug of porter . . . . . . . . .  80 cc\n"+
    "\nSnacks:\n\n"+
    " 4.  A slice of bread and jam. . . . .  18 cc\n"+ 
    " 5.  A large pickle. . . . . . . . . .  25 cc\n"+
    " 6.  A butter scone. . . . . . . . . .  40 cc\n"+
    "\nMeals:\n\n"+
    " 7.  A vegetable salad . . . . . . . .  75 cc\n"+
    " 8.  A vegetable soup. . . . . . . . . 100 cc\n"+
    " 9.  A meat pie. . . . . . . . . . . . 235 cc\n"+
    "\nDesserts:\n\n"+
    "10.  A seed cake . . . . . . . . . . .  50 cc\n"+
    "11.  An apple tart . . . . . . . . . .  75 cc\n"+
    "12.  A mincemeat pie . . . . . . . . . 120 cc\n";
 
}
 
void
reset_shire_room() 
{
/*
  if(!innkeeper) innkeeper = clone_object(FNPC_DIR + "stone_keeper");
  if (!present(innkeeper)) innkeeper->move(this_object());
*/
  set_alarm(0.4,0.0,"add_stuff");
}
 
void
init() 
{
  ::init();
  add_action("do_read", "read", 0);
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
/*
 
  if (!innkeeper || !present(innkeeper)) 
  {
    notify_fail("There is no one here to buy anything from.\n"+
                "The innkeeper has been killed!\n");
    return 0;
  }
*/
  return ::do_order(str);
}
 
mixed *
get_order(string str)
{
  object order;
  int price;
 
  switch (str) 
  {
    case "beer": case "cold beer": case "fresh cold beer": case "1":
      order = clone_object("/std/drink");
      order->set_name("beer");
      order->set_pname("beers");
      order->set_short("fresh cold  beer");
      order->set_pshort("fresh cold beers");
      order->set_adj(({"fresh", "delicious"}));
      order->set_long("A large mug of freshly brewed in " +
        "Frogmorton for hobbits to enjoy.\n");
      order->set_soft_amount(110);
      order->set_alco_amount(8);
      order->add_prop(OBJ_I_WEIGHT, 220);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 20;
      break;
 
    case "ale": case "pint": case "fresh ale": 
    case "pint of fresh ale": case "2":
      order = clone_object("/std/drink");
      order->set_name(({"ale", "pint", "fresh ale", "pint of fresh ale"}));
      order->set_pname(({"ales", "pints", "fresh ale", 
        "pints of fresh ale"}));
      order->set_short("pint of fresh ale");
      order->set_pshort("pints of fresh ale");
      order->set_long("The pint of fresh ale looks rich and " +
        "delicious.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(14);
      order->add_prop(OBJ_I_WEIGHT, 54);
      order->add_prop(OBJ_I_VOLUME, 54);
      price = 50;
      break;
    case "porter": case "mug": case "mug of porter": case "3":
      order = clone_object("/std/drink");
      order->set_name(({"porter", "mug"}));
      order->set_pname(({"porter","mugs"}));
      order->set_short("mug of porter");
      order->set_pshort("mugs of porter");
      order->set_long("This porter is a dark beer made from " +
        "browned malt somewhere in the Shire.\n");
      order->set_soft_amount(100);
      order->set_alco_amount(20);
      order->add_prop(OBJ_I_WEIGHT, 22);
      order->add_prop(OBJ_I_VOLUME, 22);
      price = 80;
      break;
    case "cracker": case "4":
      order = clone_object("/std/food");
      order->set_name(({"bread", "slice of bread", 
        "slice of bread and jam"}));
      order->set_pname(({"bread", "slices of bread", 
        "slices of bread and jam"}));
      order->set_short("slice of bread and jam");
      order->set_pshort("slices of bread and jam");
      order->set_long("This is a slice of frsh bread. It is " +
        "buttered and covered with fresh jam.\n");
      order->set_amount(100);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 200);
      order->add_prop(HEAP_S_UNIQUE_ID,"red_and_jam");
      price = 18;
      break;
    case "pickle": case "large": case "5":
      order = clone_object("/std/food");
      order->set_name(({"pickle", "large"}));
      order->set_pname(({"pickles", "large"}));
      order->set_short("large pickle");
      order->set_pshort("large pickles");
      order->set_long("It is a large cucumber, picked in brine " +
        "and aged for a couple of months. It looks crunchy.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 80);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"pickle");
      price = 25;
      break;
 
    case "butter": case "scone": case "6":
      order = clone_object("/std/food");
      order->set_name(({"butter", "scone"}));
      order->set_pname(({"butter", "scones"}));
      order->set_short("butter scone");
      order->set_pshort("butter scones");
      order->set_long("It is a round piece of bread that is " +
        "covered with rich butter.\n");
      order->set_amount(200);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 100);
      order->add_prop(HEAP_S_UNIQUE_ID,"scone");
      price = 40;
      break;
 
    case "vegetable": case "salad": case "7":
      order = clone_object("/std/food");
      order->set_name(({"vegetable", "salad"}));
      order->set_pname(({"vegetable", "salads"}));
      order->set_short("vegetable salad");
      order->set_pshort("vegetable salads");
      order->set_long("It is a mixture of lettuce, carrots, " +
        "purple cabbage, and cucumbers sliced and tossed together.\n");
      order->set_amount(150);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 120);
      order->add_prop(HEAP_S_UNIQUE_ID,"veg_salad");
      price = 75;
      break;
    
    case "soup": case "vegetable soup": case "8":
      order = clone_object("/std/food");
      order->set_name("soup");
      order->set_pname("soups");
      order->set_short("vegetable soup");
      order->set_pshort("vegetable soups");
      order->set_adj("vegetable");
      order->set_long("This soup is made of carrots, onions, "+
        "cabbage, potatoes and celery. The vegetable are in a " +
         "rich broth of seasonings.\n");
      order->set_amount(190);
      order->add_prop(OBJ_I_WEIGHT,250);
      order->add_prop(OBJ_I_VOLUME,350);
      order->add_prop(HEAP_S_UNIQUE_ID,"veg_soup");
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
      order->add_prop(HEAP_S_UNIQUE_ID,"beef_stew");
      price = 100;
      break;
    
    case "pie": case "meat": case "meat pie": case "9":
      order = clone_object("/std/food");
      order->set_name(({"meat","pie"}));
      order->set_pname(({"meat","pie"}));
      order->set_short("meat pie");
      order->set_pshort("meat pies");
      order->set_long("This meat pie is full of chunks of brown " +
        "meat vegetables, and a thick broth. The crust is " +
        "golden brown.\n");
      order->set_amount(375);
      order->add_prop(OBJ_I_WEIGHT, 400);
      order->add_prop(OBJ_I_VOLUME, 300);
      order->add_prop(HEAP_S_UNIQUE_ID,"nice juicy steak");
      price = 235;
      break;
   
    case "cake": case "seed": case "seed cake": case "10":
      order = clone_object("/std/food");
      order->set_name(({"seed", "cake"}));
      order->set_pname(({"seed", "cakes"}));
      order->set_short("seed cake");
      order->set_pshort("seed cakes");
      order->set_long("This seed cake is moist and looks " +
        "delicious. Small black seeds are scattered across " +
        "the top.\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,500);
      order->add_prop(OBJ_I_VOLUME,700);
      order->add_prop(HEAP_S_UNIQUE_ID,"seed_cake");
      price = 50;
      break;
 
    case "tart": case "apple": case "apple tart": case "11":
      order = clone_object("/std/food");
      order->set_name(({"apple", "tart"}));
      order->set_pname(({"apple", "tarts"}));
      order->set_short("apple tart");
      order->set_pshort("apple tarts");
      order->set_long("This apple tart is triagular shaped. " +
        "It's covered with a white glaze and stuffed full of " +
        "apples. It's still warm from the oven.\n");
      order->set_amount(200);
      order->add_prop(OBJ_I_WEIGHT,50);
      order->add_prop(OBJ_I_VOLUME,250);
      order->add_prop(HEAP_S_UNIQUE_ID,"apple_tart");
      price = 75;
      break;
 
    case "mincemeat": case "pie": case "mincemeat pie": case "12":
      order = clone_object("/std/food");
      order->set_name(({"mincemeat", "pie"}));
      order->set_pname(({"mincemeat", "pies"}));
      order->set_short("mincemeat pie");
      order->set_pshort("mincemeat pies");
      order->set_long("This pie is a mixture of finely chopped " +
        "apples, aromatic spices, amnd chopped rabbit meat in a " +
        "broth.\n");
      order->set_amount(575);
      order->add_prop(OBJ_I_WEIGHT,500);
      order->add_prop(OBJ_I_VOLUME,700);
      order->add_prop(HEAP_S_UNIQUE_ID,"mincemeet_pie");
      price = 120;
      break;
 
  }
 
  return (({order}) + ({price}));
}
 
 
void
add_stuff()
{
/*
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
     hobbit2->set_title("the Barkeeper of the Floating Log");
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
*/
 
}
