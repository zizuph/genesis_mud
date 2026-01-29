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
#include <composite.h>
#include <filter_funs.h>


#define LIVE_I_BLACKENING "_live_i_blackening"
#define LEFT_FORGE        "_Shire_live_i_left_forge"
#define IS_WEAPON(x)      (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x)      (function_exists("create_object", x) == "/std/armour")
#define FORGING           "_live_o_forge_"
#define FORGE_NE          SMITHSDIR_ROOMS + "test_forge"
#define FORGE_E           SMITHSDIR_ROOMS + "test2"


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
    add_cmd_item("forges", "check", "@@forge_check@@");

    add_exit(SMITHSDIR_ROOMS+"forge_entr","west","@@check_forging@@");
    

}

void init() 
{
    ::init();
    add_action("fshout", "fshout");
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


string
forge_check()
{
    object other_room;
    mixed opeople;
 
    write("You look up from your work and glance around and see " +
        "the following:\n\n");

    say(QCTNAME(TP)+" looks up from "+HIS_HER(TP)+" work and " +
        "glances around.\n");
 
    
    write("                                Forge Occupants\n");
    write("======================================================"+
            "========================\n\n");
 
 // check forge_ne
    if (!LOAD_ERR(FORGE_NE))
        other_room = find_object(FORGE_NE);
    else
        write("\tNortheast Forge: The forge is hazy. There could " +
            "be a problem with it. Please contact a shire wizard " +
            "or 'mail shire'.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\tNortheast Forge: Deserted and quiet.\n");
    else
        write("\tNortheast Forge: "+COMPOSITE_LIVE(opeople)+"\n");

 
 // check forge_e
    if (!LOAD_ERR(FORGE_E))
        other_room = find_object(FORGE_E);
    else
        write("\t     East Forge: The forge is hazy. There could " +
            "be a problem with it. Please contact a shire wizard " +
            "or 'mail shire'.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\t     East Forge: Deserted and quiet.\n");
    else
        write("\t     East Forge: "+COMPOSITE_LIVE(opeople)+"\n");


    write("\n======================================================"+
            "========================\n\n");

return "";
}


int fshout(string say_what)
{
    mixed tmp;
    int    size;

        if (!strlen(say_what))
    {
        notify_fail("Shout what?\n");
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot shout.\n");
        return 1;
    }
 
    if ((strlen(say_what) > 60) &&
        (!this_player()->query_wiz_level()) &&
        (!this_player()->query_npc()))
    {
        notify_fail("Even your mouth is not big enough to shout all that.\n");
        return 0;
    }
 
    TP->catch_msg("You shout to the forges: "+say_what+"\n");
    tell_room(FORGE_NE,QCTNAME(TP)+" shouts from "+HIS_HER(TP)+ " forge: "+say_what+"\n");
    tell_room(FORGE_E,QCTNAME(TP)+" shouts from "+HIS_HER(TP)+ " forge: "+say_what+"\n");
    return 1;
}

