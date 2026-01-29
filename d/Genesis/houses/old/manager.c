/*
 * Manager room for housing
 *
 * Keeping track of deeds
 * 
 * Varian 2020
 */
 
#pragma strict_types

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"

#define DEED_MAX    1

int do_find(string str);
static mapping deeds = ([]);

public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
}

void
create_room()

{
    set_short("Housing Manager");
    set_long("This is the room for the housing manager, made by " +
        "Varian, who has never done this before and still doesn't " +
        "know how to do this properly yet. But, at least he is " +
        "trying! There are currently no commands in this room " +
        "to check on players who own houses, or to see houses " +
        "etc.. etc.. etc..\n\nCurrently you can <find # deedname>, " +
        "<list> and <add> deeds for houses. I think.\n");

    add_exit(HOUSE + "office", "north");

    /*add_npc(HOUSE + "silladan");*/
}

public void
init()
{
    ::init();
    add_action("do_find",   "find");
    add_action("do_list",   "list");
    add_action("do_modify", "add");

}

public int
do_find(string str)
{
    object  deed;
    string  deName, heFile;
    int     deVal;

    if (!strlen(str) || !parse_command(str, ({}), "%d %s", deVal, deName))
    {
        notify_fail("Find what? 1 deedname? Check the list first?\n");    
        return 0;
    }
    
    if (deVal > DEED_MAX || deVal < 0)
    {
        notify_fail("You can use a better number than that!\n");
        return 0;
    }        

    deName = implode(explode(deName, " "), "_");
    
    if (member_array(deName, m_indexes(deeds)) > -1)
        heFile = deeds[deName];

    if (!stringp(heFile) || !safely_load_master_file(heFile))
    {
        notify_fail("No such file exists.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    deed = clone_object(heFile);
    deed->set_heap_size(deVal);
    deed->move(this_player(), 1);
    
    this_player()->catch_msg("You grab " + deVal + " " + deName +
    " deed.\n");

    return 1;
}

public int
save_deeds()
{
    save_map(deeds, HOUSE + "manager");
    return 1;
}

public int
load_deeds()
{
    if (file_size(HOUSE + "manager.o") < 0)
        return 0;
    
    deeds = restore_map(HOUSE + "manager");
    return 1;
}

public int
modify_deeds(string name, string path)
{
    if (!strlen(name) || !strlen(path))
        return 0;
    
    name = implode(explode(name, " "), "_");
    
    if (member_array(name, m_indexes(deeds)) > -1)
    {
        m_delkey(deeds, name);
        save_deeds();
        return -1;
    }
    
    deeds[name] = path;
    save_deeds();
    return 1;
}

int
do_list(string arg)
{
    if (!load_deeds() || !m_sizeof(deeds))
    {
        notify_fail("Error, no deeds added to file!\n");
        return 0;
    }
    
    if (!strlen(arg) || arg == "deeds")
    {
        write("The valid deeds are: " + 
        COMPOSITE_WORDS(sort_array(m_indexes(deeds))) + "\n");
        return 1;
    }
    
    return 1;
}

int
do_modify(string str)
{
    string deName, hePath;
    
    if (!strlen(str) || !parse_command(str, ({}), "%s ':' %s", deName, hePath))
    {
        notify_fail("add <deed_name> : <deed_path>?\n");    
        return 0;
    }
    
    switch(modify_deeds(deName, hePath))
    {
        case -1:
        write("You remove " + deName + " from the deed list.\n");
            break;
        case 1:
        write("You have added " + deName + " to the deed list.\n");
            break;
        default:
        notify_fail("I think you made a typo, try again.\n");
            return 0;
    }
    
    return 1;
}