/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/green_nw.c
 *
 * The northwestern portion of the TiO village green. 
 * 
 * HISTORY: 2003-05-11 Created by Kcirderf
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES

object *Bench = ({}); 
int Limit = 3; 

// FORWARD FUNCTION DEFINITIONS

string bench_contents(); 
int bench_sit(string command); 
int bench_stand(string command); 

// FUNCTIONS

/* 
    Name        bench_contents
    Purpose     Creates a list of people sitting on the bench
    Arguements  None
    Returns     string with the list
*/ 
string
bench_contents()
{
    string *contents = ({}); 
    string description = ""; 
    string verb = "are"; 
    object player = this_player(); 
    int pos; 

    if (sizeof(Bench))
    {
        contents = Bench->query_art_name(player); 

        pos = member_array(player, Bench); 

        if (pos >= 0)
        {
            contents[pos] = "you"; 
        } 

        if (sizeof(contents) == 1 && contents[0] != "you")
        {
            verb = "is"; 
        }
        
        description = capitalize(COMPOSITE_WORDS(contents)) + " " + verb + 
            " sitting on the bench."; 
    }
    return description; 
}

        
/*  
    Name        bench_sit
    Purpose     Makes a player sit on the bench 
    Arguments   Command the player typed
    Returns     integer indicating success 
*/ 
int
bench_sit(string command)
{
    object player = this_player(); 
    int success = 1; 

    if (member_array(player, Bench) == -1)
    {
        if (!command || parse_command(command, this_object(), 
            "[down] [on] [the] [short] [wooden] 'bench'")) 
        {
            if (sizeof(Bench) < Limit) 
            {
                write("You sit down on the bench.\n"); 
                say(QCTNAME(player) + " sits down on the bench.\n"); 

                /*  Add the player to the array of bench contents  */ 
                Bench += ({player}); 
    
                /*  This makes certain that the player does not appear in the 
                    normal inventory  of the room*/
                player->set_no_show_composite(1); 
            }
            else
            {
                notify_fail("There is no more room on the bench.\n"); 
                success = 0; 
            }
        }
        else
        {
            notify_fail("Sit where?\n"); 
            success = 0;
        }
    }
    else
    {
        write("You're already sitting on the bench.\n"); 
        success = 0;
    }
    
    return success; 
}

/*
    Name        bench_stand
    Purpose     Makes a player on the bench stand up
    Arguments   command given by the player
    Returns     Integer indicating success
*/ 
int
bench_stand(string command)
{
    object player = this_player(); 
    int success = 1; 

    if (member_array(player, Bench) >=0) 
    {   
        if (!command || command == "up")
        {
            write("You stand up.\n"); 
            say(QCTNAME(player) + " stands up.\n"); 
            
            Bench -= ({player}); 

            player->unset_no_show_composite(); 
        }
        else
        {
            success = 0; 
        }
    }
    else
    {
        notify_fail("You're not sitting down.\n"); 
        success = 0; 
    }
    
    return success; 
}
    
// ROOM DEFINITION

void
create_tio_ground_room()
{
    set_short("In a large clearing in the forest."); 
    set_long("You stand in a large grass filled clearing amidst the " + 
        "forest of enormous oak trees. Along the edge of the clearing " + 
        "there is a short wooden bench, and in the very center there is " +
        "an unusual looking gazebo. A short way into the forest on the " + 
        "western side of the clearing a tangled mass of brush blocks " + 
        "seperates you from the greater forest. Across the clearing to " + 
        "the east you can see a stream making it's way through the " + 
        "trees. In the branches high above you you can see the underside " +
        "of a village.\n"); 

    add_prop(OBJ_I_LIGHT, 2); // In a clearing, so more light gets through.

    add_item(({"bench", "wooden bench", "short bench", 
        "short wooden bench"}), 
        "The bench appears to have been made out of a single piece of " + 
        "wood. It has no real legs, but simply rises out of the ground " + 
        "at either end and flattens out into a seat in the middle, and " + 
        "curves upwards to form a back. The entire thing is covered in " + 
        "bark identical to that of the nearby trees. @@bench_contents@@\n"); 

    add_item(({"legs", "ends"}), "The bench has no real legs, but simply " +
        "a continuation of the seat that curves downward into the ground. " + 
        "Both ends appear to go several inches into the ground at least\n");

    add_item(({"seat"}), "The seat of the bench is simply a flat section " + 
        "of wood a ways off the ground.\n"); 
   
    add_item(({"back"}), "The back of the bench simply curves out of the " +
        "seat, and appears to be made from the same piece of wood.\n"); 

    add_item(Grass_Words, grass_describe(({"north"})));
    add_item(Stream_Words, stream_describe());  
    add_item(Thicket_Words, thicket_describe("west")); 
    add_item(Tree_Words, trees_describe(1, "northeast")); 
    add_item(Village_Words, village_describe()); 
    add_item(Gazebo_Words, "@@gazebo_describe@@"); 

    thicket_tells();

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw", "south"); 

}

void
init()
{
    ::init(); 

    add_action(bench_stand, "stand"); 
    add_action(bench_sit, "sit"); 

    return;
}


void
hook_smelled(string smelled)
{
    if (member_array(smelled, ({"bench", "short bench", "wooden bench", 
        "short wooden bench", "legs", "ends", "seat", "back"})) >= 0 ) 
    {
        write("The bridge smells just the same as the nearby trees, like " + 
            "a perfectly healthy oak,\n"); 
    }    
    else
    {
        common_smells(smelled); 
    }
}

void 
leave_inv(object ob, object to) 
{   
    if (member_array(ob, Bench) >= 0)
    {
        write("You stand up.\n"); 
 
        tell_room(this_object(), QCTNAME(ob) + " stands up.\n", 0, ob); 
            
        Bench -= ({ob}); 

        ob->unset_no_show_composite(); 
    }                

    ::leave_inv(ob, to); 
}


string
exits_description()
{
    string description = ""; 

    if (sizeof(Bench) > 0) 
    {
        description = bench_contents() + "\n"; 
    }

    return description + ::exits_description(); 
}
