inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "../local.h"

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

object innkeeper;
object hobbit1, hobbit2, hobbit3;

void
create_room()
{

  configure_shire_inn();
   set_short("The Bounder inn");
   set_long("This rustic room in a stone building is full of "+
    "many smells, mostly of alcohol and food cooking. "+
   "Several stools have been pushed up to the bar, but it is likely "+
   "they have been already claimed by one of the many "+
   "hobbits who are regulars here.  There is a pricelist, "+
   "or menu, affixed to the bar.  The way out is south.\n");

  add_item(({"stool", "stools"}), "The stools are made out of wood.\n");
  add_item("bar", "It's made out of wood. There is a hobbit standing "+
                      "behind it.\n");

  add_item(PRICELIST_ID, "@@pricelist_desc");

  add_prop(ROOM_I_INSIDE,1);
  add_exit(GREENHOLM_DIR + "viln1","south");
  reset_shire_room();
}

string
pricelist_desc()
{
  return "\nDrinks:\n\n"+
    " 1. 'A mug of good beer' .............   20 cc\n"+
    " 2. 'A tall glass of ale' ................   51 cc\n"+
    " 3. 'A glass of white wine' ..........   78 cc\n"+
    " 4. 'A shot of strong whiskey' ...  175 cc\n"+
    "\nSnacks:\n\n"+
    " 5. 'A bit of bread' .............   21 cc\n"+
    " 6. 'A bologna sandwich' ...............   40 cc\n"+
    "\nMeals:\n\n"+
    " 7. 'A hearty soup' .............   80 cc\n"+
    " 8. 'A murkey stew' .............  105 cc\n"+
    " 9. 'A large ham' ............  250 cc\n"+
    "10. 'A roast chicken' ..........  972 cc\n\n";
}

void
reset_shire_room() 
{
  if (!innkeeper) innkeeper = clone_object(EAST_R_NPC + "boundkeeper");
  if (!present(innkeeper)) innkeeper->move(this_object());

  if (!hobbit1)
    {
      hobbit1 = clone_object(HOBBITMAKER);
      hobbit1->set_type(MILITA);
      hobbit1->set_power(130);
      hobbit1->move(TO);
    }

  if (!hobbit2)
    {
      hobbit2 = clone_object(HOBBITMAKER);
      hobbit2->set_type(CITIZEN);
      hobbit2->set_power(60);
      hobbit2->move(TO);
    }
  
   if (!hobbit3)
     {
       hobbit3 = clone_object(HOBBITMAKER);
       hobbit3->set_type(ELDER);
       hobbit3->set_power(100);
       hobbit3->move(TO);
     }
  
}

