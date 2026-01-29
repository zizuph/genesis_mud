// file name:        /d/Avenir/common/dead/mascarvin/chalice.c
// creator(s):       Lilith, May 2021
// revision history: Lilith, Aug 2021: added some add_items.
// purpose:          Entrance to the maze.
// note:             
//                  
// bug(s):           
// to-do:

inherit "/std/room";
#include "/sys/terrain.h"
#include "defs.h"

/* Down the well and into the maze you go. */
string
do_dive()
{

    say(QCTNAME(TP) + " jumps into the pool of mist and is "
		+ "slowly lost from sight!\n");
    write("You jump into the well.\n"
	    + "Cool, milky fingers of mist seem to wrap themselves "
		+ "around you, lowering you gently.\n"
		+ "You find yourself in a different place entirely.\n");
    TP->move_living("M", MAZE + "maze1", 1, 1);
	
    return "";
}

/* You dare cast magic in a god's home? */
public int
anti_magic(object who)
{
    /* Don't bother with uncast spells. */
    if (!who->query_prop(LIVE_I_CONCENTRATE))
	    return 0;

    who->catch_tell("An oppressive force presses upon you like "+
	    "a giant hand closing around you.\n");
 
    /* hurt him some (but don't kill him) */
    who->heal_hp(-50 - random(100));
    who->add_mana(-50 - random(100));
	who->add_fatigue(-50 - random(100));

    /* break his spell */
    who->cmdhooks_break_spell("Your brain flutters wildly in "
	    +"time with your heart.\nA wave of exhaustion rolls "
	    +"over you and you can feel yourself falling forward.\n");
	who->command("$kneel");
	return 1;
	
}


void
create_room()
{
    set_short("triangular room with misty whirlpool at the center");
    set_long("This is a triangular room with smooth walls of "
	    +"reddish clay. It is a small, yet oddly comforting space. " 
		+"The mist that has followed you in the "
		+"catacombs has thickened considerably and "
		+"swirls slowly about this room, a whirlpool "
		+"at the center of which is a circular stone structure "
		+"that looks somewhat like a well.\n");
		
	add_item(({"wall","walls"}), "They are made from smooth, "
        + "warm clay the color of flesh. The walls are damp with condensed "
	    + "mist.\n"); 
	
    add_item(({"structure", "well", "circular structure", "stone structure"}),
		"This structure is made of rectangular stones "
		+"laid in a circle. It looks a lot like a "
		+"well, but there is no rope and bucket "
		+"above it. The ever-present mist is "
		+"incredibly thick within it, as if it "
		+"is the source, or collection point.\n");
	
    add_item(({"mist", "whirlpool"}), 
		"The whirlpool of mistiness swirls slowly within the "
	    +"well, so thick it seems to have substance. "
		+"Your eyes seem to make out a floor below.\n");
	
    add_item("ceiling","It is made of smooth-packed dirt.\n");
	
    add_item(({"floor","ground"}),"The ground is made "
	    +"of smooth-packed dirt -- as far as you can tell " 
	    +"with all the mist swirling around your legs.\n");
	
    add_item(({"stone", "stones", "granite stones"}),
	     "Pale quartz-flecked granite stones are "
	   + "packed neatly together to form a circular "
	   + "well much like one you would draw water from.\n");

    add_cmd_item(({"mist","in mist", "in the mist", "into mist", 
	    "into the mist",
	    "well", "in well","in the well", "into well", "into the well",
		"room","in room", "in the room", "into room", "into the room",
		"space","in space", "in the space", "into space", "into the space",
		"whirlpool", "in whirlpool", "in the whirlpool", "into whirlpool", 
    	"into the whirlpool"}),
	    ({ "enter", "dive", "climb", "jump", "fall" }),
		"@@do_dive@@");
		
    add_prop(OBJ_S_WIZINFO, "To start the maze portion of the quest "
	    +"the player must jump into the well.\nIf the player gets "
		+"lost in the maze they can jump into the mist, which will "
		+"dump them back here.\nIf they want to leave the area "
		+"they can go back west.\n");
	add_prop(ROOM_M_NO_TELEPORT, 
	    "An angry goddess-figure wreathed in red-gold flames "
       +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));
	

	IN;  
    IN_IN;
    set_terrain(({ TERRAIN_SHADOWS, TERRAIN_HASDEAD, TERRAIN_UNDERGROUND,
    	TERRAIN_ROCK }));


    add_exit(PASSAGE, "west");
}
