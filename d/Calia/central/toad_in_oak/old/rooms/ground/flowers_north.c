/*
 * /d/Calia/central/toad_in_oak/rooms/ground/flowera_north.c
 *
 * This is the northern corner of the Toad-in-Oak flower garden
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
void hook_smelled(string smelled); 
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

    description = "Flowers of many varieties and shades have invaded this " + 
        "part of the forest, covering most of the ground between the " + 
        "trees. " + capitalize(describe_flowers()) + " dominate in the " + 
        "immediate area, with smaller patches of many other types mixed " + 
        "in. A small bench sits just to the north of the narrow path " + 
        "between the flowers.\n"; 

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

/*
 * Function name: hook_smelled
 * Description:   Adds smells to certain items in the room. 
 *                
 * Arguments:     str typed by the player 
 * Returns:       nothing
 */
void
hook_smelled(string smelled)
{

    switch (smelled)
    {
        case "grass":
        case "ground":

        write("The grass has a fresh, clean smell, with just a hint of " + 
            "the earth below it.\n"); 

        break;

        case "flowers":
        case "wildflowers":

        write("The scent of the flowers here is overwhelming, the smells " +
            "of the many types mingling together.\n"); 
    
        break; 

        case "tree":
        case "trees":
        case "oak":
        case "oaks":
        case "forest":
        case "trunks":

        write("The stately oaks have a distinctly wooden scent.\n"); 

        break; 

        case "branches":
        case "leaves":

        write("Unfortunately the leaf covered branches of the oaks are " + 
            "far out of the reach of even a nose as long as yours.\n"); 

        break; 

        case "bench":

        write("The bench smells a lot like the oak trees nearby.\n"); 
    }
    return; 
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
    /*  Make sure that the flowers don't change while a mortal is wandering 
        in the area.  */ 
    if (! Control_Room->count("flower_garden"))
    {
        change_flowers(4);   
    }
}

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("A sea of flowers among the trees."); 

    set_long("@@describe_room@@"); 

    change_flowers(4); 

    /*  Objects  */ 

    Bench = clone_object(BENCH); 
    Bench->move(this_object(), 1); 
    Bench->set_limit(2); 
    Bench->set_parse_string("[down] [on] [the] [short] [wooden] 'bench'");
    Bench->set_short("short wooden bench"); 
    Bench->set_long("This little bench looks as if it was grown rather " + 
        "than built. The various parts flow together seemlessly in smooth " +
        "corners rather than angles, and the legs descend beyond sight " + 
        "into the ground like small trees. The layer of brown bark that " + 
        "covers it has been smoothed somehow on the seat and back. The " + 
        "bench looks just big enough to hold two people.\n@@contents@@"); 
    Bench->set_adjectives(({"short", "wooden"})); 

    Picker = clone_object(PICKER); 
    Picker->move(this_object(), 1); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_east", 
        "southeast", 
        Bench->exit);     
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_west", 
        "south", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10", 
        "west", 
        Bench->exit); 

    /* items */ 

    add_item(({"flowers"}), 
        "Hundreds of colourfull flowers grow between the massive trunks of " +
        "the trees in this small part of the forest. Dominated by " + 
        "@@describe_flowers@@, with occasional splotches of other " + 
        "varieties, the flowers and the plants they grow on effectively " + 
        "prevent you from moving off of the narrow path.\n"); 

    add_item(({"bushes", "vines", "plants"}), 
        "The bushes, vines, and other plants are almost completely hidden " +
        "by the flowers that grow on them. They have taken over nearly " + 
        "all of the ground space left by the trees.\n"); 
    
    add_item(({"trees", "tree", "oaks", "oak", "forest", "trunks", 
        "branches", "leaves"}), 
        "Even when compared to the flowers that surround them, the oaks " +
        "of this forest are still beautiful and impressive. It would take " +
        "number of people to circle even the thinnest trunks. Far above " + 
        "you the leaves and branches of the trees for a green canopy that " +
        "blocks most of the light before it reaches this level.\n"); 

    add_item(({"paths", "path", "grass"}), 
        "The path through this area is more of an absence of flowers than " + 
        "a true path. Lush green grass has taken this small opportunity " + 
        "and filled the small space left by all of the other plants.\n"); 

}
