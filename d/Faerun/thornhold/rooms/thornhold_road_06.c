/*
 * Road to Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

int gear_found = 0;
object gear;

void
create_road()
{
	string exit_right = "northeast";
	string exit_left = "west";

    add_road();
    add_twoway_road_string(exit_left, exit_right);
	add_extra_string_end("The weathered road is at its steepest " +
	"stretch here as it winds through the jagged rocks.");

    reset_faerun_room();

    add_exit(ROOM_DIR + "thornhold_road_05",   exit_right);
    add_exit(ROOM_DIR + "thornhold_road_07",   exit_left);
    
    set_no_exit_msg(({"northwest", "north"}),
    "A sheer cliff blocks progress in that direction, as the " +
    "road to Thornhold ascends towards the fortress in a steep " +
    "switchback.\n");

    set_no_exit_msg(({"east"}),
    "Jagged rocks block passage to the east.\n");

    set_no_exit_msg(({"south", "southeast", "southwest"}),
    "You look down at the precipitous cascade of jagged rocks that " +
    "tumble towards the sea, and decide not to proceed in that " +
    "direction.\n");
    
    // this sets up the search routine to find something on the road

    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");
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
    gear_found = 0;
}

mixed
my_search(object searcher , string str)
{
    int awareness;
    
    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < 15) 
    {
        return 0;
    }
    if(str=="ground" || str=="road" || str=="here")
    {
        if(gear_found == 1)
        {
            return "You search the road, but find nothing of interest.\n";
        }
        else
        {
            if(!QUEST_MASTER->check_gear(searcher))
            {
            
                seteuid(getuid(TO));
                gear = clone_object("/d/Faerun/thornhold/obj/gear.c");
                gear->move(searcher,1);
                say(QCTNAME(searcher)+ " finds something on the road and " +
                "picks it up.\n");
                gear_found = 1;
                return "You spot a " + gear->short() + " on the ground and " +
                "quickly pick it up.\n";
            }
            else
            {
                return "You search the road, but find nothing of interest.\n";
            }
        }            
        
      return "You search the road, but find nothing of interest.\n";
    }
    else
    {
        return ;
    }
}