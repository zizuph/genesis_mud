/*
 * Vingard Keep forge
 * By Boron, based on Finwe's forge: Finwe, March 2001
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";
inherit "/d/Shire/guild/smiths/rooms/base_forge_room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"
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
    set_short("The Armoury Workshop");
    set_long("This is the workshop of solamnian armoury masters. " +
        "The forge burns hot, so windows are open to allow " +
        "fresh air to blow through. Forging tools are available for " +
        "anyone with the skills to forge. A brass sign hangs on " +
        "one wall.\nA brass sign.\n");
    add_exit("/d/Krynn/guilds/knights/guildhall/rooms/forge","east","@@check_forging@@");


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
"      |     - Shield                                                 |\n"+
"      |                                                              |\n"+
"      |   Visitors may assist  by pumping the bellows.               |\n"+
"      |   This is done by 'smpump bellow'.                           |\n"+
"      |                                                              |\n"+
"      |    o                                                   o     |\n"+
"      |  o   o                                               o   o   |\n"+
"      +--------------------------------------------------------------+\n\n";
}
