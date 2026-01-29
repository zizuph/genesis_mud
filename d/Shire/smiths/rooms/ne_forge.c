/*
 * Test forge for Smiths
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

object door;

void
create_forge_room()
{
    set_short("The northeast forge of the Smiths Guild");
    set_long("This is the northeast forge of the Smiths guild. It " +
        "is the pride of the Guild, allowing Smiths to forge many " +
        "items. The forge burns hot, so windows are open to allow " +
        "fresh air to blow through. Forging tools are available for " +
        "anyone with the skills to forge. A brass sign hangs on " +
        "one wall.\nA brass sign.\n");
    add_exit(SMITHSDIR_ROOMS+"test_entr","southwest","@@check_forging@@");

    door = clone_object(SMITHSDIR_OBJ + "forge_ne_out");
    door -> move(this_object());
   
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
        tools->move("/d/Shire/smiths/rooms/forge_ne");
        TP->add_fatigue(-100);

    }

    if (TP->query_prop(LIVE_I_BLACKENING))
    {
        write("You remove your weapon from the forge.\n");
        TP->remove_prop(LIVE_I_BLACKENING);
    }
}
