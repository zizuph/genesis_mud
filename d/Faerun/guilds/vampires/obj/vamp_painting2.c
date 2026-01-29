/* /d/Faerun/guilds/vampires/obj/vamp_painting2.c
 * 
 * Vampire painting nr.2, for the vampires.
 *
 * Nerull 2021.
 * Credits to Varian for the descriptions.
 */

inherit "/std/object.c";

#include <stdproperties.h>
#include "../guild.h"


string box_str;
    
string box_left_dial_str;
string box_middle_dial_str;
string box_right_dial_str;

int randdesc2_0;
int randdesc2_1;
int randdesc2_2;
int randdesc2_3;
int randdesc2_4;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 2 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box2_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box2_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box2_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox2_location_identifier();
    
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
        switch(randdesc2_0)
        {
            case 0:
            box_str = "You see a dark, dense forest painted in dark greens "
            +"and every shade of grey which huddles at the base of a "
            +"steep, rocky mountainside. A narrow pond rests in the middle "
            +"of the painting, fed by a twisting, icy blue stream which "
            +"bounces over "+box_left_dial_str+" rocks as it tumbles through "
            +"the trees. While just beyond the pond you "
            +"spot "+box_middle_dial_str+" zombies, their ragged bodies a "
            +"broken mockery of life, knee deep in snow and clawing their "
            +"way through a small copse of "+box_right_dial_str
            +" fir trees.\n";
            break;
            
            case 1:
            box_str = "You see a ghastly group of "+box_left_dial_str
            +" skeletons, painted with such realism it feels that their "
            +"outstretched hands are clawing through the painting, grasping "
            +"desperately for you. A shadowy, grey forest is visible around "
            +"the perimeter of the painting, spitting out  "
            +box_middle_dial_str+" bone white leaves which swirl and jump "
            +"in an unseen wind. Yet, perhaps what catches your eye the most "
            +"are the "+box_right_dial_str+" pairs of tiny, glowing red "
            +"eyes which burn maliciously in the darkest black shadows, "
            +"the only splash of colour visible anywhere.\n";
            break;
            
            case 2:
            box_str = "You see a train of "+box_left_dial_str+" black "
            +"wraiths, their cruel eyes glowing red with malice, "
            +"floating restlessly through a thick, emerald forest. Thick, "
            +"grey tree trunks spiked with gnarled, twisted branches hide "
            +"in the background beneath the "+box_middle_dial_str+" large, "
            +"grey clouds which sprawl across the sky above, removing even "
            +"a hint of the sun. Scattered across the broken brown earth of "
            +"the forest floor, you notice "+box_right_dial_str+" thin "
            +"piles of moss covered bones, a mute tribute to the power "
            +"of the wraiths.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc2_1)
        {
            case 0:
            box_str = "You see a merry group of "+box_left_dial_str+" "
            +"dwarves celebrating at the edge of a small, rocky cliff. Behind "
            +"the dwarves, a tall grey mountain stretches up through a thin "
            +"knot of "+box_middle_dial_str+" clouds to brush against a "
            +"brilliant blue sky. Streaming down through the clouds "
            +"are "+box_right_dial_str+" rays of pale golden light from "
            +"the sun, bathing the dwarves in its warmth as they happily "
            +"raise their foaming tankards of beer in a joint toast.\n";
            break;

            case 1:
            box_str = "You see a lush green valley, tall grass bent in a "
            +"breeze as a lazy river slowly winds its way across the middle "
            +"of the painting. An unattended wicker basket full of food rests "
            +"upon a blanket at the river bank while "+box_left_dial_str+" "
            +"black ants climb over it. Several clusters of bellflowers peek "
            +"through the grass, painted in "+box_middle_dial_str+" distinct "
            +"shades of purple, while on the right side of the picture stands "
            +"a bright forest with "+box_right_dial_str+" songbirds hidden "
            +"amongst the trees.\n";
            break;
            
            case 2:
            box_str = "You see a magnificent landscape sprawling before you. "
            +"There are "+box_left_dial_str+" rocky grey mountains rising up "
            +"in the background, their snow-capped peaks clawing at a clear "
            +"blue sky. While "+box_middle_dial_str+" distinct streams tumble "
            +"down the mountainsides in a series of splashing waterfalls only "
            +"to collect themselves into a wide river that empties itself "
            +"out at the bottom right corner of the painting. The ground is "
            +"wrinkled with green grassy foothills, "+box_right_dial_str+" "
            +"of which are decorated with a grove of pine trees on top.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc2_2)
        {
            case 0:
            box_str = "You see a grotesque looking gargoyle huddled in the "
            +"stark, "
            +"charcoal stone of some gothic ceiling. A snarling mouth "
            +"reveals "+box_left_dial_str+" sharp fangs in a wicked sort "
            +"of grin, "
            +"as "+box_middle_dial_str+" wrinkles stream out from the "
            +"corners "
            +"of vengeful angry eyes to ripple across the leathery stone "
            +"cheeks. "
            +"Dark shadowy wings fan out from its back, as a ridged tail "
            +"with "+box_right_dial_str+" spikes curls around the clawed "
            +"feet "
            +"which clutch at the edge of the jet black wall.\n";
            break;

            case 1:
            box_str = "You see a dusty, empty temple long forgotten and "
            +"abandoned. There are "+box_left_dial_str+" thick pillars "
            +"reaching "
            +"up into a cavernous ceiling full of shadows. Grim walls, "
            +"decorated "
            +"with "+box_middle_dial_str+" pale skulls loom along the "
            +"sides of "
            +"the picture, before receding softly into the background. "
            +"The only "
            +"colour is in the middle of the painting, where a "
            +"bloodstained altar "
            +"stands, decorated with "+box_right_dial_str+" swirling "
            +"azure runes "
            +"which dance around the base.\n";
            break;

            case 2:
            box_str = "You see a massive demon, "+box_left_dial_str
            +" snaking "
            +"arms reaching out vengefully, each clutching the severed "
            +"head of some "
            +"unfortunate human. Broad, leathery wings stretch out from "
            +"its back, "
            +"brushing up against the  "+box_middle_dial_str+" stone "
            +"columns that "
            +"surround the demon. A wickedly spiked tail lashes out "
            +"against the "
            +"black stone of some grand chamber, illuminated only by  "
            +box_right_dial_str+" flickering torches which hang from "
            +"the walls.\n";
            break;
        }
    }
    
    if (box == 3)
    {
        switch(randdesc2_3)
        {
            case 0:
            box_str = "You see "+box_left_dial_str+" moonbeams filtering "
            +"down from the inky night sky to illuminate the snow-covered "
            +"branches of an ancient forest. Pines trees tinted in dark "
            +"shades of green dominate the forest scene, with "
            +box_middle_dial_str+" massive oak trees standing tall " 
            +"in the background. The snow on the ground seems almost blood "
            +"red in the moonlight, or perhaps it is the corpse of a minotaur "
            +"in the middle of the painting, leaning against a large boulder, "
            +box_right_dial_str+" feathered arrows protruding out from "
            +"its chest.\n";
            break;

            case 1:
            box_str = "You see "+box_left_dial_str+" heavily armed "
            +"minotaurs "
            +"marching through a brilliant forest, sparkling in every "
            +"shade of "
            +"green imaginable. The brown dirt of the forest path is lined "
            +"with "+box_middle_dial_str+" moss covered logs while thick "
            +"bushes fill the forest floor on either side of the trail. "
            +"Fluttering "
            +"above the trees in the blue sky above are "
            +box_right_dial_str+" brightly coloured birds, dipping and "
            +"diving above the trees.\n";
            break;

            case 2:
            box_str = "You see a wildlife scene in a lush, ancient forest. "
            +"Tall "
            +"oaks with massive trunks of a reddish-brown and thick pine "
            +"trees "
            +"with their wide evergreen brances fill the painting. There are "
            +box_left_dial_str+" colourful butterflies dancing in the air "
            +"above a "
            +"small, shy deer which hides behind the oaks. Zipping "
            +"through "
            +"the air are "+box_middle_dial_str+" small birds, darting "
            +"in and out "
            +"of the forest canopy. While "+box_right_dial_str+" fluffy "
            +"brown hares "
            +"peek out from the thick forest undergrowth.\n";
            break;
        }
    }
    
    if (box == 4)
    {
        switch(randdesc2_4)
        {
            case 0:
            box_str = "You see a narrow path winding up from the base of a "
            +"tall, snowy mountain. Dug into the dirt are  "
            +box_left_dial_str+" sets of strange animal tracks, huge "
            +"footprints "
            +"which each appear to boast "+box_middle_dial_str+" long claws. An "
            +"icy mist appears to settle over everything, including the  "
            +box_right_dial_str+" twisted, stunted oak trees that grow out "
            +"of the mountainside.\n";
            break;
            
            case 1:
            box_str = "You see the entrance to an ancient tomb, weathered "
            +"and "
            +"mostly forgotten by the world. Carved into the side of an icy, "
            +"grey mountain, black stone doors are bound by "
            +box_left_dial_str+" links of heavy iron chain latched by a "
            +"padlock. "
            +"Before the doors are "+box_middle_dial_str+" smooth stones "
            +"forming a "
            +"path, flanked by "+box_right_dial_str+" oak trees which "
            +"rise up out of "
            +"the thick green briar patch.\n";
            break;

            case 2:
            box_str = "You see a tall, black obelisk covered with "
            +box_left_dial_str+" strange runes running from top to bottom. "
            +"The "
            +"obelisk is in a hillside clearing, with "+box_middle_dial_str
            +" pine trees painted in clear, stunning detail just behind it, "
            +"before "
            +"melting away into a dense evergreen forest. Clumped long the "
            +"bottom "
            +"of the painting, you notice "+box_right_dial_str+" bunches of "
            +"briars, their sharp throns almost sparkling in the misty air, "
            +"leaving "
            +"the impression that you are hidden amongst them, silently "
            +"keeping watch on the tall obelisk before you.\n";
            break;
        }
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 2)
    {
        if (VAMPIRES_OBJHANDLER->query_box2_active() == 1)
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
    
    randdesc2_0 = random(3);
    randdesc2_1 = random(3);
    randdesc2_2 = random(3);
    randdesc2_3 = random(3);
    randdesc2_4 = random(3);
    
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