/*
 * Filename: /d/Avenir/common/ships/bazaar/pipe.c
 * Original creator: Kazz on May 1995
 * Purpose: inherit file for boat 'pipe' functions.
 * Last update(s):
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 *    Manat on Sep 2002   - changed so that one can hit on
 *                          the pipe with armours
 *                          And removed the use of NFN()
 * Note: Used in outpost/boat/boat_path2 and bazaar/pier/float
 * Known bug(s):
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

#include "/d/Avenir/common/common.h"

/* #define DEBUG */
#undef DEBUG
#ifdef DEBUG
#define D(x) find_player("manat")->catch_tell("PIPE DEBUG: " + (x))
#else
#define D(x) ;
#endif

public object query_ship();
public int do_call_boat(string str);
public int dont_move(string str);
private object boat_start_room;

/*
 * Function name: init_boat_room
 * Description  : init the command set for the player
 */
public void
init_boat_room()
{
    add_action( do_call_boat, "beat" );
    add_action( do_call_boat, "hit" );
    add_action( do_call_boat, "pound" );

    add_action( dont_move, "move" );
    add_action( dont_move, "pull" );
    add_action( dont_move, "push" );
    add_action( dont_move, "get" );
    add_action( dont_move, "take" );
}

/*
 * Function name: pipe_description
 * Returns      : the default string for a pipe used to call a Sea boat.
 *                for the delivery office. This can be called eg with:
 *                add_item( ({ "pipe", "metal pipe" }),
 *                         "@@pipe_description@@");
 */
public string
pipe_description()
{
    return("The hard metal pipe sticks out about two feet from the sea " +
           "surface. It leans over the beach slightly, and you can " +
           "see it disappear underwater at the same angle. Despite the " +
           "hard quality of the metal, the pipe has scratches.\n");
}

/*
 * Function name: pipe_scratch_description
 * Returns      : the default string for a pipe used to call a Sea boat.
 *                for the delivery office. This can be called eg with:
 *                add_item( ({ "scratches", "pipe scratches" }),
 *                         "@@pipe_scratch_description@@");
 */
public string
pipe_scratch_description()
{
    return("The scratches are scattered along the length of the pipe.\n");
}

/*
 * Function name: is_valid_armour
 * Description  : Filter function to check if the armour is valid
 * Arguments    : object armour - the armour to check
 * Returns      : (int)1/0 - valid/not valid
 */
public int
is_valid_armour(object armour)
{
    int at;
    at = armour->query_at();
    if (at != A_SHIELD &&
        at != A_R_ARM && at != A_L_ARM &&
        at != A_R_HAND && at != A_L_HAND)
        return 0;
    /* HERE: TODO check for a heavy armour */
    return 1;
}

/*
 * Function name: is_valid_armour
 * Description  : Filter function to check if the armour is valid
 * Arguments    : object armour - the armour to check
 * Returns      : (int)1/0 - valid/not valid
 */
public int
is_valid_weapon(object weapon)
{
    /* HERE: TODO check for a weapon heavy enough */
    return 1;
}

/*
 * Function name: do_call_boat
 * Description  : beating on a metal pipe to summon the Sea boat.
 * Arguments    : the arguments to the command
 * Returns      : 1/0 - I can handle this / This is not my problem
 */
public int
do_call_boat(string str)
{
	 object obj;
	 int this_is_armour, this_is_weapon;
	 string foo = "", *arr = ({ "pipe" });
	 object *weapons, *armours, *inv;

	 if (!str || !strlen(str))
	 {
		  notify_fail( capitalize(query_verb()) + " what?\n");
		  return 0;
	 }

	 if (!parse_command( str, ({ }), "[metal] %p", arr) &&
		  !parse_command( str, ({ }), "[metal] %p %s", arr, foo))
	 {
		  notify_fail( capitalize(query_verb()) + " what?\n");
		  return 0;
	 }

	 /* Get the weapons and armours to use */
	 weapons = this_player()->query_weapon(-1);
	 armours = this_player()->query_armour(-1);
	 if (strlen(foo))
	 {
		  inv = weapons + armours;

		  //MANAT, this parse_command is very buggy.
		  //To see how, do not wield a weapon and try
		  //to hit the pipe with it. This if statement will execute
		  //if one's weapon is not wielded (or armour is not worn).
		  //That is a Bug.
		  if (!parse_command(foo, inv, "'with' %o", obj))
		  {
				notify_fail( capitalize(query_verb()) +
								 " the pipe with what? " +
								 "Your hands would be hurt.\n");
				return 0;
		  }

		  if(member_array(obj, armours) !=-1)
				this_is_armour = 1;

		  if(member_array(obj, weapons) !=-1)
				this_is_weapon = 1;

		  if (( this_is_armour && !is_valid_armour(obj)) ||
				( this_is_weapon && !is_valid_weapon(obj)))
		  {
				write ("The " + obj->short(this_player()) +
						 " is not usable to hit the pipe with.\n");
				return 1;
		  }

		  if(this_is_weapon && !obj->query_wielded())
		  {
				write ("You aren't wielding the " +
					obj->short(this_player()) + "!\n");
				return 1;
		  }

		  if(this_is_armour && !obj->query_worn())
		  {
				write ("You aren't wearing the " +
					obj->short(this_player()) + "!\n");
				return 1;
		  }
	 }
	 else
	 {
		  /* filter the valid objects to use */
		  if (sizeof(weapons) > 0)
            weapons = filter(weapons, is_valid_weapon);
        if (sizeof(armours) > 0)
            armours = filter(armours, is_valid_armour);

        inv = weapons + armours;
        if (!sizeof(inv))
        {
            notify_fail( capitalize(query_verb()) +
                         " the pipe with what? " +
                         "Your hands would be hurt.\n");
            return 0;
        }
        obj = inv[0];
    }

    write ( "You beat on the metal pipe with the " +
            obj->short(this_player()) + "!\n");
    say( QCTNAME(this_player()) + " hits the metal pipe with " +
        this_player()->query_possessive() + " " + obj->short() + ".\n" );

    /* coming depends on the creature's current state. */
    /* call the boat: it will always return 1 */
    if (!query_ship()->call_boat(file_name(this_object())))
        write("The pipe is broken. Please leave bug report.\n");

    return 1;
}

/*
 * Function name: dont_move
 * Description  : the pipe can't be moved
 * Arguments    : string str - the argument to the command
 * Returns      : 1/0 - I can handle this / This aint my problem
 */
public int
dont_move(string str)
{
    if (!str || !strlen(str)) 
    {
        notify_fail( capitalize(query_verb()) + " what?\n");
        return 0;
    }
  
    if ((str != "pipe") && (str != "metal pipe")) 
    {
        notify_fail( capitalize(query_verb()) + " what?\n");
        return 0;
    }
  
    write( "The pipe won't budge.\n" );
    return 1;
}

/*
 * Function name: query_ship
 * Description  : return the sea ship
 * Returns      : object - the ship
 */
public object
query_ship()
{
    return boat_start_room->query_ship();
}

/*
 * Function name: set_boat_start_room
 * Description  : Let this object know which room is the starting room
 *                of the sea ship
 * Arguments    : object ob - the room where the sea ship starts
 */
public void
set_boat_start_room(object ob)
{
    boat_start_room = ob;
}
