/*  /d/Faerun/phlan/rooms/ch1.c
*
*   By Tharizdun, 2021
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_PHLAN_INDOOR;

/*
*   Making the basic room
*/

void
create_phlan_room()
{
    set_long("City hall entrance.\n"
        +"The city hall interior is beautifully furnished and meticulously"
        +" maintained. Overhead a quartz crystal chandelier apparently lit"
        +" by a diffuse magical light shines warmly on the walls and floor."
        +" The walls are paneled in a rich dark-grained hardwood and the"
        +" floor is tiled and black and white marble in a diamond pattern."
        +" Stained glass windows are spaced along the southern wall, playing"
        +" their colorful images on the innter walls. The entrance stands"
        +" directly to the south.\n");
    
    set_short("City hall entrance");
    
/*
*   Decorations
*/    
    
        
    add_item(({"walls", "wall"}),
        "The walls are paneled in a rich dark-grained hardwood, possibly"
        +" oiled cherry. They are tightly fitted with no visible seams."
        +" or nails. They appear recently polished.\n");

    add_item(({"panel", "panels", "hardwood", "cherry", "grain"}),
        "The panels are highly polished, reflecting the light from the"
        +" chandelier. They are beautiful in their simplicity showing"
        +" only the beautiful dark grain and no further decoration.\n");

    add_item(({"floor", "ground"}),
        "The floor is of alternating black and white marble tiles, buffed"
        +" to a high gloss that reflects the light of the chandelier."
        +" The tiles alternate in color forming a diamond pattern.\n");

    add_item(({"marble", "tile", "tiles"}),
        "The highly polished black and white marble tiles are cut into"
        +" diamonds approximately four inches on each side. They are laid"
        +" out in a alternating pattern.\n");

    add_item(({"pattern", "patterns", "echelon", "diamond"}),
        "The alternating black and white tiles create a repeating"
        +" diamond or echelon pattern that is pleasing to the eye.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same panels as the walls. The rich"
        +" dark wood softly reflecting the light of the chandelier.\n");

    add_item(({"chandelier", "quartz", "crystal", "crystal chandelier"}),
        "This dazzling chandelier is truly a work of art. Exquisitely"
        +" cut quartz crystals seem to be lit by a warm inner magic"
        +" refracting the light in a subtle diffuse glow.\n");

    add_item(({"window", "windows", "scenes"}),
        "Intricate stained glass windows along the southern wall play"
        +" colorful images on the inner wall. From where you stand you"
        +" cannot make out the exact scenes of any of the windows.\n");
        
    add_item(({"image", "images"}),
        "Colorful riots of light from the stained glass windows play"
        +" across the inner wall.\n");

    add_item(({"entrance"}),
        "The entrance stands close to ten feet tall with heavy oaken doors."
        +" There are no visible hingles or handles on this side.\n");

    add_item(({"door", "doors"}),
        "The doors are made of stout oak. Though primarily decorative, "
        +"you know they could withstand the axe blows of twenty orcs.\n");    

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "road2", "south");
    add_exit(ROOM_DIR + "ch2", "east");
    add_exit(ROOM_DIR + "ch3", "west");
}


void
reset_faerun_room()
{
    set_searched(0);
}