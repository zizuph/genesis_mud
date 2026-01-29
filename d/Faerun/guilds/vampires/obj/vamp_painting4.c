/* /d/Faerun/guilds/vampires/obj/vamp_painting4.c
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

int randdesc4_0;
int randdesc4_1;
int randdesc4_2;
int randdesc4_3;
int randdesc4_4;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 3 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box4_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box4_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box4_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox4_location_identifier();
    
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
        switch(randdesc4_0)
        {
            case 0:
            box_str = "At first glance, this is an abandoned home painted "
            +"only in shades of brown. Yet, where the great table lays "
            +"broken in the middle of the house, "
            +box_left_dial_str+" ghostly people sit around the whole table "
            +"enjoying a feast. Where "+box_middle_dial_str+" long stones "
            +"surround the base of an empty fire pit, the dim outline of "
            +"a smiling woman is visible stirring a cauldron full of food. "
            +"Barely noticeable on the walls are  "
            +box_right_dial_str+" impressions of small paintings hanging "
            +"comfortably. Each of these faint images are painted in "
            +"subtle, pastel colours. The sharp contrast depicting the "
            +"passage of time.\n";
            break;

            case 1:
            box_str = "This is a painting of a bright, if dusty, city "
            +"street. On the left side of the street, a tall city wall "
            +"stands high and proud, with "+box_left_dial_str+" jagged "
            +"shadows from the crenellations cutting down the middle of the "
            +"street. A busy crowd of people bustle around a long caravan "
            +"of "+box_middle_dial_str+" rich merchant wagons on their way "
            +"to (or perhaps from) market. Scattered along the sides of "
            +"the street are "+box_right_dial_str+" poorly-maintained "
            +"shacks, most of which have the appearance of abandoned "
            +"homes.\n";
            break;

            case 2:
            box_str = "This is a stunningly detailed image of a beggar "
            +"huddled before a broken and abandoned building. His greasy "
            +"white hair hangs down to his shoulders in "
            +box_left_dial_str+" dirty strings, stretching away from the "
            +"round bald spot growing atop his head. His dark brown eyes "
            +"stare out brightly from above a widely grinning mouth pocked "
            +"with gaps showing where "
            +box_middle_dial_str+" teeth have gone missing. His long limbs "
            +"are thin and spindly, while his gnarled fingers clutch a "
            +"cracked wooden bowl with "+box_right_dial_str+" small "
            +"copper coins sitting inside.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc4_1)
        {
            case 0:
            box_str = "This is a painting of a landscape so realistic, it "
            +"feels as if you are standing atop a tall cliff, surveying "
            +"the land as it spreads out before you. In the middle of the "
            +"picture is a great lake, with "+box_left_dial_str+" small "
            +"islands poking out of the surface of the placid waters. In "
            +"the distance, "+box_middle_dial_str+" craggy mountian peaks "
            +"march across the horizon as the sun peaks out between them. "
            +"Meanwhile a mountain river tumbles down in a series of "
            +box_right_dial_str+" waterfalls, a thin blue ribbon that "
            +"winds across the valley floor before emptying into "
            +"the lake.\n";
            break;
            
            case 1:
            box_str = "This is a picture of a bird's nest, wedged into a "
            +"narrow ledge on a tall cliff. Scattered inside the nest "
            +"are "+box_left_dial_str+" broken pieces of eggshells, while "
            +"a hatchling still perches on the edge of the nest. Soaring "
            +"in the air in front of the cliff, you spot "
            +box_middle_dial_str+" birds with their winds spread wide. "
            +"Adding some colour to the black rock of the cliff are "
            +box_right_dial_str+" scrawny looking bushes, sprouting out of "
            +"the thin crevasses which streak through the rock.\n";
            break;

            case 2:
            box_str = "A lightly wooded valley against the backdrop of a "
            +"tall, rocky cliff is the subject of this painting. There are "
            +box_left_dial_str+" fluffy white clouds floating across a "
            +"bright, blue sky above the brilliant, green forest below. In "
            +"the forefront of the picture there are "
            +box_middle_dial_str+" vividly coloured dragonflies which "
            +"somehow sparkle as you move your head from side to side. "
            +"Amidst all of the intense colours in the painting, you see "
            +"the almost comical figures of "+box_right_dial_str+" orcs "
            +"painted in shades of grey hiding in the boughs "
            +"of the trees.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc4_2)
        {
            case 0:
            box_str = "This is a painting of an old woman eating some "
            +"fruit. Her wispy white hair floats in the dusty breeze, while "
            +"her dark brown eyes sparkle beneath her heavily tanned skin. "
            +"Countless wrinkles crease her face as she gives a wide smile, "
            +"showing all of her "+box_left_dial_str+" remaining teeth. A "
            +"long, tattered brown robe with "+box_middle_dial_str+" blue "
            +"stripes covers her body, while several bone necklaces dangle "
            +"gently around her thin, frail neck. Her hands hold a part "
            +"of a fleshy yellow fruit, similar to the ones in the bushes "
            +"surrounding her, with "+box_right_dial_str+" tiny black "
            +"seeds and a large bite taken out of the side.\n";
            break;

            case 1:
            box_str = "A verdant oasis in the distance is the subject of "
            +"this painting. Dusty, brown dots of sand blow around the "
            +"edges of the picture, but in the middle a lush bloom of "
            +"green sprouts up around a crystal blue pond. There are "
            +box_left_dial_str+" tall palm trees which spring up to lean "
            +"over "+box_middle_dial_str+" men who have led their brown "
            +"horses to drink. You also happen to notice "
            +box_right_dial_str+" tents, alternating with red and white "
            +"stripes, hidden amongst the leafy green bushes which "
            +"surround the oasis.\n";
            break;

            case 2:
            box_str = "This is an image of a weary desert caravan, cutting "
            +"through the "+box_left_dial_str+" palm trees which spring "
            +"up around them as they move towards the middle of the oasis. "
            +"Dozens of dark green bushes have sprung up from the ground "
            +"here, and you can spot "+box_middle_dial_str+" small "
            +"animals hidden amongst them as they dart in and out of the "
            +"vegetation. It appears that the last "
            +box_right_dial_str+" merchants in the caravan have paused "
            +"to pick some of the juicy looking fruit which grows here.\n";
            break;
        }
    }
	
	if (box == 3)
    {
        switch(randdesc4_3)
        {
            case 0:
            box_str = "This is a painting depicting a small cluster of "
            +box_left_dial_str+" sandy brown tents which huddle on the "
            +"desert floor. Wandering around the tents, you can see "
            +box_middle_dial_str+" tall nomads busily scattered around the "
            +"camp, each attending to their own important duty. High "
            +"above, "+box_right_dial_str+" golden rays from a bright "
            +"yellow sun cut down through the pale blue sky to hammer "
            +"down upon the nomads with fearsome heat.\n";
            break;

            case 1:
            box_str = "This is a strange looking circular portrait of a "
            +"heavily bearded man. His strong brown eyes have a stern, "
            +"penetrating gaze and his brown skin is marked with "
            +box_left_dial_str+" angry looking scars. A strong, proud "
            +"beak of a nose looms above a grim looking smile, hidden "
            +"beneath a bushy beard with "
            +box_middle_dial_str+" distinct streaks of grey running "
            +"through it. Around the perimeter of the painting, there "
            +"smaller portraits of "+box_right_dial_str+" different "
            +"men, each in their own bordered circle.\n";
            break;
 
            case 2:
            box_str = "This image depicts a massive brown tent that appears "
            +"to blend in with the desert which surrounds it. The sun has "
            +"set behind it on the distant horizon and the first "
            +box_left_dial_str+" stars have begun to twinkle in the "
            +"cloudless night sky above. Several smaller tents are "
            +"illuminated by the "+box_middle_dial_str+" campfires which "
            +"are scattered amongst them, each with a group of nomads "
            +"eating their dinners and chatting with eachoher. In the "
            +"entrance to the huge tent which is the main focus of the "
            +"painting, "+box_right_dial_str+" determined men are "
            +"marching out each holding a deadly looking sword in his "
            +"right hand.\n";
            break;
        }
    }
	
	if (box == 4)
    {
        switch(randdesc4_4)
        {
            case 0:
            box_str = "This is a picture of a wide beach of warm, golden "
            +"sand. The beach is heavily populated, both with people "
            +"relaxing on the sand and swimmers in the water. There are "
            +box_left_dial_str+" children building a massive sand castle "
            +"near the water, even as "+box_middle_dial_str+" adults stand "
            +"around them watching with large smiles on their faces. White "
            +"seagulls are painted everywhere, even as the sun peaks out "
            +"from behind the cover of the  "+box_right_dial_str+" fluffy "
            +"white clouds drifting across the sky.\n";
            break;

            case 1:
            box_str = "This is a painting of an old, green fishing boat "
            +"bobbing up and down in the blue water. There are  "
            +box_left_dial_str+" fishermen crowded on the small boat, "
            +"working with a series of nets as they sort their catch. "
            +"Circling around the boat in hopes of stealing a meal are "
            +box_middle_dial_str+" gulls, each hungrily eyeing the catch "
            +"flopping around the bottom of the boat. A long beach of "
            +"golden sand is visible nearby, with "
            +box_right_dial_str+" children on the shore beneath the "
            +"cloudy grey sky, watching as the fishermen work.\n";
            break;

            case 2:
            box_str = "This painting shows the details of "
            +box_left_dial_str+" seashells partially buried in a bed of "
            +"golden sand. The shells are delicately painted with fine "
            +"lines and subtle depths of colour. A small hermit crab walks "
            +"across the painting, apparently paused to look at the "
            +box_middle_dial_str+" brightly coloured pebbles clustered "
            +"together at the bottom of the picture. Engraved into the "
            +"wooden frame of the painting are the words 'Day "
            +box_right_dial_str+" at the Beach'.\n";
            break;
        }
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 4)
    {
        if (VAMPIRES_OBJHANDLER->query_box4_active() == 1)
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
    
    randdesc4_0 = random(3);
    randdesc4_1 = random(3);
    randdesc4_2 = random(3);
    randdesc4_3 = random(3);
    randdesc4_4 = random(3);
    
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