/*
 * Inn at Sarn Ford
 * Varian - February 2015
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include HOBBIT_FILE
#include <state_desc.h>

#define PRICELIST_ID ({"pricelist","list","sign","menu","prices"})


static object bill, dravan, innkeeper;

void

create_room()

{
    set_short("The Sleeping Fisherman");
    set_long("You are within the warm, welcoming confines of " +
      	"the main room of the Sleeping Fisherman Inn. There are " +
      	"dozens of round tables, circled with sturdy, wooden chairs, " +
      	"scattered randomly all around the main room. Across the " +
      	"east wall, a long bar runs in front of a very busy and " +
      	"active kitchen which is working hard to keep all of the " +
      	"customers full and content. A massive stone fireplace " +
      	"stands out from against the southern wall, distracting " +
      	"your eye away from the wooden staircase beside it, which " +
      	"wanders up to the next level of the inn. In the middle " +
      	"of the western wall, is the strong, oak door from which " +
      	"you entered, and beyond there, the docks outside. Prominently " +
      	"posted above the bar, is a clearly legible pricelist.\n");
  
    add_item(({"floor", "wooden floor", "planks", "wooden planks"}),
        "The floor of the inn has been constructed out of many " +
        "long, wooden planks. While it probably looked very nice " +
        "when it was originally constructed, despite the best " +
        "efforts of the innkeeper, it is now covered in a " +
        "multitude of stains from years of heavy use.\n");
    add_item(({"stain", "stains"}),
        "There are countless stains from spilled food and " +
        "drink covering the wooden floor beneath your feet.\n");
    add_item(({"ceiling", "wooden ceiling"}),
        "The ceiling of this inn has been constructed out of " +
        "wood, just like almost everything else here. In the " +
        "middle of the ceiling, an iron chandelier hangs " +
        "down, with several lit candles burning brightly to " +
        "offer a little more light in here.\n");
    add_item(({"candles", "candle", "chandelier", "iron chandelier"}),
        "There are several candles burning in an iron chandelier " +
        "which hangs down from the ceiling, offering some " +
        "additional light to what the massive fireplace " +
        "otherwise provides.\n");
    add_item(({"wall", "walls"}),
        "Which wall did you want to look at? The northern?, " +
        "eastern?, southern? or western wall?\n");
    add_item(({"door", "oak door", "strong door", "strong oak door"}),
        "The strong oak door is how you can exit the inn and " +
        "go back to the docks outisde.\n");
    add_item(({"west wall", "western wall"}),
        "There are several windows in the western wall, in addition " +
        "to the strong oak door, which all look out towards the docks " +
        "outside.\n");
    add_item(({"south wall", "southern wall"}),
        "The south wall of the inn has a massive fireplace which " +
        "seems to be constantly burning, keeping the inn nice and " +
        "warm. A wooden staircase nearby leads upstairs.\n");
    add_item(({"north wall", "northern wall"}),
        "The northern wall of the inn is fairly unassuming, it " +
        "is really just a wooden wall.\n");
    add_item(({"east wall", "eastern wall"}),
        "A long, oaken bar stretches across almost the entire " +
        "length of the eastern wall, where a very active kitchen " +
        "is partially concealed behind it.\n");
    add_item(({"fireplace", "stone fireplace", "massive fireplace", "massive stone fireplace"}),
        "This massive stone fireplace has been set into the south " +
        "wall of the inn, providing enough warmth to make the entire " +
        "inn feel cozy. A large fire burns brightly, with a massive " +
        "stack of firewood nearby to ensure that the fire never " +
        "goes out.\n");
    add_item(({"firewood", "wood", "stack", "stack of firewood"}),
        "There is a large stack of firewood here, in an effort to help " +
        "ensure that the fireplace will be constantly running.\n");
    add_item(({"staircase", "stairs", "wooden staircase"}),
        "This wooden staircase climbs up through the ceiling to " +
        "the second level of the inn, where some customers have " +
        "purchased a place to sleep for the evening.\n");
    add_item(({"window", "windows"}),
        "There are a few windows along the western wall which look " +
        "out upon the docks outside.\n");
    add_item(({"bar", "long bar", "oak bar", "long oak bar"}),
        "This long, oak bar has obviously seen plenty of use. The " +
        "bartender behind the counter seems to be constantly busy, " +
        "taking orders for meals and drinks.\n");
    add_item(({"kitchen", "busy kitchen", "active kitchen"}),
        "Hidden behind the bar along the eastern wall, you can see a " +
        "busy kitchen, filled with workers making food for the patrons " +
        "out in the main room.\n");
    add_item(({"patrons", "customers"}),
        "There are plenty of people here, can't you see them?\n");
    add_item(({"tables", "round tables", "wooden tables", "round wooden tables"}),
        "There are plenty of available tables here, each with several " +
        "wooden chairs encircling it, offering you a comfortable place " +
        "to enjoy a meal and a drink.\n");
    add_item(({"chairs", "wooden chairs"}),
        "There are literally dozens of wooden chairs, all haphazardly " +
        "spread out across the main room of the inn, offering plenty " +
        "of options to sit around various tables as you enjoy a " +
        "drink or a meal.\n");
    add_item(({"room", "main room", "inn", "sleeping fisherman inn"}),
        "You are within the warm, welcoming confines of " +
      	"the main room of the Sleeping Fisherman Inn. There are " +
      	"dozens of round tables, circled with sturdy, wooden chairs, " +
      	"scattered randomly all around the main room. Across the " +
      	"east wall, a long bar runs in front of a very busy and " +
      	"active kitchen which is working hard to keep all of the " +
      	"customers full and content. A massive stone fireplace " +
      	"stands out from against the southern wall, distracting " +
      	"your eye away from the wooden staircase beside it, which " +
      	"wanders up to the next level of the inn. In the middle " +
      	"of the western wall, is the strong, oak door from which " +
      	"you entered, and beyond there, the docks outside.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(SARNFORD_DIR + "dock.c", "out");
    add_exit(SARNFORD_DIR + "inn2.c", "up");

    setuid(); 
    seteuid(getuid());

    configure_shire_inn();
    reset_shire_room();
}

string
pricelist_desc()
{
    return "\nDrinks:\n\n"+
        " 1. A glass of water  . . . . . . . . .    8 cc\n"+
        " 2. A mug of brown beer . . . . . . . .   50 cc\n"+
        " 3. A glass of brandywine . . . . . . .   80 cc\n"+
        " 4. A house special . . . . . . . . . .  250 cc\n"+
        "\nSnacks:\n\n"+
        " 5. A plate of roasted potatoes . . . .   18 cc\n"+
        " 6. A tray of biscuits  . . . . . . . .   40 cc\n"+
        "\nMeals:\n\n"+
        " 7. A fish stew . . . . . . . . . . . .   75 cc\n"+
        " 8. A chicken pie . . . . . . . . . . .  100 cc\n"+
        " 9. A plate of fish and chips . . . . .  235 cc\n"+
        "10. A catch of the day  . . . . . . . .  650 cc\n"+
        "\nInn Services:\n\n"+
        "11. A key for the night . . . . . . . .  144 cc\n"+
        "    (young adventurers stay for free)\n\n";
}

void
reset_shire_room() 
{
    if(!bill) bill = clone_object(SARNFORD_DIR + "npc/billingsworth.c");
    if (!present(bill)) bill->move_living("somewhere", this_object());

    if(!dravan) dravan = clone_object(SARNFORD_DIR + "npc/dravan.c");
    if (!present(dravan)) dravan->move_living("somewhere", this_object());

    if(!innkeeper) innkeeper = clone_object(SARNFORD_DIR + "npc/haestur.c");
    if (!present(innkeeper)) innkeeper->move(this_object());
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

  if (!innkeeper || !present(innkeeper)) 
  {
    notify_fail("You cannot see anyone here to serve you.\n"+
                "Perhaps Haestur has gone away for a few minutes?\n");
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
    case "water": case "glass of water": case "1":
      order = clone_object(SARNFORD_DIR + "obj/water");
      price = 8;
      break;

    case "beer": case "brown beer": case "mug of brown beer": case "2":
      order = clone_object(SARNFORD_DIR + "obj/beer");
      price = 50;
      break;
    case "wine": case "brandywine": case "glass of brandywine": case "3":
      order = clone_object(SARNFORD_DIR + "obj/brandywine");
      price = 80;
      break;
    case "special": case "house special": case "4":
      order = clone_object(SARNFORD_DIR + "obj/housespecials");
      price = 250;
      break;
    case "potatoes": case "roasted potatoes": case "plate of roasted potatoes": case "5":
      order = clone_object(SARNFORD_DIR + "obj/potatoes");
      price = 21;
      break;
    case "biscuits": case "tray of biscuits": case "6":
      order = clone_object(SARNFORD_DIR + "obj/biscuits");
      price = 40;
      break;
    
    case "stew": case "fish stew": case "7":
      order = clone_object(SARNFORD_DIR + "obj/fishstew");
      price = 75;
      break;

    case "pie": case "chicken pie": case "8":
      order = clone_object(SARNFORD_DIR + "obj/chickenpie");
      price = 100;
      break;
    
    case "fish and chips": case "plate of fish and chips": case "9":
      order = clone_object(SARNFORD_DIR + "obj/fishandchips");
      price = 235;
      break;
   
    case "catch": case "catch of the day": case "10":
      order = clone_object(SARNFORD_DIR + "obj/catchoftheday");
      price = 650;
      break;

    case "key":
      order = clone_object(SARNFORD_DIR + "obj/innkey");
      if (SD_IS_NEWBIE(this_player())) price = 0;
      else price = 144;
      break;
  }

  return (({order}) + ({price}));
}



