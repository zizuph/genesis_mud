/*
 * /d/Calia/central/toad_in_oak/animals/base_animal.c
 *
 * This is a base animal for Toad-in-Oak
 *
 * HISTORY: [99-08-10] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

//  INCLUSIONS AND DEFINITIONS

inherit "/std/creature";
inherit "/std/act/action"; 
inherit "/std/combat/unarmed"; 

#include <defs.h>
#include <stdproperties.h>
#include <const.h>

// GLOBAL VARIABLES

mixed *Acts_Normal = ({});  // The animals normal emotions, can occur anywhere 
                            // in the game
mixed *Acts_Room = ({});    // Actions specific to a room. 
mixed *Cacts_Normal = ({}); // Normal combat actions
mixed *Cacts_Room = ({});   // Room specific combat actions (will this ever 
                            // get used?)
int Restlessness = 10;      // The chances an NPC will move rather than act
string Home = TOAD_IN_OAK_ROOMS_GROUND + "entrance_west"; 

// FUNCTION DECLARATIONS

void add_act_normal(mixed new_act);
void add_act_room(mixed new_act); 
void add_cact_normal(mixed new_cact); 
void add_cact_room(mixed new_cact); 
void perform_act(); 
void perform_cact(); 
void perform_move(); 
void reset_acts_room(); 
void reset_cacts_room(); 
void set_home(string new_value); 
void set_restlessness(int new_value); 
int toad_in_oak(); 
int toad_in_oak_animal(); 

// FUNCTIONS

/*  Name:       add_act_normal
    Purpose:    Adds an act to the Acts_Normal array. 
    Arguments:  A string or a function pointer that represents the act. 
                Functions should return a command string. 
    Returns     nothing
*/ 
void
add_act_normal(mixed new_act)
{
    /*  Why not just initialize the Acts_Normal array with these? Because 
        then things like query_pronoun won't work.  */ 

    Acts_Normal += ({new_act}); 
}

/*  Name:       add_act_room
    Purpose:    Adds an act to the Acts_Room array
    Arguments:  A string or function representing the act
    Returns     nothing
*/ 
void
add_act_room(mixed new_act)
{
    Acts_Room += ({new_act}); 
}

/*  Name:       add_cact_normal
    Purpose:    Adds an act to the Cacts_Normal array. 
    Arguments:  A string or a function pointer that represents the act. 
                Functions should return a command string. 
    Returns     nothing
*/ 
void
add_cact_normal(mixed new_cact)
{
    /*  Why not just initialize the Cacts_Normal array with these? Because 
        then things like query_pronoun won't work.  */ 

    Cacts_Normal += ({new_cact}); 
}

/*  Name:       add_cact_room
    Purpose:    Adds an cact to the Acts_Room array
    Arguments:  A string representing the act
    Returns     nothing
*/ 
void
add_cact_room(mixed new_cact)
{
    Cacts_Room += ({new_cact}); 
}

/*  Name:       leave_env()
    Purpose:    Called when the animal leaves an environment
    Arguments:  Location being left, destination
    Returns:    Nothing
*/
void
leave_env(object old, object dest)
{
    if (old->toad_in_oak_room())
    {
        reset_acts_room();
        reset_cacts_room(); 
    }

    ::leave_env(old, dest); 
}

/*  Name:       perform_act()
    Purpose:    Performs an act from the Acts_Normal or Acts_Room arrays
    Arguments:  None
    Returns     nothing
*/ 
void
perform_act()
{
    /*  This is the heart of how the animals actions work. Rather than add 
        the acts individually as normal, this function is called via VBFC. 
        It selects an action at random from either the Acts_Normal or 
        Acts_Room and tells the animal to perform it. This allows the npc to 
        use actions tailored to whatever room they're in without creating a 
        huge difficult to maintain mess.  */ 

    int choice;             /*  Random number used to choose an action */ 
    int moving;             /*  Random number used to determine if the 
                                animal will move instead of act.  */ 
    function act_function;  /*  A place to store a function pointer */ 

    moving = random(100); 

    if (moving < Restlessness) 
    {
        perform_move(); 
    }
    else
    {
    
        /*  We choose a random number that's something less than the total 
            size of the two arrays. This way every act has an equal chance. 
            Unless ones in there twice to make it more likely, but I 
            digress... */ 
        choice = random(sizeof(Acts_Normal) + sizeof(Acts_Room)); 

        /*  We need to determine which array we should be looking in based on 
            the number chosen. Low numbers access the Normal acts.  */ 
        if (choice < sizeof(Acts_Normal))
        {

            /*  The array is mixed and should contain either a command string
                (ie "emote quacks") or a function pointer. (ie &quack())  */
            if (stringp(Acts_Normal[choice]))
            {
                /*  Strings are nice and simple, assuming they're done 
                    right  */
                command(Acts_Normal[choice]); 
            }
            else if (functionp(Acts_Normal[choice]))
            {
                /*  Functions are a little more difficulty. The mud got 
                    unhappy when I tried to do this all at once, so we assign 
                    the function to a scalar variable and then call it.  */ 
                act_function = Acts_Normal[choice];
                command(act_function());
            }

        }
        else
        {   
            /*  The number was high enough. Other than the adjustment to 
                correctly access the array, this is the same as above.  */

            if (stringp(Acts_Room[choice - sizeof(Acts_Normal)]))
            {
                command(Acts_Room[choice - sizeof(Acts_Normal)]); 
            }   
            else if (functionp(Acts_Room[choice - sizeof(Acts_Normal)]))
            {
                act_function = Acts_Room[choice - sizeof(Acts_Normal)]; 
                command(act_function()); 
            }        
        }
    }

    return;
}

