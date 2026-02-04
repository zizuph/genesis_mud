#include "../guild.h"

#include <std.h>
#include <macros.h>
#include <files.h>

#define GENESIS_TIMEKEEPER  "/d/Sparkle/area/city/lib/genesis_timekeeper"

int sun(string str)
{
    string s, tmp, path;
    object room, env = environment(this_player());
    int i;

    if (strlen(str))
    {
	if (strlen(tmp = SECURITY->modify_command(str, env)))
	{
	    str = tmp;
	}
      
	if ((i = member_array(str, env->query_exit_cmds())) < 0)
	{
            notify_fail("You can't seem to find that direction.\n");
	    return 0;
        }

        path = env->query_exit_rooms()[i];
        if (!(room = find_object(path)))
        {
            catch(call_other(path, "??"));
            if (!(room = find_object(path)))
            {
                write("You can't seem to detect anything in that " +
                    "direction.\n");
                return 1;
	    }
        }
    }
    else if ((MASTER_OB(env) == ROOM_DIR+"meld_cont") 
            && (room = environment(env)))
    {
        write("You try to detect sunlight above-ground.\n");
    }

    if (!room)
    {
        room = env;
    }

    if (strlen(s = this_player()->light_desc(room)))
    {
        write(s);
    }
                
    if (strlen(s = this_player()->sunlight_desc(room)))
    {
        write(s);
    }

    return 1;
}

public int
detect_dawn(string str)
{
    setuid();
    seteuid(getuid());
    
    object player = this_player();
    if (!objectp(player))
    {
        return 0;
    }
    
    object room = environment(player);
    if (!objectp(room) || !IS_ROOM_OBJECT(room))
    {
        return 0;
    }
    
    if (room->query_prop(ROOM_I_INSIDE))
    {
        // An inside room never has sunlight.
        notify_fail("You cannot detect anything without a clear view "
            + "of the sky.\n");            
        return 0;
    }
    
    mixed * time_info = GENESIS_TIMEKEEPER->query_time(player);
    if (!pointerp(time_info))
    {
        notify_fail("For some reason, you simply cannot detect anything "
            + "from where you stand.\n");
        return 0;
    }
    
    string domain = lower_case(room->query_domain());
    int hour = time_info[0];
    if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
    {
        player->catch_tell("\nThe Sun has come! Flee, creature of the night, "
            + "flee!\n\n");
        return 1;
    }
    
    // If it is night, we detect how many hours there are till day comes.
    int hours_until_dawn = 1;
    hour = (hour + 1) % 24;
    for (int i = 0; i < 24; ++i)
    {
        if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
        {
            break;
        }
        
        ++hours_until_dawn;
        hour = (hour + 1) % 24;
    }
    
    string mesg = "You look up into the sky and focus to determine the "
        + "coming of dawn. Your senses tell you:\n\n";
    switch (hours_until_dawn)
    {
    case 1:
        mesg += "    The night is all but spent! Dawn approaches with terrible "
            + "speed!\n";
        break;
        
    case 2..4:
        mesg += "    The night has begun to pass. Dawn approaches, albeit slowly.\n";
        break;
    
    case 5..8:
        mesg += "    The night remains strong, and dawn is but a distant "
            + "threat.\n";
        break;

    default:
        mesg += "    The night is strong, and dawn has not yet begun to "
            + "approach.\n";
        break;
    }
    
    player->catch_tell(mesg);
    return 1;    
}
