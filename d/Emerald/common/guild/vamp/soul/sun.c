#include "../guild.h"

#include <std.h>
#include <macros.h>

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
    else if ((MASTER_OB(env) == MELD_CONT) && (room = environment(env)))
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
