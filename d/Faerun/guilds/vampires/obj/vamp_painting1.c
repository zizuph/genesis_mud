/* /d/Faerun/guilds/vampires/obj/vamp_painting1.c
 * 
 *
 */

inherit "/std/object.c";

#include <stdproperties.h>
#include "../guild.h"


string box_str;
    
string box_left_dial_str;
string box_middle_dial_str;
string box_right_dial_str;

int randdesc1_0;
int randdesc1_1;
int randdesc1_2;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 1 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box1_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box1_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box1_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox1_location_identifier();
    
    switch(box_left_dial)
    {
        case 0:
        box_left_dial_str = "zero";
        break;
        
        case 1:
        box_left_dial_str = "one";
        break;
        
        case 2:
        box_left_dial_str = "two";
        break;
        
        case 3:
        box_left_dial_str = "three";
        break;
        
        case 4:
        box_left_dial_str = "four";
        break;
        
        case 5:
        box_left_dial_str = "five";
        break;
        
        case 6:
        box_left_dial_str = "six";
        break;
        
        case 7:
        box_left_dial_str = "seven";
        break;
        
        case 8:
        box_left_dial_str = "eight";
        break;
        
        case 9:
        box_left_dial_str = "nine";
        break;
        
        case 10:
        box_left_dial_str = "ten";
        break;
    }
    
    switch(box_middle_dial)
    {
        case 0:
        box_middle_dial_str = "zero";
        break;
        
        case 1:
        box_middle_dial_str = "one";
        break;
        
        case 2:
        box_middle_dial_str = "two";
        break;
        
        case 3:
        box_middle_dial_str = "three";
        break;
        
        case 4:
        box_middle_dial_str = "four";
        break;
        
        case 5:
        box_middle_dial_str = "five";
        break;
        
        case 6:
        box_middle_dial_str = "six";
        break;
        
        case 7:
        box_middle_dial_str = "seven";
        break;
        
        case 8:
        box_middle_dial_str = "eight";
        break;
        
        case 9:
        box_middle_dial_str = "nine";
        break;
        
        case 10:
        box_middle_dial_str = "ten";
        break;
    }
    
     switch(box_right_dial)
    {
        case 0:
        box_right_dial_str = "zero";
        break;
        
        case 1:
        box_right_dial_str = "one";
        break;
        
        case 2:
        box_right_dial_str = "two";
        break;
        
        case 3:
        box_right_dial_str = "three";
        break;
        
        case 4:
        box_right_dial_str = "four";
        break;
        
        case 5:
        box_right_dial_str = "five";
        break;
        
        case 6:
        box_right_dial_str = "six";
        break;
        
        case 7:
        box_right_dial_str = "seven";
        break;
        
        case 8:
        box_right_dial_str = "eight";
        break;
        
        case 9:
        box_right_dial_str = "nine";
        break;
        
        case 10:
        box_right_dial_str = "ten";
        break;
    }
            
    if (box == 0)
    {
        switch(randdesc1_0)
        {
            case 0:
            box_str = "This painting depicts "+box_left_dial_str+" seagulls circle "
			+"around "
            +box_middle_dial_str+" wooden fishing boats on a sunny day. "
			+"You also notice "
			+box_right_dial_str+" fishermen that wanders around on the "
			+"sandy beach, apparently looking for something.\n";
            break;
            
            case 1:
            box_str = "This painting shows a wave crashes into the sandy beach, partly covering "
			+box_left_dial_str+" green-shelled crabs. It is raining and the "
			+"sky is covered by "
            +box_middle_dial_str+" massive storm clouds. Bolts of "
			+"lightning are "
			+"striking into the ocean at "+box_right_dial_str+" different "
			+"places at once.\n";
            break;
            
            case 2:
            box_str = "This painting shows "
			+box_left_dial_str+" ships sailing away in the distance "
			+"towards the horizon, "
			+"accompanied with "
            +box_middle_dial_str+" white clouds in the sunny sky. Near "
			+"the beach, you "
			+"see an old pier with "+box_right_dial_str+" crows circling "
			+"above it.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc1_1)
        {
            case 0:
            box_str = "In this painting, you see some bright flowers and "
			+box_left_dial_str+" bumblebees circling about. Near the "
			+"circling wall of stone you see "+box_middle_dial_str
			+" stones resting at the ground, while "
			+box_right_dial_str+" crows are resting on top of "
			+"the farmhouse to the west.\n";
            break;

            case 1:
            box_str = "In this painting, you see a goat is chewing various vegetation from the "
			+"flowerbed, "
			+"surrounded by "+box_left_dial_str+" beautiful butterfiles. "
			+"Various colourful flowers cast some shade on "
			+box_middle_dial_str+" beetles battling on the ground, near "
			+box_right_dial_str+" small ponds of water.\n";
            break;

            case 2:
            box_str = "In this picture, you notice "+box_left_dial_str+" bees are buzzing about "
			+"near "
			+box_middle_dial_str+" bright flowers, while "
			+box_right_dial_str+" catepillars crawls about near the stone "
			+"wall.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc1_2)
        {
            case 0:
            box_str = "In this picture, you see that near the surface of the brown swamp water, "
			+box_left_dial_str
			+" corpses of men floats about while being slowly devoured by "
			+box_middle_dial_str+" unidentified swamp creatures. Next to "
			+"the corpses, you see "+box_right_dial_str+" arrows.\n";
            break;

            case 1:
            box_str = "In this picture, you see "+box_left_dial_str+" pair of eyes submerged "
			+"from the murky water, watching "+box_middle_dial_str
			+" lost injured "
			+"elven maidens struggling to survive. Blooded by "
			+box_right_dial_str
			+" cuts from crude blades, blood is flowing and it seems "
			+"hopeless to survive.\n";
            break;

            case 2:
            box_str = "In this picture, you see a horrible faceless spectre is busy dragging the "
			+"remains of "
			+box_left_dial_str+" humanoids within into the murky "
			+"waters, making "
			+box_middle_dial_str+" ripples on the surface in the "
			+"process. Large "
			+"and broad, the "+box_right_dial_str+" trees create shadows in "
			+"every direction.\n";
            break;
        }
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 1)
    {
        if (VAMPIRES_OBJHANDLER->query_box1_active() == 1)
        {
            return box_str;
        } 
    }        
    
    return "You look at the painting, but all you see is some "
    +"abstract colourful art that you don't understand.\n";
}


void
create_object()
{  
    setuid();
    seteuid(getuid());
    
    randdesc1_0 = random(3);
    randdesc1_1 = random(3);
    randdesc1_2 = random(3);

    set_name("painting");
    add_name("old dusty painting");
    
    set_adj("old");
    add_adj("dusty");
    
    set_short("old dusty painting");
    set_pshort("old dusty paintings");
    
    set_long(contours);
    
    add_item(({"frame", "wooden frame"}), "There is a "
    +"carefully carved 'V' into the black wooden "
    +"frame containing the painting.\n");
    
    set_no_show_composite(1);
    
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, 1);
}