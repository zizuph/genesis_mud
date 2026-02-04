/* manager.c created by Shiva@Genesis.
 * This file takes care of the logs and a few miscellanea
 * for the vampire guild.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include "../voptions.h"
#include <std.h>

inherit LIB_DIR+"manager";

#define OLD_MANAGER "/d/Emerald/common/guild/vamp/log/manager"

#define GUILD_MAP_TITLES        "guild_titles"
#define GUILD_MAP_PTITLES_SHOWN "ptitles_shown"
#define GUILD_MAP_MAX_LEVEL     "max_level"

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

#define OFFSET_UPDATE_INTERVAL (30 * 60)



/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    ::create_data_manager();    
    set_save_dir(DATA_DIR + "bg/");
    set_garbage_dir(DATA_DIR + "bg/old/");
} /* create_data_manager */


int
set_master(mixed who1, mixed who2)
{
    if (!(who2 = get_name(who2)))
    {
        return 0;
    }
    return set_info(who1, "master", who2);
}

int
remove_master(mixed who)
{
    return remove_info(who, "master");
}

string
query_master(mixed who)
{
    return get_info(who, "master");
}


int
add_member(mixed who)
{
    int result=::add_member(who);
    
    if (result)
    {
        set_options(who,VOPT_NOTIFY_THIRST);
    }
    return result;
}