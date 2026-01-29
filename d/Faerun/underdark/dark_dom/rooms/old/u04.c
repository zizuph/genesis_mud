/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT,1);
    add_prop(OBJ_S_SEARCH_FUN, "search_floor");
    set_short("A large cave");
    set_long(short() + ". The cave is larger than most. There doesn't " +
        "seem to be anyway out from here. The cave is dimly lit and " +
        "the air stale. Skeletal remains are scattered around.\n");

    add_item(({"floor", "ground"}),
        "The ground is irregular and rough looking. Skeletal remains " +
        "are scattered around the floor.\n");
    add_item(({"skeletal remains","remains"}),
        "A few scattered bones of some creatures are scattered around " +
        "the floor. The bones look chewed on and broken.\n");
    add_exit(TUN_DIR + "u03", "west", "@@check_drowwep",0);
}

public string
search_floor(object me, string arg)
{
    if (arg != "floor" || arg != "ground")
        return "";

    if (TP->query_skill(SS_AWARENESS) < 30)
        return "";

    add_exit(TUN_DIR + "u05","down");
    set_alarm(12.0,0.0,"remove_exit","down");
    return "You search the floor carefully and discover a hidden exit " +
        "leading down.\n";
}

int
check_drowwep()
{
    object *ob;
    int i;
   
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->id("drowwep"))
        {
            write("Your drow weapon disintegrates!\n");
            ob[i]->remove_object();
            return 0;
        }
    return 0;
}
