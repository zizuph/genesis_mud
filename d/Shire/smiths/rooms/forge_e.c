/*
 * road in Esgaroth
 * By Finwe, March 2001
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
    set_short("The east forge of the Smiths Guild");
    set_long("This is the east forge of the Smiths guild. It " +
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

    add_exit(SMITHSDIR_ROOMS+"forge_entr","west","@@check_forging@@");
    

}

public void
init()
{
   ::init();
   add_action(do_check,   "smcheck"); 

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
        tools->move("/d/Shire/smiths/rooms/forge_e");
        TP->add_fatigue(-100);

    }

    if (TP->query_prop(LIVE_I_BLACKENING))
    {
        write("You remove your weapon from the forge.\n");
        TP->remove_prop(LIVE_I_BLACKENING);
    }
}
