/*
 * Greathall of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
object sehis;
int ceremony_status = 0;

void
reset_room()
{
     if (!objectp(sehis)) { 
         sehis = clone_object(ELEMENTALIST_NPCS +"sehis");
         sehis->set_width_desc("lean");
         sehis->set_height_desc("tall"); 
         sehis->move_living("steps out from behind a door", TO); 
     } 
}

public void
create_temple_room()
{
    set_short("In a greathall");
    set_long("@@desc_long_description");

    try_item( ({ "passageway", "passageways", "hallway", "hallways" }),
        "You can head west and east and continue through the outer circle. It is also "
	  + "possible for some to proceed deeper into the temple through a hallway to the "
	  + "north.\n");

	try_item( ({ "brazier", "braziers" }),
		"A pair of large cast iron braziers in the north end of the room illuminate "
		+ "the area and namely a pair of long tapestries hanging in each side of the "
		+ "hallway leading north.\n");
	  
	try_item( ({ "tapestries"}),
		"Both tapestries reach from ceiling to floor and are crafted with great care "
		+ "and detail. The material appears to be a fine deep scarlet linen with a "
		+ "carefully embroided black hem. Each of the tapestries have their own "
		+ "embroidery and it would be possible to look at them individually.\n");
		
	try_item( ({"tapestry", "embroidery"}),
		"There are two tapestries. Do you wish to examine the left or the right?\n");
	
	try_item( ( {"left tapestry"}),
		"This is a vast scarlet-red tapestry that adorns the left side of the "
		+ "hallway leading north. With the use of thin pure silver threads "
		+ "someone has vowen a shiny silvery pentacle with points that glitter "
		+ "in the flickering radiance from the braziers nearby.\n");
						
	try_item( ({"radiance", "illumination", "ambience"}),
		"The room is bathed in a soft flickering radiance coming from a pair of "
		+ "braziers. The illumination highlights a pair of tapestries, a floor "
		+ "mosaic and causes the crystalline floor to flicker in vague beautiful "
		+ "multi-colored responses.\n");
	
	try_item( ({"right tapestry", "symbol", "vast symbol", "circle",
	    "circles", "illusion", }),
		"The tapestry hanging to the right of the northern hallway is a vast "
		+ "scarlet red linen. Using golden and platinum threads a vast pattern "
		+ "has been vowen into the tapestry. The pattern consists of three "
		+ "same-sized, perfect circles intertwined, surrounded by one large "
		+ "circle. The valuable threading gives the illusion of shimmering "
		+ "points travelling through the three circles in an eternal cycle.\n");
	
	try_item( ({"points", "glittering points"}),
		"Each of the points of the silvery pentacle is interwoven with a "
		+ "small jewel.\n");
		
	try_item( ({"jewel", "jewels", "shard", "shards"}),
		"The jewels are tiny shards of crystalline filigrated with rare gems. "
		+ "They are placed in on the five points of the pentacle, glittering "
		+ "in response to the ambience from the braziers. The glittering "
		+ "moves from point to point in a repeating dance of black and silver, "
		+ "blue and aquamarine, white and azure, green and brown, red and yellow.\n");
	
	try_item( ({"mosaic"}),
		"This colourful mosaic on the centre of the floor depicts a garden "
		+ "with five figures standing in a circle, heads bowed in prayer. "
		+ "In their center, a swirl of many coloured smoky tendrils "
		+ "billows towards a star-lit sky.\n");
             
    add_exit(ELEMENTALIST_TEMPLE + "outer13", "west");
    add_exit(ELEMENTALIST_TEMPLE + "outer14", "east"); 
    add_exit(ELEMENTALIST_TEMPLE + "private_chapel", "north", "@@cannot_enter_middle_circle_ceremony", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "entrance", "south"); 
    reset_room();
}

public void
set_ceremony (int i)
{
    ceremony_status = i;
}

public int
query_ceremony()
{
    return ceremony_status;
}

public void
notify_wizard_of_restricted_access_ceremony()
{
    // Give a message to wizards that they can enter because they are
    // wizards, even though normally this should not be accessible.
    if (this_player()->query_wiz_level() > 0)
    {
        write("\n=== Only members of the Elementalists of Calia can enter. However, "
            + "since you are a wizard, you are allowed entry. ===\n\n");
        write("\n=== There is a ceremony in progress. Please be polite as to not "+
            "disturb it. ===\n\n");
    }
}

public int
cannot_see_middle_circle_ceremony()
{
    if (this_player()->query_guild_name_lay() == "Elemental Worshippers of Calia"
        || this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"
        || this_player()->query_guild_name_lay() == "Elemental Seekers of Calia"
        || this_player()->query_guild_name_occ() == "Elemental Clerics of Calia")
    {
        // Allow seekers, worshippers and scop to enter the middle circle
        write("\n=== There is a ceremony in progress. Please be polite as to not "+
            "disturb it. ===\n\n");
        return 0;
    }
    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    // Non-wizards cannot use these exits.
    return 1;
}

public int
cannot_enter_middle_circle_ceremony()
{
    if (ceremony_status)
    {        
        if (!cannot_see_middle_circle_ceremony())
        {
            notify_wizard_of_restricted_access_ceremony();
            return 0;
        }
    
        // Non-wizards cannot use these exits.
        write("Only those who follow the Elementals may pass here.\n");
        return 1;
    }
    else
    {        
        if (!cannot_see_middle_circle())
        {
            notify_wizard_of_restricted_access();
            return 0;
        }
    
        // Non-wizards cannot use these exits.
        write("Only those who follow the Elementals may pass here.\n");
        return 1;
    }   
}

public string
desc_long_description()
{
    string long_desc = 
        "This is the large antechamber of the temple. This room serves as a "
		+ "central point and passageway. It is a massive octagonal shaped room with "
		+ "passageways to many parts of the temple. Large braziers shed a gentle "
		+ "illumination throughout the room which highlights two grand tapestries. " 
        + "There is a hallway to the north leading further into the temple, "
		+ "while heading west and east would allow you to continue walking in "
		+ "the outer circle. On the floor you see a grand mosaic which shimmers "
		+ "in response to the glow from the braziers. Southwards lies the "
		+ "temple entrance. "; 
    
    int bMiddleCircle = cannot_see_middle_circle();
    if (!bMiddleCircle)
    {
        return long_desc + "\n\n";
    }
    
    return long_desc += "\n\n";
}

