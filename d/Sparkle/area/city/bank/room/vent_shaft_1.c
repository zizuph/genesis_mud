/*
 * /d/Sparkle/area/city/bank/room/vent_shaft_1.c
 *
 * This is the ground floor vent shaft room. Players use this room
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
    set_short("Ventilation shaft in main branch the Gnomes of Genesis");
    set_long("This is a ventilation shaft in the main branch the Gnomes of "
        + "Genesis. The shaft is not well lit, except for a tiny square "
        + "of light, which appears to be very high above. The ledge that "
        + "you stand upon is made of metal. The railing on the ledge "
        + "and the walls are hot to the touch. A wooden door allows "
        + "access to the west and a metal ladder extends down the shaft. "
        + "Powerful gusts of wind come from below and fly upward, "
        + "from the pull of a giant fan which appears to be several "
        + "meters above. The rushing air is overbearingly hot and smells "
        + "of oil and burning.\n\n");
    
    /* Add_Items */
    add_item( ({ "room", "shaft", "ventilation shaft" }),
          "The ledge in this ventilation shaft is large enough for "
        + "multiple people to stand, but there would not be ample "
        + "room for movement.\n");
        
    add_item( ({ "square", "light", "above", "up", "tiny square",
                 "tiny square of light" }),
          "A faint and rather useless amount of light shines from above. "
        + "This must be the sky at the end of the long ventilation shaft.\n");
        
    add_item( ({ "fan", "giant fan", "large fan", "huge fan" }),
          "A giant fan seems to be the cause of the incredible gusts "
        + "of wind. It appears to be made of metal and is bolted to "
        + "the walls several meters above. It blocks all useful light "
        + "from the sky, which appears to be very far away.\n");
        
    add_item( ({ "ledge", "ground", "metal ledge" }),
          "The ledge on which you stand is not that large. A handful of "
        + "people could stand abreast, but much movement would be "
        + "dangerous. Railing, made of metal, has been attached to "
        + "prevent any accidents, though its protective worth is "
        + "questionable. A metal ladder is attached to the northern "
        + "wall and is accessable from the ledge.\n");
        
    add_item( ({ "railing", "metal railing" }),
          "The railing on the ledge is made of metal and is very warm to "
        + "the touch. It is a dark metal, which one may assume to be iron. "
        + "It is the only safety device in the visible area and is a poor "
        + "excuse for that.\n");
        
    add_item( ({ "door", "wooden door" }),
          "A thick wooden door grants access to the west. It is perfectly "
        + "centered on the western wall and seals the opening tightly. Made "
        + "of wood with metal braces, the door looks rather average. A "
        + "small latch allows one to use the door.\n");
       
    add_item( ({ "brace", "metal brace" }),
          "The metal brace holds the wooden door together. A handle is "
        + "hanging on the right side.\n");
        
    add_item( ({ "ladder", "metal ladder" }),
          "This ladder is bolted to the northern wall and is not very "
        + "noteworthy, except for the fact that it is very hot!\n");
        
    add_item( ({ "gusts", "powerful gusts", "wind", "hot air", "air" }),
          "Such a request is not only foolish, but insane.\n");
          
    add_item( ({ "walls" }),
          "The walls are made of rust coloured brick. They are warm to "
        + "the touch, because the heat coming from below is invariable "
        + "and overbearing. The wind does not seem to cool the bricks, "
        + "even though it is constantly blowing on the them.\n");
        
    add_item( ({ "brick", "bricks", "clay", "rust bricks", "rust brick",
                 "rust coloured bricks", "rust coloured brick" }),
          "These blocks are made of kiln-baked clay. They are rust "
        + "coloured and are hot to the touch.\n");
          
    add_item( ({ "north wall", "north walls", "northern wall" }),
          "The north wall is unremarkable, except for a metal ladder that "
        + "descends into a pit of utter darkness.\n");
        
    add_item( ({ "east wall", "east walls", "south wall", "south walls",
                 "eastern wall", "southern wall" }),
          "This wall is unremarkable and rather mundane.\n");
          
    add_item( ({ "west wall", "west walls", "western wall" }),
          "The western wall is made of rust coloured brick and has a wooden "
        + "door meticulously placed at its centre.\n");
        
 
    add_item( ({ "handle", "doorknob", "latch" }),
          "This handle is a small lever that is used to operate the "
        + "door.\n");
        
    add_item( ({ "down", "darkness", "pit" }),
          "Looking down, you see nothing, but darkness. Venturing down "
        + "might reveal more.\n");
    
    
    
    /* Properties */
    add_prop(ROOM_I_LIGHT, 0); /* Unlit shaft */

    /* Exits */
    add_exit(BANK_ROOM + "line3", "west", 0); /* first floor line 3 */
    add_exit(BANK_ROOM + "vent_shaft_b", "down", 0); /* basement vent */

    
} /* create_bank_room */