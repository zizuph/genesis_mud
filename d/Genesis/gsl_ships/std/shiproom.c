/*
 * Standard ship room
 */

#include <macros.h>
#include "../ships.h"

inherit "/std/room";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

static object ship;
static int is_deck;
static string   deck_sounds;    /* sounds to be heard when ship moves (VBFC) */
static string bump_sound;   /* The sound to hear when ship lands. (VBFC) */
static string cabin_sounds;     /* The sound to hear when ship lands when in cabins. (VBFC) */

string  examine_sea   ();
object  query_ship    ();
void    set_ship      (object ship_object);
int     query_is_deck ();
void    set_is_deck   (int deck_status);
int     disembark     (string str);
int     dive          (string str);
string  peer          (string str);
nomask void set_deck_sound (mixed str);
nomask string query_deck_sound ();
nomask void set_bump_sound (mixed str);
nomask string query_bump_sound ();
nomask void set_cabin_sound (mixed str);
nomask string query_cabin_sound ();

void
create_shiproom ()
{
  ::create_room();

  add_item(({"sea", "water", "ocean", "view"}), "@@examine_sea");
  
  set_deck_sound("The ship sways slightly in the wind.\n");
  set_bump_sound("You feel the ship bump into something.\n");
  set_cabin_sound("You feel ship rocking back and forth.\n");
}

public string
examine_sea ()
{
    if(!query_ship())
    {
        return "";
    }
    
    if(!query_is_deck())
    { 
        return "You can't see the outside, but you can hear sounds of "
            + "waves outside the ship.\n";
    }
    
    return NAVIGATION_MANAGER->examine_sea(ship);
}

public nomask object
query_ship ()
{
    return ship;
}

public nomask void
set_ship(object ship_object)
{
    ship = ship_object;
}

public nomask int
query_is_deck ()
{
    return is_deck;
}

public nomask void
set_is_deck (int deck_status)
{
    is_deck = deck_status;
}

public void
init()
{
    ::init();
    if (is_deck == 1) 
    {
        add_action(disembark, "disembark");
        add_action(disembark, "exit");
        add_action(disembark, "leave");
        add_action(dive,      "dive");
        add_action(peer,      "peer");
    }
}
/*
 * Function name: disembark
 * Description  : Allow a player to leave the ship if the ship is in a room
 *        that is NOT of water type
 * Arguments    : what - what we want to leave, if 0 the command have to be
 *        disembark for the command to work.
 * Returns      : 1 - success, 0 - wrong parameters
 */
varargs public int
disembark(mixed what)
{
  mixed *rows;
  
    if (!ship)
    {
        NF0(capitalize(query_verb()) + " what?");
    }

    if (ship->query_is_at_harbor() == -1)
    {
        NF0("Do you want to dive or what?");
    }

    set_dircmd(what);
    write("You leave the " + ship->short() + "\n");
    this_player()->move_living("the " + ship->short(), environment(ship));
    mapping row = PIER_DATABASE->query_row_by_id(ship->query_is_at_harbor());
    if (!mappingp(row))
    {
        return 1;
    }
    CONTROLROOM->send_debug_message(
                                    "gslcontrol_general",
                                    this_player()->query_name() +
                                    " disembarked " +
                                    ship->get_ship_id() + " " +
                                    row["port"],
                                    BOARD_LOG
                                    );
    return 1;
}

public int
dive (string str) 
{
  // TODO
    NF0("Diving is not enable yet, sorry.\n");
}

/*
 * Function name: set_deck_sound
 * Description:   Set the sound that should be heard when the ship moves
 *        Can be VBFC.
 * Arguments:     str - The string to print
 */
public nomask void
set_deck_sound(mixed str)
{
    deck_sounds = str;
}

/*
 * Function name: set_bump_sound
 * Description:   Set what sound to be heard when ship lands on a pier
 * Arguments:     The string to print
 */
public void
set_bump_sound(mixed str)
{
    bump_sound = str;
}

/*
 * Function name: query_deck_sound
 * Description:   Query the sound that should be heard when the ship moves
 *        Can be VBFC.
 */
public nomask string
query_deck_sound ()
{
  return check_call(deck_sounds);
}

/*
 * Function name: query_bump_sound
 * Description:   Query what sound to be heard when ship lands on a pier
 */
public string
query_bump_sound ()
{
  return check_call(bump_sound);
}

/*
 * Function name: set_cabin_sound
 * Description:   Set the sound that should be heard when the ship moves
 *        Can be VBFC.
 * Arguments:     str - The string to print
 */
public nomask void
set_cabin_sound(mixed str)
{
  cabin_sounds = check_call(str);
}

/*
 * Function name: query_cabin_sound
 * Description:   Query the sound that should be heard when the ship moves
 *        Can be VBFC.
 */
public nomask string
query_cabin_sound ()
{
    return cabin_sounds;
}

public int
peer (string str)
{
    if (!strlen(str) || str != "outside")
    {
        notify_fail("Peer outside?\n");
        return 0;
    }
    
    write(examine_sea());
    return 1;
}
