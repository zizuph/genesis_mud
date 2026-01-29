/*
 * /d/Calia/central/toad_in_oak/rooms/ground/garden_flower_east.c
 *
 * This is the eastern corner of the Toad-in-Oak flower garden
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include "defs.h"
#include "../../objects/flowers.h"

#define BENCH TOAD_IN_OAK_OBJECTS + "bench.c"
#define PICKER TOAD_IN_OAK_SPECIALS + "flower_picker.c"

// GLOBAL VARIABLES

string* Current_Flowers,* Current_Colours,* Current_Adjectives;
object Bench, Picker; 

// FUNCTIONS

/*  Forward Declarations */ 
void change_flowers(int num);
string describe_flowers(); 
string describe_room();
void enter_inv(object ob, object from);
void leave_inv(object ob, object to); 
string exits_description(); 

/*  Function    change_flowers
    Purpose     Changes the flowers that will be highlighted in the room
    Arguments   Number of flowers to create. 
    Returns     Nothing */  
void
change_flowers(int num)
{
    string* possible_colours, * possible_flowers, * possible_adjectives; 
    int x;
    possible_flowers = Flowers; 
    possible_colours = Colours; 

    Current_Flowers = ({}); 
    Current_Colours = ({}); 
    Current_Adjectives = ({}); 

    for (x = 0; x < num; x ++)
    {
        if ((sizeof(possible_flowers) > 0) && (sizeof(possible_colours) > 0)) 
        {
            Current_Flowers += ({possible_flowers[random(sizeof(possible_flowers))]});
            possible_flowers -= ({Current_Flowers[x]}); 
                
            Current_Colours += ({possible_colours[random(sizeof(possible_colours))]}); 
            possible_colours -= ({Current_Colours[x]}); 
    
            possible_adjectives =  Adjectives[member_array(Current_Colours[x], Colours)];        
            Current_Adjectives += ({possible_adjectives[random(sizeof(possible_adjectives))]});
        }
    }

    return;
}

/*  Name        describe_flowers
    Purpose     describes the flowers that are being highlighted. 
    Arguments   None
    Returns     String  */ 
string
describe_flowers()
{
    int x;
    string flowers = "";

    for (x = 0; x < sizeof(Current_Flowers); x++)
    {
        if (x > 0) 
        {
            flowers += ", ";
        }

        if ( x == sizeof(Current_Flowers) - 1) 
        {
            flowers += "and "; 
        }

        flowers += Current_Adjectives[x] + " " + Current_Colours[x] + " " + 
            LANG_PWORD(Current_Flowers[x]);
    }
    
    return flowers;
}

/*  Name        describe_room
    Purpose     Describes the room
    Arguments   None
    Returns     string */ 
string
describe_room()
{
    string description; 

    description = "You stand in the middle of a sea of colours. The spaces " + 
        "between the trees in this area have been taken over by a " + 
        "multitude of flowers. "; 

    description += capitalize(describe_flowers()); 

    description += " dominate amongst many other varieties and shades. " + 
        "Small gaps between the flowers form three grassy trails leading " +
        "from here. Near the point where the three paths coverge sits a " + 
        "small wooden bench.\n"; 

    return description; 
}

/*  Name        enter_inv
    Purpose     called when an object enters the room 
    arguments   See sman
    Returns     Nothing */
void
enter_inv(object ob, object from) 
{
    ::enter_inv(ob, from); 
    if (interactive(ob) && ! ob->query_wiz_level()) 
    {
        Control_Room->register("flower_garden", ob); 
    }
}

/*  Name        leave_inv
    Purpose     Called when an object leaves the room
    Arguments   see sman
    Returns     Nothing */ 
void 
leave_inv(object ob, object to) 
{   
    

    if (interactive(ob) && ! ob->query_wiz_level())
    {   
        Bench->leave(ob); 
        Control_Room->unregister("flower_garden", ob); 
    }

    ::leave_inv(ob, to); 
}

/*  Function    exits_description
    Purpose     redefinition of base function to include the contents of the
                bench
    Arguments   None
    returns     Description of the exits from the room, plus whatevers sitting
                on the bench. 
*/
string
exits_description()
{
    return ::exits_description() + Bench->contents(this_player()); 
}
   
// ROOM DEFINITION

void 
reset_room()
{
    ::reset_room(); 
    if (! Control_Room->count("flower_garden"))
    {
        change_flowers(4);   
    }
}

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("The Toad-in-Oak flower garden"); 

    set_long("@@describe_room@@"); 

    change_flowers(4);

    Bench = clone_object(BENCH); 
    Bench->move(this_object(), 1); 
    Bench->set_limit(2); 
    Bench->set_parse_string("[down] [on] [the] [short] [wooden] 'bench'");
    Bench->set_short("short wooden bench"); 
    Bench->set_long("This small bench, about the right size for two " + 
        "people, sits in a small gap between rose bushes near the spot " + 
        "where the three paths converge. You would think it was carved " + 
        "from a single block of wood, except that it is covered in smooth " +
        "bark.\n@@contents@@"); 
    Bench->set_adjectives(({"short", "wooden"})); 

    Picker = clone_object(PICKER); 
    Picker->move(this_object(), 1); 
    
    /*  Exits  */ 
        
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_south", 
        "south", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_west", 
        "west", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_north", 
        "northwest", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_05", 
        "up", 
        Bench->exit); 

    /* items */ 

    add_item(({"flowers"}), 
        "The flowers have almost completely taken over this area of the " + 
        "forest. The bushes, vines, and other plants they grow on cover " +
        "all of the space between the trees with the exception of three " + 
        "narrow paths. In the immediate vicinity @@describe_flowers@@ " + 
        "dominate, with smaller numbers of other varieties and almost " + 
        "any colour you can imagine, as well as a few you can't.\n"); 

    add_item(({"bushes", "vines", "plants"}), 
        "The bushes, vines, and other plants merely serve as places for " + 
        "the flowers to grow and aren't very interesting to look at " + 
        "themselves.\n"); 

    add_item(({"trees", "tree", "oaks", "oak", "forest", "trunks", 
        "branches", "leaves"}), 
        "These trees are the only significant break in the ocean of " + 
        "flowers. Their trunks are as wide a small building and shoot " + 
        "straight into the sky above you. The branches high above you " + 
        "support what looks like millions of green leaves that mesh " + 
        "together to stop much of the sun's light from reaching down here.\n"); 

    add_item(({"paths", "path", "grass"}), 
        "The paths that lead away from here are nothing more than narrow " + 
        "gaps between the flowers that have been filled by soft green " + 
        "grass.\n"); 
    
//    add_item(({"bench"}), "@@describe_bench@@"); 

}

