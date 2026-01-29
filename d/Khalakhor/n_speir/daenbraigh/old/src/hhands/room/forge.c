/*
 * Hammerhand forge
 * TAPAKAH, 10/2005
 * Acquired from Khalakhor forge by Boron, Damaris et al.
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Khalakhor/std/room";
inherit "/d/Shire/smiths/rooms/base_forge_room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>

#define LIVE_I_BLACKENING "_live_i_blackening"
#define LEFT_FORGE "_Shire_live_i_left_forge"
#define IS_WEAPON(x) (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x) (function_exists("create_object", x) == "/std/armour")
#define FORGING "_live_o_forge_"

void
create_forge_room()
{
  set_short("A special forge");
  set_long("This is a special forge that has been set "+
	   "aside for those who have the special skills needed "+
	   "to use. The heavy forge in the center of the room "+
	   "is full of brightly-glowing coals. It is quite a "+
	   "sight to see. There is a sign posted on the far "+
	   "wall. The bellows are ready and waiting for a nice "+
	   "strong hand.\n");
  
  add_item(({"forge"}),
	   "The heavy forge in the center of the room is full of " +
	   "brightly-glowing coals.\n");
  add_item(({"coals", "brightly-glowing coals"}),
	   "Within the stone forge in the center of the room, a " +
	   "pile of coals glow brightly, hot enough to soften " +
	   "steel for working.\n");
  add_item(({"anvil", "heavy anvil", "iron anvil"}),
	   "A heavy, iron anvil stands near the forge, where countless " +
	   "iron tools and weapons have been hammered out.\n");
  add_item(({"bin", "large bin", "bin of stock metal"}),
	   "The large bin contains piles of iron, both scrap and " +
	   "raw ingots, to be used for the forging of new blades.\n");
  add_item(({"iron", "piles of iron"}),
	   "There's two distinct different piles of iron in the bin, " +
	   "one appears to be pure, raw ingots of iron, the other " +
	   "contains shreds of scrap iron left over from projects, or " +
	   "from items that broke and couldn't be repaired.\n");
  add_item(({"ingots", "pile of ingots"}),
	   "Regular-shaped blocks of pure iron, the ingots get used " +
	   "in the blades of finer-quality weapons.\n");
  add_item(({"scrap iron", "pile of scrap iron"}),
	   "The scrap iron pile is somewhat larger than the one with " +
	   "the iron ingots, and full of pretty much what you'd " +
	   "expect in a scrap heap, nothing useful.\n");
  add_item(({"barrels"}),
	   "The barrels contain a couple different liquids, presumably " +
	   "for quenching blades off the forge. One barrel holds " +
	   "fresh water, the other some sort of oil, but neither " +
	   "strike you as all that interesting.\n");
  add_item(({"floor", "ground"}),
	   "The floor of forge is hard-packed dirt, and pock-marked " +
	   "where bits of hot iron landed.\n");
  add_item(({"walls", "wall"}),
	   "The walls of the smithy are made from various sized " +
	   "pieces of hard grey stone, carefully placed together " +
	   "and packed with clay.\n");
  add_item(({"roof", "ceiling"}),
	   "The ceiling of the forge is also made of stone, somehow " +
	   "cunningly placed and mortared in place, so no wood was " +
	   "used in the construction of the building, reportedly a " +
	   "building technique known only to the masters of the " +
	   "different smithy crafthalls.\n");
  add_item(({"sign"}),
	   "It is a piece of brass, hammered thing with some writing " +
	   "engraved on its surface. At the top of the sign, it reads "+
	   "'The Forge of Hammerhands'.\n");
  add_exit("train", "northeast", "@@check_forging@@");
  
}

public void
leave_inv(object obj, object to)
{
  object tools;
  
  ::leave_inv(obj, to);
  
  if (tools = present("smiths_forging_tools", obj))
    {
      write("You remember to drop the forging tools.\n");
      tell_room(TO, QCTNAME(obj)+" drops a "+tools->short()+".\n",obj);
      tools->move(TO);
      TP->add_fatigue(-100);
      
    }
  
  if (TP->query_prop(LIVE_I_BLACKENING))
    {
      write("You remove your weapon from the forge.\n");
      TP->remove_prop(LIVE_I_BLACKENING);
    }
}

string read_sign()
{
  return "On the brass sign you see enscribed:\n\n" +
    
    "      +--------------------------------------------------------------+\n"+
    "      |  o   o                                                o   o  |\n"+
    "      |    o                                                    o    |\n"+
    "      |                                                              |\n"+
    "      |                The Special Forge of Hammerhands              |\n"+
    "      |                     --========oo=========--                  |\n"+
    "      |                                                              |\n"+
    "      |   Forging weapons and armours successfully requires great    |\n"+
    "      |   skill. It is also tiring work and takes much out of the    |\n"+
    "      |   strongest person. Remember this as you will become quite   |\n"+
    "      |   thirsty, hungry, and tired.                                |\n"+
    "      |                                                              |\n"+
    "      |   Smithing specialists may forge the following items.        |\n"+
    "      |                                                              |\n"+
    "      |     Armours                  Weapons                         |\n"+
    "      |   =========================================================  |\n"+
    "      |     - Boots                  - Bastard Sword                 |\n"+
    "      |     - Bracers                - Battle Axe                    |\n"+
    "      |     - Platemail Bracers      - Claymore                      |\n"+
    "      |     - Scalemail Bracers      - Dirk                          |\n"+
    "      |     - Breastplate            - Halberd                       |\n"+
    "      |     - Chainmail              - Iron Waraxe                   |\n"+
    "      |     - Greaves                - Knife                         |\n"+
    "      |     - Platemail Greaves      - Longsword                     |\n"+
    "      |     - Scalemail Greaves      - Quarterstaff                  |\n"+
    "      |     - Helm                   - Short Axe                     |\n"+
    "      |     - Great Helm             - Shortsword                    |\n"+
    "      |     - Plate Helm             - Spiked Club                   |\n"+
    "      |     - Platemail              - Stiletto                      |\n"+
    "      |     - Ribbed Platemail       - Warhammer                     |\n"+
    "      |     - Ringmail                                               |\n"+
    "      |                                                              |\n"+
    "      |                                                              |\n"+
    "      |   Visitors may assist  by pumping the bellows.               |\n"+
    "      |   This is done by 'smpump bellow'.                           |\n"+
    "      |                                                              |\n"+
    "      |    o                                                   o     |\n"+
    "      |  o   o                                               o   o   |\n"+
    "      +--------------------------------------------------------------+\n\n";
}
