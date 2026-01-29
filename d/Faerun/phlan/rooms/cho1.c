/*  /d/Faerun/phlan/rooms/cho1.c
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
*   adding occupant
*/

object cadorna;

/*
*   Making the basic room
*/

void
create_phlan_room()
{
    set_long("City hall office.\n"
        +"This office would almost be considered lavish in its dedoration."
        +" The large desk, though made of wood has a metallic luster. An"
        +" equally impressive chair sits behind it. A tapestry dominates the"
        +" northern wall while a series of paintings adorn the others. The"
        +" room is comfortably lit, though you can see no source of illumina"
        +"tion. A table stands to the side of the door and an elaborate"
        +" carpet covers the floor.\n");
    
    set_short("Cadorna's office");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are paneled in a rich dark-grained hardwood, possibly"
        +" oiled cherry. They are tightly fitted with no visible seams."
        +" or nails. They appear recently polished.\n");

    add_item(({"panel", "panels", "hardwood", "cherry", "grain"}),
        "The panels are highly polished, reflecting the ambient light."
        +" They are beautiful in their simplicity showing only the"
        +" intricate dark grain and no further decoration.\n");

    add_item(({"floor", "ground"}),
        "The floor is of alternating black and white marble tiles, buffed"
        +" to a high gloss that reflects the ambient light. The tiles"
        +" alternate in color forming a diamond pattern. A large carpet"
        +" covers the center of the room.\n");

    add_item(({"marble", "tile", "tiles"}),
        "The highly polished black and white marble tiles are cut into"
        +" diamonds approximately four inches on each side. They are laid"
        +" out in a alternating pattern.\n");

    add_item(({"pattern", "patterns", "echelon", "diamond"}),
        "The alternating black and white tiles create a repeating"
        +" diamond or echelon pattern that is pleasing to the eye.\n");

    add_item(({"ceiling"}),
        "The ceiling is made of the same panels as the walls. The rich"
        +" dark wood softly reflecting the ambient light.\n");
        
    add_item(({"door", "doorway"}),
        "This door is made of polished oak with a simple handle.\n");

    add_item(({"handle"}),
        "The handle is quite simple and made of bronze.\n");  

    add_item(({"desk"}),
        "The desk, easily six feet wide, gleams with a metallic luster."
        +" It must be made from bronzewood. Engraved on a placard mounted"
        +" to the front is the name Ennio Cadorna.\n");

    add_item(({"bronzewood"}),
        "Bronzewood is a hard, heavy wood known for its metallic coloring"
        +" and luster. It is favored for elegant furniture and wizard's"
        +" staves.\n");

    add_item(({"chair"}),
        "A thickly cushioned chair upholstered in soft green velvet.\n");

    add_item(({"velvet"}),
        "It is a deep green and very soft.\n");
        
    add_item(({"tapestry", "crest"}),
        "A very large and intricately woven tapestry covers the north"
        +" wall. It depicts the Cadorna family crest - a skein of red"
        +" thread and a skein of green thread on a field of deep blue.\n");

    add_item(({"paintings", "painting"}),
        "The paintings are of high quality, depecting men with a familial"
        +" resemblance. There is one blank space amidst their orderly"
        +" progression.\n");    
        
    add_item(({"blank", "space", "blank space"}),
        "Obviously a picture has been removed here. All that remains is"
        +" the date below the blank space - 1340 The Year of the Lion.\n");

    add_item(({"table"}),
        "An unobtrusive table that holds silver service for refreshments.\n");

    add_item(({"silver", "service"}),
        "There are several silver drinking vessels on the table within"
        +" easy reach of the door where a servant can fill them while"
        +" not intruding.\n");

    add_item(({"carpet"}),
        "This carpet is masterfully woven. It appears to be a product of"
        +" the Cadorna textile mills. The colors are subdued and match"
        +" the palette of the walls and floor.\n");
         

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "ch2", "south");
}

void
reset_faerun_room()
{
    ::reset_faerun_room();
    
/*
*   Occupant Cadorna
*/    
    
    if (!cadorna)
    {
        cadorna = clone_object(NPC_DIR + "cadorna");
        cadorna->move(this_object(), 1);
    }
   
}

/*
*   This will have the npc Ennio Cadorna, descendant of Porphyrys Cadorna who
*   was a corrupt politician a century ago. He will have a quest to go to
*   the Cadorna textile mill to find a long lost hidden ledger book that 
*   details all the wrongs his ancestor did so he can make amends. Before
*   this quest is offered the PC must have done the basic quests in town
*   to show some competency. 
*/
