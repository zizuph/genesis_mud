/* /d/Faerun/guilds/vampires/obj/vamp_painting6.c
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

int randdesc6_0;
int randdesc6_1;
int randdesc6_2;
int randdesc6_3;
int randdesc6_4;


string contours()
{
    int box;
    
    int box_left_dial;
    int box_middle_dial;
    int box_right_dial;
    
    // Painting 6 is all about clues for the first puzzle box.
    box_left_dial = VAMPIRES_OBJHANDLER->query_box6_left_value();
    box_middle_dial = VAMPIRES_OBJHANDLER->query_box6_middle_value();
    box_right_dial = VAMPIRES_OBJHANDLER->query_box6_right_value();
    
    box = VAMPIRES_OBJHANDLER->query_puzzlebox6_location_identifier();
    
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
        switch(randdesc6_0)
        {
            case 0:
            box_str = "This is a painting of some underground tunnel. Dark "
            +"shadows fall away from the viewer's perspective, most "
            +"notably catching on the "+box_left_dial_str+" stalactites "
            +"which hang from the ceiling here. Scattered across the "
            +"floor of the tunnel are "+box_middle_dial_str+" separate "
            +"clumps of some pale fungus which thrive in the damp "
            +"darkness. Yet in the blackest of shadows in this picture, "
            +"you can see "+box_right_dial_str+" sets of eyes faintly "
            +"gleaming, waiting in the gloom.\n";
            break;
            			
            case 1:
            box_str = "This is a picture of "
            +box_left_dial_str+" goblins huddled in a cave. Their flat "
            +"faces contorted in an expression of terror, their yellow "
            +"and green skinned arms thrust forward protectively from "
            +"you the viewer. An apparently lifeless body of a small "
            +"goblin lays on the rocky ground before them, his neck "
            +"covered with "+box_middle_dial_str+" pairs of bloody "
            +"punctures, the sort fangs might make. Hanging on the "
            +"ceiling above the goblins, unobtrusive and hidden, are "
            +box_right_dial_str+" black bats watching silently.\n";
            break;
            		
            case 2:
            box_str = "This inspiring painting displays a great battle "
            +"of "+box_left_dial_str+" human adventurers being ambushed "
            +"by "+box_middle_dial_str+" small, wiry goblins and "
            +box_right_dial_str+" of their meanacing hobgoblin allies. "
            +"The fight is taking place in a dark rocky tunnel, with "
            +"the adventurers trapped in a small cave at the end. With "
            +"swords flashing and arrows flying through the shadows, the "
            +"picture brings with it an almost magical feeling of "
            +"excitement that thrums through your body.\n";
            break;
        }
    }
    
    if (box == 1)
    {
        switch(randdesc6_1)
        {
            case 0:
            box_str = "This is a painting of a gigantic spider, with "
            +"beady eyes and venemous fangs which stare out in an eager, "
            +"predatory manner. The spider appears to be inside a large "
            +"stone tunnel where "+box_left_dial_str+" humans appear to "
            +"be encased in webbing, hanging from the ceiling. Scattered "
            +"on the smooth floor of the tunnel are "
            +box_middle_dial_str+" sharp swords and "
            +box_right_dial_str+" sturdy wooden shields, undoubtedly the "
            +"remnants of the spider's victims.\n";
            break;
            
            case 1:
            box_str = "This is a picture of a grey tunnel which fades "
            +"away to black in the deepest shadows. The smooth walls and "
            +"floor of the tunnel are disturbed only by "
            +box_left_dial_str+" shallow steps which descend into the "
            +"shadows and "+box_middle_dial_str+" broken bits of stone "
            +"pushed up against the walls. Almost invisible along the "
            +"ceiling, you notice the artist has delictely painted "
            +"in "+box_right_dial_str+" pale silvery-white webs which "
            +"cling to the stone.\n";
            break;
            			
            case 2:
            box_str = "This painting depicts a menacing stone tower in "
            +"the cleft of a jagged mountain, guarding a narrow pass. "
            +"You notice "+box_left_dial_str+" small windows carved into "
            +"the side of the tower, each providing a clear view of the "
            +"surrounding land. The narrow road it guards twists and "
            +"turns around "+box_middle_dial_str+" rugged outcropping "
            +"of rock from the mountainside, while circling in the air "
            +"above are "+box_right_dial_str+" large black crows, "
            +"distinctly visible against the grey clouds that cloak "
            +"the sky above.\n";
            break;
        }
    }
    
    if (box == 2)
    {
        switch(randdesc6_2)
        {
            case 0:
            box_str = "This painting appears to be a spinning blur of "
            +"brilliant blue hues mixed with a frothy white. The spiral "
            +"grows tighter in the middle of the picture, where "
            +box_left_dial_str+" white tear-shaped spots of paint jump "
            +"out from a background of midnight blue. Yet, as you look "
            +"closer, you notice that there are "
            +box_middle_dial_str+" thin brown lines inserted into the "
            +"swirl with "+box_right_dial_str+" small green shapes and "
            +"suddenly you understand they are leaves and branches "
            +"caught in the powerful pull of a mighty whirlpool.\n";
            break;
            
            case 1:
            box_str = "This is a picture of lushly verdant jungle "
            +"clearing. Surrounding the edges of the painting are "
            +box_left_dial_str+" tall trees, with "
            +box_middle_dial_str+" dark green bushes crouching at "
            +"their feet. Dozens of leafy vines hang down from the "
            +"tree branches which stretch out over the rippling waters "
            +"of a dark blue pond mostly hidden by a moss-covered "
            +"ledge. Long, thick grass carpets the floor of the "
            +"clearing, interrupted by "
            +box_right_dial_str+" grey boulders all covered in lichen.\n";
            break;
            			
            case 2:
            box_str = "This picture displays a rushing stream cutting "
            +"through a lush jungle before it swirls out to empty into "
            +"a large pond. The water crashes and splashes up against "
            +box_left_dial_str+" jagged rocks which peak out above the "
            +"surface of the stream, spraying against the thick "
            +"vegetation that lines the banks. Sliding between the trees "
            +"you notice "+box_middle_dial_str+" monkeys climbing "
            +"branches and vines, even as "
            +box_right_dial_str+" small grey seabirds float in the "
            +"open air.\n";
            break;
        }
    }
	
	if (box == 3)
    {
        switch(randdesc6_3)
        {		
            case 0:
            box_str = "This aquatic painting uses just "
            +box_left_dial_str+" distinct colours of blue to define the "
            +"background waters. A rich golden sand covers the sea "
            +"bed, frequently distrubed by large rocks, drifting "
            +"seaweed and "+box_middle_dial_str+" little red starfish. "
            +"A small cave hidden in the rocks appears to be the home "
            +"of a large crab hidden in the shadows. Sprinkled across "
            +"the background of the picture are "
            +box_right_dial_str+" schools of fish, their silvery skin "
            +"sparkling radiantly.\n";
            break;
            	
            case 1:
            box_str = "This portrait depicts the torso of a stunningly "
            +"lovely woman, with perfectly symmetrical features in front "
            +"of a featureless brown horizon and a peculiarly "
            +"greenish-blue sky. Her long golden hair is decorated "
            +"with "+box_left_dial_str+" delicate white flowers and "
            +"flows down to conceal her bare breasts. Hanging from her "
            +"thin arms are "+box_middle_dial_str+" fine golden "
            +"bracelets, each uniquely engraved and set with tiny "
            +"sparkling gemstones. It is only when you notice the "
            +box_right_dial_str+" iridescent scales peeking out along "
            +"her exposed hip that you understand she is actually "
            +"a mermaid.\n";
            break;
            			
            case 2:
            box_str = "This is a painting of a great white shark as it "
            +"swims near the ocean floor. Deadly black eyes stare out "
            +"emotionlessly, as "+box_left_dial_str+" of its razor "
            +"sharp teeth peek out from a mostly closed mouth. Its "
            +"rough skin is creased with "+box_middle_dial_str+" "
            +"long scars and its dorsal fin is deeply notched. Swimming "
            +"just behind the shark are "
            +box_right_dial_str+" silvery fish, too small to be "
            +"worthy of notice by the great predator.\n";
            break;
        }
    }
	
	if (box == 4)
    {
        switch(randdesc6_4)
        {
            case 0:
            box_str = "This painting shows an old, white-bearded "
            +"fisherman working on his small red dory. Circling above "
            +"his head are "+box_left_dial_str+" faint puffs of smoke "
            +"curling up from the wooden pipe clenched tightly in his "
            +"teeth. He appears to be pulling in a net with "
            +box_middle_dial_str+" small, silvery fish writhing in "
            +"it even as several white-capped waves crash against his "
            +"boat. A bright, golden sun shines in the bright blue "
            +"sky above him, even as "+box_right_dial_str+" white "
            +"gulls float on the breeze.\n";
            break;
            
            case 1:
            box_str = "This appear to be a picture of the ocean floor, "
            +"where "+box_left_dial_str+" large patches of seaweed "
            +"flutter in the direction of a strong ocean current. A "
            +"long slender eel weaves its way through a cluster of "
            +box_middle_dial_str+" reddish rocks while a small green "
            +"octopus crawls along the sea bed. Far off in the distance "
            +"you notice "+box_right_dial_str+" creatures which appear "
            +"to be half-human and half-fish, each holding a long "
            +"trident in their hands as they swim through the murky "
            +"blue depths.\n";
            break;

            case 2:
            box_str = "This beautiful seascape is definitely the more "
            +"captivating paintings you have seen. A large sting ray "
            +"swims in the forefront of the picture, followed by "
            +box_left_dial_str+" bright yellow fish, as it drifts "
            +"across the ocean floor. Nearby a large school of fish "
            +"scatter in all directions as a long silver barracuda "
            +"sweeps in for dinner, its jaws open wide. In the upper "
            +"left hand corner of the painting, "
            +box_middle_dial_str+" dolphins chase each other "
            +"playfully and "+box_right_dial_str+" red fish duck "
            +"in and out of an ancient shipwreck half-buried in the "
            +"sand.\n";
            break;
        }
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 6)
    {
        if (VAMPIRES_OBJHANDLER->query_box6_active() == 1)
        {
            return box_str;
        } 
    }        
    
    return "You look at the painting, but all you see is some "
    +"abstract colourful art that you don't understand.\n";
}


void set_paintingscene()
{
    set_long(contours);
}


void
create_object()
{  
    setuid();
    seteuid(getuid());
    
    randdesc6_0 = random(3);
    randdesc6_1 = random(3);
    randdesc6_2 = random(3);
    randdesc6_3 = random(3);
    randdesc6_4 = random(3);
    
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