/* Shadow forge for the Shadow Union
 * Lilith 23 May 2003
 * Modified from:
 * Union forge already in existence, and 
 * Vingard Keep forge
 * By Boron, based on Finwe's forge: Finwe, March 2001
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";
inherit "/d/Shire/guild/smiths/rooms/base_forge_room";
inherit "/d/Shire/std/room/room_tell";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"
#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define FORGING           "_live_o_forge_"
#define LEFT_FORGE        "_Shire_live_i_left_forge"
#define LIVE_I_BLACKENING "_live_i_blackening"
#define SEE_EAST          ({ "/d/Avenir/union/room/forge" })

#define IS_WEAPON(x) (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x) (function_exists("create_object", x) == "/std/armour")

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
       return " In the eastern side of the cavern you can see "
          + COMPOSITE_LIVE(live) + ".";
  }
  return "";
}


void
create_forge_room()
{
    set_short("the forge of shadow and flame");
    set_long("This is the forge of the Smiths of the Flame of Jazur. "+
        "Steam rises up everywhere in this room, and the "+
        "heat is almost unbearable. It is a circular cavern, "+
        "rough-hewn and irregular, with a high ceiling. "+
        "A broad staircase rises up into the north wall, "+
        "dividing this cavernous space into two areas, of which "+
        "you are currently in the western half.@@east_view@@ "+
        "A large, square chute has been cut into "+
        "the south wall, the base of which glows bright red, "+
        "as if the rock there were superheated to the point "+
        "of melting. Words have been carved into the stone of "+
        "the west wall, just above the bellows.\n");
    add_item("bellows", "The bellows consists of a flexible, "+
        "valved bladder that is contracted and expanded "+
        "by pumping to force the air through a nozzle. It is "+
        "used to increase the draft to the fires of the forge.\n");
    add_item(({"stair","staircase"}),"The stairs are broad, "+
        "made from thick granite and rising to the west, "+
        "where it disappears around a bend to the north.\n");
    add_item(({"cave","cavern","room","chamber","forge",
        "wall","walls"}),"The walls of the cavern are rough "+
        "and irregular, almost making them seem naturally "+
        "formed. The southern wall glows with a hot, red light.\n");
    add_item(({"glow","light","south wall","southern wall"}),
        "The south wall glows molten red, as if there were "+
        "a mass of lava just behind or below it. The heat "+
        "from the wall makes the entire cavern stifling "+
        "and unbearably hot.\n");
    add_cmd_item(({"wall","rock","stone","molten rock"}),
        ({"touch","feel"}), "The rock is burning hot, almost "+
        "to the point of melting.\n");
    add_item(({"words", "wall"}), "@@read_sign@@"); 
    add_cmd_item(({"words", "wall"}), "read", "@@read_sign@@"); 

    set_room_tell_time(300);
    add_room_tell("An apprentice smith comes and stocks the " +
        "forge with more coal.");
    add_room_tell("An apprentice smith empties the barrels full " +
        "of dirty water and refills them with water from the " +
        "large barrel.");
    add_room_tell("An apprentice checks the water level in the " +
        "large barrel.");

    add_exit("/d/Avenir/union/room/forge", "east","@@check_forging@@", 2, 1);
    add_exit("/d/Avenir/union/room/f_landing", "up", "@@check_forging@@", 2, 1);
    add_exit("/d/Avenir/union/room/f_landing", "north","@@check_forging@@", 2, 1);
    
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
return "Carved into the west wall you see the following words:\n\n" +
"      +--------------------------------------------------------------+\n"+
"      |    o                                                    o    |\n"+
"      |  o   o                                                o   o  |\n"+
"      |    o                                                    o    |\n"+
"      |                                                              |\n"+
"      |              The Forge of Shadows and Flame                  |\n"+
"      |                  --========oo=========--                     |\n"+
"      |                                                              |\n"+
"      |   Forging weapons and armours successfully requires great    |\n"+
"      |   skill. It is also tiring work and takes much out of the    |\n"+
"      |   strongest person. Remember this as you will become quite   |\n"+
"      |   thirsty, hungry, and tired.                                |\n"+
"      |                                                              |\n"+
"      |   Smiths may forge the following items:                      |\n"+
"      |                                                              |\n"+
"      |     Armours                  Weapons                         |\n"+
"      |   =========================================================  |\n"+
"      |     - Boots                  - Bastard Sword                 |\n"+
"      |     - Bracers                - Claymore                      |\n"+
"      |     - Platemail Bracers      - Dirk                          |\n"+
"      |     - Scalemail Bracers      - Knife                         |\n"+
"      |     - Breastplate            - Longsword                     |\n"+
"      |     - Chainmail              - Shortsword                    |\n"+
"      |     - Greaves                - Stiletto                      |\n"+
"      |     - Platemail Greaves                                      |\n"+
"      |     - Scalemail Greaves                                      |\n"+
"      |     - Helm                                                   |\n"+
"      |     - Great Helm                                             |\n"+
"      |     - Plate Helm                                             |\n"+
"      |     - Platemail                                              |\n"+
"      |     - Ribbed Platemail                                       |\n"+
"      |     - Ringmail                                               |\n"+
"      |                                                              |\n"+
"      |                                                              |\n"+
"      |         Visitors may assist by pumping the bellows.          |\n"+
"      |            This is done using 'smpump bellow'.               |\n"+
"      |                                                              |\n"+
"      |    o                                                   o     |\n"+
"      |  o   o                                               o   o   |\n"+
"      |    o                                                   o     |\n"+
"      +--------------------------------------------------------------+\n\n";
}
