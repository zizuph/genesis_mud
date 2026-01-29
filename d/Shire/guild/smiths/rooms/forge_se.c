/*

   Bree's SouthEast Forge Room

   14 July 2006 - Palmer
     Removed un-necessary smcheck function in init and code to drop
     tools when leaving (moved to base_forge_room.c).

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
    set_short("The southeast forge of the Smiths Guild");
    set_long("This is the southeast forge of the Smiths guild. It " +
        "is the pride of the Guild, allowing Smiths to forge many " +
        "items. The forge burns hot, so windows are open to allow " +
        "fresh air to blow through. Forging tools are available for " +
        "anyone with the skills to forge. A brass sign hangs on " +
        "one wall.\nA brass sign.\n");

    set_room_tell_time(300);
    add_room_tell("A cool breeze blows in the door, cooling " +
        "the room slightly.");
    add_room_tell("An apprentice smith comes and stocks the " +
        "forge with more coal.");
    add_room_tell("Some raucous sounds float in from the windows.");
    add_room_tell("The sound of a creaking cart rolls by " +
        "outside the window.");
    add_room_tell("An apprentice smith empties the barrels full " +
        "of dirty water and refills them with water from the " +
        "large barrel.");
    add_room_tell("An apprentice checks the water level in the " +
        "large barrel.");
    add_room_tell("As it begins to rain outside, the rainwater " +
        "begins to fill the large barrel. Soon the rain stops.");

    add_exit(SMITHSDIR_ROOMS+"forge_entr","northwest","@@check_forging@@");

    add_prop("_forge_i_shire", 1);
}

