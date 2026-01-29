/* 
 * Shelf Manager for the Sparkle Genesis Library
 * 
 * This manager keeps track of all the shelves for the Genesis
 * library. This is mainly going to be used for things like
 * classifying books from one central location, such as the
 * writing room, or a wizard tool.
 *
 * Created by Petros, May 2009
 */
 
#pragma strict_types

#include <macros.h>
#include "defs.h"

// Global Variables
public mapping     shelves = ([ ]); // name => directory
public mapping     rooms   = ([ ]); // name => roomfile

// Defines
#define DATA       (LIBRARY_DATA_DIR + "shelf_data")
                    
/*
 * Function:    create
 * Description: Create function is called for every object
 *              we call it here to restore the data for it.
 */
public void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }
}

/* 
 * Function:    query_all_shelves
 * Description: This returns all the shelves that are currently
 *              in use by the Genesis Library
 */
public mapping
query_all_shelves()
{
    return shelves + ([ ]);
}

/*
 * Function:    query_shelf_directory
 * Description: Given a shelf name, it will return the directory
 *              where the books are to be stored.
 */
public string
query_shelf_directory(string name)
{
    if (!IN_ARRAY(name, m_indices(shelves))
        || !strlen(shelves[name]))
    {
        return LIBRARY_BOOK_DIR;
    }
    
    return shelves[name];
}

/*
 * Function:    query_shelf_room
 * Description: Given a shelf name, it will return the directory
 *              where the books are to be stored.
 */
public string
query_shelf_room(string name)
{
    return rooms[name];
}

/*
 * Function:    add_shelf
 * Description: This adds a new shelf to the shelf_manager, or
 *              edits an existing entry. It is called in
 *              create_genesis_library when the shelves are first
 *              added or declared
 */
public int
add_shelf(string name, string directory, string roomfile)
{
    setuid();
    seteuid(getuid());

    shelves[name] = directory;
    rooms[name] = roomfile;
    save_object(DATA);

    return 1;
}

public string *
query_rooms_with_keywords(string str)
{
    string * roomlist;
    
    roomlist = ({ });
    foreach (string roomfile : m_values(rooms))
    {
        if (IN_ARRAY(roomfile, roomlist)
            || !roomfile->contains_keywords(str))
        {
            continue;
        }
        
        roomlist += ({ roomfile });
    }
    
    return roomlist;
}
