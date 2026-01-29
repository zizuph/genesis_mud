/*
 * Meditation room in Noldor Guild
 * By Finwe, August 2000
 */
 
#pragma strict_types

#include "noldor.h" 
#include "/d/Shire/rivendell/local.h"

inherit "/lib/guild_support";
inherit BUILDING_BASE;

object meditate; 

void
create_guild_room()
{
    set_short("A meditation room");
    set_long("This quiet room is where Noldor come to meditate " +
        "and refocus their mind. Lamps and @@daylight_desc@@ " +
        "flowing in from the windows fills the room with light. " +
        "Crystals of all sizes and cuts are scattered about the room.\n");

    set_extra_wall(" Large windows are set into the south and " +
        "west walls, filling the room with @@daylight_desc@@.\n");

    set_extra_window("The windows are set into the north " +
	    "and west walls.");
    add_item(({"west window", "western window"}),
         "A winding path leads southwest towards the house.\n");
    add_item(({"north window", "northern window"}),
         "The valley spreads out to the north here.\n");
    add_item(({"crystals"}),
        "The crystals are all sizes and colours. Some are so large " +
        "they are set in stands while others lay on the ground. " +
        "They are expertly cut and catch the room's light. The " +
        "captured light give the crystals an ethereal glow.\n");
    add_item(({"stands", "crystal stands"}),
        "The crystal stands are various heights. Some are plain and " +
        "others are intricately carved. The stands are made " +
        "from mithril and gold. They hold the larger crystals in " +
        "the room.\n");
    add_cmd_item( ({"crystals", "crystal"}), ({"take", "get"}), 
        "The crystals are too precious to be taken.\n");

    create_guild_support();

    add_exit(NOLGLD_DIR + "train", "south");
    add_exit(NOLGLD_DIR + "board_rm", "east");
}
 

void
init()
{
   ::init();
   
   init_guild_support();

}


/*
* Function name: leave_inv
* Description  : Called to remove the guild support if it is stuck.
* Arguments    : object obj - the leaving object.
*                object to  - the new destination of the object.
*/
nomask public void leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
   
    gs_leave_inv(obj, to);
}

/*
* Function name: gs_hook_start_meditate
* Description  : Gives a nice description when someone starts to meditate.
*/
nomask public void
gs_hook_start_meditate()
{
    write("Pausing, you sit down and begin meditating while " +
        "admiring an exquisitely cut crystal. It is a thing of " +
        "beauty to behold " +
        "as it was cut by expert hands. Your mind clears as " +
        "your surroundings seem to melt away. Soon, you become " +
        "completely free of tension and stress in this state of " +
        "relaxation and feel yourself able to \"estimate\" your " +
        "different preferences for concentration and \"set\" " +
        "them to new values if desired. To return to the world, " +
        "all you have to do is \"rise\".\n");
    say(QCTNAME(this_player()) + " sits down and begins " +
        "admiring an excusitely cut crystal.\n");

}

/*
* Function name: gs_hook_rise
* Description  : Gives a nice description when someone is done meditating.
*/
nomask public void
gs_hook_rise()
{
    write("Having purified your mind and you feel relaxed and " +
        "ready to continue. You break your gaze from the crystal " +
        "and stand up.\n");
    say("Looking quite relaxed indeed, " + QTNAME(this_player()) + 
        " breaks " + HIS_HER(TP) + " gaze from the crystal and stands up.\n");
}

/*
* Function name: gs_hook_already_meditate
* Description  : Gives a nice message when someone tries to meditate
*                when (s)he is already mediating.
*/
nomask public int
gs_hook_already_meditate()
{
    write("It is not possible to come to become more relaxed in " +
        "this current state. Since you are already meditating, " +
        "you can now \"estimate\" your different preferences " +
        "for concentration and \"set\" them to new values. When " +
        "you are finished, just \"rise\" to return to the world " +
        "around you.\n");
   return 1;
}

/*
* Function name: gs_hook_catch_error
* Description  : Gives a friendly error message when someone gives the
*                wrong command while meditating.
*/
nomask public int
gs_hook_catch_error(string str)
{
   write("That is not possible while you are meditating.\n");
   return 1;
}



int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}
