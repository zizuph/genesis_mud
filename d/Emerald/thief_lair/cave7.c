/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir, platform functionality
   by Shiva.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/thief_lair/base_cave.c";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>

#define OTHER_ROOM (THIEF_LAIR_DIR + "cave6")

//prototypes:

void start_conversation(object player);
void end_conversation();

// Global variables.

int InConversation; //1 if a conversation between bandits and players is 
                    //presently taking place, 0 otherwise.

int PlayerUnresponsive; // 1 if the player is in danger of being attacked
                        // by the bandits due to non-cooperation.
                       
/* Determines whether or not the platform is here. Returns a
   pointer to the platform if it is here, 0 if it is not.
*/
mixed 
platform_here()
{
    return (present("thief_lair_platform"));  
}


/* Determines whether or not there are any bandits present in this room.
   
   Returns: 0 - There are no bandits in the room,
            A bandit object, if there are one or more bandits in the room.
*/

mixed
bandits_present()
{
    object *bandits = filter(all_inventory(this_object()), &->query_bandit());
    
    if (sizeof(bandits) == 0)
    {
	return 0;
    }

    return bandits[0];
}

/* Simple function which allows for a slight variation in the description
   of the mechanism, depending upon the presence of the platform which
   runs between cave6 and cave7.
*/

string
mechanism_descrip()
{
    if (platform_here())
    {
	return ("The platform is securely fastened to twin rails which " +
		"extend up the southern wall of the cavern, as far as the "+
		"overhanging ledge. A crank protrudes from the wall, " +
		"right next to the rails.\n");
    }
    
    return ("Twin metal rails extend up the southern wall as far as the "+
	    "overhanging ledge. Looking up, you notice that there is some "+
	    "sort of wooden platform attached to the rails. A crank protrudes "+
	    "from the wall, right next to the rails.\n");
}

/* Function to prevent anyone who is carrying too much from climbing
   up the rope ladder.
*/

public int
block_up()
{
    if (this_player()->query_prop(OBJ_I_WEIGHT) > 90000)
    {
	write("As you step onto the ladder, you notice the ropes tighten, " +
	      "barely able to hold your weight.  It is far too dangerous " +
	      "to continue your climb.\n");
	    return 1;
    }
   
    return 0;
}

/* Called when the player tries to climb the ladder. Climbing the ladder
   is just not possible when engaged in combat. ;)
*/

int combat_block()
{
    int i; // loop index
    object player;
    object *foes; // All current enemies of the player.
    
    player = this_player();
    foes = player->query_enemy(-1);
          
    if (sizeof(foes))
    {
	write("Um....no. You cannot climb the rope ladder while engaged "+
	      "in combat!\n");
	return 1;
    }
    
    return block_up(); // Not in combat, check the players weight.
}

int block_forward()
{
    if (bandits_present())
    {
	write(capitalize(bandits_present()->short()) + " steps in front of "+
	      "you and denies you passage.\n");
	return 1;
    }
    
    return 0;
}

/* Whenever the lieutenant makes a request from a player during
   the conversation, this function is called via set_alarm.
   If the player has not responded satisfactorily within the two
   minute time limit, she will be attacked.
*/  
 
void
attack_player(object player, object lieutenant)
{
   if (!(PlayerUnresponsive) || !present(player))
   {
       end_conversation();
       return; // The player has responded in time, or left the room.
   }
   
// The player has not responded in time:

   lieutenant->command("emote scowls.");
   lieutenant->command("say My patiance with you is exhausted.!");
   lieutenant->strike_down(player); //Commands all bandits to attack 
                                    //the player.
   InConversation = 0;
}

/* This function is called when a player arrives down the ladder.
   Probably should figure out some way of calling it should someone
   teleport in - but that possibilities seems too remote and
   difficult to bother with.
*/
void
player_arrives()
{
    object lieutenant;

    lieutenant = present("_gregarry");
    
    if ((!lieutenant) || InConversation ||
	!(this_player()->check_seen(lieutenant)))
    {
	return; // The lieutenant is not present, or the another
	        // conversation is taking place, or the player cannot
	        // be seen by Gregarry. Do nothing.
    }

    start_conversation(this_player());
}
/* This function is called from the exit function in cave6. If
   the lieutenant is present in this chamber, he will react to
   the person who enters in one of the following manners:

   1) Introduce himself and ask a question. Failure to either
   leave or respond reasonably in a reasonable amount of time
   results in the player being attacked. This is done if the
   player's current status vis-a-vis the bandits is neutral.

   2)Attacks the player if the player is a known enemy of the
   bandits. This occurs if any bandits are present within
   this room.

   3)Greet the player and allow him and his/her to team to 
   pass deeper into the cavern if the player is a friend of
   the bandits.

NB: In situation 1, a new conversation will NOT be started
    when another player enters the room.
*/

