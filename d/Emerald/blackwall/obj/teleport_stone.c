/* A teleport stone. This is a reward for solving the faerie riddle quest.
   It is autoloading, and will, once only, allow a player to teleport
   to a predetermined room, regardless of whether or not the character is
   in combat.

   Code (c) Damian Horton, BKA Casimir, 2000.
*/

inherit "/std/object";
inherit "lib/holdable_item"; //these stones can be held
inherit "lib/keep"; //the player may ensure that the stones are not sold 

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>

//global variables:
mixed Destination; //room to which the stone can teleport its user,
                   //0 if no such room is set (default).

//prototypes
int command_crush(string arg);
int command_peer(string arg);

void
create_object()
{
    set_name("stone");
    add_name("crystal");
    add_name("rock");
    add_name("_faerie_teleport_stone");
    set_adj("crystalline");
    add_adj("hard");
    add_adj("amber");
    add_adj("yellow");

    set_short("crystalline stone");
    set_long("A hard, rounded crystal of dull amber color. The stone is of a "+
	"good size, sufficiently large to be grasped comfortably in one "+
	"hand. The stone does not appear to be particularly valuable, "+
	"though a good gemsmith might be able to make something out of it. "+
	"Gazing upon it for a long time brings about the urge to hold it in "+
	"your hand and peer into it.\n");
   
    add_prop(OBJ_I_WEIGHT, 250);   
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 100 + random(200)); //looks like a rough
                                              //cut gem
    //magical, and very hard to damage
    add_prop(OBJ_I_RES_ACID, 90);
    add_prop(OBJ_I_RES_COLD, 90);
    add_prop(OBJ_I_RES_ELECTRICITY, 90);
    add_prop(OBJ_I_RES_FIRE, 90);
    add_prop(OBJ_I_RES_MAGIC, 25);

    //magical properties
    add_prop(MAGIC_AM_MAGIC, ({60, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, 
	     ({"This stone clearly has some magic about it.\n", 5,
		 "Strong summoning magic is bound to the stone.\n",
		 10, "The magic of the stone can be summoned only "+
		 "once.\n", 20, "When crushed, the stone will "+
		 "transport whomever grasps it to a predefined "+
		 "location.\n", 40}));
    add_prop(OBJ_S_WIZINFO, "This is an autoloading, one use "+
	     "only item given out as a reward for the faerie riddle "+
	     "quest in Emerald. By concentrating on the stone, "+
	     "whomever holds it can set a teleport destination "+
	     "to the room is he is presently within. Subsequently "+
	     "the stone can be crushed, destroying it, and "+
	     "transporting the holder to that location.\n");

    set_slots(W_ANYH); //stones can be held in any hand
    set_keep(1); //the stone cannot be sold, by default

    Destination = 0; //no destination to begin with
}

/* Must be done in holdeable items. */
void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

/* Must be done in holdeable items. */ 
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}
 
void
init()
{
    ::init();
    add_action(command_crush, "crush");
    add_action(command_peer, "peer");
    add_action(command_peer, "gaze");
    add_action(command_peer, "stare");
}

/* Add_action which allows the holder of the stone to set a destination
   for the teleport. Note that once a destination has been set, it cannot be
   changed (though it will be reset to unset status upon reloading). Note
   also that the destination cannot be set to a room which does not allow
   access via teleportation. */

