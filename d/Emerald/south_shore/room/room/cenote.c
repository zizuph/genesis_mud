/* /d/Emerald/south_shore/room/cenote.c
*
*  This room serves as the summoning location for Demerga.
*  Players must <search> the crack in the wall to call her.
*  After she is defeated, the player may then <search> the crack
*  for coins.
*
*  Created 12.28.2021 by Velith
*
*  Many thanks to Arman for his work on the crevice!
*/

#pragma strict_types
#include <stdproperties.h>
#include <time.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include <subloc.h>
#include <money.h>
inherit "/d/Emerald/std/room";
inherit LIBPIER;
#define WATER_SUBL "_water_subloc"
#define SERPENT_OBJECT    ("/d/Emerald/south_shore/npc/demerga.c")

/* prototypes */
public void         create_emerald_room();
public string       read_sign();
public mixed        search_crack(object searcher, string what);
public mixed        beach(object searcher, string what);
public mixed        clone_serpent(object searcher, string what);
public void         reset_room();

/* global variables */
object    Demerga_Npc;
object    serpent;
object    ob;
int crack_searched, serpent_cloned;

/*
* Function nane:        create_emerald_room
* Description  :        set up the room
*/
public void
create_emerald_room()
{
    set_short("rocky cenote");
    set_em_long(
      "Eons of storms and waves have carved a cavern near the "
      + "rocky beaches of Lake Telberin. Many sharp obsidian "
      + "stones litter the shore, making it a beautiful but "
      + "uncomfortable place to linger for long. The cenote's black "
      + "walls are composed of the same stones that coat the beach. "
      + "It has been worn smooth by water and time, and the rock "
      + "is cool to the touch. The water laps gently at the beach, "
      + "with rather powerful waves nearly reaching where you stand. "
      + "There is a small sign stuck into the craggy beach here. \n");
    add_item( ({ "cenote", "cave", "cavern" }),
      "Over eons of time, waves of water have worn away at the "
      + "shore, hollowing out a cave from its stone walls. Smooth, "
      + "glassy walls surround you on all sides, dripping with "
      + "moisture from the lake. The gentle melodies of lapping "
      + "waves brings your attention back to the tide. What "
      + "secrets do the waters hold?\n");
    add_item( ({ "water", "lake", "waves" }),
      "Cool waves of crystal-clear water lap gently at the "
      + "beach. Occasionally a larger wave will rush up the "
      + "beach and soak the rocks near you. When the sunlight "
      + "hits the water just right, the color of the water shifts "
      + "mysteriously, almost appearing holographic at times. "
      + "The waves of the water seem quite odd too, almost as "
      + "if there were a large creature moving underneath "
      + "the surface...\n");
    add_item( ({ "wall", "walls", "black wall", "back wall" }),
      "The wall at the back of the cenote has been worn "
      + "smooth by waves of water over time. As you run your "
      + "hands over the surface, you discover a huge crater "
      + "in the center! Staring in astonishment, realization "
      + "dawns on you that this dent was created when "
      + "someone - or something - smashed the stone that "
      + "originally made up the wall. As you stumble back "
      + "in shock, a flash of light draws your attention "
      + "to a hidden crevice.\n");
    add_item( ({ "beach", "craggy beach" }),
      "Instead of sand, the lake has deposited rocks on "
      + "the beach. The many pebbles and stones that now "
      + "cover this beach are slick and wet with constant "
      + "waves from the lake.\n");
    add_item( ({ "rock", "rocks", "pebble", "pebbles", "stone", "stones"  }),
      "These stones gleam a glossy black color, reminding "
      + "you of smooth pieces of obsidian. They make the "
      + "the beach glitter a beautiful deep black, lighting "
      + "up with direct light graces the cave.\n");
    add_item( ({ "crack", "crevice", "crater"  }),
      "Something is definitely lodged in this crevice. "
      + "It sparkles silver as the light hits it, bright "
      + "against the glossy black wall.\n");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_subloc(WATER_SUBL, this_object());
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    // make interactive objects
    try_item( ({ "sign", "signpost", "post", "nearby post" }),
      read_sign);
    add_cmd_item( ({ "sign", "signpost" }),
      ({ "read" }), read_sign);
    try_item( ({ "crevice", "crater", "crack" }),
      search_crack);
    add_cmd_item( ({ "crevice","crater", "crack" }),
      ({ "search" }), search_crack);

    set_no_exit_msg( ({ "northwest", "north", "west", "southwest",
	"southeast"}),
      "You find that the gleaming walls of the cenote block "
      + "your journey that way.\n");
    set_no_exit_msg( ({ "northeast", "east", }),
      "The dark waters of Lake Telberin look vicious and "
      + "unforgiving. Shuddering, you turn and wade out of the "
      + "water.\n");
    add_exit("/d/Emerald/telberin/dock/hidden_beach", "beach", beach, 1);
    reset_room();
} /* create_emerald_room */

