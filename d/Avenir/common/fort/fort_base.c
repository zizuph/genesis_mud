
#pragma strict_types

inherit "/d/Avenir/inherit/room";
inherit "/d/Avenir/inherit/room_tell";
//inherit "/d/Avenir/inherit/avenir_time";
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/defs.h"

#include <terrain.h>        
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>

/* prototypes */
void add_exit_views();  /* Adds directional exit views */
void add_basic_fort();  /* floor, fortress, etc */
void add_towers_out();  /* View of towers from outside */
void add_fort_room();   /* Source crystal wall sconses */
void add_gate_items();  /* Gate items from inside fort */
void add_fountain();    /* Adds clepsydra and drink actions */

public void
create_fort_room(void)
{
 /* Individual room code goes here in the room files */

}

void reset_fort_room()
{ 
	
    ::reset_domain_room();
}

/* This is in every room */
static void
create_domain_room(void)
{
    set_area("outpost");

//    set_tell_time(300);

	set_terrain( TERRAIN_UNDERGROUND | TERRAIN_ROCK );	
	
    create_fort_room();
    reset_fort_room();
	
}

/* Basic outdoor room in the fort */
public void 
add_basic_fort()
{
	
    add_item(({"fort", "tall fort", "black fort", "tall black fort",
	    "fortress", "basalt fortress", "fort sybarus"}),
		"This fortress was built into the opening between the Underdark "+
        "and the Sybarus Cavern using the black, smooth basaltic stone "+
		"native to these parts. The fortress has stood here for over a "+
        "thousand years and will surely stand for thousands more.\n" );
   add_item(({"cavern wall", "natural stone", "natural wall", 
        "natural stone wall", "uncarved stone", "rough stone",
        "rough stone wall", "original wall", "original cavern wall"}),
        "This wall is natural stone, part of the original cavern "+
        "wall. It is rough and uncarved.\n");		
    add_item(({"stone", "basaltic stone", "basalt", "dark stone", 
        "smooth stone"}),
        "This dark, smooth stone is igneous rock, formed by the "+
	    "cooling of magma. Basalt is a very hard, very dense stone "+		
        "that is useful for construction.\n");
    add_item(({"limestone", "white cobbles", "cobblestone", "floor",
    	"grey cobbles", "grey-white cobbles", "ground", "paving",
        "pavers", "calcite crystals", "crystals", "courtyard"}),
	    "The ground is paved in pale grey limestone cobbles with "+
        "calcite crystals that glitter when they catch the light.\n");
    add_item(({"source", "up", "light", "ceiling", "vein"}),
        "Looking up, you can see the veins of the Source glowing "+
        "in the ceiling of the cavern.\n"); 		
	add_item(({"cavern", "giant cavern"}),
        "To the north and east a giant cavern opens up. It appears "+
        "to be partially flooded with water. It is illuminated "+
		"by veins of something called the Source.\n");
		
} // add_basic_fort

/* Gate-specific add_items */
public void
add_gate_items()
{
    add_item(({"gate", "fort gate", "stone gate", "door", "sooty gate",
        "soot-stained gate", "soot-stained gateway", "gateway",
        "black door", "black stone door", "black stone gate door"}),
        "The black stone gate guards the only entrance to the fort. "+
        "An open metal window is noticeable on either side of "+
        "the door, allowing the guards to talk to whoever desires "+
		"passage. There is a stylized lock-and-key symbol engraved "+
		"into the gate and filled with gold that seems to move in "+
        "the light of the flames.\n");
    add_item(({"lock-and-key symbol", "symbol on gate", "stylized symbol",
	    "stylized lock-and-key symbol", "symbol of salilus", 
        "salilus symbol", "golden symbol", "large symbol", "gold symbol"}),
        "This stylized lock-and-key symbol is for the god Salilus, "+
        "He Who Opens The Way.\n");
} // add_gate_items


/* Indoor rooms in the fort */
public void
add_fort_room()
{
	IN_IN; // Inside room in subterranean place. No steeds.
    add_item(({"source", "source lights", "octagonal crystals",
        "source crystals", "octagonal crystal", "crystal",
    	"source crystal", "source lamp", "source lamps", "source",
        "wall lamps", "lamps", "lamp", "crystal and copper lamps"}),
        "Glowing crystals the size of your palm have been "+
        "set in the walls at regular intervals. The crystals "+
        "are octagonal in shape, and a mirrored half-circle "+
        "of copper has been installed above them, reflecting "+
        "the light.\n");  		
    add_item(({"copper mirror", "copper mirrors", "mirror", "mirrors",
	    "mirror on the wall", "mirror above the crystal", "copper",
        "half-circle", "copper half-circle", "half-circle of copper"}),
        "A mirror made of copper has been installed over each "+
        "source crystal, amplifying and reflecting the light.\n");			
    add_item(({"limestone", "white cobbles", "cobblestone", "floor",
    	"grey cobbles", "grey-white cobbles", "ground", "paving",
        "pavers", "calcite crystals", "floor tiles", "flooring"}),
	    "The ground is paved in pale grey limestone containing "+
        "calcite crystals that glitter when they catch the light.\n");
    add_item(({"wall","walls","stones", "stone", "basaltic stone", 
        "basalt", "dark stone", "black stone", "smooth stone",
		"blocks", "stone blocks", "dark blocks", "dark stone blocks"}),
        "These walls are made of dark, smooth stone blocks perfectly "+
        "joined together. Basalt is a very hard, very dense stone "+		
        "that is useful for construction.\n");
    add_item(({"cavern wall", "natural stone", "natural wall", 
        "natural stone wall", "uncarved stone", "rough stone",
        "rough stone wall", "original wall", "original cavern wall"}),
        "This wall is natural stone, part of the original cavern "+
        "wall. It is rough and uncarved.\n");
    add_item(({"ceiling", "up" }), 
        "You crane your neck to see the ceiling and find more "+
        "of the same dark stone as in the rest of the fort.\n");
    add_item(({"fort", "tall fort", "black fort", "tall black fort",
	    "fortress", "basalt fortress", "fort sybarus", "tower"}),
        "You are inside Fort Sybarus. "+
	    "This fortress was built into the opening between the Underdark "+
        "and the Sybarus Cavern using the black, smooth basaltic stone "+
		"native to these parts. The fortress has stood here for over a "+
        "thousand years and will surely stand for thousands more.\n" );
} // add_fort_room

