/*
 * Room of skulls, the fourth part of the Meet Mascarvin quest.
 *   It is modeled after part of the Union Guru quest
 *   
 *   In this room, the player must touch the skulls in
 *   the correct sequence. The sequence depends on the
 *   sequence of rooms the player passed through in order
 *   to get through the maze. Since the maze is randomly generated,
 *   the player will need to find a way to get through it,
 *   and will also need to keep track of the words at the
 *   exits through which they passed in order to reach the
 *   end of the maze. The words (stored in the player in the
 *   form of a property) are reset each time the player returns
 *   to the beginning of the maze, so they can try repeatedly.
 *   The paths through the maze remain the same for the duration
 *   of each reboot, rather than changing every time. 
 *
 * Lilith, May 2021
 * Cirion, Mar 1997
 */

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <composite.h>

#include "../defs.h"

int       door;

string    *seq = ({});
mapping   skulls = ([]);

/* Check to see if player can go west */
int go_west()
{
    object room  = find_object(RESTING);

    if(room && sizeof(filter(all_inventory(room), interactive)))
    {
        write("There is someone there ahead of you, so "+
		    "you should wait a few minutes or try again later.\n");
        return 1;
    }
	
	if (TP->query_skill(SS_MASQ_STAGE) > 3)
		return 0;
    else
	{
	   write("You are repelled from the opening, flying up and backwards "
	        +"with terrifying speed!\n\n");
	    TP->command("$enter mist");  	   
	   return 1;
    }  
}


/* Open the door to the next stage */
public void
open_door()
{
    if(door)
       return;

    tell_room(TO, "A portion of the dirt wall to the west crumbles "
        + "away, creating a skull-shaped opening.\n");

    add_exit(RESTING, "west", go_west);
    door = 1;
}

/* Close the door to Mascarvin */
void
close_door()
{
    if(!door)
        return;

    tell_room(TO, "The dirt piles back up into the hole in the west wall "
         + "until it is smooth again. What magick is this?!\n");
    remove_exit("west");
    door = 0;
}

/* If they want to turn back, this is how */
public string
go_up()
{
    say(QCTNAME(TP) + " is sucked into the mist, legs kicking!\n");
    write("You are sucked swiftly into the churning mist!"
		  + "It clings to your skin with a sickeningly cool moistness "
		  + "reminscent of a corpse's kiss.\n"
		  + "You feel yourself moving in an uncertain direction, "
		  + "only to surface suddenly on the edge of the well "
		  + "where this misadventure began.\n");
	
    TP->move_living("M", MASQ + "chalice", 1, 1);
	
    return "";
}

/* The room has a description if the doorway is open */
string
door_desc()
{
    if(!door)
       return "";
    else
       return " A portion of the western wall has crumbled away, "
          + "revealing an opening beyond.";
}

