
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "defs.h"

#define ABILITY_DATA_FILES (ABILITY_DIR + "data/files/")

string
get_data_file(string source_file)
{
    if (wildmatch(ABILITY_DIR + "*", source_file))
    {
        // Convert the source file directory to data file directory
        source_file = explode(explode(source_file, ".c")[0], ABILITY_DIR)[-1];
        return ABILITY_DATA_FILES + source_file;
    }
    
    return ABILITY_DATA_FILES + "error/";
}

string
get_source_file(object file)
{
    int     iterate;
    string *list;
    
    if (!objectp(file) || !sizeof(list = inherit_list(file)))
        return 0;
    
    // Get the last file in the inherit chain which is in the ability directory.
    for(iterate = sizeof(list) - 1; iterate > -1; iterate--)
    {
        if (wildmatch(ABILITY_DIR + "*", list[iterate]))
            break;
    }
    
    return list[iterate];
}

public status
verify_directory(string directory)
{
    string *list = ({}),
            comp = ABILITY_DIR;
    int     num = 0;
    
    // Make sure we limit this function to the pre-determined comp directory.
    if (!wildmatch(comp + "*", directory))
        return 0;
    
    directory = explode(directory, comp)[-1];
    list = explode(directory, "/");
    foreach(string dir: list)
    {
        if (strlen(dir) && !wildmatch("*.?", dir))
        {
            comp += dir + "/";
            // If we fail to create a directory, we need to abort.
            if (file_size(comp) != -2 && !mkdir(comp))
                break;
        }
        num++;
    }
    
    // Verify that there were no failures in creating the directories.
    if (num < sizeof(list))
        return 0;
    
    return 1;
}

public status
store_inherit_file(object file)
{
    string source_file;

    setuid();
    seteuid(getuid());

    if (objectp(file))
        source_file = get_source_file(file);
    
    if (source_file)
    {
        mapping files = ([ "files":({}) ]);
        string  data_file = get_data_file(source_file);
        
        if (file_size(data_file + ".o") > -1)
            files = restore_map(data_file);
        
        if (verify_directory(data_file + ".o"))
        {
            files["files"] |= ({ file_name(file) });
            save_map(files, data_file);
            return 1;
        }
    }
    
    return 0;
}

public status
reload_inherit_file(object file)
{
    string source_file;
    
    if (objectp(file))
        source_file = get_source_file(file);
    
    if (source_file)
    {
        mapping files = ([ ]);
        string  data_file = get_data_file(source_file);
        
        if (file_size(data_file + ".o") < 0)
            return 0;
        
        if (mappingp(files = restore_map(data_file)) &&
            member_array("files", m_indexes(files)) > -1 &&
            sizeof(files["files"]))
        {
            foreach(string filename: files["files"])
            {
                string error;
                if (stringp(error = LOAD_ERR(filename)))
                {
                    files["files"] -= ({ filename });
                    send_debug_message(file->short(), filename + " "
                    + error, ABILITY_DATA_FILES + "error_log");
                }
                else if (this_player()->query_wiz_level())
                {
                    if (!this_player()->command("$load " + filename))
                    {
                        this_player()->catch_msg("load -r " + filename + "\n");
                    }
                }
            }
            
            save_map(files, data_file);
            return 1;
        }
    }
    
    return 0;
}

private nomask void
create()
{
    setuid();
    seteuid(getuid());
}