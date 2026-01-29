/* /d/Faerun/guilds/vampires/obj/vamp_painting5.c
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

int randdesc5_0;
int randdesc5_1;
int randdesc5_2;
int randdesc5_3;
int randdesc5_4;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 5 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box5_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box5_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box5_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox5_location_identifier();
    
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
        switch(randdesc5_0)
        {
            case 0:
            box_str = "This is a portrait of an obese and slovenly "
            +"hobgoblin. Wispy white hair flies out above the top of an "
            +"ugly round face punctuated with "
            +box_left_dial_str+" massive warts even as "
            +box_middle_dial_str+" streams of sweat roll down over his "
            +"pasty skin. A dirty red uniform is stretched almost to the "
            +"point of bursting over his obese body, even as his skinny "
            +"hands proudly grasp the hilt of an ornate sword. Rising up "
            +"from the garbage strewn around his feet are "
            +box_right_dial_str+" black flies flying erratically.\n";
            break;
            			
            case 1:
            box_str = "This is a painting of a dull grey cave which has "
            +"evidently become the proud home of some humanoid. A long "
            +"table covered in a red cloth rests against the back wall, "
            +"surrounded by "+box_left_dial_str+" lopsided wooden "
            +"stools. You also notice a box suffed with straw to serve as "
            +"a bed, with several quilts in "
            +box_middle_dial_str+" different shades of brown dumped "
            +"messily on top of it. Meanwhile, the several piles of "
            +"garbage left on the floor appear to have attracted the "
            +box_right_dial_str+" black rats which scurry around the "
            +"picture.\n";
            break;
            			
            case 2:
            box_str = "This is a painting of some rocky hills that climb "
            +"up out of a dense forest. The woods appear to be mostly "
            +"composed of pine and fir trees, but a cluster of "
            +box_left_dial_str+" poplar trees stand in front of the "
            +"hills. Several large cave mouths can be seen in the hills, "
            +"with "+box_middle_dial_str+" raggedly clothed goblins "
            +"sitting out in front of them. Flying above the trees are "
            +box_right_dial_str+" red breasted robins, highlighted as "
            +"they stand out against the dark grey clouds drifting "
            +"across a deep blue sky.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc5_1)
        {
            case 0:
            box_str = "This is a painting of "+box_left_dial_str+" "
            +"black-clad people standing sorrowfully at the edge of an open "
            +"grave. A white clad priestess with "
            +box_middle_dial_str+" brightly coloured flowers carefully "
            +"placed in her hair stands at the head of the grave, her open "
            +"mouth reciting words from the golden book held in her hands. "
            +"A thin old man with pale skin leans on his shovel in the "
            +"background, "+box_right_dial_str+" clumps of dark brown dirt "
            +"piled at his feet.\n";
            break;

            case 1:
            box_str = "This eerie painting depicts a graveyard at night. "
            +"A light fog drifts above the grass, swirling around "
            +box_left_dial_str+" worn and weathered gravestones in addition "
            +"to the large mausoleum bathed in cloudy moonlight. Carved "
            +"into the stone walls of the mausoleum are "
            +box_middle_dial_str+" noble looking faces, each one painted "
            +"in fine detail. Around the perimeter of the graveyard is an "
            +"iron fence running between "
            +box_right_dial_str+" posts made of brown fieldstone and "
            +"mortar.\n";
            break;

            case 2:
            box_str = "This morbid picture appears to be painted from the "
            +"perspective of someone lying at the bottom of an open grave. "
            +"Flat walls of dirt rise up on all sides, with the remains "
            +"of "+box_left_dial_str+" roots poking out into the open "
            +"air. In the middle of the painting, dark grey clouds roll "
            +"across the sky dumping their rain, "
            +box_middle_dial_str+" large fat drops plummeting down towards "
            +"your eyes. The only other feature you notice in the picture "
            +"is the silvery head of a shovel thrust out, dumping "
            +box_right_dial_str+" clods of dark black dirt down to cover "
            +"the occupant in the hole.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc5_2)
        {
            case 0:
            box_str = "You see a group of "
            +box_left_dial_str+" black-skinned orcs in this picture. "
            +"Each of the orcs is displaying their fangs in a cheerful "
            +"grin, each hoisting large foaming tankards of drink. A wide "
            +"window has been cut into the grey stone wall behind them "
            +"with "+box_middle_dial_str+" iron bars running vertically "
            +"in the middle of it. Piled on a low table in front of them "
            +"are "+box_right_dial_str+" bloody and mutilated human "
            +"heads, undoubtedly the inspiration for their celebration.\n";
            break;

            case 1:
            box_str = "This is a painting of a regimented and structured "
            +"room, what appears to be the quarters of some military "
            +"organization. Lined up against a wall on the left side of the "
            +"picture are "+box_left_dial_str+" beds, each of uniform "
            +"size and distance apart. Several pieces of fine wooden "
            +"furniture is depicted around the rest of the room, including "
            +"a round table with "+box_middle_dial_str+" stools huddled "
            +"beneath it. On the right side of the painting, you see parts "
            +"of "+box_right_dial_str+" stone steps as they march down out "
            +"of this room. A clear view of a cloudy sky through a narrow "
            +"window above the table shows only a hint of rooftops "
            +"below.\n";
            break;
            
            case 2:
            box_str = "Looming in the middle of this painting is a "
            +"massive city gate, as you gaze down upon a city full of "
            +"stone buildings. The gate opens into a narrow mountain pass, "
            +"and "+box_left_dial_str+" sturdy towers dot the city walls "
            +"which press up against the mountainside. Wandering along the "
            +"top of the walls are "+box_middle_dial_str+" armoured "
            +"guards walking their patrols, while the rest of the city "
            +"rests quietly in cold grey stone below. The only source of "
            +"colour you can see are "+box_right_dial_str+" orange "
            +"symbols, vaguely eye shaped, painted on some of the doors "
            +"in the city.\n";
            break;
        }
    }
	
	if (box == 3)
    {
        switch(randdesc5_3)
        {
            case 0:
            box_str = "This verdant painting depicts a lushly dense "
            +"thicket of bay trees. There are "+box_left_dial_str+" tall "
            +"cedars on either side of the thicket, and the ground is "
            +"absolutely covered in ferns. The thicket appears to run up "
            +"a hillside, where they are illuminated by "
            +box_middle_dial_str+" rays of sunlight which shine down "
            +"through the green canopy of the forest. Scampering around "
            +"the various tree branches are "+box_right_dial_str+" grey "
            +"squirrels, each painted in stunning detail.\n";
            break;
            		
            case 1:
            box_str = "This is a picture of a crystal blue pond in the "
            +"middle of a forest clearing. Thick bushes interspersed with "
            +"brightly coloured wildflowers circle the edge of the "
            +"pond as "+box_left_dial_str+" deer poke their way through "
            +"to take a drink. At one edge of the lake, a small stream "
            +"empties out to fall over "+box_middle_dial_str+" natural "
            +"terraces of stone, in a series of sparkling waterfalls. At "
            +"the bottom of the painting are the tops of "
            +box_right_dial_str+" large boulders, making it appear as "
            +"if you were there in person, hidden behind the rocks.\n";
            break;
            			
            case 2:
            box_str = "This is a painting of a forest clearing, filled "
            +"with all sorts of wildlife. You can see "
            +box_left_dial_str+" rabbits bounding through the tall "
            +"ferns that cover the forest floor, even as "
            +box_middle_dial_str+" deer huddle near a cluster of cedar. "
            +"Dozens of squirrels and chipmunks in shades of brown and "
            +"grey race along the tree branches, even as a multitude of "
            +"colourful birds fill the air. As you look closer, you seem "
            +"to be able to pick out "+box_right_dial_str+" black-skinned "
            +"orcs, each of them hidden and well concealed behind "
            +"the forest trees.\n";
            break;
        }
    }
	
	if (box == 4)
    {
        switch(randdesc5_4)
        {
            case 0:
            box_str = "This painting shows a large abandoned building "
            +"sitting on a well-travelled roadside. Thick planks of wood "
            +"cover the "+box_left_dial_str+" windows and door facing "
            +"the road, and the roof above appears to be collapsing. "
            +"Behind the building are "+box_middle_dial_str+" tall "
            +"willows, their long thin branches hanging over some nearby "
            +"wetlands. Several overgrown bushes line the front porch "
            +"as a series of "+box_right_dial_str+" flat stones mark "
            +"the path towards the broken stairs which lead to the "
            +"entrance. The bright, golden sun hangs low in a bright "
            +"blue sky which is only occasionally broken up with a "
            +"fluffy white cloud.\n";
            break;
            
            case 1:
            box_str = "This is a painting of a broken fortress, its jagged "
            +"remnants sitting upon a flat-topped, conical hill. The "
            +"slopes of the hill are mostly bare, with just "
            +box_left_dial_str+" small evergreens dotting the lush "
            +"grass. The ruins appear to be incredibly ancient, yet there "
            +"is still a lingering majesty the artist has captured here, "
            +"a hint of "+box_middle_dial_str+" tall towers faintly "
            +"outlined above the cracked stone walls. Yet most vivid "
            +"are "+box_right_dial_str+" large chunks of shattered "
            +"stone which have fallen beside what were once grand gates.\n";
            break;
            			
            case 2:
            box_str = "This painting shows a vast marsh stretching out "
            +"as far as the eye can see. You notice "
            +box_left_dial_str+" distinct shades of blue dancing across "
            +"the rippling waters, even as the long reeds bend in the "
            +"wind. Swimming amongst the tall grasses and lily pads "
            +"are "+box_middle_dial_str+" ducks, their mottled brown "
            +"feathers making them difficult to see clearly. Finding "
            +"purchase on the rare bits of solid ground are "
            +box_right_dial_str+" willow trees, their long branches "
            +"bending gracefully towards the wetlands below.\n";
            break;
        }
    }
    

        if (VAMPIRES_OBJHANDLER->query_box5_active() == 1)
        {
            return box_str;
        } 
            
    
    return "You look at the painting, but all you see is some "
    +"abstract colourful art that you don't understand.\n";
}


void
create_object()
{  
    setuid();
    seteuid(getuid());
    
    randdesc5_0 = random(3);
    randdesc5_1 = random(3);
    randdesc5_2 = random(3);
    randdesc5_3 = random(3);
    randdesc5_4 = random(3);
    
    set_name("painting5");
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