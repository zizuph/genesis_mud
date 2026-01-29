/*
 * /d/calia/yuleware/toys/kender.c
 *
 *  This is a kender doll for the collection of christmas toys. 
 *
 * 
 * HISTORY: [98-12-14] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1998
 *
 */

// INCLUSIONS 

inherit "/std/object"; 

#include <stdproperties.h>
#include <macros.h>

// GLOBAL VARIABLES

string* hair_colours = ({"blonde" , "brown" , "black" , "red"});
string* eye_colours = ({"blue", "green", "brown", "grey"}); 
string* clothing_colours = ({"red", "yellow", "green", "blue", "violet",
    "brown", "grey", "white", "pink", "gold", "silver"}); 
string pronoun, possessive, objective, type, hair, eyes; 
// OBJECT DEFINITION

void
create_object()
{
    string leggings, vest;     
    
    set_name("kender"); 
    add_name("toy"); 
    add_name("doll"); 

    if (random(4)) 
    {
        type = "kender"; 
        pronoun = "he"; 
        possessive = "his";
        objective = "him"; 
    }
    else
    {
        add_name("kendermaid"); 
        type = "kendermaid"; 
        pronoun = "she"; 
        possessive = "her"; 
        objective = "her"; 
    }

    hair = hair_colours[random(sizeof(hair_colours))]; 
    eyes = eye_colours[random(sizeof(eye_colours))]; 
    leggings = clothing_colours[random(sizeof(clothing_colours))]; 
    clothing_colours = clothing_colours - ({leggings}); 
    vest = clothing_colours[random(sizeof(clothing_colours))]; 

    set_short("cute " + type + " doll"); 
    set_adj(({"cute", type, "toy"})); 
    
    set_long("This is a cute little doll that has been made to resemble " + 
        "a " + type + ". " + capitalize(pronoun) + " has long " + hair + 
        " hair tied into a topknot and mischievous " + eyes + " eyes. " + 
        capitalize(pronoun) + " is dressed in a typical kender outfit and " + 
        "has a hoopak in " + possessive + " hand. " + capitalize(pronoun) + 
        " has a silly smile on " + possessive + " face as if someone were " + 
        "tickling " + objective + ".\n"); 
    
    add_prop(OBJ_I_WEIGHT, 300); 
    add_prop(OBJ_I_VOLUME, 1000); 
    add_prop(OBJ_I_VALUE, 10); 
    add_prop(OBJ_M_NO_SELL, "The merchant takes one look at the toy and " + 
        "says: Ack! Get out of here with that. I don't want any kender " + 
        "in here, not even if it's a toy.\n"); 

    add_item(({"hair", "topknot"}), 
        "The " + type + " doll's long " + hair + " flaxen hair has been " + 
        "tied up into a topknot that hangs down " + possessive + " back.\n"); 

    add_item(({"eye", "eyes"}), 
        "The " + type + " doll's eyes are made out of " + eyes + " glass. " +
        "Somehow the maker of the doll has given the eyes a mischievous " + 
        "glint.\n"); 

    add_item(({"clothes", "clothing", "leggings", "vest", "tunic", 
        "belt", "tunic", "outfit"}), 
        "The " + type + " doll is dressed in normal kender fashion. " + 
        capitalize(pronoun) + " has a white tunic, " + leggings + 
        " leggings, and a " + vest + " furred vest. " + capitalize(pronoun) +
        " has a belt with a number of tiny pouches on it. " + 
        capitalize(pronoun) + " also has the traditional kender hoopak " + 
        "in her hand.\n"); 

    add_item(({"hoopak", "weapon", "stick", "sling"}), 
        "The " + type + " doll has a miniature version of a traditional " + 
        "kender hoopak in " + possessive + " hand. It's a wooden stick " + 
        "that has a fork at one end with a sling attached, and has been " + 
        "sharpened to a point on the other end. Actually, the toy's " + 
        "hoopak isn't very sharp, but the doll still manages to poke you " + 
        "with it as you inspect it. Maybe you should poke " + objective + 
        " back.\n"); 

    add_item(({"smile", "face"}), 
        "The " + type + " doll has " + eyes + " eyes, " + hair + " hair, " +
        "pointed ears, and a silly smile on " + possessive + " face. It " + 
        "looks almost as if " + pronoun + " is giggling in response to " + 
        "being tickled.\n"); 

}

/* 
 * Name:        tickle_kender
 * Purpose:     Allows the player to tickle their kender doll. 
 * Arguments:   The rest string the player typed. 
 * Returns: 
 */ 
int 
tickle_kender(string input)
{
    string *adverbs = ({"happily", "merrily", "mischievously", "gleefully", 
        "impishly", "childishly"}); 
    string how = adverbs[random(sizeof(adverbs))]; 
    object player = this_player(), target; 
    int success = 1; 

    if (!input)
    {
        success = 0; 
    }
    else
    {
        if (parse_command(input, all_inventory(player), "[the] %o" , target)
           && target == this_object())
        {
            write("You tickle the " + type + " doll. " + 
                capitalize(possessive) + " " + eyes + " eyes twinkle in " + 
                "the light and " + pronoun + " giggles " + how + ".\n"); 
 

            say(QCTNAME(player) + " tickles " + player->query_possessive() + 
                " " + type + " doll. The doll's " + eyes + " eyes twinkle " + 
                "and " + pronoun + " giggles " + how + ".\n"); 
        }
        else
        {
            success = 0; 
        }
    }

    return success; 
}

/* 
 * Name:        poke_kender
 * Purpose:     Allows the player to poke the doll 
 * Arguments:   The rest of the string the player typed. 
 * Returns:     0/1
 */ 
int
poke_kender(string input)
{
    object player = this_player(), target;
    int success = 1; 

    if (!input)
    {
        success = 0; 
    }
    else
    {
        if (parse_command(input, all_inventory(player), "[the] %o" , target) 
            && target == this_object()) 
        {
            
            write( "You poke the " + type + " doll in the nose. " +
                capitalize(possessive) + " face scrunches up, making " + 
                objective + " look even more mischievous, and " + pronoun + 
                " says \"Oops!\" in a high pitched childish voice.\n"); 

            say(QCTNAME(player) + " pokes " + player->query_possessive() + 
                " " + type + " doll in the nose. The dolls face scrunches " + 
                "up and " + pronoun + " says \"Oops!\" in a high pitched " + 
                "childish voice.\n"); 

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

    add_action(tickle_kender, "tickle"); 
    add_action(poke_kender, "poke"); 
}
