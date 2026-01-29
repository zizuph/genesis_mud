/* data_manager.c created by Shiva@Genesis.
 * 
 * Some routines for persistent data storage, particularly suited for
 * storing player data.
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#include <std.h>

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

static string save_dir;
static string log_dir;
static string garbage_dir;
static mapping data_map = ([]);


public void
set_save_dir(string dir)
{
    if (dir[-1..] != "/")
    {
        dir += "/";
    }

    save_dir = dir;
}


public void
set_log_dir(string dir)
{
    if (dir[-1..] != "/")
    {
        dir += "/";
    }

    log_dir = dir;
}


public void
set_garbage_dir(string dir)
{
    if (dir[-1..] != "/")
    {
        dir += "/";
    }

    garbage_dir = dir;
}


static void
manager_log(string text)
{
    setuid();
    seteuid(getuid());
    write_file(log_dir, ctime(time()) + " " + text + "\n");
}


public string
query_data_file(string id)
{
    return (save_dir + id);
}


public string
query_old_data_file(string id)
{
    return (strlen(garbage_dir) ? garbage_dir + id : 0);
}


/*
 * Function name: load_data
 * Description:   Read a data file from disk and store it in memory
 * Arguments:     1. (string) The data's id (filename)
 * Returns:       1/0 - data loaded/not loaded
 */
public int
load_data(string id)
{
    string data_file;

    id = lower_case(id);
  
    if (data_map[id])
    {
        // Data already loaded
        return 1;
    }
  
    data_file = query_data_file(id);

    if (file_size(data_file + ".o") < 0)
    {
        // No data file exists
        return 0;
    }
  
    // Load the data file
    data_map[id] = restore_map(data_file);
    return 1;
}


public int
clear_data(string id)
{
    id = lower_case(id);

    if (IS_INDEX(id, data_map))
    {
        data_map = m_delete(data_map, id);
        return 1;
    }
   
    return 0;
}


/*
 * Function name: update_data
 * Description:   Read data from disk and store it in memory, replacing any
 *                old data.
 * Arguments:     1. (string) The member's name
 * Returns:       1/0 - Member data reloaded/not reloaded
 */
public int
update_data(string id)
{
    clear_data(id);
    load_data(id);
}


public int
delete_data(string id)
{
    string fname;

    if (IS_INDEX(id, data_map))
    {
        data_map = m_delete(data_map, id);
    }

    fname = query_data_file(id) + ".o";  
    if (file_size(fname) >= 0)
    {
        string old_fname = query_old_data_file(id);
        if (old_fname)
        {
            // Make a backup of the file if a garbage diretory has been given
            rename(fname, old_fname + ".o");
        }
        else
        {
            // Delete the file if no garbage directory is given
            rm(fname);
        }
    }
  
    return 1;
}


public void
create_data_manager()
{
}


/*
 * Function name: create
 * Description:   Initialize the manager
 */
static nomask void
create()
{
    setuid();
    seteuid(getuid());
  
    create_data_manager();
}


varargs int
save(string id)
{
    mapping info;
  
    id = lower_case(id);
   
    if (!mappingp(info = data_map[id]))
    {
        // There's no in-memory data to save
        return 0;
    }
  
    save_map(info, query_data_file(id));
    return 1;
}


string
get_id(mixed val)
{
    if (objectp(val))
    {
        if (IS_PLAYER_OBJECT(val))
        {
            val = val->query_real_name();
        }
        else
        {
            val = val->query_name();
        }
    }
  
    if (!stringp(val))
    {
        return 0;
    }
  
    return lower_case(val);
}


mixed
get_info(mixed index_val, string info)
{
    string id;
    if (!(id = get_id(index_val))
        || (!data_map[id] && !load_data(id)))
    {
        // First check for a valid id from the index_val
        // If it's valid, we check to see if it's been loaded.
        // If not loaded, we'll try to load it.
        // If nothing succeeds, we just return 0.
        return 0;
    }

    return data_map[id][info];
}


int
set_info(mixed index_val, string info, mixed val)
{
    string id;
    if (!(id = get_id(index_val)))
    {
        return 0;
    }

    if (!load_data(id))
    {
        data_map[id] = ([]);
    }

    data_map[id][info] = val;
    return save(id);
}


int
remove_info(mixed index_val, string info)
{
    string id;
    if (!(id = get_id(index_val)) || !load_data(id))
    {
        return 0;
    }
  
    data_map[id] = m_delete(data_map[id], info);
    return save(id);
}


#if 0
static void
update_members()
{
    int i;
    string *member_files, who;
  
    setuid();
    seteuid(getuid());
  
    member_files = filter(get_dir(MEMBER_SAVE_DIR), &wildmatch("*.o"));
    
    for (i = sizeof(member_files); i--;)
    {
        who = lower_case(member_files[i][..(strlen(member_files[i]) - 3)]);
    
        if (!SECURITY->exist_player(who))
        {
            rename(MEMBER_SAVE_DIR + member_files[i], 
                   OLD_MEMBER_SAVE_DIR + member_files[i]);
            manager_log(member_files[i] + " removed: player no longer exists.\n");
        }
    }
}
#endif


public mapping
query_data_map()
{
    return data_map + ([]);
}


public string *
query_ids()
{
    return m_indices(data_map);
}
