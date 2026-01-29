/*
 * Abaddon - 2020 /d/Faerun/underdark/dark_dom2/rooms/
 */
#define NPC "/d/Faerun/underdark/dark_dom2/npc/"
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_DOM2_INDOOR;

//inherit BASE_TUNNEL;
#define MIN_TRACKING    30 
#define MIN_AWARENESS   30
#define CRACK_PROP "_found_necro_crack"
string extraline = "The walls are irregular and cracked. They are warm and red, running through the mountain.";


void
create_dom2_room()
{
    set_long("Somewhere underground.\n"
        +"Silence and darkness fills the tunnel. The weight of the mount"
        +"ain seems heavy in this forbidding place. The dark tunnel is r"
        +"ough and starts to decline deeper into the mountain. The air he"
        +"re looks faintly red, and smells of fresh gore. A path leads to"
        +" the southwest and northwest.\n");
    
    set_short("Somewhere underground");
    
    //If we want herbs here.
    //add_std_herbs("mere");
    add_std_herbs("underdark");
        
     add_item(({"walls", "wall"}),
        "The walls are jagged and roughed over, with dips and depressions"
        +" encapsulating your view.");

     add_item(({"path", "footsteps"}),
        "You can see slight footsteps leading deeper into the tunnel.\n");

     add_item(({"underground"}),
        "It's hard to say how far undergound you are, but it would be unw"
        +"ise to get lost here.\n");

     add_item(({"darkness"}),
        "No light from the surface could ever hope to reach here.\n");

    add_item(({"tunnel"}),
        "This tunnel looks jagged as if something forced its way into sol"
        +"id rock.\n");

    add_item(({"floor", "ground"}),
        "The floor is full of pebbles, stones, and other debris from brea"
        +"kage that created it. You notice cracks by your feet.\n");

    add_item(({"air", "haze"}),
        "The air here reeks of death. A crimson haze seems to surround al"
        +"l you see.\n");

    add_item(({"cracks", "crack"}),
        "They are narrow, vertical breaks in the rock and walls. They were created eons ago as the rock has shifted.\n");

    add_item(({"wall", "walls"}),
        "The walls are naturally carved from the rock. They are irregularly shaped and rough looking, arching overhead to form a rough ceiling above you. There are cracks in them.\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    reset_room();

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "4", "northwest");
    add_npc(NPC + "skeleton", 2);
}


public void
init()
{
    ::init();
    add_action("enter_crack", "enter");
}
/*void
reset_room()
{
    make_skeleton();
    set_searched(0);
}
/*
 * search routine to find entrance in wall
 */
mixed do_search(object searcher, string str)
{
    int awareness, tracking;
    if (!parse_command(str, ({}),
       "'cracks' / 'crack' / 'wall' [the] [large] "))
        return 0;
    awareness = searcher->query_skill(SS_AWARENESS);
    tracking  = searcher->query_skill(SS_TRACKING);
    if (awareness >= MIN_AWARENESS && tracking >= MIN_TRACKING)
    {
        TP->add_prop(CRACK_PROP,1);
        return "You find a hidden opening in the wall.\n";
    }
    return 0;
}
int
enter_crack(string str)
{
    if( str=="cracks" ||
        str=="crack" || 
        str=="fissure" || 
        str=="wall" ||
        str=="opening")
    {
        if(TP->query_prop(CRACK_PROP))
        {    
            write("You enter a crack in the wall.\n");
            say(QCTNAME(TP)+" disappears into a crack in the wall.\n");
            tell_room("/d/Faerun/underdark/dark_dom2/rooms/6.c",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", "/d/Faerun/underdark/dark_dom2/rooms/6",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}
