/*  /d/Faerun/phlan/rooms/kw.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "/d/Faerun/phlan/rooms/defs.h"

inherit BASE_PHLAN_OUTDOOR;

#define LEDGE PODOL_DIR + "kw1"

int ladder_found = 0;
int do_climb(string str);

/*
*   Making the basic room. 
*/

void
create_phlan_outdoor()
{
    extraline = "Podol Plaza is a field of short clipped, manicured grass."
                +" It is still green and resilient despite being trod by many"
                +" feet every year. Podol Street lies to the north. You stand"
                +" before Kuto's Well.";
    
    set_short("Kuto's Well");

/*
*   Decorations
*/    
        
    add_item(({"plaza", "podol plaza"}),
        "Podol Plaza is an open air market. Though mostly selling items for"
        +" the residents of town and the outlying areas, there are stalls"
        +" from traders farther away selling their goods.\n"); 

    add_item(({"grass", "short grass", "clipped grass", "manicured grass"}),
        "Healthy green and clipped short, the grass of the plaza is well"
        +" maintained by both the city and the local merchants.\n");

    add_item(({"city", "phlan"}),
        "The port city of Phlan, on the shores of the Moonsea, stands to"
        +" the east. You are in Podol Plaza.\n");

    add_item(({"street", "podol street"}),
        "Podol street lies along the northern edge of the plaza.\n");

    add_item(({"wall", "city wall"}),
        "The city wall is carefully mortared and well maintained. On the"
        +" other side of the wall you can hear waves on the Moonsea"
        +" lapping against the shoreline.\n");         
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"well", "kuto's well"}),
        "The well is about eight feet in diameter with a wooden canopy protecting it"
        +" from overhead contaminants and any drawing water from rain or other"
        +" inclement weather. The stones comprising the well are about three feet"
        +" high.\n");
        
    add_item(({"canopy"}),
        "The canopy rises eight feet above the edge of the well and extends three"
        +" feet beyond the circle of the well itself to protect those using"
        +" the well. It is made of heavily varnished cedar posts and shingles."
        +" A crank and pulley system is suspended between each of the four"
        +" posts supporting the canopy, allowing four people to draw water at"
        +" the same time.\n"); 

    add_item(({"crank", "pulley", "system"}),
        "Hand cranks at waist height pull ropes over a pulley higher in the"
        +" canopy to raise and lower buckets into the well to draw up water.\n");  

    add_item(({"rope", "ropes"}),
        "Strong and smooth hemp rope mounted to the hand crank.\n"); 

    add_item(({"stone", "stones"}),
        "The stones are flat on top and bottom, almost like natural bricks,"
        +" and form a circumferance around the well eight feet in diameter"
        +" amd three feet high.\n");        

/*
*   Sound effects
*/

    add_room_tell("A seagull cries raucously overhead.");                 

    reset_faerun_room();
    
    add_prop(OBJ_S_SEARCH_FUN,"do_search");     
        
    add_exit(PODOL_DIR + "pp1", "northeast");     
    add_exit(PODOL_DIR + "pp2", "north");   
    add_exit(PODOL_DIR + "pp3", "northwest"); 
    add_exit(PODOL_DIR + "pp12", "east");     
    add_exit(PODOL_DIR + "pp13", "west");   
    add_exit(PODOL_DIR + "pp19", "southeast"); 
    add_exit(PODOL_DIR + "pp20", "south");     
    add_exit(PODOL_DIR + "pp21", "southwest");       
    
}

void
reset_faerun_room()
{
    ladder_found = 0;
}

void
init()
{
    ::init();
    add_action("do_climb","climb down");
}

public string
do_search(object pl, string arg)
{
    if (IN_ARRAY(arg,
        ({ "stone", 
           "stones",}) ) == 0)
    {
        return "Your search reveals nothing special.\n";
    }
    ladder_found = 1;
    return "One of the stones appears slightly dislodged. As you inspect"
        +" this stone you see faint scratch marks and below it down"
        +" the inner surface of well you can faintly discern tiny niches"
        +" that may allow you to climb down.\n";
}   

mixed
do_climb(string str)
{ 
    if(ladder_found == 0)
    {
        return "You have found nothing to climb.\n";
    }
    
    if(!strlen(str))
    {
        notify_fail("Did you want to climb down the well?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [down] [inside] [the] 'well'"))
    {
        notify_fail("Climb down what? The well?\n");
        return 0;
    }

    write("You climb down the inner surface of the well.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " climbs over the ledge"
        +" and down inside the well.\n");
    tell_room(LEDGE, QCTNAME(this_player()) + " arrives climbing down the wall of the well.\n");
    this_player()->move_living("M", LEDGE, 1, 0);
    return 1;
}
