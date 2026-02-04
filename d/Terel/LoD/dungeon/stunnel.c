/*
 * stunnel.c
 *
 * A secret tunnel below the Legion of Darkness quarters.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#define DUNG_DIR (LOD_DIR + "dungeon/")
#define S_EXIT   "/d/Terel/common/town/road_e/road_e09"

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2"});
}

public void
create_room()
{
    ::create_room();
    
    set_short("dark tunnel");
    set_long("You are down in a dark but straight tunnel.\n");
             
    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(DUNG_DIR + "behind", "north", -7);
    add_exit(S_EXIT, "southeast", "@@check_leave");
    
    reset_room();
}

public int
check_leave()
{
    if (TP->query_race_name() == "bat") return 1;
    
    write("As you stumble out from the dark tunnel, you " +
          "forget to remember where it emerged. You seem not " +
          "be able to locate where the mouth of the tunnel is " +
          "hidden. What a perfect escape route!\n");
    return 0;
}
