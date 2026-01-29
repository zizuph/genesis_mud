/* An example door made by Nick, 1991-12-19 */
/* used by Olorin to make door for          */
/* /d/Gondor/rohan/farm/road/yard1.c        */
/* Dec-1992                                 */

inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

create_door() 
{
    ::create_door();
    /* You need an id, and both sides should have the same id               */
    set_door_id("farm_stable_trapdoor");

    set_pass_command(({"d","down"}));

    set_door_name(({"trap door","hatch","door","trapdoor"}));
    set_door_desc("A simple plank covering a hole in the floor. The " +
        "plank looks quite heavy.\n");

    set_other_room(FARM_DIR + "farm/cellar");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(1);       /* 1 if locked, 0 if unlocked */
    set_key("Stable_Trapdoor_Key");
}

int
open_door(string arg)
{
    int strength;
    strength = TP->query_stat(SS_STR);

    if( arg != "trap door" && arg != "hatch" && 
        arg != "door" && arg != "trapdoor")
    {
        return 0;
    }

    if(strength < 50)
    {
	    write("The large plank is too heavy.\n");
	    say(QCTNAME(TP) + " tries to lift the heavy plank to open the " +
            "trapdoor, but fails.\n");
	    return 1;
    }

    return ::open_door(arg);
}