/*
* Function name:        read_sign
* Description  :        show the sign, in fun text graphics
* Returns      :        string - the sign text
*/
public string
read_sign()
{
    string desc;
    desc = "\n"
    + " _________________\n"
    + "|         B E W A -,\n"
    + "|                  |_____\n"
    + "| Disturb neither the roc^._\n"
    + "| pebbles of this beach, les<-,\n"
    + "| great serpent of the depths t|_\n"
    + "| her wrathful revenge on us all!-,\n"
    + "|_________________________________|\n"
    + "            |      |\n"
    + "            |      |\n";
    return desc;
}

/*
* Function name :        search_crack
* Description   :        Allows the player to search the crack
*                        for coins, which also summons the serpent.
* Returns       :        The serpent, coins.
*/
public mixed
search_crack(object searcher, string what)
{
    if (CAN_SEE_IN_ROOM(this_player()))
    {
	object searcher = this_player();
	// can't search if serpent still in the room.
	if(objectp(serpent))
	{
	    this_player()->catch_msg("The serpent hisses, forcing "
	      + "your attention away from the crack.\n");
	    return 1;
	}
	// check if serpent has been recently cloned.
	if(!serpent_cloned)
	{
	    tell_room(this_object(), "An eerie aura of dread envelopes "
	      + "the room. \n", this_object(), this_object());
	    set_alarm(10.0, 0.0, &tell_room
	      ("/d/Emerald/south_shore/room/cenote.c", "Every fiber "
		+ "of your being screams for you to leave this place! \n",
		0, this_player()));
	    set_alarm(15.0, 0.0, &tell_room
	      ("/d/Emerald/south_shore/room/cenote.c", "The lake ripples "
		+ "as something large moves towards the shore. This is your "
		+ "last chance to leave! \n", 0, this_player()));
	    set_alarm(25.0, 0.0, &clone_serpent(searcher, what));
	}
	else if (!crack_searched)
	{
	    setuid();
	    seteuid(getuid());
	    MONEY_MAKE_PC(5 + random(45))->move(this_player(), 1);
	    crack_searched = 1;
	    say(QCTNAME(this_player())+ " finds something in the crack!\n");
	    return ("You search the crack and find something!\n");
	}
	else
	{
	    say(QCTNAME(this_player())+ " searches the crack but doesn't " +
	      "find anything.\n");
	    return "You search the crack but do not find anything.\n";
	}
    }
    return 0;
} /* search crack */

/*
* Function name :        clone_serpent
* Description   :        Clone the serpent
* Returns       :        The serpent
*/
public mixed
clone_serpent(object searcher, string what)
{
    tell_room(this_object(), "\nA great serpent " +
      "erupts from the waters behind you!\n", this_object(),
      this_object());
    setuid();
    seteuid(getuid());
    serpent = clone_object(SERPENT_OBJECT);
    serpent->move(this_object(), 1);
    serpent->command("$kill " +searcher->query_real_name());
    serpent_cloned = 1;
    return "";
} /* clone serpent */

/*
* Function name :        beach
* Description   :        Traps the player if they're fighting the
*                        serpent.
* Returns       :        A block or exit message.
*/
public mixed
beach(object searcher, string what)
{
    if (CAN_SEE_IN_ROOM(this_player()))
    {
	// can't search if serpent still in the room.
	if(objectp(serpent))
	{
	    if( serpent->query_serpent_half_health() )
	    {
		this_player()->catch_msg("The serpent's tail is blocking the exit!\n");
		return 1;
	    }
	}
	else
	{
	    return 0;
	}
    }
} /* beach */

/*
* Function name:        reset_room
* Description  :        clone some npcs to the room at resets
*/
public void
reset_room()
{
    crack_searched = 0;
    serpent_cloned = 0;
} /* reset_room */
