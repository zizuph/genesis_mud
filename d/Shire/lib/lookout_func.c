/*
 * Ranger Lookout functions
 * By Finwe, April 2005
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
//#include "defs.h"
#include <stdproperties.h>
#include <std.h>
#include <composite.h>
#include <filter_funs.h>

#define tell_watchers(watcher_loc,msg)   tell_room(watcher_loc + ".c",\
    QCTNAME(TP) + " " + msg + "\n");

object other_room;
mixed opeople;
string views;


//public int query_prevent_snoop() {return 1;}

string room_check(string outside_room, string outside_room_desc)
{
    if (!LOAD_ERR(outside_room))
        other_room = find_object(outside_room);
    else
        return "Error with " + outside_room + ". Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = "   No rangers are standing " + outside_room_desc + ".\n";
    else
        views = "   " + CAP(COMPOSITE_LIVE(opeople)) + " is standing " + outside_room_desc + "\n";

}


string ambush_desc()
{
// insert a room_check() here for each room to look at. That room will also
// need a tell_watchers() set in the exit so the watchers know when players enter
// or leave the room.

    views = "\nBelow, you see the following:\n" + views;
    return views;

}

int rglance()
{
    write(ambush_desc() + "\n");
    return 1;
}
