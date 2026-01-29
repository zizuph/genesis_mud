inherit "/std/object";
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/terrain/terrain.h"
#include <macros.h>

#define TERR_MASTER     ("/d/Krynn/common/terrain/master")
#define CHECK_USER      if (!TERR_MASTER->check_user(TP->query_real_name())) \
                            return 0;

public void
create_object()
{
    set_name("terradder");
    add_name("_krynn_terradder_");

    set_long("With this object you are able to add terrain properties to the land " +
	     "of Krynn. Possible commands are:\n" +
             "   tadd <type>     Add a terrain type to the room.\n" +
             "   tremove <type>  Remove a terrain type from a room.\n" +
             "   tlist           List all the terrain types.\n\n");

    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_NO_STEAL, 1);
}

public int
do_add(string str)
{
    string origstr = str;
    string file = MASTER_OB(E(TP));
    string tmp;

    CHECK_USER

    if (!str || !strlen(str))
        return NF("You have to supply a terrain type as argument.\n");

    if (sscanf(file, "/d/Krynn/%s", tmp) != 1)
        return NF("You can only do this in the Krynn domain.\n");

    str = lower_case(str);

    if (!TERR_MASTER->valid_terrain(str))
        return NF("Invalid terrain '" + origstr + "'.\n");

    if (!TERR_MASTER->add_terrain_prop(str, file))
        return NF("Failed to add the terrain.\n");

    write("Terrain added.\n");
    return 1;        
}

public int
do_remove(string str)
{
    string origstr = str;
    string tmp, file = MASTER_OB(E(TP));

    CHECK_USER

    if (!str || !strlen(str))
        return NF("You have to supply a terrain type as argument.\n");

    str = lower_case(str);

    if (sscanf(file, "/d/Krynn/%s", tmp) != 1)
        return NF("You can only do this in the Krynn domain.\n");

    if (!TERR_MASTER->valid_terrain(str))
        return NF("Invalid terrain '" + origstr + "'.\n");

    if (!TERR_MASTER->remove_terrain_prop(str, file))
        return NF("Failed to remove the terrain.\n");

    write("Terrain removed.\n");
    return 1;        
}

public int
do_list(string str)
{
    string origstr = str;
    string *terrains;
    int i, size;

    CHECK_USER

    terrains = TERR_MASTER->query_terrain();

    if ((sizeof(terrains) % 2) != 0)
        terrains += ({ "" });

    size = sizeof(terrains) / 2;

    for (i = 0; i < size; i++)
    {
        write(sprintf("%-15s %-15s\n", terrains[i], terrains[i+1]));
	  i++;
    }

    return 1;        
}

public void
init()
{
    add_action(do_add, "tadd");
    add_action(do_remove, "tremove");
    add_action(do_list, "tlist");
    ::init();
}

string
query_auto_load()
{
        return MASTER + ":";
}    
