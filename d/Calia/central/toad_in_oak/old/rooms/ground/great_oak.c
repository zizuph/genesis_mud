/*
 * /d/Calia/central/toad_in_oak/rooms/ground/great_oak.c
 *
 * This is the area on the ground around the great oak at the center 
 * of Toad-in-Oak
 * 
 * HISTORY: [99-06-17] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define STREAM TOAD_IN_OAK_OBJECTS + "stream.c"

// GLOBAL VARIABLES

object Stream; 

// FUNCTIONS

string
describe_room()
{

    string desc; 
    object player = this_player(); 
   
    if (player->query_race_name() == "elf")
    {
        desc = "You stand at the foot of what could easily be the biggest " + 
            "tree in the entire forest. This gargantuan oak dwarfs even " + 
            "the other trees of this huge forest. You feel almost as if " +
            "the tree was calling to you somehow. A small stream bends " + 
            "around the roots of the tree a few feet away, and the area " +
            "in between is covered in lush green grass.\n"; 
    }
    else
    {
        desc = "You stand in a grassy area at the south side of an oak " + 
            "that seems immense even in comparison to the other giant " + 
            "trees nearby. A small stream curves gently around the " + 
            "ground covered by the roots of the tree.\n";
    }
    
    return desc;
}


string 
describe_tree()
{
    object player = this_player(); 
    string desc; 
    
    desc = "This tree is big. Very big. Much bigger than the other trees " +
        "nearby, being nearly twice as wide and a good deal taller then " + 
        "any of the other oaks in the area. The difference in size " + 
        "has allowed some sunlight to sneak through to form a ring of " + 
        "sunlight high up on the trunk of the tree. The trunk is perfectly " + 
        "straight and stretches hundreds of feet into the air before the " +
        "lowest branches begin. The leaves of the tree form a green blob " +
        "high in the air, blocking out all but a small ring of sky. "; 

    if (player->query_race_name() == "elf")
    {
        desc += "You can tell that there is something special about this " + 
            "tree, but you can't quite pinpoint what it is. It feels as if " +
            "life itself is concentrated in tis tree somehow. ";
    }

    desc += "\n"; 

    return desc;
}

/*  Function    hug_tree
    Purpose     gives a silly remark when somebody hugs the Great Oak
    Arguments   command entered
    returns     success
*/
int
hug_tree(string command)
{
    object player;    
    int success = 0;

    if (command && (parse_command(command, this_object(), 
        "[giant] [oak] [huge] 'tree'") || parse_command(command, this_object(), 
        "[giant] [huge] [great] 'oak'")))  
    {
        success = 1; 
        player = this_player(); 
    
        if (player->query_race_name() == "elf")
        {
            write("As you try to put your arms around the tree you can " + 
                "feel the life of this tree, and all of the others nearby " + 
                "as well.\n"); 
            say(QCTNAME(player) + " gives a demonstration of why some " + 
                "people call elves 'tree-huggers'.\n");
        }
        else
        {
            write("You feel rather silly hugging a tree that's many times " +
                "wider than your arms can stretch.\n"); 
            say(QCTNAME(player) + " looks rather silly trying to hug the " + 
                "giant tree.\n"); 
        }
    }

    return success;
}
                
// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("At the base of a giant oak."); 

    set_long("@@describe_room@@"); 

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_BEACH); /*   Not a true beach, but 
                                            next to a stream. */ 
    add_prop(OBJ_I_CONTAIN_WATER, -1); /*   Infinite water due to the                                            stream */ 

    /* Obejects */ 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("The clean blue stream takes a wide turn around the base of the " + 
        "giant tree, forming a small grassy point here.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling", "blue"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /*  Exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10", "northeast"); 

    /* items */ 

    add_item(({"grass", "ground"}), "The grass here is a healthy green " + 
        "and fills in all of the spaces left on the ground between the " + 
        "roots of the giant tree.\n"); 

    add_item(({"trees", "forest"}), "All of the trees you can see from " + 
        "here are enormous, but none of them compare to the one right " + 
        "in front of you.\n");  

    add_item(({"roots"}), "The roots of the giant oak can be seen poking " + 
        "out of the ground for a good distance from the trunk. A few of " + 
        "them are nearly as big around as the biggest branches of the " + 
        "\"lesser\" trees of the forest. They seem to be doing a good job " + 
        "of holding the ground together and diverting the stream.\n"); 

    add_item(({"tree", "oak", "giant tree", "giant oak", "great oak",
        "leaves", "branches", "bark", "limbs"}), 
        "@@describe_tree@@"); 

    set_tell_time(150); 

    add_tell("The stream babbles as it flows past you.\n"); 
    add_tell("A loud \"Gronk!\" sounds from above.\n");         
    add_tell("A loud \"Gronk!\" sounds from above.\n"); 
    add_tell("A loud \"Gronk!\" sounds from above.\n"); 
    add_tell("A loud \"Gronk!\" sounds from above.\n"); 
    add_tell("A loud \"Gronk!\" sounds from above.\n"); 

}
