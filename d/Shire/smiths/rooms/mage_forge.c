/* Forge for Mages in the Dark Tower
 * Finwe, November 2004
 * Union forge already in existence, and 
 * Vingard Keep forge
 * By Boron, based on Finwe's forge: Finwe, March 2001
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";
inherit "/d/Shire/smiths/rooms/base_forge_room";
inherit "/d/Shire/std/room/room_tell";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
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
#define SEE_UP          ({ "/d/Gondor/morgul/city/darkstr0" })

#define IS_WEAPON(x) (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x) (function_exists("create_object", x) == "/std/armour")

string up_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_UP); i++)
    if((room = find_object(SEE_UP[i])) && CAN_SEE_IN_A_ROOM(TP, room))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "Looking through the grate above, you see " + 
        COMPOSITE_LIVE(live) + ".\n";
  }
  return "You look through the grate, but see nothing special.\n";
}


void
create_forge_room()
{
    set_short("The Forge of Minas Morgul");
    set_long("This is a dark forge underneath the city of Minas Morgul. " +
		"A grate in the ceiling allows the smoke and the heat of the large " +
		"forge to escape. The black stone walls are smooth but for the " +
		"writing on the northern wall and the occasional burn marks of " +
		"the fire.\n");

	add_item( ({ "walls", "black stone walls", "black walls" }),
		"The walls are smooth but for the words on the northern wall.\n" );
	add_item( ({ "black stone", "stone" }), "The walls are made of very " +
		"smooth black stone, and are covered with burn marks of the fire. " +
		"There are some words on the northern wall.\n");
	add_item( "ceiling", "A grate is set in it to allow smoke and heat to " +
		"escape.\n");
	add_item( ({ "occasional burn marks", "marks", "burn marks" }),
		"Occasionally the fire of the forge leaps high, leaving marks on " +
		"the already black walls.\n" );
	add_item(({"iron grate", "grate"}),up_view);
    add_item(({"words", "wall", "north wall"}), "@@read_sign@@"); 
    add_cmd_item(({"words", "wall", "north wall"}), "read", "@@read_sign@@"); 

    add_exit("/d/Gondor/morgul/city/forge/forge_supplies", "east","@@check_forging@@", 2);
    set_room_tell_time(300);
    add_room_tell("An acrid smoke rises up from the forge.");
        add_room_tell("A cool breeze blows in the door, cooling " +
        "the room slightly.");
	add_room_tell("A grumpy black orc comes and stocks the " +
        "forge with more coal.");
    add_room_tell("A grumpy black orc empties the barrels full " +
        "of dirty water and refills them with water from the " +
        "large barrel.");
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
"      |                 The Forge of Minas Morgul                    |\n"+
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
