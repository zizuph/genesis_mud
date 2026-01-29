/* Fort Sybarus Forge 
 * Lilith Apr 2022
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/guild/smiths/rooms/base_forge_room";
inherit "/d/Shire/std/room/room_tell";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"
#include "/d/Avenir/include/macros.h"

#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define OUTPOST           "/d/Avenir/common/outpost/"
#define FORGING           "_live_o_forge_"
#define LEFT_FORGE        "_Shire_live_i_left_forge"
#define LIVE_I_BLACKENING "_live_i_blackening"
//#define SEE_EAST          ({ OUTPOST +"foundry" })

#define IS_WEAPON(x) (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x) (function_exists("create_object", x) == "/std/armour")

/*
string east_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_EAST); i++)
    if((room = find_object(SEE_EAST[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return ", where you can see "+ COMPOSITE_LIVE(live) + 
       " standing there";
  }
  return "";
}
*/

void
create_forge_room()
{
    set_short("the forge at Fort Sybarus");
    set_long("This is the forge at Fort Sybarus, where Smiths "+
	    "may pursue their art. "+
        "Steam rises up everywhere in this room, and the "+
        "heat is almost unbearable. "+
        "There is a yellowish-orange glow coming from an opening in "+
        "the wall to the south, where it looks like magma is "+
        "being used to heat the forge. "+		
        "There is a contraption made of chains and buckets "+
		"connecting with the weaponsmith above. "+ 
		"Near it, a ladder leans against the north wall. "+
        "An opening in the east wall provides access "+
        "to the foundry. "+
        "Words have been carved into the stone of "+
        "the east wall, just above the bellows.\n");
    add_item(({"contraption", "buckets", "chains", "lift", 
	    "bucket lift", "bucket-lift"}),
        "This is a bucket-lift, a contraption designed to lift "+
        "and lower metals and ores between the foundry and "+
        "forges below and those up above.\n");
    add_item("bellows", "The bellows consists of a flexible, "+
        "valved bladder that is contracted and expanded "+
        "by pumping to force the air through a nozzle. It is "+
        "used to increase the draft to the fires of the forge.\n");
    add_item(({"ladder","wooden ladder"}),"A ladder made of "+
        "wood is attached to the wall. It leads up.\n");
    add_item(({"cave","cavern","room","chamber","forge",
        "wall","walls"}),"The walls of the cavern are rough "+
        "and irregular, almost making them seem naturally "+
        "formed. The southern wall glows with a hot, red light.\n");
    add_item(({"glow","light","south wall","southern wall"}),
        "The south wall glows molten red, as if there were "+
        "a mass of lava just behind or below it. The heat "+
        "from the wall makes the room unbearably hot.\n");
    add_cmd_item(({"wall","rock","stone","molten rock"}),
        ({"touch","feel"}), "The rock is burning hot, almost "+
        "to the point of melting.\n");
    add_item(({"words", "wall", "sign"}), "@@read_sign@@"); 
    add_cmd_item(({"words", "wall", "sigh"}), "read", "@@read_sign@@"); 

    add_exit("smithy",   "up",  "@@check_forging@@");
//    add_exit("foundry", "east","@@check_forging@@", 2, 1);
  
	// no flux messages, room inside, no steeds
    IN_IN   
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
    }

    if (TP->query_prop(LIVE_I_BLACKENING))
    {
        write("You remove your weapon from the forge.\n");
        TP->remove_prop(LIVE_I_BLACKENING);
    }
}

string read_sign()
{
return "Carved into the west wall you see the following words:\n\n" +
"      +--------------------------------------------------------------+\n"+
"      |    (O)                                                (O)    |\n"+
"      |   (O)O)                                              (O)O)   |\n"+
"      |                                                              |\n"+
"      |                                                              |\n"+
"      |                 The Forge at Fort Sybarus                    |\n"+
"      |                 --=====================--                    |\n"+
"      |                                                              |\n"+
"      |   Forging weapons and armours successfully requires great    |\n"+
"      |   skill. It is also tiring work and takes much out of the    |\n"+
"      |   strongest person. Remember this as you will become quite   |\n"+
"      |   thirsty, hungry, and tired.                                |\n"+
"      |                                                              |\n"+
"      |   Smiths may forge the following items:                      |\n\n"+
"      |     General Equipment                                        |\n"+
"      |   =========================================================  |\n"+
"      |     - Horsehoes (set of four)                                |\n"+
"      |     - Megaphone                                              |\n"+
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
"      |     - Shield                                                 |\n"+
"      |     - Grand Tower Shield                                     |\n"+
"      |                                                              |\n"+
"      |                                                              |\n"+
"      |         Visitors may assist by pumping the bellows.          |\n"+
"      |            This is done using 'smpump bellow'.               |\n"+
"      |                                                              |\n"+
"      |                                                              |\n"+
"      |    (O)                                                (O)    |\n"+
"      |   (O)O)                                              (O)O)   |\n"+
"      |                                                              |\n"+
"      +--------------------------------------------------------------+\n\n";
}



