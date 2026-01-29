// file name:        /d/Avenir/common/port/port_room.c
// creator(s):       Denis, Sep'96
// revisions: Lilith, Sep 2021: added support for fisherman's club
//            Lilith, Apr 2022: added missing add_item 
// purpose:          Base room to be inherited forthe port/ area
// note:             Is recode of old Ilyian's (Cirion's) port.h file.
// bug(s):           
// to-do:            

# pragma strict_types
inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";
#include <terrain.h>
#include "/sys/stdproperties.h"
#define VIEW      CEILING CLIFF VEINS_EAST SEA ISLAND

public void
create_port_room()
{
}

public nomask void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);  // underground.
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	set_terrain(TERRAIN_SHADOWS | TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_ROCK);
	add_prop("_live_i_can_fish", "saltwater");		 

    add_item("mist",
	    "The white, flowing mist that fills the cavern rushes " +
        "around you in ghostly tendrils, making eerie shapes appear " +
        "before your eyes.\n");

    add_item(({ "water", "waters", "lake" }),
        "The churning water of this underground lake is a shade of " +
        "blue so deep it is almost black. Its surface is distorted by " +
        "the waves, and it all moves slowly from the great rift on the " +
        "west end of the cavern to the waterfall at the east ledge.\n");
		
    add_item(({ "floor", "ground" }),
	    "The ground beneath you is smooth and wet from " +
        "the mist that clings to everything. It appears to be man made, " +
        "hewn from the natural rock.\n");

    set_tell_time (110);

    add_tell("A dense wisp of mist blows before your eyes, obscuring " +
             "your vision for a brief moment.\n");

    add_tell("A wave crashes over the side of the lake, soaking your " +
             "feet and the surrounding floor.\n");

    add_tell("The wind seems to bring ghostly music and voices to your " +
             "ears.\n");

    add_tell("The mist around you shifts and curls into strange shapes.\n");

    add_tell("The wind rises to a howling fury, making sprays of water " +
             "fly everywhere.\n");
			 
    create_port_room();
}

public void
add_view_items()
{
    add_item(({ "ceiling", "rocks" }),
        "Over the water, you can barely make out anything " +
        "except a white glow from the ceiling, as the mist shrouds " +
        "your vision. But to the east you can see the enormous cavern " +
        "ceiling that stretches over all of the land. It seems to be " +
        "criss-crossed by veins of some substance that sheds a dazzling " +
        "white light. The veins seem more prominent on the eastern " +
        "reaches of the ceiling, many leagues away.\n");

    add_item(({"waterfall", "water"}),
        "Water flows from the Rift and tumbles many, many meters "+
        "until it meets the waters of the semi-flooded cavern "+
        "of the Sea of Sybarus. It is spectacular waterfall, "+
		"full of frothy whiteness and mist.\n");

    add_item(({ "ledge", "cliff", "dropoff", "view" }),
        "Merely looking over the dropoff gives " +
        "you a terrifying sense of vertigo. The cliff falls hundreds " +
        "of meters down to a great sea in which appear to be islands. " +
        "The entire great cavern is lit by strange phosphorescent veins " +
        "that run through the ceiling. A narrow path has been carved " +
        "out of the cliff below you, winding steeply downwards to " +
        "the southern part of the cavern.\n");

    add_item(({ "island", "islands" }),
        "There are a number of islands of various " +
        "shapes and sizes far beneath you in the sea. From this height " +
        "you can make out few details, but one larger island in the " +
        "centre seems to contain a city, while others appear to be " +
        "green with forests and vegetation.\n");

    add_item(({ "sea", "ocean" }),
	    "The great underground sea stretches out thousands " +
        "of meters beneath you, making for a breathtaking sight. " +
        "Throughout the sea are islands of various sizes, and you can " +
        "even make out a ship or two travelling across the waters. The " +
        "light from above does not penetrate the sea, making it a heavy " +
        "shade of black.\n");

     add_item(({ "veins", "light", "glow"}),
	     "The veins seem to be more clustered to the " +
         "eastern end of the cavern, but elsewhere they are " +
	     "fairly evenly distributed. The light " +
         "gives an unearthly glow to everything, " +
         "reminding you that you are in the sunless realms, " +
         "far from the light of day.\n");
}

static void
add_ceiling_in_item()
{
    add_item(({ "ceiling", "rocks" }),
             "Over the water, you can barely make out anything " +
             "except a white glow from the ceiling, as the mist shrouds " +
             "your vision.\n");
}

static void
add_path_item()
{
    add_item("path",
	     "The prospect of climbing down the path is " +
             "unappealing to say the least. It is wet from the mist that " +
             "pours down over the ledge, and it is extremely steep. The path " +
             "runs southward along the cliff until it enters a hole in " +
             "the southern wall of the great cavern.\n");
}

static void
add_rift_item()
{
    add_item("rift",
             "The rift in the west wall of the cavern is " +
             "immense, and through it flows massive amounts of water " +
             "and wind, creating the mist that you see around you. It is " +
             "difficult to tell from here, but you think you can detect a " +
             "hint of sunlight on the water near the rift.\n");
}

static void
add_rift_no_see_item()
{
    add_item("rift",
	     "You cannot make out the great rift through the mist from " +
             "where you are standing, but the roar of the water " +
             "rushing through it fills your ears.\n");
}

static void
add_wall_item()
{
    add_item(({ "wall", "walls" }),
             "These rough hewn walls of the cavern " +
             "appear to be man made, hewn from the natural rock. They are " +
             "wet from the mist and spray of the stormy port, and rivulets " +
             "of water run down them to the floor.\n");
}

static void
add_no_swim_cmditems()
{
    add_cmd_item(({ "water", "ledge", "off", "into" }),
		 ({"dive", "jump", "leap" }),
                 "The water is too rough here, it would be suicide.\n");
    add_cmd_item(({ "lake", "water" }),
		 ({ "swim", "enter" }),
		 "It is too rough to swim in the water here.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