/* Exterior view of the towers */
public void
add_towers_out()
{
	add_item(({"tower", "towers", "black tower", "black towers"}), 
        "Two towers rise above you. The taller tower is to the south "+
        "and the short one to the north.\n");
    add_item(({"tall tower", "south tower", "taller tower", 
        "tall black tower"}), 	
		"The tall black tower rises high above you, providing whoever "+
        "stands within a view of the fort and the cavern. It rises high "+
		"enough that it joins with the ceiling of the cavern.\n" );
    add_item(({"north tower", "short tower", "squat tower"}),
        "This tower squats in place, wide and a few stories high. "+
        "Its parapets seem to connect with those above the gate, "+
        "providing good defensive capability against invaders.\n");	
    add_item(({"parapet", "parapets", "tower parapets"}),
        "Each tower seems to have its own parapets, as does the gate.\n");		
} // add_towers_out


/* Functions relating to the fountain/clepsydra */
public string
do_wash()
{
    write("Wow that water is very cold!\nYou do a quick wash-up.\n");
	say(QCTNAME(TP)+" quickly washes up at the fountain.\n");
	return "";
}
	
public string 
do_drink()
{
    int dr;

    dr = TP->query_prop(LIVE_I_MAX_DRINK) / 10;
    if (!dr) dr = 200;
	
    if (!TP->drink_soft(dr))
    {
        write("The water is too much for you.\n");
        return "";
    }

    write("You sip from the fountain with cupped hands.\n"+
        "The water is cool and sweet with minerals.\n");
    say(QCTNAME(TP)+" uses "+ TP->query_possessive() +" hands "+
        "to sip water from the fountain.\n");
    return "";		
}

/* Add this when you want a water clock/fountain in the room */
public void
add_fountain()
{
    room_add_object("/d/Avenir/common/obj/clepsydra");
    add_cmd_item(({"in water", "in pool", "in fountain"}),
	    ({ "wash", "wash up", "clean", "bathe" }), do_wash);
    add_cmd_item(({"water", "pool", "fountain", "spring" }),
	    ({ "drink", "sip" }), do_drink);
}	

public string
see_nearby(void)
{
    object room, *obs = ({});
    int idx, size = sizeof(room_exits);

    for(idx = 0; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx + 1], ({"in","out","up","down"})))
	    continue;

	ix = (idx / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	catch(room_exits[idx]->teleledningsanka());
	if (objectp(room = find_object(room_exits[idx])))
	    obs += all_inventory(room);
    }

    if (!sizeof(obs = filter(obs, living)))
	return "";

    return " In the surroundings nearby, you see "+
	COMPOSITE_LIVE(obs) +".";
}

/*
 * Mask this to print a message for a non-exit view.
 */
static string
view_static(string str)
{
    return "You see nothing of interest is to the "+ str +".\n";
}

/*
 * Dynamic direction views.
 */
static string
view_nearby(string str)
{
    mixed room;
    object *obs;
    int idx = member_array(str, room_exits);

    if (!strlen(str))
	return "Error!";

    /* No exit in that direction. */
    if (idx == -1)
	return view_static(str);

    room = room_exits[idx - 1];
    catch(room->teleledningsanka());

    /* Did the room load? */
    if (!objectp(room = find_object(room)))
    {
	return "You have difficulty making out what is to "+
	"the "+ str +".\n";
    }

    obs = filter(all_inventory(room), living);
    str = "Off to the "+ str +" is "+ (room->short()) +".\n";

    if (sizeof(obs))
	str += "You can see "+ COMPOSITE_LIVE(obs) +" in that direction.\n";
    else
	str += "It doesn't appear that anyone is there right now.\n";

    return str;
}

/*
 * Auto adds directional view (ex. "exa north, exa south, etc")
 */
static void
add_exit_views(void)
{
    int idx, size = sizeof(room_exits);

    for(idx = 1; idx < size; idx += 3)
    {
	int ix, sz = sizeof(non_obvious_exits);

	if (IN_ARRAY(room_exits[idx], ({"in","out","up","down"})))
	    continue;

	ix = ((idx - 1) / 3);
	/* Check if exit is non-obvious. */
	if (sz > ix)
	{
	    if (non_obvious_exits[ix])
		continue;
	}

	add_item(({ room_exits[idx] }),
	    &view_nearby(room_exits[idx]));
    }
}

/*
 * Function name: exa_window
 * Description  : This lets people see the outside room
 *                from a window.
 * Usage: In the create_room do:
 * 	add_item( ({ "east windows", "east facing windows", "east window"}), 
 *  "@@exa_window|You look through the window.\n|" + OUTPOST +"fort2@@");
 *
 */
#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
          ".\n");

    if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
          ".\n");

    return "";
} 

	