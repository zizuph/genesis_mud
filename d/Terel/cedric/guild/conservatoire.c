#pragma save_binary

inherit "/lib/guild_support"; 
inherit "/std/room";

#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: Conservatoire
 * A music room where players can <compose> 
 * themselves(read meditate).
 * Jorl 3/93
 */

int
check_enter()
{
    if ( 1 /* !BLACKLIST(TP()) */)
    {
	return 0;
    }
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

create_room()
{
    create_guild_support();
    
    set_short("The Conservatoire of the Minstrels");
    set_long(BS("This conservatoire is a place to relax and reflect upon "
    + "your adventures.  Perhaps as you rest here, listening to the tick "
    + "of the metronome, you could compose yourself...\n"));
    
    add_item("metronome", BS("TICK...TICK...TICK...TICK\nThe rhythmic sound "
    + "of the metronome is incredibly soothing.\n"));
    
    add_exit(GUILD+"dorm", "north", "@@check_enter");
   add_exit("/d/Terel/guilds/minstrels/room/workshop", "south", "@@check_enter");
    add_exit(GUILD+"tower_mundane", "southwest");
    
    add_prop(ROOM_I_INSIDE, 1);
}

init()
{
    init_guild_support();
    add_action("no_meditate", "meditate");
    add_action("do_compose", "compose");
    ::init();
}

int
no_meditate()
{
    TP()->catch_msg("If you wish to compose yourself then simply say so.\n");
    return 1;
}

int
do_compose(string str)
{
    notify_fail("Compose yourself, perhaps?\n");
    if (!str)
    return 0;
	
    if (member_array(str, ({"me", "self", "myself", 
    TP()->query_real_name()}))!= -1)
    {
        gs_meditate(str);
	return 1;
    }
    
}

void
gs_hook_start_meditate()
{
    write(BS("\n"+"You choose a comfortable-looking chair to recline upon.  "
    + "A novice minstrel hands you a glass of warm goat's milk to relax "
    + "you and settle your stomach. As you listen to the tick of the "
    + "metronome you feel yourself drift inward. Soon you are able to "
    + "<estimate> your different preferences and <set> them at your own "
    + "desire.\n"+"Just <rise> when you are done composing your mind.\n"));
    say (QCTNAME(TP()) + " sits down in an overstuffed chair and starts "
    + "to compose their mind.\n");
}

void
gs_hook_rise()
{
    write(BS("Your consciousness returns slowly.  You stand, feeling refreshed, "
    + "relaxed, and more confident about yourself.\n"));
    say(QCTNAME(TP()) +" rises from the comfortable chair.\n");
}
