#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h" 
//#include "/d/Shire/greyhavens/local.h"

inherit "/lib/guild_support";
inherit "/d/Shire/std/room";

void
create_shire_room()
{
    set_short("A meditation room");
    set_long("This is where you may meditate.\n");


    create_guild_support();

    add_exit(SINDAR_RACE_DIR + "train", "south");
    add_exit(SINDAR_RACE_DIR + "board_rm", "east");
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
    write("Pausing, you sit down and begin vegitating. Soon, you become " +
        "completely free of tension and stress in this state of " +
        "relaxation and feel yourself able to \"estimate\" your " +
        "different preferences for concentration and \"set\" " +
        "them to new values if desired. To return to the world, " +
        "all you have to do is \"rise\".\n");
    say(QCTNAME(this_player()) + " sits down and begins " +
        "vegitating.\n");

}

/*
* Function name: gs_hook_rise
* Description  : Gives a nice description when someone is done meditating.
*/
nomask public void
gs_hook_rise()
{
    write("Having purified your mind and you feel relaxed and " +
        "ready to continue on. You stand up.\n");
    say("Looking quite relaxed indeed, " + QTNAME(this_player()) + 
        " breaks " + HIS_HER(TP) + " vegitating and stands up.\n");
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
   write("That is not possilbe to do while you are meditating.\n");
   return 1;
}



int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}
