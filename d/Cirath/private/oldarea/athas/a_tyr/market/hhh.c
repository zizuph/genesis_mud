/* The Inn of the Hungry Hungry Halfling */

inherit "/std/room";
inherit "/lib/pub";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
  bring_room_mob("tar",TYR_NPCS+"tar.c",1,1);
}


void
create_room()
{
  set_short("the Inn of the Hungry Hungry Halfling.");
  set_long("This dark, crowded pub is the "+
    "famous Inn of the Hungry Hungry Halfling.  The owners "+
    "Tar and K'kikrik established the Inn, specializing "+
    "in Athasian halfling cuisine, years ago. Business has been "+
    "brisk ever since. "+
    "The clientele seems mostly made up of thri-keen, "+
    "with a few humans and dwarves also jostling for space "+
    "at the tables. "+
    "Carven into the wall are some symbols, which seem "+
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
  add_item(({"menu","symbols"}),
    "In symbols widely recognized throughout Athas, the "+
    "menu lists:\n"+
    " Food                          Drinks\n"+
    "Dried Mul Ears   30 cc        Water                6 cc\n"+
    "Elf Stew         75 cc        Bulis Wine          70 cc\n"+
    "Roast Elf Leg   120 cc        Elf Blood          150 cc\n\n");

  add_cmd_item(({"menu","symbols"}),"read","Surely you jest, "+
    "reading is illegal in Tyr!  Fortunately, the menu is "+
    "examinable.\n");

  add_drink(({"water","waters"}),"water","cold",50,0,6,0,0,
    "A mug of cold water drawn from a Tyrian well.\n",0);
  add_drink(({"wine","wines","bulis wine","bulis wines"}),
    "wine","bulis",125,25,70,0,0,
    "Warm, heavy, and sickeningly sweet: This blue-purple "+
    "liquid is a Tyr favorite.\n",0);
/* Above description swiped directly from Serpine ;)  
   and a _few_ other things i suppose...             */
  add_drink(({"blood", "bloods","elf blood","elf bloods","cup of blood", "cups of blood", "cup","cups","cup of elf blood","cups of elf blood"}),
    ({"blood", "cup"}), "elf", 200, 50, 150, "cup of elf blood", "cups of elf blood",
    "A thick red wine made from the blood of elves, served warm.\n",0);
  add_food(({"ear","ears","dried ear","dried ears",
    "dried mul ear","dried mul ears","mul ear","mul ears"}),
    "ear","dried mul",25,30,0,0,
    "Sun dried and lightly spiced, this is a chewy treat.\n",0);
  add_food(({"stew","stews","elf stew","elf stews"}),
    "stew","elf",50,75,0,0,
    "Thick chunks of elf meat and vegetables simmering in a spicy "+
    "broth.  Watch you don't burn your tongue!\n",0);
  add_food(({"roast","roasts","leg","legs","roast leg",
    "roast legs","elf leg","elf legs","roast elf leg",
    "roast elf legs"}),"leg","roast elf",100,120,0,0,
    "Fresh leg of elf, roasted over an open fire, with "+
    "Tar's special seasoning. A terrific meal at a great "+
    "price!\n",0);

  INSIDE
  add_exit(TZ_MARKET+"shdwsqrs.c","west",0,1,0);

  reset_room();

}

void
init()
{
  ::init();
  init_pub();
}

