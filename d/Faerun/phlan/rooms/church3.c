/*  /d/Faerun/phlan/rooms/church3.c
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
    set_long("Church of Tyr upper foyer.\n"
        +"This is the waiting room to see the bishop through the eastern"
        +" door or go to the confessional to the west. The walls are white,"
        +" as are the carpet and ceiling. Orbs floating near the ceiling glow"
        +" with an inner light. The north and south walls each bear the emblem"
        +" of Tyr The Even-Handed. A comfortable looking chair is the only piece"
        +" of furniture here. A spiral staircase leads down to the"
        +" second floor.\n");
    
    set_short("Upper foyer");

/*
*   Decorations
*/     
        
    add_item(({"walls", "wall"}),
        "The walls are of pure white alabaster. Doors leade east and west,"
        +" while the north and south bear the emblem of Tyr skillfully emblazoned"
        +" on their reflective surface.\n");

    add_item(({"alabaster"}),
        "The pure white alabaster is polished to a mirror-like shine. It reflects"
        +" the soft light of the floating orbs.\n");

    add_item(({"floor", "ground"}),
        "The floor is covered in a thick white carpet that stretches"
        +" from wall to wall.\n");

    add_item(({"carpet"}),
        "This carpet extends from wall to wall. It is soft enough to muffle"
        +" footsteps. It is the same pure white as the alabaster walls and"
        +" is absolutely spotless.\n");

    add_item(({"ceiling"}),
        "The ceiling, like the walls, is made of polished alabaster. It"
        +" reflects the light of the floating orbs.\n");

    add_item(({"orb", "orbs"}),
        "Transparent orbs of crystal shed a soft, warm, magical light.\n");

    add_item(({"emblem", "emblems"}),
        "The emblem of Tyr is a warhammer standing upright on its handle"
        +" with the balance of law atop. It is emblazoned in shiny black"
        +" enamel by a master artisan.\n");
        
    add_item(({"chair", "furniture"}),
        "The chair has overstuffed cushions and is upholstered in white"
        +" velvet.\n");

    add_item(({"cushions"}),
        "The cushions are thick and soft. They are covered in white velvet.\n");
        
    add_item(({"velvet"}),
        "The deep velvet is soft and luxurious.\n"); 
        
    add_item(({"door", "doors"}),
        "Which door do you wish to look at? The eastern door or western door?\n");

    add_item(({"eastern door"}),
        "The eastern door is ebony black. The name Bishop Tulloch is painted"
        +" with gold leaf.\n");

    add_item(({"western door"}),
        "The western door is alabaster white. It leads to the confessional.\n");           

    add_item(({"staircase", "spiral staircase"}),
        "A simple wrought iron staircase a descending counter-clockwise"
        +" twist. This would make it difficult for ascending attackers to"
        +" effectively use a weapon.\n"); 

/*   
*    There will be opening and closing doors. A key from the bishop will be needed
*    to open the western door.  
*
*/     

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "church2", "down"); 
    add_exit(ROOM_DIR + "church4", "east");
    add_exit(ROOM_DIR + "church5", "west");   
}


void
reset_faerun_room()
{
    set_searched(0);
}

/*
 * Function that allows the player to sit in the chair
 */
 
int action_sit(string str)
{
    if(this_player()->query_prop("_sitting_in_chair"))
    {
        write("But you are already sitting in the chair.\n");
        return 1;
    }


    if(str == "in chair" | str == "in the chair"
    | str == "on chair" | str == "on the chair")
    {
        this_player()->catch_msg("You sit in the overstuffed white chair.\n");
        say(QCTNAME(this_player()) + " sits in the overstuffed white chair.\n");
        this_player()->add_prop("_sitting_in_chair", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting in the"
        +" overstuffed white chair");
        return 1;
    }


    else
    {
        this_player()->catch_msg("Would you like to sit in the chair?\n");
        return 1;
    }

    return 1;
}


/*
 * Function that allows the player to stand up
 */
 
int
action_stand(string str)
{
    if(str == "up" | str == "stand"
    | str == "stand up")
    {
        if(this_player()->query_prop("_sitting_in_chair"))
        {
            this_player()->catch_msg("You stand up from the chair.\n");
            say(QCTNAME(this_player())+" stands up from the chair.\n");
            this_player()->remove_prop("_sitting_in_chair");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }

    }

    else
    {
        this_player()->catch_msg("Stand up?\n");
        return 1;
    }

    return 1;
}


/*
 * Function to cleanup props if a player leaves before standing
 */

void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_in_chair"))
    {
        ob->catch_msg("You stand up from the chair before leaving.\n");
        say(QCTNAME(ob) + " stands up from the chair before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_in_chair");
    }

}

void init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
