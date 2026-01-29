/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 * Added by Nerull 2018
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;


void
create_mere()
{
    set_short("You are somewhere deep in the Mere of Dead Men");
    
    set_extraline("You are "
    +"on the path from the nearby storehouse. In the distance you see a "
    +"small tunnel leading to an unknown area. It is hard to make your way to it "
    +"because of the tall, ridig, and stiff grass and the thick mud your feet seeps into. "
    +"Screeches of some type come from the distance, but you can not identify the faint sounds. "
    +"the longer you stay here, the worse the smell in the mere gets.\n");
    
    add_item(({"path", "trail"}),
    "The path leads from the storehouse nearby, it would be wise to stay on it. "
    +"It seems to wade through the tall grass and thick mud making it hard to see. "
    +"Obvious parts of the path have been covered in sticks and mud in an attempt to hide it.\n");
    
    add_item(({"storehouse"}),
    "The storehouse is old and missing a few bricks from it's wall. "
    +"it is quite strange that it's out here in the fairly empty mere.\n");
    
    add_item(({"tunnel"}),
    "You see a large and dark tunnel. "
    +"The tunnel leads further into the mere and has a more rancid smell "
    +"coming from it and assaulting your senses.\n");
    
    add_item(({"ground", "grass", "mud", "tall grass"}),
    "The grass is tall and blocks most of your view and makes it harder to navigate "
    +"this area. The mud grabs at your legs like a strong grip from a hand. "
    +"You really hope there isn't anything dangerous under this deep mud, "
    +"it'll be a task to get away from. \n");
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "1", "south");
}


public void
init()
{
    ::init();
}

void
reset_faerun_room()
{

}