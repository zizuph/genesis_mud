/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/south_path/base_south_path";

#include <ss_types.h>
#include <stdproperties.h>

private object man;

public void
create_gloomy_forest()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    add_my_desc("The path continues to the northwest and " +
        "southeast.\n");
    add_exit("south_path_20", "northwest");
    add_exit("south_path_22", "southeast");
//  add_exit("trails1.c", "west", 0, 0, 1);
    reset_room();
}

public void
reset_room()
{
    if(!man)
    {
        man = clone_object("/d/Earthsea/gont/tenalders/npc/blind_man");
        man->move(this_object(), 1);
        man->command("emote dodders in.");
    }
}

public string 
see_path()
{
    if(this_player()->query_skill(SS_LOC_SENSE) > 15)
    {
        return "Your keen eyes notice a small trail that " +
            "opens to the west.\n";
    }

    return "\n";
}

public void
init()
{
    ::init();
    write("A low-hanging branch smacks you in the face.\n");
}
