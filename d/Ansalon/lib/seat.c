/*
 * Support for sitting in rooms
 * 
 * Not ready for use yet
 * 
 * Last updated:
 *   98 09 02 Ashlar
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <composite.h>

static mixed    seats;
static mixed    seat_id;
static mixed    preps;
static int      set_desc;

int cmd_sit(string str);
int cmd_stand(string str);
int find_seat(string id);

/*
 * Function name: init_seat
 * Description:   This function adds the sit and stand command to this_player()
 *		          call it from your init()
 */
void
init_seat()
{
    add_action(cmd_sit, "sit");
    add_action(cmd_stand, "stand");
}

/*
 * Function name: cmd_sit
 * Description:   Parses the player's input and tries to seat him.
 * Arguments:     str - The input from the player
 * Returns:       1 or 0
 */
int
cmd_sit(string str)
{
    string *words;
    mixed prep;
    int i,tmp;
    mixed seat;
    
    if (!str)
    {
	notify_fail(capitalize(query_verb()) + " where?\n");
	return 0;
    }

    words = explode(str, " ");

    prep = 0;
    if (sizeof(words) > 1)
    {
	tmp = member_array(words[0], preps);
	if (tmp >= 0)
	{
	    prep = words[0];
	    str = implode(words[1 .. sizeof(words)], " ");
	}
    }

    i = find_seat(str);
    if (i < 0)
    {
	notify_fail("You find no " + str + " to " + query_verb() + " " +
		    (stringp(prep) ? prep : "on") + ".\n");
	return 0;
    }

    seat = seats[i];

    if (stringp(prep) && (member_array(prep, seat[0]) < 0))
    {
	notify_fail("You can not " + query_verb() + " " + prep +
		    " the " + seat[1] + ".\n");
	return 0;
    }

    if (!stringp(prep))
	prep = "on";
        
    if (seat[2] > 0 && sizeof(seat[3] -= ({ 0 })) >= seat[2])
    {
	notify_fail("There is no room for you " + prep + " the " +
		    seat[1] + ".\n");
	return 0;
    }

    write("You sit down " + prep + " " + LANG_ADDART(seat[1]) + ".\n");
    say(QCTNAME(this_player()) + " sits down " + prep + " " +
	LANG_ADDART(seat[1]) + ".\n");

    seats[i][3] += ({ this_player() });

    return 1;
}

/*
 * Function name: cmd_stand
 * Description:   Parses the player's input and tries to stand him up
 * Arguments:     str - The input from the player
 * Returns:       1 or 0
 */
int
cmd_stand(string str)
{
    int i, tmp;
    
    if (stringp(str) && str != "up")
    {
        notify_fail(capitalize(query_verb()) + " how?\n");
        return 0;
    }

    tmp = -1;
    for (i = 0; i < sizeof(seat_id); i++)
    {
        if (member_array(this_player(), seats[i][3]) >= 0)
        {
            tmp = i;
            break;
        }
    }

    if (tmp < 0)
    {
        notify_fail("You are already standing up.\n");
        return 0;
    }

    write("You stand up from the " + seats[i][1] + ".\n");
    say(QCTNAME(this_player()) + " stands up from the " + seats[i][1] + ".\n");

    seats[i][3] -= ({ this_player() });
    
    return 1;
}


/*
 * Function name: add_seat
 * Description:   Add a seat in the room
 * Arguments:	  id	    - An array with names to id the seat
 *                prep      - The prepositions used with this seat
 *                short     - The short description of the seat
 *                numseats  - How many people it can seat, or 0 for
 *                            unlimited seats
 */
varargs void
add_seat(mixed id, mixed prep, string short, int numseats)
{
    if (!pointerp(id))
    	id = ({ id });
    if (!pointerp(prep))
	    prep = ({ prep });

    if (!seats)
	    seats = ({ });
    if (!seat_id)
    	seat_id = ({ });
	if (!preps)
	    preps = ({ });
    if (!set_desc)
        this_object()->add_my_desc("@@describe_all_seats@@", this_object());

    seat_id += ({ id });
    seats += ({ ({ prep, short, numseats, ({ }) }) });
    preps |= prep;
}

/*
 * Function name: query_seats
 * Description:   Query the seats array
 * Returns:	      The seats array
 */
mixed
query_seats() { return seats; }

/*
 * Function name: query_seat_id
 * Description:   Query the seat id:s
 * Returns:	      The array holding all seat id:s
 */
mixed
query_seat_id() { return seat_id; }

/*
 * Function name: remove_seat
 * Description:   Remove a special seat, identified with id
 * Arguments:	  id - A identifying string
 * Returns:	      1 if removed
 */
int
remove_seat(string id)
{
    int i;

    i = find_seat(id);
    if (i >= 0)
	{
	    seat_id = exclude_array(seat_id, i, i);
	    seats = exclude_array(seats, i, i);
	    return 1;
	}

    return 0;
}

static int
find_seat(string id)
{
    int i;

    for (i = 0; i < sizeof(seat_id); i++)
	    if (member_array(id, seat_id[i]) >= 0)
	        return i;

    return -1;
}

/*
 * Function name: describe_seated
 * Description:   Shows a description of who are sitting on the seat
 * Arguments:     id - An identifying string
 * Returns:       A string describing who is sitting, if any, else ""
 */
string
describe_seated(string id)
{
    int i,num;
    object *pl;
    mixed seat;

    i = find_seat(id);
    if (i < 0)
        return "";

    seat = seats[i];

    pl = seat[3] -= ({ 0 });
    pl -= ({ this_player() });

    num = sizeof(pl);

    if (num == 0)
        return "";

    return capitalize(COMPOSITE_LIVE(pl)) + 
        (num == 1 ? " is " : " are ") +
        "sitting " + seat[0][0] + " " +
        LANG_ADDART(seat[1]) + ".\n";
}

/*
 * Function name: describe_seated
 * Description:   Shows a description of who are sitting in the room
 * Returns:       A string describing who is sitting, if any, else ""
 */
string
describe_all_seats()
{
    int i,j,num;
    string s = "";
    object *pl;
    
    for (i = 0; i < sizeof(seat_id); i++)
    {
        pl = seats[i][3] -= ({ 0 });
        
        pl -= ({ this_player() });

        num = sizeof(pl);

        if (num > 0)
            s += capitalize(COMPOSITE_LIVE(pl)) + 
                (num == 1 ? " is " : " are ") +
                "sitting " + seats[i][0][0] + " " +
                LANG_ADDART(seats[i][1]) + ".\n";
    }

    return s;
}
        
    
