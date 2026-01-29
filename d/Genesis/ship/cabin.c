#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>

static	string	cabin_sounds;
		/* Sounds to be heard when in the cabin. (VBFC) */
static	string	bump_sound;
		/* The sound to hear when ship lands. (VBFC) */
static	object	ship;

/*
 * Function name: set_cabin_sound
 * Description:   Set what sound to be heard when the ship moves, can be VBFC
 * Arguments:	  str - The string to print
 */
public void
set_cabin_sound(string str)
{
    cabin_sounds = str;
}

/*
 * Function name: set_bump_sound
 * Description:   Set what sound to be heard when ship lands on a pier 
 * Arguments:     The string to print
 */
public void
set_bump_sound(string str)
{
    bump_sound = str;
}

/*
 * Function name: create_cabin
 * Description  : Create the ship cabin
 */
public void
create_cabin()
{
    set_short("Ship cabin");
    set_long("You are in the ship's cabin\n");
}

/*
 * Function name: create_room
 * Description  : Set up default values for the ship cabin
 */
nomask void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    set_cabin_sound("The ship sways slightly in the wind.\n");
    set_bump_sound("You feel the ship bump into something.\n");
    create_cabin();
}

nomask void
reset_room() { this_object()->reset_cabin(); }

/*
 * Function name: ship_arrived
 * Description  : Give a description about where we currently got to
 * Arguments    : A string or object pointing to the current room
 */
public void
ship_arrived(mixed where)
{
    ship = previous_object();

    if (where->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
	tell_room(this_object(), check_call(bump_sound));
    else
	tell_room(this_object(), check_call(cabin_sounds));
}