void 
start_conversation(object player)
{
    object lieutenant;
    lieutenant = present("_gregarry");

    InConversation = 1;
    lieutenant->command("introduce myself");
    lieutenant->command("say You shouldn't be here. Who are you "+
			   "and what do you want?\n");
    write("\nYou get the impression that he wants you to 'respond' with "+
	  "only one word.\n");

    PlayerUnresponsive = 1;
    set_alarm(120.0, 0.0, &attack_player(player, lieutenant));
   
    return;
}

/* Moves the specified player and his team into cave8. Note that 
   any player in a team may successfully respond to gregarry's
   queries, allowing the whole team to pass deeper into the bandits
   lair.
 */

void
move_team(object player)
{
    object lieutenant; //gregarry, the bandit leader found here
    object *team; // The players team.
    object member; // A member of team.
    int i; // loop index 
    
    lieutenant = present("_gregarry");
    team = player->query_team_others();
    team += ({player});
    
    lieutenant->command("say Alright. You may pass. "+
			"Don't try anything funny though, or you will "+
			"regret it.\n");

    for (i = 0; i < sizeof(team); i++)
    {
	member = team[i];
	member->catch_msg(QCTNAME(lieutenant) + " ushers you past "+
			   "him, deeper into the cavern.\n");
	member->move_living("north", THIEF_LAIR_DIR + "cave8", 1, 0);
    }
}

/* Called when a player succesfully "responds" to gregarry's
   query. Cleans up global variables and checks to see if other
   players have arrived during the previous conversation, in
   which case a new conversation is started.
*/
void
end_conversation()
{
    object *inv; //inventory of the room
    object member; //member of inventory
    object lieutenant; //gregarry, if he is present
    int i, sz; // loop index, sizeof(inv)

// First, lets make sure a player who has left the room is not attacked!
    PlayerUnresponsive = 0;

    lieutenant = present("_gregarry");

    inv = all_inventory(this_object());

    for (i = 0, sz = sizeof(inv); i < sz; i++)
    {
	member = inv[i];

	if (living(member)&& !(member->query_npc()) && 
			       member->check_seen(lieutenant));
	{
	    /* The lieutenant spies that another player has entered the room -
	       he starts to converse with him. Note that the this function 
	       terminates upon finding the first such player. */
	  
	    start_conversation(member);
	    return;
	}
    }

    // No livings in the room, therefore:
    
    InConversation = 0;
}
	    
/* Function which allows players to respond to Gregarry when he
   begins a conversation with them. Returns true if a response is
   given - i.e. works like any other add_action().  
   Note that I have opted to allow anyone to respond to 
   gregarry's question, rather than employing input_to(). There
   were other reasons for this choice, also, but I am have forgotten
   them at the moment.
*/