string
skulls_desc()
{
    int *where = m_values(skulls);
    int raised = sizeof(where);

    string str = "\n   Illuminating the room are " + LANG_WNUM(raised)
      + " crystalline skulls arranged in a circle";
	  
    where -= ({ 0 });
    raised = sizeof(where);

    if(!raised)
      str += ", gleaming dully.";
    else if(raised == m_sizeof(skulls))
      str += ", all of which are glowing brightly.";
    else
      str += ", " + LANG_WNUM(raised) + " of which are glowing "
        + "brightly.";

    return str;
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
reset_room()
{
    int *where = m_values(skulls);
	int num;
    string *which = ({ });

    seq = ({ });

    foreach(string sk, int val: skulls)
    {
    	num++;
    	if (!val) continue;

	    which += ({ LANG_WORD(num) });
	    skulls[sk] = 0;
    }

    if(sizeof(which))
    {      
	  tell_room(TO, "The " + COMPOSITE_WORDS(which) + " skull"
             + ( sizeof(which) > 1 ? "s stop" : " stops" )
             + " glowing.\n");
    }

    close_door();
}

string
dir_from_num(int i)
{
    string *dirs = ({ "north", "northeast", "east", "southeast", "south",
                      "southwest", "west", "northwest" });
    int which = i * sizeof(dirs) / m_sizeof(skulls);

    return dirs[which];
}

string
hover_desc(string which)
{
    if(!skulls[which])
      return "It is gleaming dully with faint internal light.\n";

    else
      return "It is glowing " + LANG_NUM2WORD(skulls[which]) 
        + " times brighter than it originally was.\n";
}

void
create_room()
{
    int     num;

    set_short("domed room of crystalline skulls");
    set_long("This is a large round room with an earthen dome arching overhead "
			 + "and a narrow staircase winding toward an opening midway up the "
			 + "wall. The rich scent of moist dirt fills the air, reminding "
			 + "you that you are essentially buried underground. A faintly "
			 + "luminescent mist seems to spiral down to the floor, "
			 + "where it circles and then flows back upwards to form "
			 + "a helix of sorts. @@skulls_desc@@ @@door_desc@@\n");

    /* Initialiaze the state of the skulls */
    foreach(string str: WORDS)
	    skulls[str] = 0;

    add_item(({ "skull", "skulls", "circle", "crystalline skulls" }), 
	      "There are "+ LANG_NUM2WORD(m_sizeof(skulls)) 
          + " skulls arranged in a perfect circle in the center "
          + "of the room. Each one seems faintly illuminated from within, "
		  + "like it is carved from a piece of the Source.\n"
		  + "The letters   MAS  CAR   VIN  are inscribed in the "
		  + "center of the circle.\n");


    foreach(string sk: m_indices(skulls))
    {
	   num++;

	   add_item(({ sk + " skull", 
	        "skull "+ LANG_NUM2WORD(num), LANG_NUM2WORD(num) +" skull",
			"skull "+ LANG_ORD2WORD(num), LANG_ORD2WORD(num)  +" skull",
			"skull "+ LANG_ORD2EXT(num),  LANG_ORD2EXT(num)  +" skull" }),
	          "It is a skull that appears to have been transformed into a form of crystal. "
	        + "It is near the "+ dir_from_num(num - 1) +" side of the room.\n"
	        + "There are letters carved into the skull.\n"
	        + VBFC("hover_desc:" + file_name(TO) +"|" + sk));

      add_cmd_item(({ sk +" skull", 
	   	    "skull "+ LANG_NUM2WORD(num), LANG_NUM2WORD(num) +" skull",
			"skull "+ LANG_ORD2WORD(num), LANG_ORD2WORD(num)  +" skull",
			"skull "+ LANG_ORD2EXT(num),  LANG_ORD2EXT(num)  +" skull" }),
	        "read", "The letters on the "+ LANG_ORD2WORD(num) +" skull "+
	        "read: "+ CAP(sk) + ".\n");
     }
	 
	add_item(({"letters", "inscription", "center" }),
		  "Cut deeply into the stone floor are the hand-sized letters\n "
		  + "   MAS\n   CAR\n   VIN.\n"); 
	add_item(({"floor", "stone"}), "In contrast to the dirt from which "
		  + "this room was carved, the floor appears to be mostly "
		  + "rough and seamless stone. Perhaps it is the bedrock of "
		  + "this island.\n");
		  
		  	/* Lost or frustrated? There is always a way out. */
	add_item(({"ceiling","mist","rope", "flow", "helix", "spiral"}),
		"There is a thick rope of glowing white mist flowing both "
		+ "upwards and downwards, braiding upon itself in a "
		+ "helical spiral. "
		+ "It beckons to you, seeming to whisper into your "
		+ "mind some absurdity about it being a way out "
		+ "of this disquieting place.\n");

    add_cmd_item(({"mist","river","flow",
	    "into the mist","into mist", "in mist", "in the mist", 
		"up into mist", 
		"into the river","into river","in river", "in the river",
		"up into river", 
		"into the flow", "into flow", "in flow", "in the flow",
		"up into the flow"}),
	    ({ "enter", "swim", "climb", "jump", "leap", "reach" }),
		"@@go_up@@");
  
		  
    add_exit("maze13", "up");
    
	add_prop(OBJ_S_WIZINFO, "This room is part of Mascarvin's Quest.\nThe "
	      + "player has gotten here through a maze. The words on the "
		  + "threshold of the exits taken to get here must be tracked "
		  + "by the players in order to solve this puzzle.\nEach skull has "
		  + "a word-name corresponding to the exits in the maze. The "
		  + "players are supposed to polish the skulls in the order "
		  + "of the word-names on the exits taken. If the players don't "
		  + "know the correct order, they will have to reach into the "
		  + "mist to be carried back to the beginning of the maze. "
          + "They will then have to walk through the maze again, "
		  + "keeping track of the names on the exits taken.\n"
		  + "   The maze words reset when the players go back to the "
		  + "beginning, but the exits only reset with Armageddon, so "
		  + "the player doesn't have to re-solve the maze, just keep "
		  + "track of the names on the thresholds they pass through.\n");
	add_prop(ROOM_M_NO_TELEPORT_TO, 
	    "An angry goddess-figure wreathed in red-gold flames "
       +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));
	
    IN;	
	IN_IN;   // inside room, in underground place
	
 //   reset_room();
}

