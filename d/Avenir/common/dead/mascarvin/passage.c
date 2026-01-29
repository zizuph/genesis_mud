// file name:        /d/Avenir/common/dead/mascarvin/passage.c
// creator(s):       Lilith, May 2021
// revision history: Lilith, Aug 2021: added some add_items.
// purpose:          This room transits between two quest stages.  
// note:                             
// bug(s):           
// to-do:

inherit "/std/room";
#include "defs.h"
#include "/sys/terrain.h"

/* Player can go back the way they came */
string open_door()
{      
        write("You heave against the stone slab.\n");
        say(QCTNAME(TP) + " heaves against the stone slab.\n");
        TP->move_living("west", MASQ +"spots");
        return "";
}

/* Move on to the next room */
int go_east()
{
	/* Sanity check. If player somehow got past the dots puzzle
	 * without solving it they are not worthy to proceed.
	 */
	if (TP->query_skill(SS_MASQ_STAGE) == STAGE_2_DOTS)		
	   return 0;
	
    else
	{
	   write("The mist congeals to form a wall that prevents you "
	       +"from going east. White dots dance before your eyes.\n");
	   return 1;
    }  
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
    set_short("narrow glistening passageway");
    set_long("This passage is narrow and smooth, with "
      + "flesh-coloured walls that look like hard-baked "
      + "clay. The ever-present mist has condensed on "
	  + "walls, leaving them glistening with moisture. "
	  + "Something vaguely decorative is etched into the "
	  + "walls at eye-level. The passageway leads to the east " 
	  + "and ends in a massive stone slab in the west.\n");

    add_item(({"mist", "swirls"}), 
	    "A thin white mist moves along the ground, making the "
	   +"walls and floor wet and slippery. Something about it "
	   +"makes you paranoid. You feel as though you are being "
	   +"watched.\n");
    add_item(({"wall","walls"}), "They are made from smooth, "
      + "warm clay the color of flesh. There is a band of "
	  + "faint etchings about midway between the ceiling "
	  + "and the floor. The walls are damp with condensed "
	  + "mist.\n"); 
    add_item(({"floor","ground"}), "The floor of this "
      + "tunnel appears to be rough-hewn bedrock.\n");
    add_item(({"slab","rock"}), "The stone slab is "
      + "massive and appears to be made of pinkish "
	  + "red carnelian.\n");
    add_item("ceiling", "The ceiling high above is "
      + "vaulted.\n");
    add_item(({"etchings", "decorations", "band of etchings"}),
	    "Your eyes are drawn to an overhead view of "
      + "some sort of maze. Perhaps it should be examined "
	  + "more closely?\n");
    add_item(({"maze", "mazes" }), 
	    "There are multiple etchings of mazes at about "
	  + "eye-level. After careful examination, "
	  + "you get the feeling that "
	  + "others who were here before you were "
	  + "trying to map a challenging maze. "
	  + "You think there might be some words, too.\n");

    add_cmd_item(({"words","maze","etchings", "runes", "grooves", "letters"}),
	    "read",
        "The only words you can make out are:\n"
       +"		Forget not the Gods on the Path to Mascarvin.\n");
	add_cmd_item(({"words", "maze", "etchings", "rune", "runes", "grooves" }),
                  ({"touch","feel","reach","push","move"}),
        "The etchings feel like grooves carved into clay "
	    +"and some appear to be letters you could read.\n");				 
    add_cmd_item(({"ceiling", "roof"}),
		         ({"touch","feel","reach","push","move"}),
        "The ceiling is far beyond your reach.\n");
    add_cmd_item(({"slab", "stone slab"}), 
				 ({"lift", "move", "push" }), 
				 open_door);
	
    add_exit("chalice", "east", go_east);
	
	add_prop(OBJ_S_WIZINFO, 
	   "This room is part of the Meet Mascarvin Quest. The "
	   +"player can go east to do the next stage of the "
	   +"quest, or west to leave the area.\n");
	add_prop(ROOM_M_NO_TELEPORT, 
	    "An angry goddess-figure wreathed in red-gold flames "
       +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));


	IN;  
    IN_IN;
    set_terrain(({ TERRAIN_SHADOWS, TERRAIN_HASDEAD, TERRAIN_UNDERGROUND,
    	TERRAIN_ROCK }));

}

