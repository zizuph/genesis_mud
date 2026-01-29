/* 
    /d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c
    
    This is the baseroom that will be inherited by all rooms on the 
    ground level of Toad-in-Oak, and provides common functions and 
    properties.

    HISTORY: 2003-08-18 Created by Kcirderf (Based on earlier version)
                
    Copyright: Sean Dunphy (Kcirderf) 2003                    
*/ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Calia/central/toad_in_oak/rooms/baseroom.c"; 

// GLOBAL VARIABLES

string* Gazebo_Words = ({"gazebo", "platfrom", "stairs", "stump", 
        "trunks", "trunk"});
string* Grass_Words = ({"grass", "ground", "path", "trail"}); 
string* Hill_Words = ({"hill"}); 
string* Pond_Words = ({"pond", "water"}); 
string* Stream_Words = ({"stream", "water", "clear water"}); 
string* Swim_Words = ({"pool"}); 
string* Thicket_Words = ({"vegetation", "thicket", "shrubs", "vines", 
        "thorns", "wall"}); 
string* Tree_Words = ({"trees", "tree", "oaks", "forest"}); 
string* Village_Words = ({"village", "walkways", "walkway"}); 

// FORWARD FUNCTION DECLARATIONS

void common_smells(string smelled); 
void common_tells(); 
string gazebo_contents(); 
string gazebo_describe(); 
string grass_describe(string *directions);
string hill_describe(); 
string pond_contents(); 
string pond_describe();
void pond_tells(); 
string stream_describe(); 
void stream_tells(); 
string swim_contents(); 
string swim_describe(); 
string thicket_describe(string direction); 
void thicket_tells(); 
string trail_describe(string uphill, string downhill); 
string trees_describe(int great_oak, string direction); 
string village_describe();

// FUNCTIONS

/*  
    Name        common_smells()
    Purpose     Provide smells of common items to the room. This should be 
                called from hook_smelled in individual rooms. 
    Arguments   string smelled - the item the player smelled. 
    Returns     String with the smell
*/ 
void
common_smells(string smelled) 
{

    /* Check if smelled is in each of the arrays of words for each of the
        common items and write the message for the first one found. */ 
    if (member_array(smelled, Gazebo_Words) >= 0) 
    {
        write("The gazebo smells like a perfectly healthy oak tree.\n"); 
    }
    else if (member_array(smelled, Grass_Words) >= 0)
    {
        write("The grass smells rather grassy.\n"); 
    }
    else if (member_array(smelled, Pond_Words) >= 0) 
    {
        write("The pond smells a little of the animals and plants living " + 
            "in it.\n"); 
    }
    else if (member_array(smelled, Stream_Words) >= 0) 
    {
        write("The water of the stream does not smell much at all, which " +
            "means that it is likely very clean.\n"); 
    }
    else if (member_array(smelled, Swim_Words) >= 0) 
    {
        write("If the pool has any smell, it's too faint to detect from " + 
            "this distance.\n"); 
    }
    else if (member_array(smelled, Thicket_Words) >= 0) 
    {
        write("The thicket smells of wood and leaves.\n"); 
    }
    else if (member_array(smelled, Tree_Words) >= 0 ) 
    {
        write("The trees here smell like typical oaks.\n"); 
    }
    else if (member_array(smelled, Village_Words) >= 0) 
    {
        write("The village is too far above you to smell.\n"); 
    }
}

/*
    Name:       common_tells(); 
    Purpose:    add tells that should be included in all ground rooms.
    Arguments:  None
    Returns:    Nothing
*/ 
void 
common_tells()
{
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("The singing of a songbird sounds from somewhere " + 
        "in the distance.\n"); 
    add_tell("A squirrel scampers across your path.\n"); 
    add_tell("A hawk screeches high above.\n"); 
}

/*  
    Name:       gazebo_contents(); 
    Purpose:    Describe what's currently in the gazebo
    Arguments:  None
    Returns:    string describing the contents 
*/
string
gazebo_contents()
{
    object gazebo = find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 
    object *living_things; 
    string contents = ""; 

    /* Check if the gazebo room has been loaded. */ 
    if (gazebo == 0) 
    {
        /*  It hasn't been loaded, so force it now and 
            find the object again */
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 
        gazebo = find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 
    }
    
    /*  Check again if the gazebo has been loaded. If it hasn't now
        something is really wrong. */ 
    if (gazebo != 0) 
    {
        /*  Get an array of all living things in the gazebo */ 
        living_things = FILTER_LIVE(all_inventory(gazebo)); 

        /*  If there are livings there, create a line to add to the
            gazebo description including them. */ 
        if (sizeof(living_things)) 
        {
            contents = " You can see " + COMPOSITE_ALL_LIVE(living_things) + 
                " inside the gazebo."; 
        }
    }
    else
    {
        contents = " Err... Something is wrong here. Please file a bug report."; 
    }

    return contents; 
}



