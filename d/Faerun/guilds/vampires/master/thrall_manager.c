/* thrall_manager.c created by Novo
 * This file takes care of the sires.
 */
inherit "/d/Faerun/guilds/vampires/master/data_manager";
#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "../guild.h"
#include <std.h>



#define MEMBER_FILE(who)    save_dir + who
#define DATA_DIR            "/d/Faerun/guilds/vampires/master/log/"


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    ::create_data_manager();    
    
    set_save_dir(DATA_DIR + "thrall/");
    set_garbage_dir(DATA_DIR + "thrall/old/");
} /* create_data_manager */

string save_dir;

public void
set_save_dir(string dir)
{
    save_dir=dir;
    ::set_save_dir(dir);
}


string
get_name(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }
  
    return lower_case(who);
}


string member_name_from_member_file(string file)
{
    string name;

    if (!sscanf(file, "%s.o", name))
    {
        return 0;
    }

    if (!SECURITY->exist_player(name))
    {
        return 0;
    }

    return name;
}


int
set_thrall(mixed who1, mixed who2)
{
    return set_info(who1, "thrall", who2);
}


int
remove_thrall(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
        
    }
    
    return delete_data(lower_case(who));
}


string
query_thrall(mixed who)
{
    return get_info(who, "thrall");
}
