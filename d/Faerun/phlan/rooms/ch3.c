/*  /d/Faerun/phlan/rooms/ch3.c
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
    set_long("City hall hallway.\n"
        +"The city hall interior is beautifully furnished and meticulously"
        +" maintained. Overhead a quartz crystal chandelier apparently lit"
        +" by a diffuse magical light shines warmly on the walls and floor."
        +" The walls are paneled in a rich dark-grained hardwood and the"
        +" floor is tiled and black and white marble in a diamond pattern."
        +" A stained glass window is mounted in the southern wall, playing"
        +" its colorful image on the innter wall. A doorway stands directly"
        +" to the north.\n");
    
    set_short("City hall hallway");
    
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

    add_item(({"window"}),
        "The intricate stained glass window mounted high on the"
        +" southern wall throws an image on the inner wall.\n");
        
    add_item(({"image", "scene"}),
        "Colorful riots of light from the stained glass windows play"
        +" across the inner wall. You see a scene from Phlan's past,"
        +" showing a powerful party of adventurers driving the demon"
        +" Tyranthraxus from the possessed body of a great bronze"
        +" dragon, Srossar, and freeing the area from a terrible evil.\n");

    add_item(({"door", "doorway"}),
        "This door is made of polished oak with a simple handle.\n");

    add_item(({"handle"}),
        "The handle is quite simple and made of bronze.\n");   

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "ch1", "east");
    add_exit(ROOM_DIR + "ch4", "west");
    add_exit(ROOM_DIR + "cho2", "north");
}


void
reset_faerun_room()
{
    set_searched(0);
}