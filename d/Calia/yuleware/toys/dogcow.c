/*
 * /d/calia/yuleware/toys/dogcow.c
 *
 * PURPOSE: A toy for the domain office christmas tree.  
 * 
 * HISTORY: [98-11-01] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1998
 *
 */

// INCLUSIONS

inherit "/std/object"; 

#include <stdproperties.h> 
#include <macros.h>

// OBJECT DEFINITION

void
create_object()
{

    set_short("stuffed toy dogcow"); 
    set_name("dogcow"); 
    add_name("toy"); 
    set_adj(({"stuffed", "toy", "dogcow"}));

    set_long("This large stuffed toy has long shaggy white fur with " + 
        "black spots. She has a long tail sticking into the air and " + 
        "two horns on the top of her head. It looks as if she was " + 
        "overstuffed to make her more huggable. Her slightly sad " + 
        "expression makes you think she could use a friendly pat on " + 
        "the head.\n"); 

    add_prop(OBJ_I_WEIGHT, 500); 
    add_prop(OBJ_I_VOLUME, 3000); 
    add_prop(OBJ_I_VALUE, 25); 

    add_prop(OBJ_M_NO_SELL, "You consider selling your dogcow, but you " + 
        "decide you can not part with such a loyal companion.\n"); 

    add_item(({"eyes", "horns", "face", "expression", "nose", "mouth", 
        "thread"}), 
        "The dogcows' face has two big black buttons for eyes, and a " + 
        "small pink nose of carved wood. The two horns on the top of " + 
        "her head are as overstuffed as the rest of her. She has a " + 
        "small mouth stitched on, which droops slightly as if she were " +
        "sad.\n"); 

    add_item(({"fur", "spots", "coat"}), 
        "The dogcows' long shaggy fur is incredibly soft. Most of it " + 
        "is pure white in colour, but there are a number of spots dyed " +
        "black.\n"); 

    add_item(({"tail"}), 
        "The dogcows' tail is quite long and sticks straight up into " + 
        "the air. It's covered in the same shaggy fur as the rest of " + 
        "the toy.\n"); 

}

/* 
    Name:       pat_dogcow
    Purpose:    Allows the player to pat the dogcow. 
    Arguments:  string indicating this toy
    Returns:    0/1
*/     
int
pat_dogcow(string input)
{
    object player = this_player(); 
    object target; 
    int success = 1;     

    if (!input)
    {
        success = 0; 
    }
    else
    {
        if (parse_command(input, all_inventory(player), 
            "[the] %o", target) && target == this_object())
        {

            write("You pet the stuffed dogcow adoringly on the head. " + 
                "It's face scrunches up, turning the frown into a " + 
                "happy grin, and she makes a suprisingly loud " + 
                "\"Moof!\" sound.\n"); 

            say(QCTNAME(player) + " pets " + player->query_possessive() + 
                " stuffed dogcow. A loud \"Moof!\" issues from the toy.\n"); 
        }
        else
        {
            success = 0; 
        }
    }

    return success; 
}

/* 
    Name:       hug_dogcow
    Purpose:    Allows the player to hug the dogcow. 
    Arguments:  string indicating this toy
    Returns:    0/1
*/                
int
hug_dogcow(string input)
{

    object player = this_player(); 
    object target; 
    int success = 1; 

    if (!input) 
    {
        success = 0; 
    }
    else
    {
        if (parse_command(input, all_inventory(player), 
            "[the] %o", target) && target == this_object())
        {
            write("You give your dogcow a long and mighty hug. As " + 
                "you squeeze her against your body, her eyes look " + 
                "as if they're about to pop out of her head, and " + 
                "her frown has turned into a silly grin. She " + 
                "quickly returns to her normal shape when you " + 
                "finally release her.\n"); 

            say(QCTNAME(player) + " looks rather childish as " + 
                player->query_pronoun() + " hugs a toy dogcow to " + 
                player->query_objective() + "self. Both " + 
                QTNAME(player) + " and the toy have big silly grins " + 
                "on their faces.\n"); 
        }
        else
        {
            success = 0; 
        }
    }

    return success; 
}

/* 
    Name:       init
    Purpose:    define commands 
    Arguments:  none
    Returns:    none
*/ 
void
init()
{
    ::init(); 

    add_action(pat_dogcow, "pat"); 
    add_action(pat_dogcow, "pet"); 
    add_action(hug_dogcow, "hug"); 
}
