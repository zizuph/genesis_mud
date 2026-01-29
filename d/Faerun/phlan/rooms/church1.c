/*  /d/Faerun/phlan/rooms/church1.c
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
    set_long("Church atrium.\n"
        +"This is the atrium of the Phlan Church of Tyr The Even-Handed. It is"
        +" circular with a diameter of approximately ten feet."
        +" Warm soft light is shed from glowing orbs floating near the ceiling"
        +" that are emitting gentle music. The circular walls are draped"
        +" with royal purple wallhangings between the four doors at the"
        +" cardinal points of the compass. Two chairs and a couch stand by the"
        +" walls and a spiral staircase leads to the second floor.\n");
    
    set_short("Church of Tyr atrium");

/*
*   Decorations
*/    
        
    add_item(({"walls", "wall"}),
        "The walls are made of a translucent amethyst, darkening with depth"
        +" to the point you cannot see what comprises the outer walls."
        +" Between the four doorways hang beautiful royal purple wallhangings.\n");

    add_item(({"hangings", "wallhangings"}),
        "The wallhangings of gauzy royal purple are suspended from the ceiling"
        +" to the floor. Strangely you do not see anything supporting them.\n");

    add_item(({"floor", "ground"}),
        "The floor is covered in a thick purple carpet that stretches"
        +" from wall to wall.\n");

    add_item(({"carpet"}),
        "This carpet extends from wall to wall. It is soft enough to muffle"
        +" footsteps. It is the same royal puple as the wallhangings.\n");

    add_item(({"ceiling"}),
        "The ceiling, like the walls, is made of translucent amethyst. It"
        +" deepens and darkens as if looking into a deep pool.\n");

    add_item(({"orb", "orbs"}),
        "Transparent orbs of crystal shed a soft, warm, magical light.\n");

    add_item(({"chair", "chairs"}),
        "Two identical high-backed chairs with purple velvet cushions.\n");
        
    add_item(({"couch"}),
        "A comfortable couch that could hold three people. It has thick"
        +" cushions upholstered with purple velvet.\n");

    add_item(({"cushions", "velvet"}),
        "The cushions are six inches thick and soft. They are upholstered"
        +" in luxurious purple velvet that quickly warms at a touch.\n");

    add_item(({"staircase", "spiral staircase"}),
        "A simple wrought iron staircase a descending counter-clockwise"
        +" twist. This would make it difficult for ascending attackers to"
        +" effectively use a weapon.\n");  

/*
*   Sound effects
*/

    add_room_tell("Delicate music, orderly and patterned, evokes a sense of lawfulness."); 
    add_room_tell("The wallhangings ruffle slightly in a cross breeze through"
    +" the doorways.");    

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "road4", "north"); 
    add_exit(ROOM_DIR + "road8", "south");
    add_exit(ROOM_DIR + "road10", "east");
    add_exit(ROOM_DIR + "road6", "west");
    add_exit(ROOM_DIR + "church2", "up");
}


void
reset_faerun_room()
{
    set_searched(0);
}

/*
 * Function that allows the player to sit in the chairs or on the couch
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
        this_player()->catch_msg("You sit in one of the high-backed chairs.\n");
        say(QCTNAME(this_player()) + " sits in the high-backed chairs.\n");
        this_player()->add_prop("_sitting_in_chair", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting in one of"
        +" the high-backed chairs");
        return 1;
    }
    
    if(this_player()->query_prop("_sitting_on_couch"))
    {
        write("But you are already sitting on the couch.\n");
        return 1;
    }


    if(str == "on couch" | str == "on the couch")
    {
        this_player()->catch_msg("You sit on the comfortable couch.\n");
        say(QCTNAME(this_player()) + " sits on the comfortable couch.\n");
        this_player()->add_prop("_sitting_on_couch", 1);
        this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting on the"
        +" comfortable couch");
        return 1;
    }    


    else
    {
        this_player()->catch_msg("Would you like to sit in one of the chairs"
        +" or on the couch?\n");
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
        
        if(this_player()->query_prop("_sitting_on_couch"))
        {
            this_player()->catch_msg("You stand up from the couch.\n");
            say(QCTNAME(this_player())+" stands up from the couch.\n");
            this_player()->remove_prop("_sitting_on_couch");
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
    
    if(ob->query_prop("_sitting_on_couch"))
    {
        ob->catch_msg("You stand up from the couch before leaving.\n");
        say(QCTNAME(ob) + " stands up from the couch before "
        +"leaving the room.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_on_couch");
    }    

}

void init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
