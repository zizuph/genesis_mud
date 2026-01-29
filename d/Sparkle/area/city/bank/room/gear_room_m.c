/*
 * /d/Sparkle/area/city/bank/room/gear_room_m.c
 *
 * This is the middle gear room of the basement of the Gnomes of
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
    set_short("Central gear room of the basement");
    set_long( &add_desc("long") );
        
       /* Add_Items */
       add_item( ({ "engine", "giant engine", "steam engine", "parts" }),
              &add_desc("engine"));
       
       add_item( ({ "room", "basement", "area", "cellar", "pit" }),
              "This room is the home of a large machine and very dirty "
            + "gnomes. Perhaps a closer look will yield more "
            + "information?\n");
            
       add_item( ({ "mountings", "mounting" }),
              "Wooden mountings keep gears and timbers in place. They allow "
            + "for these things to hang from the ceiling.\n");
            
       add_item( ({ "tubes", "tube" }),
              "Metal tubes connect the boiler with the machine. They "
            + "appear to be made of copper.\n");
            
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
              "The hatch to the furnace is open, so the gnomes are able "
            + "to fuel the fire.\n");
            
       add_item( ({ "boiler", "tank", "large boiler", "boiler tank" }),
              &add_desc("boiler"));
            
       add_item( ({ "machine" }),
              &add_desc("machine"));
       
       add_item( ({ "fuel", "coal" }),
              "The gnomes shovel coal into the hatch of the furnace at, "
            + "what appear to be, timed intervals.\n");
            
       add_item( ({ "arm", "extended arm", "mechanical arm" }),
              "This arm extends from the machine and connects to the giant "
            + "wheel. It is the cause for the movement of the giant "
            + "wheel.\n");
           
       add_item( ({ "giant wheel", "large wheel", "big wheel", "larger wheel",
                    "bigger wheel" }),
              "This wheel is quite large and spins quite fast. It is mounted "
            + "to the ground, but is spun by the extended arm of the "
            + "machine. The wheel is spun in the direction that if a gnome "
            + "sat on the top of the wheel, while spinning, he would be flung "
            + "into the eastern wall. That could happen, except for the fact "
            + "that a band of tarnished leather spans the distance between "
            + "the giant wheel its smaller counterpart above.\n");
            
       add_item( ({ "leather", "tarnished leather", "band" }),
              "A large band of leather connects the giant wheel to the "
            + "smaller wheel. The leather seems to be properly fit, so that "
            + "it does not slip on the wheels and remains in contact at all "
            + "times.\n");
      
       add_item( ({ "wheel", "wheels" }),
              "Which wheel would you like to examine?\n");
                   
       add_item( ({ "small wheel", "smaller wheel", "tiny wheel" }),
              "The small wheel is connected to a long timber, which "
            + "runs from the north to the south. If one stands toward "
            + "the south and looks at it, the wheel appears to spin "
            + "clockwise.\n");
            
       add_item( ({ "timber", "rod", "beam" }),
              "A large timber hangs from rotating mountings, just beneath "
            + "the ceiling. The timber goes through the small wheel and "
            + "spins identically with it. To the north and south, you see "
            + "large gears capping the ends of the timber. Inspecting "
            + "them there might reveal more.\n");
        
       add_item( ({ "ground", "floor", "stone" }),
              "Dusty blocks of stone create the flat surface on which "
            + "you walk. They are grey in colour and do not strike you as "
            + "foreign nor noteworthy.\n");
       
       add_item( ({ "wall", "walls" }),
              "Which wall would you like to examine?\n");
              
       add_item( ({ "north wall", "south wall", "southern wall",
                    "northern wall" }),
              "This wall is too distant to examine closely. There are gnomes, "
            + "machines, gears and gizmos in the way.\n");
            
       add_item( ({ "west wall", "western wall" }),
              "The western wall is too far in the distance, past the engine, "
            + "to inspect closely. Perhaps if the basement wern't so "
            + "steamy, you could see.\n");
            
       add_item( ({ "east wall", "eastern wall" }),
              "The eastern wall is made of metal bars. They are tilted to "
            + "allow hot air to escape the basement, also to "
            + "block the vision of onlookers.\n");
            
       add_item( ({ "ceiling", "top" }),
              "The ceiling is made of stone slabs. Their immense weight is "
            + "supported by the dense walls and the strategically placed "
            + "columns.\n");
            
       add_item( ({ "column", "columns", "supports", "pillars", "support", 
                    "pillar" }),
              "Stone columns are strategically placed to help support the "
            + "heavy ceiling. Many lives depend on the strength and "
            + "placement of these columns.\n");
              
       add_item( ({ "steam", "fog", "cloud", }),
              "Steam spews from a valve on the boiler. It seems that whenever "
            + "a gnome pulls any random lever, the room becomes a dense soup "
            + "of fog.\n");
            
       add_item( ({ "soup" }),
              "No fatty, it is a dense soup of fog; not soup.\n");
            
       add_item( ({ "levers", "handles" }),
              "Gnomes use levers, as well as other gadgets, to manage "
            + "the engine.\n");

       add_item( ({ "chair", "chairs", "strange chair", "interesting chair" }),
              "To the north, a chair sits facing the wall.\n");
       
       add_item( ({ "gear", "gears" }),
              "Above, the large timber is capped with thick toothed gears. "
            + "The first gear, which is attached to the timber and is "
            + "identical on both ends of the timber, is mounted "
            + "vertically. The following gears alternate from horizontal "
            + "back to vertical. This process involves many sizes of gears "
            + "and extends into the northern and southern rooms.\n");
            
       add_item( ({ "door", "small door", "wooden door", "small wooden door" }),
              "This door is made of wooden planks that are vertically placed "
            + "and nailed to a horizontal metal brace. The brace is halfway "
            + "from the ground and has a handle on the right side.\n");
            
       add_item( ({ "bars", "metal bars" }),
              "The metal bars are hot to the touch!\n");       
             
       add_item( ({ "chimney" }),
              "The furnace is connected to the ceiling by an apparatus that "
            + "appears to be a chimney. It is unexciting.\n");
            
            
        /* Properties */
    add_prop(ROOM_I_LIGHT, 1); /* Lit room */

    /* Exits */
    add_exit(BANK_ROOM + "gear_room_n", "north", 0); /* North gear room */    
    add_exit(BANK_ROOM + "vent_shaft_b", "east", 0); /* Basement vent */


    
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
            + "stands ominously to the west, with several gnomes nearby. "
            + "It appears very straightforward and simple. The most "
            + "noteworthy thing about the engine is the giant wheel that "
            + "protrudes perpendicularly with the eastern door. The giant "
            + "wheel is connected to a much smaller wheel which is directly "
            + "above the first. A long band of tarnished leather spans the "
            + "distance and is the cause for the second wheel to spin. The "
            + "smaller wheel is connected to a long timber, that spins many "
            + "important looking gears. This room is decently lit by the "
            + "fire that the gnomes constantly fuel. It is very hot in this "
            + "room and the air is thick. An interesting chair sits just to "
            + "the north.\n\n";
        break;            
        
    case "engine":
        description =
              "The giant steam engine consists of four parts. The furnace "
            + "is the portion that is furthest west. Headed easterly, a "
            + "large boiler tank with multiple tubes and gadgets stands in "
            + "contact with the furnace. A handful of tubes connect the tank "
            + "with a cube-shaped machine that bounces with every movement "
            + "of its extended arm. The arm is connected to the giant "
            + "wheel and spins it quickly. The entire engine is covered "
            + "with vital bells and whistles. It is a beautiful gizmo and "
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
              "The furnace is the module that is farthest west. Gnomes are "
            + "constantly adding coal to the open hatch, in order to keep "
            + "the temperature high. Other gnomes pull levers, press "
            + "buttons and monitor measuring devices. The base of the "
            + "furnace is five meters by four meters and the height is "
            + "three meters, except for the most western part which "
            + "attaches to a chimney which extends to the ceiling. The "
            + "measurements are obvious, because the gnomes have "
            + "plainly written them on the furnace. Following the "
            + "dimensions is written: ProductOfGnomishIndustries.\n";
        break; 
        
    case "boiler":
        description =
              "The boiler is a large structure that is connected to the "
            + "eastern side of the furnace. The tank is a large opaque "
            + "dome. It has a series of windows, which allow the gnomes "
            + "to peer into the tank. Near the windows are meters, "
            + "instruments and verious useful gadgets; all things a gnome "
            + "would need to properly manage the "
            + "tank. A handful of tubes connect the top of the tank with "
            + "the machine to the east.\n";
        break;
        
    case "machine":
        description =
              "The machine is the module that is farthest east. Your keen "
            + "eyes reveal that this machine converts the steam from the "
            + "boiler into mechanical energy. An arm extends from the "
            + "machine and spins the attached wheel. If a gnome sat on the "
            + "top of the spinning wheel, he would be flung toward the "
            + "eastern door, not into the machine. You cannot see inside "
            + "the machine, but you must assume that the steam moves a "
            + "piston to create movement. The brilliance of this machine "
            + "is unparalleled.\n";
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
            + "stands ominously to the west, with several gnomes nearby. It "
            + "appears very complex, because of it's moving parts and the "
            + "over exaggerated gestures of the opperating gnomes. The most "
            + "noteworthy thing about the engine is the giant wheel that "
            + "sticks out, pointing toward the eastern door. The giant "
            + "wheel is connected to a much smaller wheel which is directly "
            + "above the first. A long band of tarnished leather spans the "
            + "distance and is the cause for the second wheel to spin. The "
            + "smaller wheel is connected to a long timber, that spins many "
            + "complicated looking gears. This room is decently lit by the "
            + "fire that the gnomes constantly fuel. It is very hot in this "
            + "room and the air is thick. A strange chair sits just to the "
            + "north.\n\n";
        break;
            
    case "engine":
        description = "You see a very complex and unnecessary engine. "
            + "The engine seems to be broken (no pun intended) into "
            + "four parts: Furnace, "
            + "tank, machine, and mechanical arm. The engine is noisy "
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
              "The furnace is the module that is farthest west. Gnomes are "
            + "constantly adding coal to the open hatch, in order to keep "
            + "the temperature high. Other gnomes pull levers, press "
            + "buttons and monitor measuring devices. The furnace is quite "
            + "large and touches the ceiling at a point that looks like "
            + "a chimney. The gnomes appear to have written some "
            + "information on the side of the furnace, but it is completely "
            + "illegible to you. Following the scribble, 'ProductOfGnomish"
            + "Industries,' is plainly written.\n";
        break;   

    case "boiler":
        description =
              "The boiler is a large structure that is connected to the "
            + "eastern side of the furnace. The tank is a large opaque "
            + "dome. It has a series of windows, through which the gnomes "
            + "periodically peer. Near the windows are meters, "
            + "instruments and other seemingly useless gadgets. "
            + "A handful of tubes connect the top of the tank with the "
            + "machine to the east.\n";
        break;
                      
    case "machine":
        description =
              "The machine is the module that is farthest east. It is hard "
            + "to say how, but it appears to convert steam, from the tank, "
            + "into movement. An arm extends from the machine and moves in "
            + "a manner that spins the attached wheel. If a gnome sat on the "
            + "top of the spinning wheel, he would be flung toward the "
            + "eastern door, not into the machine.\n";
        break;
              
    default:
        description = "Default Description\n";
    }
    
    return description;
} /* get_default_desc */