/*  Name:       perform_cact()
    Purpose:    Performs an cact from the Cacts_Normal or Cacts_Room arrays
    Arguments:  None
    Returns     nothing
*/ 
void
perform_cact()
{
    /*  If you've just looked at perform_act this will give you deja vu. 
        If you haven't, go do so. This is the same except for a few extra C's
        and a lack of comments  */ 

    int choice;             /*  Random number used to choose an action */ 
    function cact_function;  /*  A place to store a function pointer */ 

    choice = random(sizeof(Cacts_Normal) + sizeof(Cacts_Room)); 

    if (choice < sizeof(Cacts_Normal))
    {
        if (stringp(Cacts_Normal[choice]))
        {
            command(Cacts_Normal[choice]); 
        }
        else if (functionp(Cacts_Normal[choice]))
        {
            cact_function = Cacts_Normal[choice];
            command(cact_function());
        }
    }
    else
    {
        if (stringp(Cacts_Room[choice - sizeof(Cacts_Normal)]))
        {
            command(Cacts_Room[choice - sizeof(Cacts_Normal)]); 
        }
        else if (functionp(Cacts_Room[choice - sizeof(Cacts_Normal)]))
        {
            cact_function = Cacts_Room[choice - sizeof(Cacts_Normal)]; 
            command(cact_function()); 
        }        
    }

    return;
}

/*  Name:       perform_move    (Why perform_move? to match perform_(c)act) 
    Purpose:    Moves the animal, usually at random. 
    Arguments:  None
    Returns:    Nothing
*/ 
void
perform_move()
{
    /*  Get the current room.  */ 
    object room = environment(this_object()); 

    /*  Get the exits from the room.  */ 
    string *exits = room->query_exit_cmds(); 

    /*  Get the rooms those exits lead to.  */ 
    string *destinations = room->query_exit_rooms(); 
    int choice = random(100);   // Deciding if the animal will fly home1
    string dir, dest;   // Temporary storage. 

    /*  First we check if the animal is in somebody's inventory.  */         
    if ( !living(room))
    {
        /*  It's not in somebody's inventory, so it can at least try to 
            move  */ 
        if (!room->toad_in_oak_room() &&
            !room->query_prop(ROOM_I_INSIDE) &&
            choice < Restlessness)
        {
            /*  The animal has been dragged out of TiO and dropped, is not 
                indoors, and has decided to flee back to the village.  */
            move_living("X", Home, 0, 0); 
        }
        else if (sizeof(exits)) 
        {
            /*  At this point the animal will move through a random exit  */ 
            choice = random(sizeof(exits)); // The choice of exit to use  
            dir = exits[choice];            // I don't know why this is 
            dest = destinations[choice];    // needed but it is. 

            if (!room->toad_in_oak_room() || 
                wildmatch(TOAD_IN_OAK_ROOMS + "*", dest))
            {
                move_living(dir, dest, 0, 0); 
            }

        }
    }

    return; 
}

/*  Name:       reset_acts_room
    Purpose:    Cleans out the Acts_Room array
    Arguments:  none
    Returns     nothing
*/ 
void
reset_acts_room()
{
    /*  This will normally be called by the rooms as the animal leaves. 
        I could do this from the animals leave_env routine, but this way it
        will only get called when it's really needed.  */ 

    Acts_Room = ({}); 
}

/*  Name:       reset_cacts_room 
    Purpose:    Cleans out the Cacts_Room array
    Arguments:  none
    Returns     nothing
*/ 
void
reset_cacts_room()
{
    Cacts_Room = ({}); 
}

/*  Name:       set_home
    Purpose:    Sets the home room of the animal where it will hopefully
                teleport back to if it somehow gets out of the village. 
    Arguments:  Path name
    Returns:    Nothing
*/
void
set_home(string new_value)
{
    Home = new_value;

    return; 
}

/*  Name:       set_restlessness
    Purpose:    Set the chance that the creature will move each time it is
                supposed to act. NOTE: The creatures overall rate of movement
                is also affected by set_act_time.
    Arguments:  Int
    Returns:    Nothing
*/
void
set_restlessness(int new_value)
{
    Restlessness = new_value; 
    
    return; 
}

/*  Name:       toad_in_oak
    Purpose:    Identifies this object as coming from Toad-in-Oak
    Arguments:  None
    Returns:    1
*/ 
int
toad_in_oak()
{
    return 1; 
}

/*  Name:       toad_in_oak_animal
    Purpose:    Identifies this animal as coming from Toad-in-Oak
    Arguments:  None
    Returns:    1
*/
int 
toad_in_oak_animal()
{
    return 1; 
}

// CREATURE DEFINITION

void
create_tio_animal()
{
}

public nomask void
create_creature()
{

    /* Just in case somebody messes with the gender constants */ 
    if (random(2)) 
    {
        set_gender(G_MALE); 
    }
    else
    {
        set_gender(G_FEMALE); 
    }

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1); 

    set_act_time(5); 
    set_cact_time(3); 

    add_act("@@perform_act@@"); 
    add_cact("@@perform_cact@@"); 

    create_tio_animal();
}
