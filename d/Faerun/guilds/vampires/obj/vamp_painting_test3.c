/* /d/Faerun/guilds/vampires/obj/vamp_painting3.c
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

int randdesc3_0;
int randdesc3_1;
int randdesc3_2;
int randdesc3_3;
int randdesc3_4;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 3 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box3_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box3_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box3_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox3_location_identifier();
    
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
        switch(randdesc3_0)
        {			
            case 0:
            box_str = "You see a remarkable black-and-white painting "
            +"depicting a tall, slender tree rising up into the air amidst "
            +"a wintery forest. There are "+box_left_dial_str+" thick, " 
            +"snow-covered branches stretching out, covered in leaves "
            +"painted so light that they almost appear silvery. Scurrying "
            +"around the branches and concealed behind patches of snow, you "
            +"count "+box_middle_dial_str+" grey squirrels hiding "
            +"playfully as  "+box_right_dial_str+" black starlings are "
            +"circling the tree in mid-flight.\n";
            break;

            case 1:
            box_str = "This painting depicts an open forest clearing in "
            +"the winter. A massive fallen log is the central focus of the "
            +"picture, covered in snow as "+box_left_dial_str+" brown "
            +"rabbits huddle beside it. There is also a small copse of "
            +box_middle_dial_str+" tall trees clustered together on the "
            +"right side of the painting, illuminated by the bright yellow "
            +"sun that shines in the clear blue sky above. Completing the "
            +"picture, you notice deep holes in the snow, distinct "
            +"footprints of "+box_right_dial_str+" different travellers "
            +"who skirted around the left side of the log.\n";
            break;

            case 2:
            box_str = "You see an incredibly detailed picture of a strange "
            +"looking leaf with "+box_left_dial_str+" points on a black "
            +"background. The leaf itself appears to be green from one "
            +"angle, but as you move your head it seems to turn bronze "
            +"instead. Racing through the middle of the leaf are  "
            +box_middle_dial_str+" thin silvery streaks, sprouting like "
            +"jagged lightning bolts out away from the stem. The edges "
            +"of the painting are decorated with "
            +box_right_dial_str+" additional leaves, much smaller and "
            +"twisting as if falling away in a cold autumn breeze.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc3_1)
        {
            case 0:
            box_str = "You see a dark green forest, shrouded in darkness "
            +"with "+box_left_dial_str+" faint rays of sunlight filtering "
            +"through the thick canopy of leaves above. These beams of light "
            +"all seem to fall down on a hunched over warrior, kneeling "
            +"on the dirt path which winds its way through the trees. "
            +"Hovering around the fighter are "+box_middle_dial_str
            +" faintly spectral figures in long robes watching patiently "
            +"even as "+box_right_dial_str+" brown leaves, oddly "
            +"contrasting with the rest of the forest, flutter down "
            +"through the air around them.\n";
            break;

            case 1:
            box_str = "This painting depicts "+box_left_dial_str
            +" massive trees, their branches extended like clawed arms, "
            +"coming alive in the middle of a dark forest. Lunging forward "
            +"as if to burst out of the picture, subtle hints of enraged "
            +"faces appear in the bark of their trunks. Hidden in the "
            +"shadows are  "+box_middle_dial_str+" menacing pairs of "
            +"glowing red eyes, while  "+box_right_dial_str
            +" small birds take flight as they flee in fright.\n";
            break;

            case 2:
            box_str = "You a forest landscape depicting a labyrinth of "
            +box_left_dial_str+" wide paths winding through clusters of "
            +"tall trees so dense that they block out any light from "
            +"shining through. Further complicating the scene are "
            +box_middle_dial_str+" game trails, each crossing the larger "
            +"paths many times as they dart in and out of the tree "
            +"clusters. As you look closely, it appears that almost every "
            +"tree in the painting is from a different species save for  "
            +box_right_dial_str+" absolutely identical spruce trees in the "
            +"middle of the picture.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc3_2)
        {
            case 0:
            box_str = "This serene image shows a small village, settled in "
            +"a wide clearing at the bottom of a large forest valley. A "
            +"small dirt road has several brown wagons following it as it "
            +"winds past the "+box_left_dial_str+" large buildings in the "
            +"middle of the village, with "+box_middle_dial_str+" groups "
            +"of villagers wandering around the surrounding houses. On the "
            +"outskirts, "+box_right_dial_str+" thin streams flow out of "
            +"the woods, slowly gathering into one larger river in the "
            +"distance.\n";
            break;

            case 1:
            box_str = "Hundreds of tall, green trees dot a hillside as a "
            +"brilliant blue sky soars overhead. A winding river on the "
            +"left side of the painting cuts through the forest, tumbling "
            +"over a series of "+box_left_dial_str+" waterfalls before "
            +"running off the edge of the picture. The sun is partially "
            +"hidden behind "+box_middle_dial_str+" snow-white clouds "
            +"which float across the sky, but still shines down on "
            +box_right_dial_str+" black crows as they circle above the "
            +"wooded valley.\n";
            break;

            case 2:
            box_str = "This is a painting of a sparkling blue river "
            +"running through a rocky dike. There are "
            +box_left_dial_str+" tall, green trees standing on the far "
            +"bank of the river as a brilliant yellow sun beats down out "
            +"of a clear blue sky. The dike itself has been built from "
            +"large fieldstones, "+box_middle_dial_str+" of which have "
            +"been painted in excrutiating detail in the middle of the "
            +"picture. Countless smaller rocks and gravel have been used "
            +"as filler, all piled up at the edge of a small dirt track "
            +"which skirts the dike. Marching along the path are  "
            +box_right_dial_str+" orcs, each wearing identical armours "
            +"and wielding wicked looking weapons.\n";
            break;
        }
    }
	
	if (box == 3)
    {
        switch(randdesc3_3)
        {
            case 0:
            box_str = "This is a painting of an old well, broken as "
            +box_left_dial_str+" of the stones have fallen from the front "
            +"side to lay sprawling on the ground before it. An old wooden "
            +"bucket rests on the ground beside the well, tied to a frayed "
            +"old rope which loops "+box_middle_dial_str+" times around "
            +"a rusty winch. Talls weeds sprout out of the ground around "
            +"the base of the well, with "+box_right_dial_str
            +" green vines encasing it as they climb up the stones.\n";
            break;

            case 1:
            box_str = "You see an abandoned terraced garden, sitting at "
            +"the back of an ancient manor house. There are "
            +box_left_dial_str+" stone steps which march down into what "
            +"remains of the garden, the beds now filled with weeds and "
            +"tall grass. Scattered around the grey stone paths that wind "
            +"through the garden are "+box_middle_dial_str+" piles of "
            +"broken masonry, fallen down after years of neglect. Yet as "
            +"you look closer, you see a barely visible image of the "
            +"garden as it must have looked in full bloom along with "
            +box_right_dial_str+" richly dressed nobles wandering along "
            +"the paths, all faintly superimposed over the now "
            +"ruined garden.\n";
            break;
 
            case 2:
            box_str = "You see a carousing group of "+box_left_dial_str
            +" men, drinking and laughing outside what appears to be an "
            +"ancient mansion. The face of the mansion is showered in "
            +"luxury, with dozens of expensive windows displayed on its "
            +"face, but poorly maintained when you notice that "
            +box_middle_dial_str+" of the windows are actually broken. "
            +"The front porch is in similar disrepair, but the shadows "
            +"there carefully conceal another "
            +box_right_dial_str+" men, their hands firmly clasping the "
            +"hilts of the swords at their side.\n";
            break;
        }
    }
	
	if (box == 4)
    {
        switch(randdesc3_4)
        {
            case 0:
            box_str = "You see the swollen hills of some distant moorland "
            +"rising up and down like waves on a grassy green sea. Atop "
            +box_left_dial_str+" of the smaller hillocks, you see a "
            +"rusty, red heather spreading out, a strange reflection of "
            +"the "+box_middle_dial_str+" fiery red clouds which drift "
            +"past the rising sun. Far off in the distance, the purple "
            +"outlines of "+box_right_dial_str+" snow-capped mountain "
            +"peaks reach up into the morning sky, granting a certain sense "
            +"of serenity to the painting.\n";
            break;
 
            case 1:
            box_str = "This painting shows a shallow glen at the bottom of "
            +"a grassy hillside, dotted with "+box_left_dial_str
            +" patches of heather. Scattered along the ground are the "
            +"corpses of "+box_middle_dial_str+" soldiers, left behind "
            +"after falling to a superior foe in battle. Colourful "
            +"wildflowers bend in an unseen wind, while "
            +box_right_dial_str+" crows circle in the sky in anticipation "
            +"of the fresh feast below.\n";
            break;
 
            case 2:
            box_str = "You see a remarkable scene painted before you, a "
            +"tall picturesque castle with "+box_left_dial_str+" towers "
            +"rising proudly to hoist flags which flap bravely in the "
            +"wind. A winding road curves around "
            +box_middle_dial_str+" hills as it climbs up to the castle "
            +"gate, while countless green, grassy hills surround it as "
            +"they slowly grow into distant mountains. A brilliant blue "
            +"sky bears "+box_right_dial_str+" fluffy white clouds "
            +"which float past the bright sun sitting directly above the "
            +"castle.\n";
            break;
        }
    }
    

        if (VAMPIRES_OBJHANDLER->query_box3_active() == 1)
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
    
    randdesc3_0 = random(3);
    randdesc3_1 = random(3);
    randdesc3_2 = random(3);
    randdesc3_3 = random(3);
    randdesc3_4 = random(3);
    
    set_name("painting3");
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