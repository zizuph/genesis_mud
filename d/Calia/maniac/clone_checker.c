
/* 
 *  /d/Calia/maniac/clone_checker.c 
 * 
 * Lets you get object clone information easily. 
 */ 

#include "defs.h"
inherit "/std/object"; 

#include <stdproperties.h>
#include <macros.h>
#include <const.h>


void
create_object()
{
    set_adj("clone"); 
    set_name("checker"); 
    set_long("This object lets you check what clones of an object " +
             "path exist and their locations, using the <clones path> " +
             "command.\n");  
}

string
query_auto_load()
{
    return MASTER; 
}


string 
loc_display(object obj, object tp)
{
    object e = environment(obj); 

    if (!objectp(e)) 
        return "The void."; 
    else
        return (file_name(e) + " (" + 
                e->short(tp) + 
                ")"); 
}


int
check_clones(string str)
{
    object obj, *obj_clones; 
    
    if (!stringp(str) || !strlen(str) ||
        !objectp(obj = find_object(str))) {
        notify_fail("No such object loaded.\n"); 
        return 0;
    } 

    obj_clones = object_clones(obj); 

    if (!sizeof(obj_clones)) {
        notify_fail("No clones for that object.\n"); 
        return 0;
    } 

    this_player()->more("Clones of that object are present at " +
                        "the following locations:\n" + 
                        implode(map(obj_clones, &loc_display(,this_player())), 
                        "\n")); 

    return 1;
}


void
init()
{
    ::init(); 
    add_action(check_clones, "clones"); 
}