/* 
    Name:       gazebo_describe
    Purpose:    Describes the gazebo from the outside, including any 
                livings inside. 
    Arguments:  None
    Returns:    The description
*/ 
string
gazebo_describe()
{
    return "This gazebo looks as if it was grown rather than " +
        "built. Further, it appears to be a single tree, with several " + 
        "\"trunks\" growing from a stump-like base, and joining into a " + 
        "single massive trunk some distance above you. There are even a " +
        "couple of stairs leading up to the platform which is about a " + 
        "foot above the ground." + gazebo_contents() + "\n"; 
}


/* 
    Name:       grass_describe
    Purpose     Describe the grass in most ground rooms, including
                a faint path if provided with directions. 
    Arguments   An array of directions the path leads in 
    Returns     The description
*/ 
string
grass_describe(string *directions)
{
    string description;
    int x;

    /* Basic description of the grass */ 
    description = "The ground here is covered by a thick carpet of " + 
        "green grass that feels springy beneath your step. Covered " + 
        "in ever shifting shadows the grass appears to be quite " + 
        "healthy despite the low light.";

    /* Check if there is a visible path from here. */ 
    if (sizeof(directions) >0) 
    {
        description += " A faint path leads off to the "; 
    
        if( sizeof(directions) == 1) 
        {
            /* Only one direction, so just add it. */ 
            description += directions[0]; 
        }
        else if (sizeof(directions) == 2)
        {
            /* Two directions need an and but no comma. */ 
            description += directions[0] + " and " + directions[1];
        }
        else
        {
            /* More than two have to be listed */ 
            for (x=0; x < sizeof(directions) - 1; x++) 
            {
                description += directions[x] + ", "; 
            }
            
            description += "and " + directions[sizeof(directions) -1]; 
        }
        description += "."; 
    }

    description += "\n"; 
    
    return description; 
}

/* 
    Name        hill_describe
    Purpose     Provides a very basic description of the hill on the east
                side of the village.
    Arguments   None
    Returns     Description
*/ 
string
hill_describe()
{
    return "The hill looks very much like the rest of the forest, a lot " + 
        "of trees with grass growing between them. The only major " + 
        "difference is that it is sloped upward rather than lying flat.\n"; 
}
       
/* 
    Name        pond_contents
    Purpose     Describe what's currently in the pond. 
    Arguments   None
    Returns     Description
*/ 
string
pond_contents()
{
    object pond = find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    object *livings; 
    string contents = ""; 

    /*  Does the pond exist? */ 
    if (pond == 0) 
    {
        /*  No, so load it */ 
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
        pond = find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    }

    /* Now does it exist */ 
    if (pond != 0) 
    {
        /* Good. Now are there livings in it? */ 
        livings = FILTER_LIVE(all_inventory(pond)); 
        if(sizeof(livings)) 
        {
            /* Yes, so create a description of them. */ 
            contents = " You can see " + COMPOSITE_ALL_LIVE(livings) + 
                " on the surface of the pond."; 
        }
    }
    else
    {
        /* Uh oh */ 
        contents = " Err... Something is wrong here. Please file a bug report."; 
    }

    return contents; 
}

/* 
    Name        pond_describe
    Purpose     Provide a description of the pond, including any
                animals in the pond_surface room
    Arguments   None
    Returns     string with the description
*/ 
string
pond_describe()
{
    /* Add any livings on the pond to the end */ 
    return "The stream that flows through the village has formed " +
        "a small pond here. The water looks to be a little muddy " +
        "as if something had been stirring up the mud at the " + 
        "bottom." + pond_contents() + "\n"; 
}

/* 
    Name        pond_tells
    Purpose     Add tells specific to rooms that are near the duck pond
    Arguements  None
    Returns     Nothing
*/ 
void
pond_tells()
{
    add_tell("Ribbit! A frog croaks from the nearby pond.\n"); 
    add_tell("Insects buzz around the surface of the pond.\n"); 
}

/* 
    Name        stream_describe
    Purpose     Describe the stream
    Arguments   None
    Returns     String with the description
*/ 
string 
stream_describe()
{
    return "The clear water of the small stream sparkles and makes " + 
        "a faint babbling noise as it makes it's way through the " + 
        "forest.\n"; 
}

/*  
    Name        stream_drink
    Purpose     allows a player to drink from the stream. 
    Arguements  The command line the player typed, supplied automatically
                when used in an add_act
    Returns     Integer indicating success or failure. 
*/ 
int
stream_drink(string command)
{
    object player = this_player(); 
    int success = 1;
    int x = 0; 

    /* Did the player type something somewhat understandable and 
        related to the stream? */ 
    if(parse_command(command, this_object(), 
        "[water] 'from' [the] 'stream'"))
    {

        while (player->drink_soft(50, 0) && x < 15)
        {
            x++;
        }

        if (!x) 
        {
            write("You feel as if you'll burst if you drink any more.\n"); 
        }
        else
        {
            write("You drink some water from the stream. It tastes " + 
                "very refreshing.\n"); 
            say(QCTNAME(player) + " drinks some water from the stream.\n");
        }
    }
    else
    {
        success = 0; 
    }

    return success;
}

