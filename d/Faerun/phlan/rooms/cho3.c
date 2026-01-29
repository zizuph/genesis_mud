/*  /d/Faerun/phlan/rooms/cho3.c
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
        +"This office does not seem to see much use. It is still kept spotless"
        +"ly clean, but just does not have a lived in feel. A desk with a purple"
        +" cloth covering it is the main piece of furniture. A stuffed chair of"
        +" purple and blue sits behind it. The floor is covered by a thick wall"
        +" to wall carpet. The south and west walls are unadorned panels."
        +" The northern wall is dominated by a large window, while the east"
        +" wall has the doorway out.\n");
    
    set_short("Tulloch's office");
 
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
        "The floor is covered by a wall to wall carpet.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same panels as the walls. The rich"
        +" dark wood softly reflecting the light entering the window.\n");
        
    add_item(({"door", "doorway"}),
        "This door is made of polished oak with a simple handle.\n");

    add_item(({"handle"}),
        "The handle is quite simple and made of bronze.\n");  

    add_item(({"desk"}),
        "The desk is about five feet wide. It is covered with a smooth"
        +" purple cloth. Two items sit on the desk: a silver scale and"
        +" a pair of silk gloves.\n");

    add_item(({"cloth"}),
        "The cloth has a close, tight weave. It is a deep royal purple"
        +" in color and looks as if it would be equally at home on"
        +" a religious altar.\n");

    add_item(({"chair"}),
        "The chair has soft cushions and is upholstered in royal purple"
        +" and turquoise blue.\n");
        
    add_item(({"cushion", "cushions"}),
        "The cushions are thick and look comfortable. They are upho"
        +"lstered in royal purple and turquoise blue.\n");
        
    add_item(({"window", "windows"}),
        "A large window looking northward from the city. You can make out"
        +" the Barren River, the mansions beyond and the Quivering Forest"
        +" far off in the distance.\n");

    add_item(({"river", "barren river"}),
        "The Stojanow River flows from the west, emptying into the Moonsea"
        +" north of Phlan.\n");

    add_item(({"mansion", "mansions"}),
        "The mansions of Phlan have been rebuilt over the years from their"
        +" sad state of disrepair a century ago.\n");

    add_item(({"forest", "quivering forest"}),
        "The Quivering Forest, far off to the north, is a verdant green"
        +" sea of trees stretching to the horizon.\n");
        
    add_item(({"gloves"}),
        "A pair of gloves, the left is of white silk and the right is"
        +" black silk.\n");

    add_item(({"scale", "fulcrum", "bar", "plates"}),
        "The scale is of unblemished silver with a central fulcrum and"
        +" bar and two suspended plates.\n");  

    add_item(({"weights"}),
        "There is a small set of weights, all the same size, half with"
        +" black enamel and the other half with white.\n");

    add_item(({"carpet", "balance", "hammer"}),
        "The wall to wall carpet covers the floor totally. It is royal"
        +" purple with an elaborate balance atop a hammer. Below are"
        +" embroidered Tyr The Even-Handed.\n");
         

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "ch4", "east");
}

/*
*   This is the office of Bishop Tulloch. He is not here as he resides in
*   the church. There will be a holy book in the desk that he will send
*   PC's to retrieve as a small quest as part of a series of escalating
*   quests culminating in finishing the job of putting down a vampire that
*   was not properly killed a century ago in Valhingen Graveyard.
*/

void
reset_faerun_room()
{
    set_searched(0);
}