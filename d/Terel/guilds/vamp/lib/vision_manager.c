
#include "../guild.h"

void
create()
{
    setuid();
    seteuid(getuid());
  
}

string
get_dir_name(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
  
    if (!stringp(who))
    {
        return 0;
    }
  
    return lower_case(who)+"/";
}

public int check_existing_dir(mixed who)
{
    int size=file_size(VISION_DIR+get_dir_name(who));
    
    if (size==-2)
    {
        return 1;
    }
    return mkdir(VISION_DIR+get_dir_name(who));
}

public string * get_all_visions(mixed who)
{
    if (!check_existing_dir(who))
    {
        return 0;
    }
    return get_dir(VISION_DIR+get_dir_name(who));
}

public int query_vision_exists(mixed who,string name)
{
    return (member_array(name,get_all_visions(who))>=0);
}

public int add_vision(mixed who,string name,string vision)
{
    if (!check_existing_dir(who))
    {
        return 0;
    }
    string filename=VISION_DIR+get_dir_name(who)+name;
    if (file_size(filename)!=-1)
    {
        return 0;
    }
    write_file(filename,vision);
    return 1;
}

public int update_vision(mixed who,string name,string vision)
{
    if (!check_existing_dir(who))
    {
        return 0;
    }
    string filename=VISION_DIR+get_dir_name(who)+name;
    if (file_size(filename)<=0)
    {
        return 0;
    }
    rm(filename);
    write_file(filename,vision);
    return 1;
}

public string query_vision(mixed who,string name)
{
    if (!check_existing_dir(who))
    {
        return 0;
    }
    string filename=VISION_DIR+get_dir_name(who)+name;
    if (file_size(filename)<=0)
    {
        return 0;
    }
    return read_file(filename);
}


public int remove_vision(mixed who,string name)
{
    if (!check_existing_dir(who))
    {
        return 0;
    }
    string filename=VISION_DIR+get_dir_name(who)+name;
    if (file_size(filename)<=0)
    {
        return 0;
    }
    rm(filename);
    return 1;
}