int
command_peer(string arg)
{
    if (! arg)
    {
	notify_fail("Peer into what, the crystalline stone?");
	return 0; //command failed
    }

    if (! parse_command(arg, ({}), "'at' / 'into' [the] [hard] "+
			"[crystalline] 'stone' / 'rock' ") &&
	(! parse_command(arg, ({}), "'at' / 'into' [the] [hard] "+
			"'crystal' "))) 
	/* The correct syntax is 'peer', 'stare' gaze' at/into [the]
	   stone/rock or crystal'. Any of these will succeed. */
    {
	notify_fail("Peer into what, the crystalline rock?\n");
	return 0; //command failed
    }
    
    //command succeeded to some degree beyond here:
    
    if (! query_held())
    {
	//the stone is not held, peering into will have no effect
	write("You concentrate upon the crystal, staring into it "+
	      "feverishly but nothing seems to happen. Perhaps "+
	      "if you held the stone, it would be easier to "+
	      "concentrate upon it.\n");
	return 1; //command successful
    }
    if (Destination || (holder->query_mana() < 100))

    {
	/* Either a destination has already been set, or the
	   holder has insufficient mana (100 is required) to 
	   transform the stone.
	*/
	write("You concentrate upon the crystal, staring into it "+
	      "feverishly but you cannot seem to invoke any kind "+
	      "of effect. You exhaust yourself, but nothing happens.\n");
	say(QCTPNAME(holder) + " eyes glaze over as " + 
	    holder->query_pronoun() + " stares into "+
	    "the delicate crystal " + holder->query_pronoun() + 
	    " holds in " + holder->query_possessive() + " hands.\n");
	
	if (holder->query_mana() < 100)
	{
	    holder->set_mana(0);//exhaust the players mana
	}
	
	else
	{
	    holder->add_mana(-100); //the player loses 100 mana
	}

	return 1; //command succeeded.
    }

    else
    {
	holder->add_mana(-100); //mana cost to try to transform the stone
	Destination = environment(holder);

	if (Destination->query_prop(ROOM_M_NO_TELEPORT) ||
	    Destination->query_prop(ROOM_M_NO_TELEPORT_TO) ||
	    Destination->query_prop(ROOM_M_NO_MAGIC) ||
	    Destination->query_prop(OBJ_M_NO_MAGIC))
	{
	    /* The room the stone's holder is in is teleport shielded for
	       some reason, and therefor he cannot set it as the destination.
	    */
	    Destination = 0; //that destination will not be set
	    
	    write("You peer hesitantly into the stone. Some strange force "+
		  "seems to draw you inwards towards it. Abruptly, you find "+
		  "that your gaze is drawn to your surroundings, you seem "+
		  "to be able to see them more clearly and in great detail, "+
		  "but that sensation only lasts a moment. It is replaced "+
		  "by a rapidly growing confusion and blurriness which "+
		  "quickly fills your mind until all you perceive is "+
		  "darkness!\nThe trance breaks, leaving your face "+
		  "dripping with cold sweat.\n");
	    say(QCTPNAME(holder) + " eyes glaze over as " + 
		holder->query_pronoun() + " stares feverishly into "+
		"the crystalline stone " + holder->query_pronoun() + 
		" holds in " + holder->query_possessive() + " hands. "+
		"Sweat begins to bead upon " + holder->query_possessive() +
		" forehead and then " + holder->query_pronoun() +
		" throws " + holder->query_possessive() + " head back "+
		"and breaks out of the trance.\n");
	    return 1;//command succeeded
	}
							    
	write("You peer hesitantly into the stone. Some strange force "+
	      "seems to draw you inwards towards it. You concentrate "+
	      "upon the stone and then find yourself gazing around at "+
	      "your surroundings. For a moment, you almost fancy that "+
	      "you can see everything around you, all at once. Every "+
	      "detail of every object becomes briefly fixed in your "+
	      "mind, even things not within your immediate field of "+
	      "view. Then, that sensation is gone, to be replaced by "+
	      "a gentle warmth within your hand. The hard stone you "+
	      "had held has taken on a different appearance; that "+
	      "of a sharply defined, almost brittle-looking translucent "+
	      "crystal of a bluish coloration.\n");
	say(QCTPNAME(holder) + " eyes glaze over as " + 
	    holder->query_pronoun() + " stares feverishly into "+
	    "the crystalline stone. "+
	    "As if in a trance, " + holder->query_pronoun() + 
	    " slowly turns " + holder->query_possessive() + " head around, "+
	    "allowing " + holder->query_possessive() + " feverish "+
	    "gaze to fall briefly upon everything in the area. The "+
	    "next moment, there is a small flash of light emanating from "+
	    "the hand in which " + holder->query_pronoun() + " held "+
	    "the stone and the trance like state is dispelled.\n");

	// Changes in the stone's state:

	set_long("A roundish translucent crystal with a light bluish tint to "+
		 "its coloration. The stone is of a good size, large enough to be "+
		 "grasped firmly in your hand, but does not look to be overly "+
		 "valuable. It appears to be delicate however, and you can't help "+
		 "but feel that you could crush it in the palm of your hand, if "+
		 "you so desired.\n");

	set_short("delicate crystal");
	add_adj("delicate");
	add_adj("translucent");
	add_adj("blue");
	add_adj("bluish");
	remove_adj("hard");
	remove_adj("yellow");
	remove_adj("amber");

	return 1;//the holder has succeeded in setting the crystals destination
    }
}

