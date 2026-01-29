/*
 * Road in Neverwinter, Protector Enclave 
 * -- Finwe, February 2017
 */

#include "/d/Faerun/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_COMMON;
inherit BASE_ROAD;
//inherit "/d/Faerun/neverw/std/base_road.c";

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"neverw_pr.txt");
    setuid(); 
    seteuid(getuid());
    
    set_short("outside the ruins of Castle Never");
    set_extraline("The ruins look old and deserted. It haven't been rebuilt " +
        "and look weather worned. Southeast is a large bridge. The bridge " +
        "looks in disrepair and use, but in need of repairs. To the south " +
        "runs a river. It flows west under the bridge and past the ruined " +
        "castle. ");

    add_castle_never();
    add_river("south");
    add_dolphin_bridge();

    add_exit(PR_DIR + "castle_01", "northwest");
    add_exit(PR_DIR + "d_bridge", "southeast");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}
