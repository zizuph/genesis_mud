/*
 * /d/Gondor/common/dwarf_guild/bear/home.c
 * 
 * Mercade @ Genesis - April 24 2000
 *
 * The home for the bears and the bear control system.
 */

inherit "/std/room";

#pragma save_binary
#pragma strict_types

#include "bear.h"
#include <macros.h>
#include <stdproperties.h>

/*
 * Global variables.
 */
mapping bears = ([ ]);
string *honeys = ({ });

/*
 * Function name: long_description
 * Description  : Composes a long description dependent on the person who is
 *                looking.
 * Returns      : string - the long description.
 */
string
long_description()
{
    string text;

    text = "This is the home of bears.\n";

    if (!this_player()->query_wiz_level())
    {
        text += "When so desired, you may \"return\" to your previous " +
            "location.\n";
    }

    return text;
}

/*
 * Function name: return_room
 * Description  : For mortals that get stuck here, make it possible to return
 *                to some other room.
 * Returns      : mixed - the room to transport the mortal to.
 */
nomask mixed
return_room()
{
    mixed exit;

    if (strlen(exit = (string)this_player()->query_prop(PLAYER_S_TRANSED_FROM)))
    {
        return exit;
    }

    if (objectp(exit = (object)this_player()->query_prop(LIVE_O_LAST_ROOM)))
    {
        return exit;
    }

    return this_player()->query_default_start_location();
}

void
restore_bears()
{
    mapping save;

    setuid();
    seteuid(getuid());
    
    save = restore_map(BEAR_SAVE);

//  bears = (pointerp(save["bears"]) ? save["bears"] : ([ ]) );
    honeys = (pointerp(save["honeys"]) ? save["honeys"] : ({ }) );
}

void
save_bears()
{
    setuid();
    seteuid(getuid());
    
    save_map( ([ "honeys": honeys ]) , BEAR_SAVE);
}

/*
 * Function name: create_room
 * Description  : Constructor.
 */
void
create_room()
{
    set_short("home of bears");
    set_long(long_description);

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(return_room, "return");

    restore_bears();
}

/*
 * Function name: add_honey
 * Description  : Adds a honey description to the list.
 * Arguments    : string honey - the honey description to add.
 */
void
add_honey(string honey)
{
    if (!IN_ARRAY(honey, honeys))
    {
        honeys += ({ honey });
        save_bears();
    }
}

/*
 * Function name: remove_honey
 * Description  : Removes a honey description from the list.
 * Arguments    : string honey - the honey description to remove.
 */
void
remove_honey(string honey)
{
    honeys -= ({ honey });
    save_bears();
}

/*
 * Function name: query_num_honeys
 * Description  : Find out how many honey descriptions are listed.
 * Returns      : int - the number of honeys.
 */
int
query_num_honeys()
{
    return sizeof(honeys);
}

/*
 * Function name: query_honeys
 * Description  : Find the listed honey descriptions.
 * Returns      : string * - the honey descriptions.
 */
string *
query_honeys()
{
    return secure_var(honeys);
}

/*
 * Function name: valid_bear
 * Description  : Checks whether a bear exists with this number.
 * Arguments    : int bear_number - the number of the bear to check.
 * Returns      : int - true if the bear exists, else false.
 */
int
valid_bear(int bear_number)
{
    if (!pointerp(bears[bear_number]))
    {
        return 0;
    }
    if (!sizeof(bears[bear_number]))
    {
        return 0;
    }
    return 1;
}

/*
 * Function name: query_bear_name
 * Description  : Get the name of the bear for a particular number.
 * Arguments    : int bear_number - the number of the bear.
 * Returns      : string - the name of the bear.
 */
string
query_bear_name(int bear_number)
{
    if (!valid_bear(bear_number))
    {
        return "bear";
    }

    return bears[bear_number][BEAR_NAME];
}

/*
 * Function name: query_bear_gender
 * Description  : Get the gender of the bear for a particular number.
 * Arguments    : int bear_number - the number of the bear.
 * Returns      : int - the gender of the bear.
 */
int
query_bear_gender(int bear_number)
{
    if (!valid_bear(bear_number))
    {
        return -1;
    }

    return bears[bear_number][BEAR_GENDER];
}

/*
 * Function name: query_bear_history
 * Description  : Generate the history for this bear.
 * Arguments    : int bear_number - the number of the bear.
 *                int backwards - if true, then the history is printed in
 *                    reverse order, i.e. last first.
 * Returns      : string - the history.
 */
string
query_bear_history(int bear_number, int backwards)
{
    if (!valid_bear(bear_number))
    {
        return 0;
    }

}