int
compare(string *arr1, string *arr2)
{
    int i;

    for(i=0;i<sizeof(arr1) && i<sizeof(arr2);i++)
    {
       if(arr1[i] != arr2[i])
         return 0;
    }

    if(sizeof(arr1) == sizeof(arr2))
      return 2;  // exact match
    else
      return 1;  // partial match
}

int
touch(string str)
{
    int which, comp;
    string *words = ({ }), sk;

    NF(CAP(query_verb()) + " what?\n");
    if(!strlen(str))
        return 0;
	
    str = lower_case(str);
    if (!parse_command(str, ({}), "[the] %s 'skull'", sk))
        return 0;

    if(strlen(TP->query_prop(WORD_PROP)))
       words = explode(TP->query_prop(WORD_PROP), " ");

    sscanf(sk, "%d", which);
	
    NF(CAP(query_verb()) + " which skull?\n");
    if(!which && !(which = LANG_NUMW(sk)) && !(which = LANG_ORDW(sk)))
     {
	    which = member_array(sk, m_indices(skulls));
        if (++which == 0)
           return 0;
    }

    which--;

    NF(CAP(query_verb()) + " which skull?\n");
    if(which >= sizeof(m_indices(skulls)))
      return 0;

    write("You polish the " + LANG_WORD(which + 1) + " skull with great care.\n");
    say(QCTNAME(TP) + " does something to the "+ LANG_WORD(which + 1) + " skull.\n");

    sk = m_indices(skulls)[which];

    seq += ({ sk });
    if(!sizeof(words) || !(comp = compare(words, seq)))
       set_alarm(1.0, 0.0, reset_room);

    if(!skulls[sk]++)
      tell_room(TO, "The light within the crystalline skull slowly brightens.\n");
    else
       tell_room(TO, "The glow within the skull slowly brightens further, until it "
         + "seems to be " + LANG_WNUM(skulls[sk]) + " times "
         + "brighter than before.\n");

   if(comp == 2)
   {
      open_door();
	  TO->catch_msg("A thrill of adrenaline rushes through you as you realize "
	      +"that you're closer than ever to meeting Mascarvin.\n"); 
	  TP->set_skill(SS_MASQ_STAGE, STAGE_4_SKULLS);
      return 1;
   }

   return 1;
}

void
init()
{
    ::init();

    add_action(touch, "touch");
    add_action(touch, "rub");
    add_action(touch, "feel");
	add_action(touch, "polish");
    add_action(touch, "press");
    add_action(touch, "massage");
    add_action(touch, "caress");
	add_action(touch, "worship");
	add_action(touch, "clean");
	add_action(touch, "shine");
}



