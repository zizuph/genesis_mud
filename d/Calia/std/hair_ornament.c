/*
 * /d/calia/kcirderf/hair_ornament.c
 *
 * This is a base object for hair ornaments. It works with Maniac's hair
 * code, using a persons hair length and colour if hair is present. 
 *  
 * HISTORY: [99-05-17] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

//INCLUDES, INHERITS, AND DEFINITIONS

#define HAIRSTYLE_SUBLOC "_calia_hair_ornament_hairstyle"
#define NO_HAIRSTYLE_SUBLOC "_calia_hair_ornament_no_hairstyle"

inherit "/std/object"; 
inherit "/lib/wearable_item"; 

#include <wa_types.h>
#include <macros.h>

//FUNCTIONS

/*
 * Function name: wear
 * Description:   This function is executed when a person attempts to wear 
 *                a hair ornament and gives special messages if successful. 
 * Arguments:     None
 * Returns:       see 'sman wear' 
 */
public mixed
wear()
{    
    object player = this_player(); // The player who wants to wear the object
    mixed success = 1;             // The return value. This is NOT just a 
                                   // boolean. 
  
    /*  We want to do different things depending on wether or not the player
        has hair. First we check if they've been to the hair dresser in gelan.
        The function query_hair_length is defined in the hair shadow, and if 
        it returns, we know they've got the shadow and therefore hair. */        
    if (player -> query_hair_length())
    {
        /*  If the player has their hair cut too short, then the ornament 
            would just fall out.  */ 
        if (player->query_hair_length() != "very short")
        {
            player->catch_msg("You wear the " + query_short() + 
                " in your " + player->query_hair_length() + " " + 
                player->query_hair_colour() + " hair.\n"); 
    
            tell_room(environment(player), QCTNAME(player) + 
                " wears the " + query_short() + " in " + 
                player->query_possessive() + " " + 
                player->query_hair_length() + " " + 
                player->query_hair_colour() +
                " hair.\n", ({player})); 

            player->add_subloc(HAIRSTYLE_SUBLOC, this_object()); 
            set_no_show(); 
        }
        else
        {            
            success = "Your " + player->query_hair_colour() + 
                " hair is too short for you to wear the " + query_short() + 
                ".\n"; 
        }
    }
    else
    {
        /*  The player is too cheap to go to the hairdresser, but they could
            still have hair, so we check for the bald adjective.  */
        if (member_array("bald", player->query_adj(1)) == -1)
        {

            player->catch_msg("You wear the " + query_short() + 
                " in your hair.\n"); 
        
            tell_room(environment(player) , QCTNAME(player) + " wears the " + 
                query_short() + " in " + player->query_possessive() + 
                " hair.\n", ({player})); 

            player->add_subloc(NO_HAIRSTYLE_SUBLOC, this_object()); 
            set_no_show(); 
        }
        else
        {
            success = "You have no hair in which to place the " + 
                query_short() + ".\n"; 
        }
    }

    return success; 
}

/*
 * Function name: remove
 * Description:   This function is executed when a person attempts to remove
 *                a hair ornament and gives special messages if successful. 
 * Arguments:     None
 * Returns:       see 'sman remove' 
 */
public mixed 
remove()
{
    object player = this_player(); // The player removing the object
    mixed success = 1;             // The return value. This probably won't
                                   // change, but it's declared to be 
                                   // thourough

    if (player->query_hair_length())
    {
        player->catch_msg("You remove the " + query_short() + " from your " + 
            player->query_hair_length() + " " + player->query_hair_colour() + 
            " hair.\n"); 

        tell_room(environment(player), QCTNAME(player) + " removes the " + 
            query_short() + " from " + player->query_possessive() + " " + 
            player->query_hair_length() + " " + player->query_hair_colour() + 
            " hair.\n", ({player})); 

        player->remove_subloc(HAIRSTYLE_SUBLOC); 
        unset_no_show(); 
        unset_no_show_composite(); 
    }
    else
    {
        player->catch_msg("You remove the " + query_short() + 
            " from your hair.\n"); 

        tell_room(environment(player), QCTNAME(player) + " removes the " + 
            query_short() + " from " + player->query_possessive() + 
            " hair.\n", ({player})); 

        player->remove_subloc(NO_HAIRSTYLE_SUBLOC); 
        unset_no_show(); 
        unset_no_show_composite(); 
    
    }

    return success; 
}

/*
 * Function name: leave_inv()
 * Description:   We need to override leave_env() so that we can be sure to 
 *                remove the hair ornament if it gets moved from the wearer 
 *                while it is still worn.
 * Arguments:     see 'sman leave_env' 
 * Returns:       nothing 
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

/*
 * Function name: appraise_object
 * Description:   We need to override appraise_object() so that we can be sure 
 *                that the player can appraise it properly.
 * Arguments:     see 'sman appraise_object' 
 * Returns:       nothing 
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/*
 * Function name: show_subloc
 * Description:   SHow cthe hair ornament sublocation
 *                
 * Arguments:     see 'sman show_subloc' 
 * Returns:       subloc string 
 */
string
show_subloc(string subloc, object player, object looker)
{
    string return_value; // The value that will be returned. 
    


    if (subloc == HAIRSTYLE_SUBLOC)
    {
        if (player == looker)
        {
            return_value = "You are wearing a " + query_short() + 
                " in your " + player->query_hair_length() + " " + 
                player->query_hair_colour() + " hair.\n"; 
        }
        else
        {
            return_value = capitalize(player->query_pronoun()) + 
                " is wearing a " + query_short() + " in " + 
                player->query_possessive() + " " + 
                player->query_hair_length() + " " + 
                player->query_hair_colour() + " hair.\n"; 
        }

    }
    else if (subloc == NO_HAIRSTYLE_SUBLOC)
    {

        if (player == looker)
        {
            return_value = "You are wearing a " + query_short() + 
                " in your hair.\n"; 
        }
        else
        {
            return_value = capitalize(player->query_pronoun()) + 
                " is wearing a " + query_short() + " in " + 
                player->query_possessive() + " hair.\n"; 
        }
    }
    else
    {
        return_value = player->show_subloc(subloc, player, looker); 
    }

    return return_value; 
}

//CONSTRUCTORS

/*
 * Function name: create_hair_ornament
 * Description:   A blank constructor, meant to be overridden. 
 * Arguments:     none 
 * Returns:       nothing 
 */
void
create_hair_ornament() 
{
}

/*
 * Function name: create_object
 * Description:   The object constructor. Sets the values needed for 
 *                every hair_ornament object
 * Arguments:     none 
 * Returns:       nothing 
 */
public nomask void
create_object()
{
    set_layers(1); 
    set_looseness(0); 
    set_slots(A_HEAD); 
    set_wf(this_object());     

    create_hair_ornament(); 
}

