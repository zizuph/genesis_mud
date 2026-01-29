/*
 * The Beach of Faerie
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
 
inherit BEACH_BASE;

#define MIN_AWARE 13

object nails;

string check_nails();

void
create_beach_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A deserted beach alongside a lake");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is covered " +
        "with yellow sand and scattered shells. It stretches east and " +
        "west and slopes northward into the lake. A ridge rises above " +
        "you to the south. @@check_nails@@\n" );

// this defines the search function
    add_prop("_obj_s_search_fun","do_search");

    reset_room();
    
    set_add_beach();
    set_add_forest();

    add_exit(FOREST_DIR + "beach02s", "west");

}
void
reset_room()
{
    nails = 0;
}

string
check_nails()
{
    if(!nails) 
        return "Something glints in the sand.";
    else 
        return "";
}

string
do_search(object searcher, string str)
{
    int awareness;
    FIXEUID;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;

// if nails has been searched for already, search will fail
    if(nails) 
    {
        return 0;
    }
    
    seteuid(getuid(TO));
    nails = clone_object(OBJ_DIR + "nails");
    nails->move(searcher,1);
    say(QCTNAME(searcher)+ " finds something buried in the sand.\n");
    return "You find a "+nails->short()+" buried in the sand.\n";
}
