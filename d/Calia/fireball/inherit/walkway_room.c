
/* 
    ~Calia/fireball/inherit/walkway_room.c

    The inheritable room for walkway rooms around the Firedrome. 

    Coded by Maniac@Genesis, August 1997

    Copyright(C) Miguel Leith 1997. 

    Last revised April 1999 by Maniac
*/ 

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <language.h> 
#include <macros.h>
#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_OUTSIDE_ROOM;


void
make_walkway_room(int gate, string gate_direc, string walkway_direc)
{
    string s;

    add_item(({"firedrome", "stadium", "wall", 
               "high wall", "outer wall" }),  
         "The Firedrome is a huge circular stadium that hosts " +
         "fireball games. It is constructed " +
         "from blocks of rough-hewn faded red stone with an " +
         "arid and faintly fiery appearance. " +
         "Random blocks are chiselled with depictions of " +
         "savage battles.\n"); 

    add_item(({"block", "blocks"}), "The blocks are made of pale red " +
         "stone. The battles depicted on the blocks look intriguing.\n"); 

    add_item(({"arena"}), "The arena is not visible from outside the " +
                          "Firedrome!\n"); 

    if (gate) { 
        s = ("You are on a walkway at the base of an imperious " +
             "gateway framed with marble stones. " +
             "The mahogany gates, opening the way to your " + 
             gate_direc + ", are decorated " +
             "with intricate carvings of wild animals. " +
             "The faded red stone wall of the stadium " +
             "curves gradually in a giant " +
             "circle forming the back of the arena stand. ");  

        add_item(({"gate", "gateway", "gates"}), 
           "The gateway is framed with stones of marble. " +
           "The gates are made of mahogany carved with intricate designs " +
           "of fierce wild animals. They stand open.\n"); 

        add_item(({"wild animals", "fierce animals", "animals", 
                   "gilding", "carvings", "designs", "intricate carvings"}), 
           "There are carvings of fierce wild animals on the gates. " +
           "Among them are a pack of wolves on the hunt through a dense " +
           "dark forest, a pair of raging bulls locking horns and " +
           "a pride of lions chasing its prey across an arid plain.\n");  
        add_item(({"lion", "lions", "wolf", "wolves", "bull", "bulls" }), 
                  "It doesn't look like you'd want to be in their way.\n"); 
    } 
    else 
        s =  ("The lofty wall of the Firedrome looms in front of " +
           "you, its rough-hewn blocks of faded red stone locked " +
           "seamlessly together like a mountainside. It curves " +
           "gradually in a giant circle forming the back of the " +
           "arena stand. Random blocks are chiselled with " +
           "depictions of savage battles. "); 

    add_item(({"stand", "arena stand"}),  
             "Here you see only the back of the stand. It is made " +
             "of rough-hewn blocks of pale red stone. From the " +
             "other side you can hear the buzz of a crowd.\n"); 

    add_item(({"battles", "battle", "warriors", "savage battles", 
               "savage battle", "depictions"}), 
         "Each decorated block exhibits a chiselled picture of a " +
         "different battle. " + 
         "The weapons and garb of the warriors are very " +
         "primitive, consisting of cudgels and untreated animal " +
         "skins. Most pictures are similar except for one that " +
         "shows Og dribbling Thak's head across the battlefield and " +
         "setting up Gruk to volley it twenty yards between a pair " +
         "of trees.\n"); 

    add_item(({"diamond-shaped tiles", "grey-edged tiles", 
               "red tiles", "tiles", "walkway"}), 
        "The walkway is surfaced with diamond-shaped faded red tiles. " +
        "It runs all the way around the stadium.\n"); 

    add_item(({"stones", "stone"}), "Do you want to look at " +
               "the marble stones or the blocks that comprise " +
               "the wall?\n"); 

    add_item(({"mahogany", "marble stones", "marble"}), 
               "The material is of high quality. It appears that " +
               "no expense was spared here.\n"); 

    set_short("Walkway around the Firedrome"); 
    set_long(s + "The walkway runs " + 
             walkway_direc + " here.\n"); 
}

