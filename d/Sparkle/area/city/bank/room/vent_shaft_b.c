/*
 * /d/Sparkle/area/city/bank/room/vent_shaft_b.c
 *
 * This is the basement vent shaft room. Players use this room
 * to climb between the basement and the first floor. 
 *
 * Created April 2008, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
       set_short("Ventilation shaft beneath the Gnomes of Genesis");
       set_long("This is a ventilation shaft beneath the Gnomes of Genesis. "
           + "The shaft is not well lit, except for a tiny square of light, "
           + "which appears to be very high above. The ground and walls are "
           + "made of rust coloured brick, except for the western wall. The "
           + "western wall is made of metal and forms a grate around a small "
           + "wooden door. The only other choice for movement is up. A "
           + "ladder, which is bolted to the north wall, allows for upward "
           + "movement. Powerful gusts of wind come from the west and fly "
           + "upward, from the pull of a giant fan which appears to be "
           + "several meters above. The rushing air is overbearingly hot "
           + "and smells of oil and burning.\n\n");
        
    /* Add_Items */
       add_item( ({ "room", "shaft", "ventilation shaft" }),
             "The ventilation shaft is large enough for multiple people to "
           + "stand, but there would not be ample room for movement.\n");
    
       add_item( ({ "walls", "wall", "ground", "floor" }),
             "The walls, save the western wall, and ground are made of "
           + "rust coloured brick. They are warm to the touch, because the "
           + "heat coming from the west is constant and overbearing. The "
           + "wind does not seem to cool the bricks, even though it is "
           + "constantly blowing on the them.\n");
     
       add_item( ({ "north wall", "northern wall" }),
             "The north wall is unremarkable, except for a metal ladder that "
           + "ascends toward the huge fan and the tiny square of light.\n");
    
       add_item( ({ "south wall", "southern wall", "eastern wall",
                    "east wall" }),
             "This wall is unremarkable and rather mundane.\n");
        
       add_item( ({ "west wall", "western wall", "grate", "metal grate" }),
             "This wall is made of metal bars. They are spaced far enough "
           + "apart to allow air to flow freely, but are angled to prevent "
           + "any light from escaping the western room. A small wooden door "
           + "has been built in the center of the wall to allow access to the "
           + "west.\n");
     
       add_item( ({ "bars", "metal bars" }),
             "The metal bars are hot to the touch!\n");
          
       add_item( ({ "door", "small door", "wooden door", 
                    "small wooden door" }),
             "This door is made of wooden planks that are vertically placed "
           + "and nailed to a horizontal metal brace. The brace is halfway "
           + "from the ground and has a handle on the right side.\n");
     
       add_item( ({ "brace", "metal brace" }),
             "The metal brace holds the wooden door together. A handle is "
           + "hanging on the right side.\n");
      
       add_item( ({ "handle", "latch", "doorknob" }),
             "This handle is a small lever that is used to operate the "
           + "door.\n");
    
       add_item( ({ "air", "wind", "heat", "smell", "gust", "gusts" }),
             "Such a request is foolish and insane.\n");
         
       add_item( ({ "brick", "bricks", "clay", "rust bricks", "rust brick",
                    "rust coloured bricks", "rust coloured brick" }),
             "These blocks are made of kiln-baked clay. They are rust "
           + "coloured and are hot to the touch.\n");
     
        add_item( ({ "ladder" }),
             "This ladder is bolted to the northern wall and is not very "
           + "noteworthy, except for the fact that it is very hot!\n");
        
       add_item( ({ "fan", "giant fan", "huge fan", "large fan" }),
             "A giant fan seems to be the cause of the incredible gusts "
           + "of wind. It appears to be made of metal and is bolted to "
           + "the walls several meters above. It blocks all useful light "
           + "from the sky, which appears to be very far away.\n");
        
       add_item( ({ "light", "square", "tiny square", "tiny square of light",
                    "up" }),
             "A faint and rather useless amount of light shines from above. "
           + "This must be the sky at the end of the long ventilation "
           + "shaft.\n");
        
    /* Properties */
       add_prop(ROOM_I_LIGHT, 0); /* Unlit shaft */

    /* Exits */
       add_exit(BANK_ROOM + "gear_room_m", "west", 0); /* basement gear room */
       add_exit(BANK_ROOM + "vent_shaft_1", "up", 0); /* floor 1 vent */

    
} /* create_bank_room */