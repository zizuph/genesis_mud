/*  /d/Faerun/phlan/rooms/cho2.c
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
    set_long("City hall office.\n"
        +"This office is spartan and efficient. It obviously belongs to a"
        +" person of military background. A small desk with neatly stacked"
        +" papers is the only furniture. A large window with navy blue"
        +" curtains is centered in the north wall. The other walls are"
        +" bare. No carpet adorns the floor.\n");
    
    set_short("Van Horn's office");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are paneled in a rich dark-grained hardwood, possibly"
        +" oiled cherry. They are tightly fitted with no visible seams."
        +" or nails. They appear recently polished.\n");

    add_item(({"panel", "panels", "hardwood", "cherry", "grain"}),
        "The panels are highly polished, reflecting the light entering"
        +" through the window. They are beautiful in their simplicity"
        +" showing only the intricate dark grain and no further"
        +" decoration.\n");

    add_item(({"floor", "ground"}),
        "The floor is of alternating black and white marble tiles, buffed"
        +" to a high gloss that reflects the light entering through the"
        +" window. The tiles alternate in color forming a diamond pattern.\n");

    add_item(({"marble", "tile", "tiles"}),
        "The highly polished black and white marble tiles are cut into"
        +" diamonds approximately four inches on each side. They are laid"
        +" out in a alternating pattern.\n");

    add_item(({"pattern", "patterns", "echelon", "diamond"}),
        "The alternating black and white tiles create a repeating"
        +" diamond or echelon pattern that is pleasing to the eye.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same panels as the walls. The rich"
        +" dark wood softly reflecting the light entering the window.\n");
        
    add_item(({"door", "doorway"}),
        "This door is made of polished oak with a simple handle.\n");

    add_item(({"handle"}),
        "The handle is quite simple and made of bronze.\n");  

    add_item(({"desk"}),
        "The desk, barely four feet wide, is made of plain maple."
        +" There are neatly organized piles of papers on it.\n");

    add_item(({"piles", "papers"}),
        "These papers seem to document the normal financial operations of"
        +" the town.\n");

    add_item(({"chair"}),
        "The chair is simple, sturdy, and looks somewhat uncomfortable.\n");
        
    add_item(({"window", "windows"}),
        "A large window looking northward from the city. You can make out"
        +" the Stojanow River, the mansions beyond and the Quivering Forest"
        +" far off in the distance.\n");

    add_item(({"curtain", "curtains"}),
        "The curtains are thick and navy blue in color. They would block"
        +" out all external life if drawn closed.\n");   
        
    add_item(({"river", "stojanow river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"mansion", "mansions"}),
        "The mansions of Phlan have been rebuilt over the years from their"
        +" sad state of disrepair a century ago.\n");

    add_item(({"forest", "quivering forest"}),
        "The Quivering Forest, far off to the north, is a verdant green"
        +" sea of trees stretching to the horizon.\n");
         

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "ch3", "south");
}

/*
*   This is the office of Daari Van Horn. She is the leader of the local troops
*   and will have several quests for the PC, including sabotaging the siege
*   equipment in the orc camp of Thar and making a report on recovered stolen
*   items hidden in a series of rooms inside the well at Kuto's Well.
*/


void
reset_faerun_room()
{
    set_searched(0);
}