/* Add_action which allows the user to crush the stone when held. If
   its in its brittle state, it will teleport the holder to destination.
   A stone so used is permanently destroyed.
*/
int
command_crush(string arg)
{    
    object teleport_destination; //room to teleport to

    if ((! arg) || (! parse_command(arg, ({}), "[the] [hard] 'stone' / "+
				    "'crystal' / 'rock'")))
    {
	//command failed
	notify_fail("Crush what?");
	return 0;
    }

    if (! query_held())
    {
	//this command only functions when the crystal is held
	notify_fail("You can only crush something that you hold.\n");
	return 0;
    }

    if (! Destination)
    {
	//the Destination of the stone has not been set, it cannot be
	//crushed.
	write("You squeeze the hard crystalline stone as hard as you can, "+
	      "but to no avail. The stone is too hard for you to crush.\n");
	return 1; //command succeeded
    }

//Command succeeded in fullness:

    if (environment(holder)->query_prop(ROOM_M_NO_TELEPORT) ||
	environment(holder)->query_prop(ROOM_M_NO_TELEPORT_FROM))
    {
	//player cannot teleport from that room, as it is magically
	//shielded (presumably)

	write("Slowly and deliberately, you squeeze the crystal, its sharp "+
	      "edges digging into the soft flesh of the palm of your hand. "+
	      "Gradually, you increase the pressure until you are crushing "+
	      "it with all your might! Just when you think you can squeeze "+
	      "no harder, the crystal snaps into a fine sprinkle of dust "+
	      "which sticks to your bloody hands. At that moment, you "+
	      "are engulfed in intense pain. Your vision blurs, and you "+
	      "see flashes of darkness as your body feels as if it were "+
	      "being torn in all different directions at once.\n");
	
	say(QCTNAME(holder) + " crushes something in " +
	    holder->query_possessive() + " hands and is immediately "+
	    "engulfed in what can best be called some kind of distortion "+
	    "field. " + capitalize(holder->query_possessive()) + " body "+
	    "writhes and contorts into impossible positions!\n");
	
	holder->command("$scream");    
	
	write("Mercifully, the pain ends as abruptly as it came, and you "+
	      "collapse to the ground in a quivering heap.\n");

	say("Momentarily, the effect ceases and " + QCTNAME(holder) + 
	    "collapses into a quivering heap.\n");

	//Im not nice - the stone has been expended in this effort"
	remove_object();
	return 1; //command succeeded
    }

// The teleport succeeds below this line:

    write("Slowly and deliberately, you squeeze the crystal, its sharp "+
	  "edges digging into the soft flesh of the palm of your hand. "+
	  "Gradually, you increase the pressure until you are crushing "+
	  "it with all of your might! Just when you think you can squeeze "+
	  "no harder, the crystal snaps into a fine sprinkle of dust which "+
	  "sticks to your bloody hands. Abruptly, you become very dizzy, "+
	  "and the world around you turns to darkness...\n");

    teleport_destination = Destination; //must do this since the stone is
                                        //destroyed
    //    remove_object(); //the stone is forever destroyed when crushed
    /* commented out because I cannot get the code to behave properly
       if I destroy the stone here - results in a somewhat inappropriate
       release message at the instant when the stone is actually
       destroyed (at the end of this function) */

    if (teleport_destination == environment(this_player()))
 
	/* Player is attempting to teleport to the room he is already
	   standing in. This presents no problems. Note that holder is
	   a static variable of holdable_item. */
    { 
	write("Then there is a flash of bright light, and you struggle "+
	      "to retain your footing as the world spins back into view.\n");
	say(QCTNAME(this_player()) + " crushes something in " +
	    this_player()->query_possessive() + " hands then staggers "+
	    "around as if hit on the head with a club.\n");
	remove_object(); //the stone is destroyed
	return 1; //command successful
    }

    //this say is done here for timing purposes:
    say(QCTNAME(this_player()) + " crushes something in " +
	this_player()->query_possessive() + " hands. Then abruptly dissapears "+
	"from view! Gone, vanished as if " + this_player()->query_pronoun() +
	" never was!\n");

    // check to make sure it is still possible to teleport to the destination:

    if (teleport_destination->query_prop(ROOM_M_NO_TELEPORT) ||
	teleport_destination->query_prop(ROOM_M_NO_TELEPORT_TO) ||
	teleport_destination->query_prop(ROOM_M_NO_MAGIC) ||
	teleport_destination->query_prop(OBJ_M_NO_MAGIC))
    {
      // its not, therefor:

      write("Then there is a flash of bright light, and you struggle "+
	    "to retain your footing as the world spins back into view.\n");
      say("Abruptly, " + QCTNAME(this_player()) + " reappears and staggers "+
	  "around as if hit on the head with a club.\n");
      remove_object(); //stone is destroyed anyhow
      return 1; //command succeded
    }

    if ( this_player()->move_living("M", teleport_destination, 1, 1))
    {
      /* the teleport has failed, for some reason, this shouldn't have
	 happened... Note the use of M as the first argument - even though
         its a move by 'teleportation', I print my own special messages.*/

	write("Then there is a flash of bright light, and you struggle "+
	      "to retain your footing as the world spins back into view.\n");
	say("Abruptly, " + QCTNAME(this_player()) + " reappears and staggers "+
	    "around as if hit on the head with a club.\n");
    }

    else
    {
	//he has teleported successfully
	write("Then there is a flash of bright light, and you struggle "+
	      "to retain your footing as the world spins back into view : "+
	      "only you are not where you used to be!!");
	say("Suddenly, out of thin air, " + QCTNAME(this_player()) +
	    " appears and staggers around for a moment, as if just hit on the "+
	    "head with a club.\n");
	this_player()->command("$look");
    }

    remove_object(); //the stone has been destroyed permanently
    return 1; //command was successful
}

/* Changed the tense of the original message so that it would
   be accurate when it is printed as a result of the stone destruction
   by crushing (see command_crush, above, for details). I also
   do not echo to the room that the player released the stone. Doing
   so would look silly, in light of the user teleporting to a new room
   and then the message being printed, and the action is so small as
   to be reasonably overlooked in other circumstanced.*/

public mixed
release()
{
    write("You have released the " + short() + ".\n");
    return 1; //do not print default messages.
}
 
/* The teleport stones are autoloading, until used. (at which point,
   they are destoyed). Note that the state of the stone is not saved,
   therefor the player will have to set a new destination for the stone
   upon each login. Destination's for the teleport will not be saved
   over reboot. */

public string
query_auto_load()
{
    return MASTER + ":";
}




