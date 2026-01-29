inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "../local.h"

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define SUPL_DIR "/d/Shire/eastroad/western/villages/greenholm/supplies/"

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
    " 1. 'A mug of good beer' .................   20 cc\n"+
    " 2. 'A tall glass of ale' ................   51 cc\n"+
    " 3. 'A glass of white wine' ..............   78 cc\n"+
    " 4. 'A shot of strong whiskey' ...........  175 cc\n"+
    "\nSnacks:\n\n"+
    " 5. 'A bit of bread' .....................   21 cc\n"+
    " 6. 'A bologna sandwich' .................   40 cc\n"+
    "\nMeals:\n\n"+
    " 7. 'A hearty soup' ......................   80 cc\n"+
    " 8. 'A murkey stew' ......................  105 cc\n"+
    " 9. 'A large ham' ........................  250 cc\n"+
    "10. 'A roast chicken' ....................  972 cc\n\n";
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
     order = clone_object(SUPL_DIR + "beer");
     price = 20;
     break;
   case "ale": case "glass of ale": case "tall glass of ale": case "2":
     order = clone_object(SUPL_DIR + "ale");
     price = 54;
     break;
   case "wine": case "glass of white wine": case "white wine": case "3":
     order = clone_object(SUPL_DIR + "wwine");
     price = 78;
     break;
   case "whiskey": case "strong whiskey": case "4":
     order = clone_object(SUPL_DIR + "whiskey");
     price = 175;
     break;
   case "bread": case "5":
     order = clone_object(SUPL_DIR + "bread");
     price = 21;
     break;
   case "sandwich": case "bologna sandwich": case "6":
     order = clone_object(SUPL_DIR + "sandwich");
     price = 40;
     break;
   case "soup": case "hearty soup": case "7":
     order = clone_object(SUPL_DIR + "soup");
     price = 80;
     break;
   case "stew": case "murkey stew": case "8":
     order = clone_object(SUPL_DIR + "stew");
     price = 105;
     break;
   case "large ham": case "ham": case "big hambone": case "9":
     order = clone_object(SUPL_DIR + "ham");
     price = 250;
     break;
   case "chicken": case "roast chicken": case "10":
     order = clone_object(SUPL_DIR + "chicken");
     price = 972;
     break;
  }
  return (({order}) + ({price}));
}