int
get_response(string arg)
{
    string garbage; // exactly what the name implies
    object lieutenant;
    lieutenant = present("_gregarry");

/* The players are not in conversation with Gregarry, therefor we 
   effectivly remove the respond command:
   
   Note: Any player in the room can respond to Gregarry's queries.
*/

    if ((!InConversation) || (! lieutenant) )
    {
	notify_fail("There is nothing for you to respond to.\n");
	return 0;
    }

    /* They are in conversation, therefor check to see if the player
       responded with only one word, as instructed.
    */

    if (sscanf(arg, " %s", garbage))
    {
	notify_fail("Please respond with only one word.\n");
	return 0;
    }

    say(QCTNAME(this_player()) + " explains that he is seeking " +
	arg + ".\n");

    /* On a temporary basis, I wish to record all responses by players in a log,
       so that I can get a good idea of how players react to this particular
       situation, and add appropriate new args which will trigger a response 
       from the bandits.
    */
    
    write_file(THIEF_LAIR_DIR + "log/response_log", this_player()->
	       query_met_name() + " replied with: " + arg + "\n");


    /* Various possible responses by the bandits, depending upon the players
       response to Gregarry's queries:
    */

    if (arg ==  "help")
    {	
	lieutenant->command("emote nods slowly.");
	lieutenant->command("say Now, are you in need of help...");
	lieutenant->command("say Or would you like to help us out?");
	lieutenant->command("emote raises his eyebrow inquisitivly.");
	lieutenant->command("say I suppose it doesn't really matter...");
	PlayerUnresponsive = 0;
	move_team(this_player());
	return 1;
    }	
	
    if (arg == "loot" || arg == "treasure" || arg == "wealth" ||
	arg == "money" || arg == "gold" || arg == "coins")
    {
	lieutenant->command("say Isn't that what we all seek?");
	lieutenant->command("Hmmm... perhaps we will increase ours - " +
			    "at your expense, of course.");
	lieutenant->command("emote grinds amusedly.");
	tell_room(this_object(), "Snickers, giggles, and outright laughter follow that "+
		  "last comment.\n", 0, this_object());
	return 1;
    }

    if (arg == "exploring" || arg == "adventure" || arg == "adventuring" ||
	arg == "experience") 
    {
    }
	
	
 // None of the above responses were given:
    
    lieutenant->command("say And just what do you mean by that?");
    lieutenant->command("snicker");
    lieutenant->command("say You had better give me a straight answer...");
    
    return 1;
}

void
create_banditcave_room()
{
    set_short("By a stream in a huge, moist subterranean cavern.");
    set_em_long("In a huge, moist subterranean cavern. A stream "+
		"runs across the floor of the cavern, the water "+
		"flowing southwards into the southern wall of the "+
		"cavern. A rope ladder climbs its way up the "+
		"southern wall towards a ledge which overlooks "+
		"the cavern. Some sort of strange mechanism of "+
		"rails and pulleys has been set into the cavern "+
		"wall, beside the ladder.\n");

    Track_Descrip = "You notice the occasional footprint "+
	"in the rare patches of mud on the floor\n";

    Track_Difficulty = 35 + random(20);
    
    add_item(({"stream", "brook", "underground stream", "bubbling brook"}),
	     "A shallow stream flows from north to south along the western "+
	     "wall of this cavern. The flows into the south wall of the "+
	     "cavern but passage in that direction appears impossible. The "+
	     "swift flowing water is reasonably clear and looks to be "+
	     "wholesome.\n");

    add_item(({"wall", "walls"}),
	     "The walls of this cavern are composed of black "+
	     "basalt. In places, water drips off of the walls "+
	     "to form pools of moisture on the cavern floor. "+
	     "An abundance of green moss grows in patches along "+
	     "the walls. The southern wall of the cavern is in "+
	     "fact a cliff which leads to a ledge some thirty "+
	     "feet above you. A rope ladder and some sort of "+
	     "rail and pulley system are to be found on this "+
	     "cliff face.\n");

    add_item(({"floor", "cavern floor", "bottom"}),
	     "The floor of this cavern is very uneven. Much of it "+
	     "is covered by a thick green moss. Water occasionally "+
	     "drips into pools at the base of the cavern walls. "+
	     "@@discover_tracks@@");
			     

    add_item(({"footprints", "footprint", "outline", "outlines",
	     "vague outline", "vague outlines"}),
	     "A closer examination of the footprints reveals that they "+
	     "were made by booted feet of normal human (or elven, or "+
	     "orcish ... ) size. The number of footprints suggests "+
	     "many creatures have passed through here, though the "+
	     "footprints lead in all different directions.\n");

    add_item(({"roof", "ceiling"}),
	     "The cavern roof is far above you, a hundred feet or more.\n");

    add_item(({"cliff", "cliff face", "south wall"}),
	     "A slippery, moss covered cliff leads up to a wide ledge "+
	     "some 30 feet above you.\n");

    add_cmd_item(({"cliff", "cliff face", "south wall"}),
		 ({"climb", "climb up"}),
		 "Covered in moss and moisture, the south wall looks "+
		 "to be anything but climbable. The rope ladder "+
		 "appears to a much safer method of reaching the "+
		 "overhanging ledge.\n");
      
    add_item("ledge",
	     "An overhanging ledge runs along most of the southern "+
	     "wall of the cavern. It can be reached by climbing the "+
	     "rope ladder.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");


    add_item(({"ladder", "rope ladder", "rope"}),
	     "A ladder, made of thick hemp rope ascends 30 feet up "+
	     "the southern wall of the cavern, ending at wide ledge "+
	     "which overlooks the cavern. It looks to be sturdy "+
	     "enough, but just the same, you would not want to "+
	     "push your luck by climbing up it while carrying too "+
	     "much.\n");

    add_item(({"puddle", "puddles", "pools"}),
	     "The moisture which trickles down the walls of the "+
	     "occasionally forms small puddles on the cavern floor.\n");

    add_cmd_item(({"puddles", "pools"}), ({"drink", "drink from"}),
           "The puddles of water look to be rather stagnant and dirty. "+
	   "The swift flowing stream, on the other hand, looks to much "+
	   "more pleasant.\n");

    add_item(({"mechanism", "strange mechanism", "rails", "rail",
		 "rails and pulleys", "pulleys"}),
	     mechanism_descrip);

    add_item("crank",
	     "A heavy looking crank, made of iron, is set into the cavern "+
	     "wall, near the mechanism.\n");	

    add_exit("cave8", "north", block_forward, 0, 0);
} 

