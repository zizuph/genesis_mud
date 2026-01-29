/*
 * /d/Calia/central/toad_in_oak/specials/stream_drink.h
 *
 * This is the common code used to allow people to drink from the
 * stream in Toad-in-Oak
 * 
 * HISTORY: [99-03-02] Created by Kcirderf  
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

/*
 * Function name: drink
 * Description:   Lets people drink from the stream in Toad-in-Oak and
 *                tells them to drink from the stream instead if they 
 *                try to drink from the duck pond. 
 * Arguments:     str typed by the player 
 * Returns:       0/1
 */
int
drink(string input, int pond) 
{
    /* player       - The player trying to drink
     * success      - The success of this function
     * what         - What they try to drink
     * from         - What they try to drink from
     * from_short   - Used to eliminate a "the" 
     * x            - counter. 
     */

    object player = this_player(); 
    int success = 1, x; 
    string what, from, from_short; 

    /*  We need to make sure that the player typed more than drink, 
        and that they got the basic syntax right. */
    if (!input || (sscanf( input , "%sfrom %s" , what, from) != 2 ))
    {
        success = 0; 
    }
    else 
    {
        /* Now, did they want to drink water. */ 
        if ( what == "" || what == "water " || what == "the water " )        
        {
        
            /*  Now we know that the wanted drink water from something,
                but we don't know from what. We don't care wether
                or not they typed the in from of it, so kill it. */ 
            if (sscanf(from, "the %s", from_short) == 1)
            {
                from = from_short; 
            }

            /*  Now, finally did they target our stream? */ 
            if (    from == "stream" || 
                    from == "brook" || 
                    (from == "pond" && pond == 1))
            {
                if (from == "brook") 
                {
                    from == "stream"; 
                }

                /*  We want the player to get 250 mls. We do it in
                    small doses for little people  */ 
                x = 0; 
                while( player->drink_soft(50,0) && x < 5 ) 
                    {
                        x++ ; 
                    } 

                /*  We give different messages based on wether they 
                    got any water or not. */ 
                if (x) 
                {
                    player->catch_msg("You drink some water from " + 
                        "the " + from + ". It tastes very refreshing.\n"); 
                    tell_room(this_object(),
                        QCTNAME(player) + " drinks some water from " +
                        "the " + from + ".\n", player); 
                }
                else
                {
                    player->catch_msg("You're already full and " + 
                        "can't drink anymore.\n"); 
                }
            }
            else
            {
                success = 0; 
            }  
        }
        else
        {
            success = 0; 
        }
    }    
    return success; 
}

/*
 * Function name: drink_stream
 * Description:   Allows people to try to drink from the stream in 
 *                rooms where only the stream is present. 
 * Arguments:     str typed by the player 
 * Returns:       0/1
 */
int
drink_stream(string input)
{
    /*  We want to return the success value of the drink function.
        The second argument to drink indicates theres no pond here. */    
    return drink(input, 0); 
}

/*
 * Function name: drink_pond
 * Description:   Allows people to try to drink from the stream in 
 *                rooms where the duck pond is also nearby
 * Arguments:     str typed by the player 
 * Returns:       0/1
 */
int
drink_pond(string input)
{
    /* In this case there is a pond so the second arg. is 1. */
    return drink(input, 1); 
}

