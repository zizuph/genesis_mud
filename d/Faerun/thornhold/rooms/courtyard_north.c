/*
 * Thornhold
 * -- Twire/Gnim June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

#define CARAVAN_NONE  "none"

string current_caravan;
object caravan_npc;

public void check_schedule();

string caravan_empty_extra();

string base_extraline;

void
create_road()
{
    set_short("The courtyard of Thornhold");

    base_extraline = "The broad open area is enclosed by the buildings of " +
                     "the hold. Supplies are stacked against the walls. " +
                     "A narrow door leads to a simple provisioner to, " +
                     "the north, and to the west you see what appears " +
                     "to be a tavern, with a wooden sign hanging from " +
                     "the door. A large schedule engraved in wood is " +
                     "mounted on the eastern wall. The courtyard extends " + 
                     "to the south.";

	add_item(({ "yard", "down", "ground" }),
		"The ground of the courtyard is packed dirt dotted " +
		"with patches of grass.\n");
		
	add_item(({ "schedule", "wall", "wood" }),
		"A large schedule engraved in wood is mounted to " +
		"the east wall. It appears to contain detailed " +
		"information about the Thornhold " +
		"trade schedule. You can <read> it if you'd like.\n");
		
	add_item(({ "supplies", "crates", "barrels", "stacks" }),
		"The supplies are packed in crates, barrels, and " +
		"stacks. They are intended for merchants who stop " +
		"by Thornhold to resupply their " +
		"caravans, and are of no interest to you.\n");

	add_item(({ "sign", "wooden sign" }),
		"The wooden sign is plain with dark lettering. " +
		"You can read or examine it, to see what it says.\n");
	
	add_item(({ "large schedule", "schedule" }),
		"You see a large schedule engraved in wood on the " +
		"east wall. You can <read schedule> to see what " +
		"it says.\n");
		
	add_item(({ "eastern wall" }),
		"You notice a large schedule engraved in wood mounted " +
		"on the east wall. You can <read schedule> to see what " +
		"says.\n");
	
	add_item(({ "door", "narrow door" }),
		"You see a door leading north.\n");
	
	add_item(({ "simple provisioner", "provisioner", "storeroom" }),
		"You see a storeroom to the north.\n");
		
    add_item(({"up", "sky"}),
        TIME_DESC_ROOM + "\n");

  	extraline = base_extraline+caravan_empty_extra();
    
    add_cmd_item("sign", ({"read", "exa", "examine"}), 
    	"@@read_sign@@");
    
    add_cmd_item("schedule", ({"read",}), 
    	"@@read_schedule@@");


    reset_faerun_room();

    current_caravan = CARAVAN_NONE;
    set_alarm(60.0, 60.0, &check_schedule());

    add_exit(ROOM_DIR + "courtyard_south",   "south");
    add_exit(ROOM_DIR + "alehouse",   "west");
    add_exit(ROOM_DIR + "provisions",   "north");
    
    add_exit(ROOM_DIR + "arm_stock", "arms", WIZ_CHECK, 1, 1);
    add_exit(ROOM_DIR + "tink_stock", "tink", WIZ_CHECK, 1, 1);
    add_exit(ROOM_DIR + "gems_stock", "gems", WIZ_CHECK, 1, 1);

}

string 
caravan_empty_extra()
{
return "Here wooden stalls have been erected, where " +
       "merchants from visiting caravans can set up shop and " +
       "trade with travellers and locals when they stop in " +
       "Thornhold to rest and resupply.";
}

string 
read_sign()
{
return    "   o                     o   \n" +
          ".--|---------------------|--.\n" +
          "|  The Thornhold Alehouse   |\n" +
          "'---------------------------'\n";
}

string 
read_schedule()
{
return    " .----------------------------------------. \n" +
          " |                                        | \n" +
          " |    -= T R A D E   S C H E D U L E =-   | \n" +
          " |                                        | \n" +
          " |  ___________________________________   | \n" +  
          " |  | ARRIVAL DAY  |  AVAILABLE GOODS  |  | \n" +   
          " |  +--------------+-------------------+  | \n" + 
          " |  |  First-Day   |     Textiles*     |  | \n" +
          " |  |  Third-Day   |     Armaments     |  | \n" +
          " |  |  Fifth-Day   |   General Goods   |  | \n" +
          " |  |  Seventh-Day |      Spices       |  | \n" +
          " |  |  Ninth-Day   |  Precious Stones  |  | \n" +
          " |  +--------------+-------------------+  | \n" + 
          " |  |  Please Note All Festivals are   |  | \n" +
          " |  |     Observed Trade Holidays.**   |  | \n" +
          " |  '----------------------------------'  | \n" +
          " | * Textiles are available for purchase  | \n" +
          " |  by members of the Textile Guild only. | \n" +
          " |                                        | \n" +
          " | ** Information for Foreign Visitors:   | \n" +
          " |  The Faerunian Calendar is comprised   | \n" +
          " |  of twelve months of three Tendays     | \n" +
          " |  each (thirty days). Festivals lasting | \n" +
          " |  lasting 1-2 days occur at every       | \n" +
          " |  solstice and equinox.                 | \n" +
          " '----------------------------------------' \n" +
          " (Consult the <time> command for reference.) \n";
          
}

// This function should setup a caravan when passed a 1 and clean it up when passed a 0						   
public void
textile_caravan(int setup)
{
    setuid(); 
    seteuid(getuid());

    if(setup)
    {
        if(!objectp(caravan_npc))
            caravan_npc = clone_object(NPC_DIR + "textile_merchant");
        if(objectp(caravan_npc))
            caravan_npc->move(this_object()); 
            
        tell_room(this_object(), "A creaking wagon loaded with bolts " +
        "of fabric slowly rumbles in and comes to a stop in the courtyard. " +
        "A velvet drape is pushed aside as a textile merchant steps out " +
        "from the passenger compartment.\n");
        
        extraline = base_extraline + " " +
          "Bolts of cloth lean against the wooden merchant stalls here, " +
          "and a few featured textiles hang proudly on display.";
        set_extraline(extraline);
    }
    else
    {
        tell_room(this_object(), "Heaving the last bolt of fabric back " +
        "on to her laden wagon, the textile merchant pulls aside a velvet " +
        "drape and slips inside. Pulled by two horses, the wagon slowly " +
        "rumbles south.\n");

        extraline = base_extraline + " " + caravan_empty_extra();
        set_extraline(extraline);
        
        if(objectp(caravan_npc))
            caravan_npc->remove_object();
    }
    return;
}

public void
tinker_caravan(int setup)
{
    setuid(); 
    seteuid(getuid());

    if(setup)
    {
        if(!objectp(caravan_npc))
            caravan_npc = clone_object(NPC_DIR + "tinkerer");
        if(objectp(caravan_npc))
            caravan_npc->move(this_object()); 

        extraline = base_extraline + " " +
          "Here wooden stalls have all manner of displaced junk " +
          "cluttering the area. It seems a tinkerer has set up his " +
          "wares here for a time.";
        set_extraline(extraline);
            
        tell_room(this_object(), "A ramshackle wagon creaks and clatters " +
        "merrily into the courtyard and comes to a stop with a clang. A " +  
        "quirky little halfling tinkerer hops down off a pile of junk " + 
        "and sets up shop.\n");
    }
    else
    {
        tell_room(this_object(), "The tinkerer scrambles up on top of " +
        "his overstuffed junk wagon. He snaps his reigns, and the " + 
        "poor overburdened donkey pulls the clattering wagon south.\n");

        extraline = base_extraline + " " + caravan_empty_extra();
        set_extraline(extraline);
        
        if(objectp(caravan_npc))
            caravan_npc->remove_object();
    }
    return;
}

public void
weapon_caravan(int setup)
{
    setuid(); 
    seteuid(getuid());

    if(setup)
    {
        if(!objectp(caravan_npc))
            caravan_npc = clone_object(NPC_DIR + "arms_dealer");
        if(objectp(caravan_npc))
            caravan_npc->move(this_object()); 

        extraline = base_extraline + " " +
          "A covered oxcart is here next to a stall with various " +
          "weapons on display. Sealed crates are stacked nearby, marked " +
          "to indicate they contain smithing materials for shipment.";
        set_extraline(extraline);
            
        tell_room(this_object(), "A covered oxcart is drawn in by " +
        "a sturdy ox driven by a muscular arms dealer. The ox snorts as " +
        "the wagon stops here, and the arms dealer pulls some weapons " +
        "from his stock to offer for sale.\n");
    }
    else
    {
        tell_room(this_object(), "The muscular arms dealer finishes " +
        "reloading his cart, and then quickly takes charge of his ox. " +
        "With a single bellowed command, the ox pulls the rumbling " +
        "cart away.\n");

        extraline = base_extraline + " " + caravan_empty_extra();
        set_extraline(extraline);
        
        if(objectp(caravan_npc))
            caravan_npc->remove_object();
    }
    return;
}

public void
gem_caravan(int setup)
{
    setuid(); 
    seteuid(getuid());

    if(setup)
    {
        if(!objectp(caravan_npc))
            caravan_npc = clone_object(NPC_DIR + "gem_merchant");
        if(objectp(caravan_npc))
            caravan_npc->move(this_object()); 

        extraline = base_extraline + " " +
          "The wooden stalls here have been draped with velvet " +
          "fabric where a few choice gems have been placed on display " +
          "by a visiting gem merchant.";
        set_extraline(extraline);
        
        tell_room(this_object(), "A strange, grey-skinned gnome rides " +
        "in on a trodding mule overburdened with heavy saddlebags. The " + 
        "gnome pulls her mule to a stop and dismounts. All manner of " +
        "jewels and gems dangle from cords and chains that adorn her.\n");
    }
    else
    {
        tell_room(this_object(), "The gem merchant tosses a saddlebag " +
        "with fresh supplies on her already-overburdened mule. Mounting " +
        "the beast, she whistles, and the mule trods south, its movement " +
        "sending an array of sparkles glimmering across the courtyard " + 
        "as it departs.\n");

        extraline = base_extraline + " " + caravan_empty_extra();
        set_extraline(extraline);
        
        if(objectp(caravan_npc))
            caravan_npc->remove_object();
    }
    return;
}

public void
spice_caravan(int setup)
{
    setuid(); 
    seteuid(getuid());

    if(setup)
    {
        if(!objectp(caravan_npc))
            caravan_npc = clone_object(NPC_DIR + "spice_merchant");
        if(objectp(caravan_npc))
            caravan_npc->move(this_object()); 

        extraline = base_extraline + " " + 
          "Various garlands and sprigs of various herbs and spices " +
          "have been strung up from the wooden stalls here by a visiting " +
          "spice merchant.";
        set_extraline(extraline);
            
        tell_room(this_object(), "A fragrant aroma filles the courtyard " +
        "as a dusky elven spice merchant on a roan horse rides in. She " +
        "slides off her steed gracefully and unbinds her saddlebags, " +
        "revealing the herbs and spices for sale within.\n");
    }
    else
    {
        tell_room(this_object(), "The spice merchant repacks her herbs " +
        "and binds her saddlebacks securely. She mounts her horse and " +
        "utters an elven command. The horse tosses its mane and trots " + 
        "south.\n");

        extraline = base_extraline + " " + caravan_empty_extra();
        set_extraline(extraline);
        
        if(objectp(caravan_npc))
            caravan_npc->remove_object();
    }
    return;
}

//Change to a the next caravan if it is different from the current one
public void
change_caravan(string next_caravan=CARAVAN_NONE)
{
    mapping cfuncs;
    function curr_func;
    function next_func;
    string *caravan_types;

    tell_room(this_object(), "Attempt to switch to " + next_caravan + "\n");
    
    cfuncs = ([ "cloth":textile_caravan, 
                "tinker":tinker_caravan, 	
                "spice":spice_caravan, 	
                "gems":gem_caravan, 	
                "weapons":weapon_caravan, 	
                ]);
                
    caravan_types = m_indices(cfuncs) + ({CARAVAN_NONE});

    if(next_caravan == "random")
        next_caravan = one_of_list( caravan_types );

    if( !IN_ARRAY(next_caravan, caravan_types) )
        next_caravan = CARAVAN_NONE;
    
    tell_room(this_object(), 
    "Switch from " + current_caravan + " to " + next_caravan + "\n");
        
    //No change
    if(next_caravan == current_caravan)
        return;
        
    //Clear the old one
    if(current_caravan != CARAVAN_NONE)
    {
        curr_func = cfuncs[current_caravan];
        curr_func(0);
    }

    //Bring in the new one
    if(next_caravan != CARAVAN_NONE)
    {
        next_func = cfuncs[next_caravan];
        next_func(1);
    }

    current_caravan = next_caravan;
    return;
}

public int
faerun_time(string str)
{
    //"the fourth day of the first tenday of Flamerule"
    //"It is evening, fifth day of the third tenday of 
    // Deepwinter, the month of Hammer, 1484 DR."
    string time_string = "";
    string *arr;

    time_string += "It is " + CLOCK->query_part_of_day() + ", ";

    if (CLOCK->is_special_day())
    {
        time_string += ", " + CLOCK->query_special_day() + " ";
    }
    else
    {
        time_string += "on the " + CLOCK->query_day(2) + " ";
        time_string += "of the " + CLOCK->query_week(2) + " ";
        time_string += "of " + CLOCK->query_month(2) + ", ";
        time_string += "the month of " + CLOCK->query_month(1) + " ";
    }

    time_string += "in " + CLOCK->query_year() + " DR\n";

    write(time_string);
    return 1;
}

// This function is called by the room alarm to see if it is time 
// to change caravans, and if so which one is scheduled and switch to it
//	switch_caravan deals with caravans that stay multiple days
public void
check_schedule()
{
    tell_room(this_object(), "The day is " + CLOCK->query_day(2) 
    + " the hour is " + CLOCK->query_hour(1) + "\n");
    
    //For now change each day at Noon
    if(CLOCK->query_hour() == 12)
    {
        switch(CLOCK->query_day(2))
        {
            case "First day":
                change_caravan("cloth");
                break;
            case "Second day":
                change_caravan("cloth");
                break;
            case "Third day":
                change_caravan("weapons");
                break;
            case "Fourth day":
                change_caravan("weapons");
                break;
            case "Fifth day":
                change_caravan("tinker");
                break;
            case "Sixth day":
                change_caravan("tinker");
                break;
            case "Seventh day":
                change_caravan("spice");
                break;
            case "Eighth day":
                change_caravan("spice");
                break;
            case "Nineth day":
                change_caravan("gems");
                break;
            case "Tenth day":
                change_caravan("gems");
                break;
            default:
                change_caravan(CARAVAN_NONE);
                break;
        }
    }
}

public void
init()
{
    ::init();
}