/* Player activated command to raise or lower the platform
   which allows the transportation of goods between this room
   and cave6.

   Argument string str - Player input.

   Returns  1 - Success.
   Returns  0 - Failure. The crank was not turned.
*/

public int
turn_crank(string str)
{
    string arg;
    object platform, oroom;

    if (!strlen(str))
    {
        return 0;
    }

    if ((str != "crank") && !sscanf(str, "crank %s", arg))
    {
        notify_fail("Turn what?\n");
        return 0;
    }
    
    if (bandits_present())
    {
      write(capitalize(bandits_present()->short()) + " steps firmly in front of "+
	    "you, preventing you from getting anywhere near the "+
	    "mechanism.\n");
      return 1;
    }

    if ((str == "crank") || ((arg != "clockwise") &&
        arg != "counterclockwise"))
    {
        notify_fail("Do you wish to turn the crank " +
            "clockwise or counterclockwise?\n");
        return 0;
    }

    catch(OTHER_ROOM->load_me());
    if (!(oroom = find_object(OTHER_ROOM)))
    {
        write("The crank won't turn.\n");
        return 1;
    }
   
    if (arg == "clockwise")
    {

// Turning the platform clockwise - lowering the platform.

        if (!(platform = present("thief_lair_platform", oroom)))
	{
            write("The crank won't turn.\n");
            return 1;
	}

        write("As you begin to turn the crank, the platform begins to "+
	      "descend towards you, coasting along the metal rails. "+
	      "Eventually, you have lowered the platform to near "+
	      "ground level.\n");

        say(QCTNAME(this_player()) + " begins turning the crank. You "+
	    "notice that the platform begins to slowly descend towards "+
	    "you, coasting along the metal rails.\nThe platform "+
	    "eventually comes to a rest at ground level.\n");
	
	platform->move(this_object(), 1);
        return 1;
    }
    
// Turning counter-clockwise: Raising the platform.

    if (!(platform = platform_here()))
    {
        write("The crank won't turn.\n");
        return 1;
    }

    platform->move(oroom, 1);
    write("As you turn the crank, the platform is gradually lifted off "+
	  "of the ground, sliding upwards along the metail rails. You "+
	  "continue turning the crank until the platform reaches the "+
	  "top of the rails at the height of the ledge.\n");

    say(QCTNAME(this_player()) + " turns a crank and the platform " +
        "is gradually lifted off of the ground, sliding upwards along "+
	"the metal rails. The platform continues upward until it "+
	"reaches the end of the rails at the height of the overhanging "+
	"ledge.\n");

    return 1;
}

public int
climb_ladder(string arg)
{   

    if ((arg == "up") || (arg == "ladder") || (arg == "up ladder") 
	|| (arg == "up the ladder"))
    {

// Make sure the player is not in combat, and is not too heavy for the ladder:

	if (!(combat_block()))
	{
// He isn't:
	    this_player()->move_living("up", THIEF_LAIR_DIR + "cave6", 1, 0);
	    return 1;
	}
    }

    // Command fails.

    return 0;
}

void
init()
{
    ::init();
    add_action(turn_crank, "turn");
    add_action(drink_from_stream, "drink");
    add_action(climb_ladder, "climb");
    add_action(get_response, "respond");
}
    
 



