/*
    /d/Calia/argos/nowhere/rooms/outside/road_02.c
   
    Part of the road in Nowhere
  
    HISTORY: 2003-07-13 Created by Kcirderf
  
    Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Calia/argos/nowhere/rooms/outside/baseroom_outside.c";

// FUNCTIONS

/*
    Name:           hook_smelled
    Purpose:        Adds smells to certain items in the room.                 
    Arguments:      str typed by the player 
    Returns:        nothing
 */
void
hook_smelled(string smelled)
{

    if (member_array(smelled, ({"hut", "wooden hut", "walls", 
        "roof", "planks", "wood"})) >= 0) 
    {
        write("The wood of the hut and sign smells faintly of " + 
            "rot.\n");
    }
    else if (member_array(smelled, ({"tree", "lemon tree", 
        "small tree", "small lemon tree", "trunk", "bark"}))
        >= 0) 
    {
        write("The tree smells rather wooden, with just a hint " +
            "of lemon.\n"); 
    }
    else if (member_array(smelled, ({"branches", "leaves"})) >= 0)
    {
        write("The branches and leaves of the tree smell quite " + 
            "lemony.\n"); 
    }
    else if (member_array(smelled, ({"lemons"})) >= 0) 
    {
        write("The lemons smell lemony fresh.\n"); 
    }    
}

/*
    Name:       pick_lemon
    Purpose:    Allows players to pick lemons from the tree
    Arguments:  string that the player typed.
    Returns:    0/1 depending on success
*/
int
pick_lemon(string input)
{
    object player = this_player(), 
                    lemon; 
    int success = 0; 
    string target; 

    notify_fail("Pick what?\n"); 

    if (input) 
    {
        if (parse_command(input, this_object(), "[a] [ripe] %s", target))
        {
            if( target == "lemon")
            {
                lemon = clone_object(NOWHERE_OBJECTS + "lemon"); 

                if (lemon->move(player))
                {
                    write("You can't carry anything more, and " + 
                        "drop the lemon on the ground.\n"); 
                    tell_room(this_object(), 
                        QCTNAME(player) + " picks a lemon from " + 
                        "tree and drops it on the ground.\n", player);                     
                    lemon->move(this_object()); 
                }
                else
                {
                    write("You pick a lemon from the tree.\n"); 
                    tell_room(this_object(), QCTNAME(player) + 
                        " picks a lemon from the tree.\n", player); 
                }
            
                success = 1; 
            }
        }
    }
    return success;
}
// ROOM DEFINITION

void 
create_nowhere_outside_room()
{
    set_short("A road through a small village."); 
    set_long("You stand on a stone road that runs through this " + 
        "small cliffside village. There are a number of low " + 
        "stone houses around you, and a dilapidated wooden hut " + 
        "to the west. Off to one side of the road stands a small " + 
        "lemon tree.\n"); 

    add_item(({"hut", "wooden hut", "walls", "roof"}),
        "It looks as if it were constructed in a hurry and then " +
        "ignored for several years. The walls and the roof are " + 
        "rotting wooden planks fastened together with rusted " + 
        "nails. There does not appear to be any way into the " + 
        "hut on this side.\n");

    add_item(({"planks", "wood"}), 
        "The wooden planks that make up the hut are old, rotting, " + 
        "and in some cases broken.\n"); 

    add_item(({"nails"}), 
        "These old rusted nails are barely holding together the " + 
        "rotten wood of the hut.\n"); 

    add_item(({"tree", "lemon tree", "small tree", 
        "small lemon tree"}), 
        "This appears to be a normal lemon tree, though not a " + 
        "particularly tall one. It has a trunk, branches, and " + 
        "lots of green leaves, as well as lemons in various " + 
        "stages of ripeness.\n"); 

    add_item(({"trunk"}), 
        "The trunk of the lemon tree grows straight up for a few " +
        "feet before splitting off into several smaller " + 
        "branches.\n"); 

    add_item(({"bark"}), 
        "The bark covering the trunk and branches of the lemon " + 
        "tree is rough and brown.\n"); 
    
    add_item(({"branches"}), 
        "The trunk of the lemon tree splits into a number of " + 
        "branches, which split into smaller branches. They " + 
        "support a multitude of green leaves and a number of " + 
        "yellow lemons.\n"); 

    add_item(({"leaves", "green leaves"}), 
        "The leaves covering the lemon tree are various shades " + 
        "of bright green, contrasting nicely with the yellow " + 
        "of the lemons.\n"); 

    add_item(({"lemons"}), 
        "There are a number of lemons on the tree at various " + 
        "stages of ripeness. There are a few that look perfect " + 
        "on the lower branches of the tree.\n"); 

    add_item(Cliff_Words, describe_cliff()); 
    add_item(House_Words, describe_houses()); 
    add_item(Road_Words, describe_road(({"north", "south"}))); 
    add_item(Village_Words, describe_village());     

    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_03", "north"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_01", "southwest"); 

}

/*
 * Function name: init
 * Description:   Initialize the room
 * Arguments:     none
 * Returns:       none
 */
void 
init() 
{
    ::init(); 
    
    add_action(pick_lemon , "pick") ; 
}
