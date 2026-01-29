/*
 * Terel forge, Based on the VK Forge
 * By Boron, based on Finwe's forge: Finwe, March 2001
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";
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
    set_short("A smithy");
    set_long("The smithy is hot, with a forge set in the center of the room. Windows are open and allow fresh air to cool the smithy. There are some forging tools set next to the forge and available for anyone skilled in the art. Some barrels are scattered around the room. A brass sign hangs on the wall.\nA brass sign.\n");
    add_exit("path","direction","@@check_forging@@");

// add more room tells if you like, in this format:
    add_room_tell("Fresh air blows in through the windows.");

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
"      |                     The Armoury of Solamnia                  |\n"+
"      |                     --========oo=========--                  |\n"+
"      |                                                              |\n"+
"      |   Forging weapons and armours successfully requires great    |\n"+
"      |   skill. It is also tiring work and takes much out of the    |\n"+
"      |   strongest person. Remember this as you will become quite   |\n"+
"      |   thirsty, hungry, and tired.                                |\n"+
"      |                                                              |\n"+
"      |   Armoury masters may forge the following items.             |\n"+
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