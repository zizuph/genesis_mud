/*
 * /d/Sparkle/area/city/bank/room/gear_room_n.c
 *
 * This is the north gear room of the basement of the Gnomes of
 * Genesis. The steam engine of the building is shown here.
 *
 * Created April 2008, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */

/* Prototypes */
public string           add_desc(string item);
public string           get_default_desc(string item);
public string           get_gnome_desc(string item);

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    set_short("North gear room of the basement");
    set_long( &add_desc("long") );
        
       /* Add_Items */
       add_item( ({ "engine", "giant engine", "steam engine", "parts" }),
              &add_desc("engine"));
       
       add_item( ({ "room", "basement", "area", "cellar", "pit" }),
              "This room full of gears that are mounted above your head. "
            + "Gnomes seem to operate levers and gadgets that make all of "
            + "these machines work.\n");
            
       add_item( ({ "mountings", "mounting" }),
              "Wooden mountings keep gears and timbers in place. They allow "
            + "for these things to hang from the ceiling.\n");
                 
       add_item( ({ "tubes", "tube" }),
              "Metal tubes connect gadgets to the southwest. Closer "
            + "inspection can be done to the south.\n");
            
       add_item( ({ "gadgets", "gadget", "meters", "bells", "whistles",
                    "bell", "whistle", "button", "buttons" }),
              &add_desc("gadgets"));
                       
       add_item( ({ "gnomes", "gnome", "operator", "operators", "worker", 
                    "workers" }),
              &add_desc("gnomes"));
            
       add_item( ({ "module", "modules" }),
              "The furnace, boiler, machine or arm?\n");
            
       add_item( ({ "furnace", "fire" }),
              &add_desc("furnace"));
              
       add_item( ({ "hatch" }),
              "The hatch is difficult so see from here. Perhaps you should "
            + "inspect it from the south.\n");
            
       add_item( ({ "boiler", "tank", "large boiler", "boiler tank" }),
              &add_desc("boiler"));
            
       add_item( ({ "machine" }),
              &add_desc("machine"));
       
       add_item( ({ "fuel", "coal" }),
              "Gnomes seem to be working with coal, near the furnace. "
            + "It is difficult to see clearly from this vantage point.\n");
            
       add_item( ({ "arm", "extended arm", "mechanical arm" }),
              "To the south, you see a mechanical arm that gives movement "
            + "to a giant wheel. One should travel south to inspect it "
            + "more closely.\n");
           
       add_item( ({ "giant wheel", "large wheel", "big wheel" }),
              "To the south, a giant wheel spins quite quickly. It is mounted "
            + "to the ground, but is spun by the extended arm of the "
            + "machine. A band of tarnished leather spans the distance "
            + "between the giant wheel its smaller counterpart above.\n");
            
       add_item( ({ "leather", "tarnished leather", "band" }),
              "It is quite difficult to see from here. Perhaps you should step "
            + "closer to inspect it?\n");
      
       add_item( ({ "wheel", "wheels" }),
              "Which wheel would you like to inspect?\n");
                   
       add_item( ({ "small wheel", "smaller wheel", "tiny wheel" }),
              "To the south, a small wheel is connected to a long timber, "
            + "which extends above your head. Facing south and looking up, "
            + "the beam spins counterclockwise.\n");
            
       add_item( ({ "timber", "rod", "beam" }),
              "A large timber hangs from rotating mountings, just beneath "
            + "the ceiling. The timber goes through the small wheel, to the "
            + "south, and spins identically to it. A large gear is attached "
            + "to the beam, directly above you. Perhaps if you inspect the "
            + "gears you might learn more?\n");
            
       add_item( ({ "gear", "gears" }),
              "Above you, the timber is capped with a large vertical gear. "
            + "This gear is the first in a series of wildly spinning gears. "
            + "The following gears alternate between vertical and horizontal "
            + "and progresively get smaller as they are placed further "
            + "north. Near the northern wall, two gears are connected to one "
            + "gear that ends up making a split in the line. On the eastern "
            + "limb of gears, you notice four gears folling the split and "
            + "seven on the western limb. The limbs come back together and "
            + "connect to a giant vertical timber. Only one gear limb appears "
            + "to be spinning at a time.\n");
            
       add_item( ({ "gear limb", "limb", "gear limbs", "limbs" }),
              "A large gear is connected to two smaller gears, which appear "
            + "to lead to two different gear lines. One gear line has four "
            + "gears and the other has seven. This causes the gear lines to "
            + "spin opposite directions when engaged. Only one gear line is "
            + "engaged at a time, which spins the connecting gear one "
            + "direction or the other. "
            + "Each gear limb has one gear missing from the strand. The "
            + "gear appears to be connected to a pulley system, which allows "
            + "them to be raised and lowered to connect and disconnect the "
            + "limbs.\n");
       
       add_item( ({ "connecting gear" }),
              "The connecting gear is much like the splitting gear. It is "
            + "large and both limbs connect to it, thus bringing the strands "
            + "back together.\n");
            
       add_item( ({ "splitting gear" }),
              "The splitting gear is a large gear that has two smaller gears "
            + "attached, which causes a fork in the strand. This setup allows "
            + "for the gnomes to bring power to other parts of the room.\n"); 
            
       add_item( ({ "pulleys", "pulley system" }),
              "A pulley system allows a gnome to control the removable gears "
            + "from the gear limbs. This allows the connecting gear to spin "
            + "one direction or another. The pulleys are connected to levers "
            + "which are located near a chair near the north wall.\n");
        
       add_item( ({ "ground", "floor", "stone" }),
              "Dusty blocks of stone create the flat surface on which "
            + "you walk. They are grey in colour and do not strike you as "
            + "foreign or noteworthy.\n");
       
       add_item( ({ "wall", "walls" }),
              "Which wall would you like to examine?\n");
              
       add_item( ({ "north wall", "south wall", "southern wall",
                    "northern wall" }),
              "A tunnel leads north into a better lit room and south "
            + "toward the machine.\n");
            
       add_item( ({ "west wall", "western wall" }),
              "The western wall is too far in the distance, past the engine, "
            + "to inspect closely. Perhaps if the basement wern't so "
            + "steamy, you could see.\n");
            
       add_item( ({ "east wall", "eastern wall" }),
              "The eastern wall is made of metal bars. They are tilted to "
            + "allow hot air to escape the basement. They are tilted to "
            + "block the vision of onlookers.\n");
            
       add_item( ({ "ceiling", "top" }),
              "The ceiling is made of stone slabs. Their immense weight is "
            + "supported by the dense walls and the strategically placed "
            + "column.\n");
            
       add_item( ({ "column", "support", "pillar", "pillars", "columns",
                    "supports" }),
              "Stone columns are strategically placed to help support the "
            + "heavy ceiling. Many lives depend on the strength and "
            + "placement of these columns.\n");
              
       add_item( ({ "steam", "fog", "cloud", "soup" }),
              "Steam spews from a valve on the boiler. Whenever a gnome "
            + "pulls a specific lever, the room becomes a dense soup of "
            + "fog.\n");
            
       add_item( ({ "levers", "handles" }),
              "Gnomes use levers, as well as other gadgets, to manage "
            + "the engine.\n");
          
       /*add_item( ({ "chair", "strange chair", "interesting chair" }),
              "*/
            
            
        /* Properties */
    add_prop(ROOM_I_LIGHT, 1); /* Lit room */

    /* Exits */
    add_exit(BANK_ROOM + "gear_room_m", "south", 0); /* Middle gear room */
    add_exit(BANK_ROOM + "guard_room", "north", 0); /* Guard room */



    
} /* create_bank_room */


