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
#define MAX_CITIZENS 3
#define SUPL_DIR "/d/Shire/frogmortom/supplies/"
 
static object *hobbits = allocate(MAX_CITIZENS);
static object innkeeper;
object hobbit1, hobbit2, hobbit3;
 
void add_stuff();
 
void
create_shire_room()
{
 
   configure_shire_inn();
   set_short("The Floating Log Inn");
   set_long("This is the Floating Log, one of the best inns in " +
        "the Shire. Hobbits from all over the Shire stop here " +
        "on their travels because of the good food and drink. " +
        "The inn is always busy, but especially in the evening " +      
        "when travellers stop in for a bite to eat and to spend " +
        "the night and socialize with friends and family. A " +
        "busy hobbit runs around, cleaning tables and filling " +
        "orders. A pricelist is on the wall.\n");
   add_item(({"chair","chairs","table","tables"}),
            "The chairs and tables have had rather rough treatment by "+
            "the guests but most seem intact.\n");
   add_item(({"counter","counters"}),
            "The counter is made of two shipping crates with an old "+
            "round hobbitish door placed atop them.\n");
 
   add_item(PRICELIST_ID, "@@pricelist_desc");
 
   set_room_tell_time(30);
   add_room_tell("A group of hobbits suddenly laugh out loud.");
   add_room_tell("A drunk hobbit stands up on a table and does a " +
        "little jig.");
   add_room_tell("The innkeeper runs around and fills beer mugs.\n");
   add_room_tell("A hobbit yells for refills.");
   add_room_tell("A drunk hobbit stumbles out of the Inn.");
   add_room_tell("A group of weary travellers enter the Inn.");
   
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
 
    int index;
 
    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_CITIZENS; index++)
    {
        if (!objectp(hobbits[index]))
         {
            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index]->set_type(CITIZEN);
            hobbits[index]->set_power(100);
            hobbits[index]->add_chat("Another round of ale for " +
                "my friends here!");
            hobbits[index]->add_chat("I can drink any hobbit " +
                "under the table!");
            hobbits[index]->add_chat("Frogmorton is the best " +
                "village in the Shire.");
            hobbits[index]->add_chat("Where's Mungo?!? My " +
                "tankard needs refilling!"); 
            hobbits[index]->add_chat("This is the best inn around.");
            hobbits[index]->move(TO);
 
        }
    }

// clone innkeeper
  if(!innkeeper) innkeeper = clone_object(FNPC_DIR + "mungo");
    if (!present(innkeeper)) innkeeper->move(this_object());

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
      order = clone_object(SUPL_DIR + "beer");
      price = 20;
      break;
    case "ale": case "pint": case "fresh ale": 
    case "pint of fresh ale": case "2":
      order = clone_object(SUPL_DIR + "ale");
      price = 50;
      break;
    case "porter": case "mug": case "mug of porter": case "3":
      order = clone_object(SUPL_DIR + "porter");
      price = 80;
      break;
    case "bread": case "slice": case "bread and jam": 
    case "slice of bread and jam": case "4":
      order = clone_object(SUPL_DIR + "bread");
      price = 18;
      break;
    case "pickle": case "large": case "large pickle" : case "5":
      order = clone_object(SUPL_DIR + "pickle");
      price = 25;
      break;
    case "butter": case "scone": case "butter scone": case "6":
      order = clone_object(SUPL_DIR + "scone");
      price = 40;
      break;
    case "vegetable": case "salad": case "vegetable salad": case "7":
      order = clone_object(SUPL_DIR + "salad");
      price = 75;
      break;
    case "soup": case "vegetable soup": case "8":
      order = clone_object(SUPL_DIR + "soup");
      price = 75;
      break;
    case "meat": case "meat pie": case "9":
      order = clone_object(SUPL_DIR + "meat");
      price = 235;
      break;
    case "cake": case "seed": case "seed cake": case "10":
      order = clone_object(SUPL_DIR + "cake");
      price = 50;
      break;
    case "tart": case "apple": case "apple tart": case "11":
      order = clone_object(SUPL_DIR + "tart");
      price = 75;
      break;
    case "mincemeat": case "pie": case "mincemeat pie": case "12":
      order = clone_object(SUPL_DIR + "pie");
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
