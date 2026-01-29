/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/main_tunnel_dam.c
 *
 *  This is the dam room of the sewers of Gont. It is the
 *  final destination of any sliding items from the main tunnels.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Below a high cliff" -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road15
 *
 * What is above and nearby?
 * Old pier (shire_pier) (east)
 * Road (city_road14) (north)
 * Thwil dock (pier3) (south)
 *
 *  Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

/* Defines */

/* Inheritance */
inherit MAIN_TUNNEL_BASE;

/* Global Variables */

/* Prototypes */
public void             init();
public void             create_tunnel_room();

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} // init

/* 
 * Function name:       create_tunnel_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_tunnel_room()
{
    // Descriptions Section
    set_short("Dammed sewer tunnel");
           
    set_long_extra("This is the lowest most spot in the sewers of Gont. All "
		+ "of the sewage flows to this point. Someone has, rather "
        + "ingeniously, constructed a dam in the water. It is located near "
        + "the end of the tunnel and blocks most solid objects from flowing "
        + "into the harbour.");
		   
    // Room Item Section                              
          
    add_item( ({ "dam", "makeshift dam" }),
            "This is a makeshift dam that someone has constructed. It would "
          + "appear that their intent was to let the sewage flow through "
          + "and larger items would get stuck. It is constructed with all "
          + "sorts of materials.\n");
          
    add_item( ({ "harbour", "harbor", "end of the tunnel", "tunnel end" }),
            "Just beyond the makeshift dam, the sewage is expunged from "
          + "the tunnel and into the harbour.\n");
  
    add_item( ({ "materials", "material", "objects", "solid objects" }),
            "All sorts! Some of it appears to be raw materials, such as wood "
          + "and stone. Some of it seems to be broken crafted items, "
          + "such as furniture legs, glass panes, crates, cloth, and metal "
          + "scraps. The rest of it looks to be general refuse that got "
          + "caught in the original frame.\n");
          
    add_item( ({ "refuse", "general refuse", "simple junk", "junk",
                 "tangles of hair", "food scraps", "broken tools",
                 "broken toys", "actual piles of shit", "shit", 
                 "broken tools and toys", "piles of shit" }),
            "The excrement and byproduct of a living city. Including, but "
          + "not limted to: Tangles of hair, bone, "
          + "food scraps, broken tools and toys, actual piles of shit and "
          + "simple junk.\n");          
          
    add_item( ({ "original frame", "frame" }),
            "Its hard to tell exactly what the original frame was, because "
          + "it has grown with every additional item caught in the flow. "
          + "Needless to say, it is a combination of all sorts of "
          + "materials.\n");
  
    add_item( ({ "raw materials", "raw material", "basic items",
                 "basic item" }),
            "Wood, stone, and other basic items that can be found in the "
          + "wild would be classified as a raw material. After a closer "
          + "inspection, bone (clear of flesh and whitened by time) can "
          + "be seen strewn about.\n");  
          
    add_item( ({ "wood" }),
            "The assortment of wood ranges from broken vein-like roots to "
          + "bits of log. The wood that is in the water lightly rises and "
          + "falls with any movement in the water. The other bits of wood "
          + "are pinned down in one manner or another, rendering them "
          + "motionless. while some of it appears new, the majority of the "
          + "pieces of wood are softened and discoloured by time.\n");
          
    add_item( ({ "bits of wood", "yew", "yew branch" }),
            "This yew branch could have easily made a brilliant staff - "
          + "the envy of any apprentice wizard - if it had been noticed "
          + "a year ago. Now it merely sits and rots.\n");

    add_item( ({ "bits of log", "log", "logs" }),
            "This is a genuine log of a tree. How it got in the sewer "
          + "system is not clearly apparent.\n");
          
    add_item( ({ "vein-like roots", "roots", "vein roots" }),
            "These roots form a rough web and are flexible. There must "
          + "be somewhere upstream where the roots of a tree penetrated "
          + "the tunnels, or they were somehow deposited down a sewer "
          + "grate during a storm.\n");          
          
    add_item( ({ "stone", "stones", "gontish stone", "Gontish stone" }),
            "The stone of the walls is solid and cold to the touch. The "
          + "stone of the makeshift dam is rather fragmented, brittle, but "
          + "still cold to the touch. Both appear to match the stone that "
          + "can be found in the mountain. This is Gontish stone, not some "
          + "cheap import.\n");
          
    add_item( ({ "broken crafted items", "broken items", "broken item",
                 "broken crafted item", "crafted items", "crafted item" }),
            "Once the pride of some craftsman, these are now the skeletal "
          + "framework of a subterranian dam in a sewer. At a glance you "
          + "can see furniture legs, glass panes, crates, cloth, and "
          + "scraps of metal.\n");  

    add_item( ({ "metal", "scraps", "scraps of metal", "metal scraps",
                 "ship parts", "rusty bits", "rusty weapons",
                 "rusty weapon", "rusty armours", "rusty armour",
                 "window frames", "countless nails", "nails", 
                 "rusty bits of weapon", "rusty bits of weapons",
                 "rusty bits of weapons and armour" }),
            "Twisted and rusted metal scraps are a cornerstone of this "
          + "makeshift dam. Perusing through, you can see some ship parts, "
          + "rusty bits of weapon and armour, some window frames, countless "
          + "nails, even some rusty old spoons.\n");          

    add_item( ({ "rusty spoon", "rusty spoons", "spoon", "spoons",
                 "old spoons", "old spoon" }),
            "Yes, spoons with rust on them. Even more might be found "
          + "in the heap.\n");
            
    add_item( ({ "cloth", "clothes", "fabric", "fabrics", "tunics",
                 "dresses", "pants", "undies", "cloths", "tunic", "dress",
                 "soiled clothes" }),
            "Clearly, someone thinks they can just dump their old, soiled "
          + "clothes down the sewer grates. Throughout the heap, you can "
          + "see torn tunics, dresses, pants, and unidentifiable fabrics.\n");      
          
    add_item( ({ "crates", "crate", "broken crates" }),
            "These are standard crates that would be used as shipping "
          + "containers on ships or in warehouses. Almost all of them "
          + "are broken and the few that are not, are empty.\n");         
          
    add_item( ({ "furniture", "broken furniture", "furniture legs",
                 "furniture leg" }),
            "Some townsman somewhere probably thought this would be the "
          + "last table he would ever have to buy. If he exists, he is "
          + "wrong.\n");
          
    add_item( ({ "glass", "glass panes", "pane of glass",
                 "panes of glass" }),
            "Broken glass. Another simple reminder that this place can "
          + "be dangerous. You should be careful if you look further in "
          + "the heap.\n");
          
    add_item( ({ "bones", "bone", "remains" }),
            "These are the remains of some creature. The bones are picked dry "
          + "and are discoloured by the sewage and time.\n");
          
    add_item( ({ "damn bait", "dam bait" }),
            "No. You do not find any damn bait.\n");
    
    add_item( ({ "sea", "bay", "ocean" }),
            "Nearby, the waters are off-coloured and don't look healthy. Far "
          + "away, the waters look clear and pure. It's amazing how nature "
          + "takes care of itself.\n");


   // Properties Section

    
    // Exits Section
    
    add_exit(SEWER_MAIN_TUNNEL + "low_west_1", "north", 0);
	
    
    set_downstream_enabled(0); // the dam is the end, so no need to stream downwards.
} // create_sewer_room

/*
 * Function name:       reset_room
 * Description  :       restore npcs and things as needed
 */
public void
reset_room()
{
   
        object dam_heap;
/*        object otbus; */

    if (!present("dam_heap"))
    {
        dam_heap = clone_object(SEWER_OBJ_DIR + "dam_heap.c");
        dam_heap->move(this_object());
    }
    
/*    if (!present("otbus"))
    {
        otbus = clone_object("/d/Sparkle/area/city/bank/npc/otbus");
        otbus->move(this_object());
    }
*/
    
} /* reset_room */