/*
 * Function name:       add_desc
 * Description  :       Checks to see if a gnome is doing the looking or 
 *                      not.
 */
public string
add_desc(string item)
{
    string race;
    string description;
    
    race = this_player()->query_race_name();
    switch (race)
    {
    case "gnome":
        description = get_gnome_desc(item);
        break;
        
    default:
        description = get_default_desc(item);
    }
    
    return description;
} /* add_desc */


/*
 * Function name:       get_gnome_desc
 * Description  :       All of the descriptions that only gnomes would 
 *                      see.
 */
public string
get_gnome_desc(string item)
{
    string description;
    
    switch (item)
    {
    case "long":
        description =
              "A giant engine is the main attraction of this basement. It "
            + "stands ominously to the southwest. "
            + "It appears very straightforward and simple. "
            + "This room is decently lit by the "
            + "fire that the gnomes constantly fuel. It is very hot in this "
            + "room and the air is thick. An interesting chair sits near the "
            + "wall.\n\n";
        break;            
        
    case "engine":
        description =
              "The giant steam engine consists of four parts. Heading "
            + "south will allow a closer look. From here you can tell "
            + "that it is a beautiful gizmo and "
            + "it works flawlessly.\n";
        break;
        
    case "gadgets":
        description =
              "Gnomes seem to manage the gadgets and other very important "
            + "things that are attached to the engine. Each module "
            + "has a team of operating gnomes and every gadget seems to "
            + "be professionally watched and monitored.\n";
        break;
        
    case "gnomes":
        description =
              "Gnomes manage each module of the engine, much like worker "
            + "bees manage a hive -- brilliantly and gracefully.\n";
        break;
              
    case "furnace":
        description =
              "Keen eyes! Travel south if you want to see details about "
            + "the furnace.\n";
        break; 
        
    case "boiler":
        description =
              "Keen eyes! Travel south if you want to see details about "
            + "the boiler.\n";
        break;
        
    case "machine":
        description =
              "Keen eyes! Travel south if you want to see details about "
            + "the machine.\n";
        break;
        
    default:
        description = get_default_desc(item);
    }
    
    return description;
} /* get_gnome_desc */


/*
 * Function name:       get_default_desc
 * Description  :       All of the descriptions that non-gnomes would 
 *                      see.
 */

public string
get_default_desc(string item)
{
    string description;
    
    switch (item)
    {
    case "long":
        description =
              "A giant engine is the main attraction of this basement. It "
            + "stands ominously to the southwest. "
            + "It appears very straightforward and simple. "
            + "This room is decently lit by the "
            + "fire that the gnomes constantly fuel. It is very hot in this "
            + "room and the air is thick. A strange chair sits near the "
            + "wall.\n\n";
        break;
            
    case "engine":
        description = "The giant steam engine consists of four parts. Heading "
            + "south will allow a closer look. From here you can tell "
            + "that the engine is noisy "
            + "and very dirty.\n";
        break;
    
    case "gadgets":
        description = "You see a wide assortment of unimportant and "
            + "confusing gadgets.\n";
        break;
        
    case "gnomes":
        description =
              "Gnomes manage each module of the engine, much like worker "
            + "bees manage a hive -- devoutly and unquestioningly.\n";
        break;
        
    case "furnace":
        description =
              "Travel south if you want to see details about "
            + "the furnace.\n";
        break; 
        
    case "boiler":
        description =
              "Travel south if you want to see details about "
            + "the boiler.\n";
        break;
        
    case "machine":
        description =
              "Travel south if you want to see details about "
            + "the machine.\n";
        break;
        
    default:
        description = "Default Description\n";
    }
    
    return description;
} /* get_default_desc */
