inherit "/d/Emerald/std/room";

#include "defs.h"
#include <stdproperties.h>

static mixed tower_dir = 0;

public void
create_prominence_room()
{
}

public nomask void
create_emerald_room()
{
    set_short("Atop a rocky prominence");
    // Do not replace string VBFC with a function pointer.  It will not work.
    set_em_long("@@prominence_long@@\n");

    add_prop(ROOM_I_LIGHT, -10);
    add_prop("_room_i_free_vamp_dvis", 11);

    add_item(({ "tower", "dark tower", "eerie tower", "dark wall",
	"six-sided tower", "wall", "featureless wall", "dark featureless wall",
        "walls", "dark walls", "featureless walls", "dark featureless walls",
        "ruins", "ruin", "ruins of a dark tower", "ruin of a dark tower" }),
        "The tower appears to have been destroyed. Little remains of it.\n");

    add_item(({ "rock", "rocks", "prominence", "ground" }),
        "The ground here is rocky and uneven.\n");

    create_prominence_room();
}

public void
set_tower_dir(string dir)
{
    tower_dir = dir;
}

public string
prominence_long()
{
    if (CAN_SEE_TOWER(this_player()))
    {
        if (stringp(tower_dir))
	{
            return "From atop this rocky prominence, you can look out " +
                "out over the mist-covered island.  To the " + tower_dir + 
                " stand the ruins of a dark tower.";
	}

        return "The dark, featureless, outer wall of an eerie tower looms " +
            "above you, atop this rocky prominence.  From this perspective, " +
            "you can see out over the entirety of the mist-covered island " +
            "and out into the sea.";
    }

    if (stringp(tower_dir))
    {
        return "From atop this rocky prominence, you can look out out over " +
            "the mist-covered island.";
    }

    return "Rocks here.";
}
