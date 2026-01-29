/*
 * Mapfile Manager
 *
 * The Genesis Magic Map system (man genesis_maps) is very useful for
 * adding drawn maps and allowing users to see the surrounding areas
 * including zoom. However, as of this writing (August 2009), it
 * requires a prop to be set in every room. This can be prohibitive
 * to expanding the use of the magic map since there are many old
 * rooms which are difficult to change to add a room. It is much easier
 * to add this information into a central location and then retrieve
 * it using the magic map.
 *
 * This module is designed to handle those changes.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <files.h>
#include <macros.h>

// We store all the information inside this one mapping
// The format is:
//    directory : ([ filename : mapfile ])
//
// The reason that we use directory first is because mapping has a 5000
// item limit, and we hope to eventually have more than 5000 rooms mapped.
// By using directory, we are assuming that there will not be more than
// 5000 rooms in a particular directory. This should hopefully hold true.
public mapping  mapfile_locations = ([ ]);

#define DATA    "/d/Sparkle/std/data/mapfile_locations"

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }
}

public string
get_roomfile(mixed room)
{
    string roomfile;
    
    if (objectp(room) && IS_ROOM_OBJECT(room))
    {
        roomfile = MASTER_OB(room) + ".c";
    }
    else if (stringp(room))
    {
        roomfile = room;
    }
    else
    {
        // Not valid input. Must be either room or file
        return 0;
    }
    
    if (!objectp(find_object(roomfile)))
    {
        // The file hasn't been loaded yet. So no mapfile.
        return 0;
    }
    
    return roomfile;
}

public string
query_map_location(mixed room)
{
    string roomfile;
    
    if (!stringp(roomfile = get_roomfile(room)))
    {
        return 0;
    }
        
    // Get the directory for the filename, which is a key to the mapping
    string directory = implode(explode(roomfile, "/")[..-2], "/") + "/";
    mapping directory_map;
    string mapfile;
    if (!mappingp(directory_map = mapfile_locations[directory])
        || !stringp(mapfile = directory_map[roomfile]))
    {
        return 0;
    }
    
    // Found the mapfile stored. We return it.
    return mapfile;
}

public void
set_map_location(mixed room, string mapfile)
{
    string roomfile;
    
    if (!stringp(roomfile = get_roomfile(room)))
    {
        return 0;
    }

    string directory = implode(explode(roomfile, "/")[..-2], "/") + "/";
    mapping directory_map;
    if (!mappingp(directory_map = mapfile_locations[directory]))
    {
        mapfile_locations[directory] = ([ ]);
        directory_map = mapfile_locations[directory];
    }
    
    string oldvalue = directory_map[roomfile];
    if (!strlen(oldvalue))
    {
        oldvalue = "nothing";
    }
    
    m_delkey(directory_map, roomfile);
    // Set the mapfile if it is valid
    if (strlen(mapfile) > 0)
    {
        directory_map[roomfile] = mapfile;
        log_file("mapfile_manager", ctime(time()) + ": "
          + capitalize(this_player()->query_real_name()) + " changes the "
          + "mapfile for " + roomfile + " from '" + oldvalue + "' to '" 
          + mapfile + "'\n");
    }
    else
    {
        log_file("mapfile_manager", ctime(time()) + ": "
          + capitalize(this_player()->query_real_name()) + " unsets the "
          + "mapfile for " + roomfile + " from '" + oldvalue + "'\n");
    }
    save_object(DATA);
}

mapping
get_mapfile_locations() 
{
    if (file_name(previous_object()) != "/d/Genesis/ateam/aow/client/magicmap")
        return 0;

    return mapfile_locations;
}
