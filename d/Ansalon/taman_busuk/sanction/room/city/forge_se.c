/*

   Sanction Southeast Forge Room

 */
 
#pragma strict_types;
#pragma save_binary;

inherit "/d/Ansalon/std/room";
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
    set_short("The southeast smith forge");
    set_long("This is the southeast forge in Sanction. " +
        "Smiths are allowed to force many items here. " +
        "Forging tools are available for " +
        "anyone with the skills to forge. A brass sign hangs on " +
        "one wall.\n");

    set_room_tell_time(300);
    add_room_tell("An apprentice smith comes and stocks the " +
        "forge with more coal.");
    add_room_tell("An apprentice smith empties the barrels full " +
        "of dirty water and refills them with water from the " +
        "large barrel.");
    add_room_tell("An apprentice checks the water level in the " +
        "large barrel.");
    add_room_tell("As it begins to rain outside, the rainwater " +
        "begins to fill the large barrel. Soon the rain stops.");

    add_exit("/d/Ansalon/taman_busuk/sanction/room/city/yard","northwest","@@check_forging@@");
    add_prop("_forge_i_ansalon", 1);

    clone_object("/d/Shire/guild/smiths/obj/sm_leath")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/sm_leath")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/sm_leath")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/sm_leath")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/ir_bar")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/ir_bar")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/ir_bar")->move(TO,1);
    clone_object("/d/Shire/guild/smiths/obj/ir_bar")->move(TO,1);
}

