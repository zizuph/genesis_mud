 /*
 * /d/calia/kcirderf/hair_flower.c
 *
 * This is the wearable flowers from the village of Toad-in-Oak
 *  
 * HISTORY: [99-06-10] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINATION

inherit "/d/Calia/std/hair_ornament.c"; 

#include "defs.h"
#include "flowers.h"

// GLOBAL VARIABLES

string Flower, Colour, Adjective; 

// FUNCTIONS

void 
change_descriptions()
{
    set_adj(({Flower, Colour, Adjective + " " + Colour}));  
    set_short(Adjective + " " + Colour + " " + Flower); 
    set_long("This is a " + Adjective + " " + Colour + " " + Flower + 
        ". It has a long stem that you might be able to stick " + 
        "in your hair.\n"); 
}

int
set_flower(string flower)
{
    int success = 0; 
    int pos = member_array(flower, Flowers); 

    if (pos >= 0)
    {
        remove_name(Flower); 
        Flower = flower;
        add_name(Flower); 

        success = 1; 

        change_descriptions();
    }
    return success; 
}

int
set_colour(string colour)
{
    int success = 0; 
    string *adjectives; 
    int pos = member_array(colour, Colours); 

    if (pos >= 0)
    {
        Colour = colour;
        adjectives = Adjectives[pos] ;
        Adjective = adjectives[random(sizeof(adjectives))]; 
        success = 1; 
    
        change_descriptions();
    }
    return success; 
}

int
set_adjective(string adjective)
{
    int success = 0; 
    string *adjectives = Adjectives[member_array(Colour, Colours)];         

    int pos = member_array(adjective, adjectives); 
    
    if (pos >= 0) 
    {
        Adjective = adjective; 
        success = 1; 

        change_descriptions(); 
    }
    
    return success; 
}

// OBJECT DEFINITION

void
create_hair_ornament()
{
    string * adjectives;

    Flower = Flowers[random(sizeof(Flowers))]; 
    Colour = Colours[random(sizeof(Colours))]; 
    adjectives = Adjectives[member_array(Colour, Colours)]; 
    Adjective = adjectives[random(sizeof(adjectives))]; 

    set_name("flower"); 
    add_name(Flower); 

    change_descriptions();
}