/* 
    Name        stream_tells
    Purpose     Add tells specific to rooms that are near the stream
    Arguments   None
    Returns     Nothing
*/
void
stream_tells()
{
    add_tell("The stream babbles as it flows by.\n"); 
    add_tell("A reddish colored fish leaps out of the stream and " + 
        "splashes back in.\n"); 
}

/* 
    Name        swim_contents
    Purpose     describe anything that can be seen in the pool (from outside)
    Arguments   None
    Returns     String with the description
*/
string
swim_contents()
{
    object pool = find_object(TOAD_IN_OAK_ROOMS_GROUND + "swim"); 
    object *livings;
    string contents = ""; 

    /* Does the pool exist */
    if(pool == 0)   
    {
        /* No, so load it */ 
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "swim"); 
        pool = find_object(TOAD_IN_OAK_ROOMS_GROUND + "swim"); 
    }

    /* Now does it exist */ 
    if(pool != 0) 
    {
        /* Yes. Is anyone in it? */ 
        livings = FILTER_LIVE(all_inventory(pool)); 
        if(sizeof(livings)) 
        {
            /* Describe the people in the pool. Can't see details from here,
                but can tell they're nekkid */ 
            contents = " You can see " + COMPOSITE_ALL_LIVE(livings) + 
                " swimming naked in the pool."; 
        }
    }
    else
    {
        /* Uh oh */
        contents = " Err... Something is wrong here. Please file a bug report."; 
    }
   
    return contents; 
}

/* 
    Name        swim_describe
    Purpose     Describe the pool, including any contents
    Arguments   None
    Returns     String with the description
*/
string
swim_describe()
{
    return "THIS SPACE INTENTIONALLY LEFT BLANK." + swim_contents() + "\n"; 
}

/*  
    Name:       thicket_describe
    Purpose:    Return a generic description of the thicket that surrounds
                the village including where it is in relation to the player.
    Arguments:  direction - The direction of the thicket from here. It can 
                    include more than one direction. ie "west and south" 
    Returns:    The description
*/ 
string
thicket_describe(string direction)
{
    return "A dense thicket of shrubs, branches, thorny vines and " +  
        "other vegetation forms an impassible wall to the " + 
        direction + ".\n"; 
}

/* 
    Name        thicket_tells
    Purpose     Add tells specific to rooms near the thicket surrounding
                the village.
    Arguments   None
    Returns     Nothing
*/ 
void
thicket_tells()
{
    add_tell("You hear something moving through the forest beyond " + 
        "the thicket.\n"); 
    add_tell("Something causes the thicket to rustle slightly.\n"); 
    add_tell("You hear a faint hissing from the thicket.\n"); 
}

/* 
    Name:       trail_describe
    Purpose     Describe the grass in the eastern trail rooms, 
                Including which direction is uphill and which downhill
    Arguments   The uphill and downhill directions
    Returns     The description
*/ 
string
trail_describe(string uphill, string downhill)
{
    return "The ground here is covered by a thick carpet of " + 
        "green grass that feels springy beneath your step. Covered " + 
        "in ever shifting shadows the grass appears to be quite " + 
        "healthy despite the low light. A faint path through the " + 
        "grass leads uphill to the " + uphill + " and back down to the " + 
        downhill + ".\n";
}
    
/*  
    Name:       trees_describe
    Purpose:    Returns a generic description of the trees for use in 
                add_item. 
    Arguments:  great_oak - 1 = include a reference to the great oak
                            0 = don't. 
                direction - The direction of the great oak from here. 
                    (May be blank if the oak can't be seen.)
    Returns:    The description            
*/
string
trees_describe(int great_oak, string direction)
{
    string description;

    description = "The trees here are enormous, reaching so high " + 
        "that they seem to touch the sky. Their upper leaves and " + 
        "branches mesh together to form a canopy that covers the " + 
        "ground in ever shifting shadows."; 
    
    /* If the extra giant oak can be seen from here add it to the 
        trees description */ 
    if(great_oak) 
    {
        description += " Immense as they are off to the " + direction + 
            " you can see a single oak that towers over the rest.";
    }
    
    description += "\n"; 
    
    return description; 
}

/*  Name:       village_describe
    Purporse:   Returns a description of the village as seen from the
                ground level. Only the underside of things can be seen from 
                here, so it doesn't change.
    Arguments:  Nothing
    Returns:    The description
*/
string
village_describe()
{
    return "You can see the underside of the village walkways among " + 
        "the branches high above you, but it's impossible to see " + 
        "any details from down here.\n";
}

// ROOM DEFINITION

void 
create_tio_ground_room()
{
}

public nomask void
create_tio_room()
{
    set_short("A room on the ground level of Toad-In-Oak."); 
    set_long("A room on the ground level of Toad-In-Oak.\n"); 

    add_prop(ROOM_I_LIGHT, 1); 

    common_tells(); 
    set_tell_time(150);    

    create_tio_ground_room(); 
}


