/* The Inn of the Hungry Hungry Halfling
 * Updated the menu and the pub inherits
 * along with the add_food, add_drink so 
 * they would fit well with the new pub menu
 * For inclusion in Raumdor
 * Damaris 5/2001
 */

inherit "/std/room";
inherit "/d/Cirath/lib/pub";

#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


string
dummy_menu()
{
    read_menu("menu");
    return "";
}
void
reset_room()
{
   bring_room_mob("tar",TYR_NPC+"tar.c",1,1);
}


void
create_room()
{
  ::create_room();
  set_short("the Inn of the Hungry Hungry Halfling");
  set_long("This dark, crowded pub is the "+
    "famous Inn of the Hungry Hungry Halfling.  The owners "+
    "Tar and K'kikrik established the Inn, specializing "+
    "in Athasian halfling cuisine, years ago. Business has been "+
    "brisk ever since. "+
    "The clientele seems mostly made up of thri-keen, "+
    "with a few humans and dwarves also jostling for space "+
    "at the tables. "+
    "Carved into the wall are some symbols, which seem "+
    "to represent menu items.  Westward lies the dusty "+
    "street and the heat of the Athasian sun.\n");

  add_item(({"table","tables"}),
    "There are tables and chairs crammed into every "+
    "possible inch of this room, and all of them are "+
    "occupied.  There isn't much room to move, but the "+
    "customers are too preoccupied with eating to "+
    "notice.\n");
  add_item(({"clientele","customers"}),
    "The thri-keen customers seem intent on their dinner, "+
    "gorging themselves with a fervor, and "+
    "clacking their mandibles in culinary ecstacy.  The "+
    "more sedate human and dwarven customers also seem "+
    "to be enjoying themselves.  Remarkably, there are no "+
    "elven customers.\n");
  add_item(({"thrikeen","thri-keen"}),
    "The thri-keen are enthusiastically devouring everything "+
    "placed in front of them.  Including the occasional "+
    "waitress.\n");
  add_item(({"menu", "symbols"}), &dummy_menu());


    add_drink(({ "water", "mugs of water", "cold water", "cups of" }),
      "water", "mug of cold", 50, 0, 6, "mug of cold water", "mugs of cold water",
    "A mug of cold water drawn from a Tyrian well.\n",0);
    add_drink(({ "wine", "mugs of wine", "bulis wine", "mugs of" }),
      "wine", "mug of bulis", 125, 25, 70, "mug of bulis wine", "mugs of bulis wine",
    "A mug of bulis wine is warm, heavy, and sickeningly sweet: "+
    "This blue-purple liquid is a Tyr favorite.\n",0);
/* Above description swiped directly from Serpine ;)  
   and a _few_ other things i suppose... (revamped Damaris 5/2001) */
    add_drink(({ "blood", "cups of blood", "elf blood", "cups of" }),
      "blood", "cup of elf", 200, 50, 150, "cup of elf blood", "cups of elf blood",
    "A thick red wine made from the blood of elves, served warm.\n",0);
    add_food(({ "ear", "dried ear", "dried mul ear", "mul ear" }),
      "ear", "mul", 25, 30, "dried mul ear",
      "dried mul ears",
    "Sun dried and lightly spiced, this is a chewy treat.\n",0);
    add_food(({ "stew", "hot stew", "hot elf stew", "elf stew" }),
      "stew", "elf", 50, 75, "hot elf stew",
      "hot elf stews",
    "Thick chunks of elf meat and vegetables simmering in a spicy "+
    "broth.  Watch you don't burn your tongue!\n",0);
    add_food(({ "leg", "roasted leg", "roasted elf leg", "elf leg" }),
      "leg", "elf", 100, 120, "roasted elf leg",
      "roasted elf legs",
    "Fresh leg of elf, roasted over an open fire, with "+
    "Tar's special seasoning. A terrific meal at a great "+
    "price!\n",0);

  INSIDE
   add_exit(TYR_MARKET+"shdwsqrs.c","west",0,1,0);

  reset_room();

}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Hungry Hungry Halfling"));
}
int
do_read(string str)
{
    if (str != "menu")
    {
	notify_fail("Read what?\n");
	return 0;
    }

    write("It is forbidden to read in Tyr.\n");
    return 1;
}
   
void
init()
{
    ::init();
    init_pub();
    add_action(do_read, "read");  
}   

