#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include "defs.h"

#include <macros.h>

#define MAX_COUNT   10
#define MAX_TIME    1000

static mapping hoopaks = ([]);

void
create()
{
    setuid();
    seteuid(getuid());
}

string
get_name(int id)
{
    return "ob_" + id;
}

public int
save_hoopak(int id)
{
    mapping hoopak_save;
    string  name = get_name(id);
   
    if (!mappingp(hoopak_save = hoopaks[name]))
        return 0;
  
    save_map(hoopaks, HOOPAK_DATA(name));
    return 1;
}

public int
load_hoopak(int id)
{
    string name = get_name(id);
    
    if (file_size(HOOPAK_DATA(name) + ".o") < 0)
        return 0;
    
    hoopaks[name] = restore_map(HOOPAK_DATA(name));
    
    return 1;
}

public varargs mixed
get_hoopak(int id, string map)
{
    string name = get_name(id);
    
    if (!id || !load_hoopak(id))
        return 0;
    
    if (!strlen(map))
        return hoopaks[name];
    
    if (member_array(map, m_indexes(hoopaks[name])) < 0)
        return 0;
    
    return hoopaks[name];
}

public int
add_hoopak(int id)
{
    string name = get_name(id);
    
    if (load_hoopak(id))
        return 0;
    
    hoopaks[name] = ([ "time" : time() ]);
    
    return save_hoopak(id);
}

public int
available_id()
{
    int     count = 0;
    string  name;

    while(count < MAX_COUNT)
    {
        count++;
        name = get_name(count);
        
        if ((file_size(HOOPAK_DATA(name)) > -1 &&
            (time() - get_hoopak(count, "time") > MAX_TIME)))
            rm(HOOPAK_DATA(name) + ".o");
        
        if (file_size(HOOPAK_DATA(name)) == -1)
            return count;
    }
    // Change return count to return 0
    return count;
}