void
init() 
{
  ::init();
  init_shire_inn();
  add_action("do_read", "read", 0);
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
   int    price;

   switch (str) 
   {
   case "beer": case "good beer": case "mug of good beer": case "1":
     order = clone_object("/std/drink");
     order->set_name("beer");
     order->set_pname("beers");
     order->set_short("mug of good beer");
     order->set_pshort("mugs of good beer");
     order->set_adj(({"mug", "good"}));
     order->set_long("A very fresh, delicious beer, brewed for the "+
		     "tired Bounders to aid them in their work.\n");
     order->set_soft_amount(110);
     order->set_alco_amount(8);
      order->add_prop(OBJ_I_WEIGHT, 220);
     order->add_prop(OBJ_I_VOLUME, 220);
     price = 20;
     break;
     
   case "ale": case "glass of ale": case "tall glass of ale": case "2":
     order = clone_object("/std/drink");
     order->set_name(({"ale", "glass", "tall glass"}));
     order->set_pname(({"ales", "glasses", "tall glasses"}));
     order->set_short("tall glass of ale");
     order->set_pshort("glasses of ale");
     order->set_long("The tall glass of ale looks inviting.\n");
     order->set_soft_amount(100);
     order->set_alco_amount(14);
     order->add_prop(OBJ_I_WEIGHT, 54);
     order->add_prop(OBJ_I_VOLUME, 54);
     price = 54;
     break;
   case "wine": case "glass of white wine": case "white wine": case "3":
     order = clone_object("/std/drink");
     order->set_name(({"wine","white wine","glass"}));
     order->set_pname(({"wines","white wines","glasses"}));
     order->set_short("glass of white wine");
     order->set_pshort("glasses of white wine");
     order->set_long("This white wine has a touch of yellow to it,, "+
		     "and not completely white.\n");
     order->set_soft_amount(90);
     order->set_alco_amount(18);
     order->add_prop(OBJ_I_WEIGHT, 20);
     order->add_prop(OBJ_I_VOLUME, 20);
     price = 78;
     break;
   case "whiskey": case "strong whiskey": case "4":
     order = clone_object("/std/drink");
     order->set_name("whiskey");
     order->set_pname("whiskeys");
     order->set_short("strong whiskey");
     order->set_pshort("strong whiskeys");
     order->set_adj("strong");
     order->set_long("Greenholm is famous for its strong, but foul-tasting "+
		     "whiskey.\n");
     order->set_soft_amount(50);
     order->set_alco_amount(30);
     order->add_prop(OBJ_I_WEIGHT, 100);
     order->add_prop(OBJ_I_VOLUME, 100);
     price = 175;
     break;
   case "bread": case "5":
     order = clone_object("/std/food");
     order->set_name("bread");
     order->set_pname("breadss");
     order->set_short("bit of bread");
     order->set_pshort("bits of bread");
     order->set_long("This is a lightly toasted bit of bread.\n");
     order->set_amount(100);
     order->add_prop(OBJ_I_WEIGHT, 100);
     order->add_prop(OBJ_I_VOLUME, 200);
     order->add_prop(HEAP_S_UNIQUE_ID,"bread");
     price = 21;
     break;
   case "sandwich": case "bologna sandwich": case "6":
     order = clone_object("/std/food");
     order->set_name("sandwich");
     order->set_pname("sandwiches");
     order->set_short("bologna sandwich");
     order->set_pshort("bologna sandwiches");
     order->set_adj("bologna");
     order->set_long("It looks worth a try.\n");
     order->set_amount(150);
     order->add_prop(OBJ_I_WEIGHT, 80);
     order->add_prop(OBJ_I_VOLUME, 100);
     order->add_prop(HEAP_S_UNIQUE_ID,"bologna sandwich");
     price = 40;
     break;
    
   case "soup": case "hearty soup": case "7":
     order = clone_object("/std/food");
     order->set_name("soup");
     order->set_pname("soups");
     order->set_short("hearty soup");
     order->set_pshort("hearty soups");
     order->set_adj("hearty");
     order->set_long("This soup is made of carrots, onions, "+
		     "cabbage, potatoes and celery.\n");
     order->set_amount(190);
     order->add_prop(OBJ_I_WEIGHT,250);
     order->add_prop(OBJ_I_VOLUME,350);
     order->add_prop(HEAP_S_UNIQUE_ID,"hearty soup");
     price = 80;
     break;
     
   case "stew": case "murkey stew": case "8":
     order = clone_object("/std/food");
     order->set_name("stew");
     order->set_pname("stews");
     order->set_short("murkey stew");
     order->set_pshort("murkey stews");
     order->set_adj(({"murkey"}));
     order->set_long("This is some delicious looking beef stew "+
		     "with chunks of taters and carrots and beans drowning in a "+
		     "thick, brown gravy.\n");
     order->set_amount(250);
     order->add_prop(OBJ_I_WEIGHT, 200);
     order->add_prop(OBJ_I_VOLUME, 300);
     order->add_prop(HEAP_S_UNIQUE_ID,"murkey stew");
     price = 105;
     break;
     
   case "large ham": case "ham": case "big hambone": case "9":
     order = clone_object("/std/food");
     order->set_name(({"ham","hambone"}));
     order->set_pname(({"hams","hambones"}));
     order->set_short("large steak");
     order->set_pshort("large steaks");
     order->set_adj(({"large", "hambone"}));
     order->set_long("Juices ooze from this nice, thick ham "+
		     "as it steams slightly, fresh from the oven.\n");
     order->set_amount(375);
     order->add_prop(OBJ_I_WEIGHT, 400);
     order->add_prop(OBJ_I_VOLUME, 300);
     order->add_prop(HEAP_S_UNIQUE_ID,"big hambone");
     price = 250;
     break;
     
   case "chicken": case "roast chicken": case "10":
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
     order->add_prop(HEAP_S_UNIQUE_ID,"roast chicken");
     price = 972;
     break;
  }
  return (({order}) + ({price}));
}
