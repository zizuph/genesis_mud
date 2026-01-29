// OBJECT:  pile

    /* Calia Domain

    HISTORY

    [1998-12-07] Created by Uhclem from [C:\CALIA\YULEWARE\PILE.DOC].
    [2000-12-23] Uhclem added datetime routine in init() to replenish pile.

    PURPOSE

    A pile of gifts under the tree in the domain office to be dispensed one to
    each visiting player. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// GLOBAL VARIABLES

string *Recipients = ({});  /*  List of players who have received gifts.  */
string Pile_Date = explode(ctime(time()), " ")[2];

    /*
     *  See init() for date/time usage.   
     */

// FUNCTIONS

// Function:  look_at_gifts

/*

Purpose:  returns the long description and also puts a gift in the player's
inventory if he hasn't already received one.

Arguments:  none

Returns:  string containing pile description

*/

string
look_at_gifts()

{

    object tp = this_player();
    object gift;

    string text = "The packages are all wrapped in a variety of" +
        " bright colors and loosely piled as if someone simply" +
        " emptied a big sack of them here. ";

    if (member_array(tp->query_name(), Recipients) == -1)

    {

        gift = clone_object("/d/Calia/yuleware/package");
        gift->write_tag(tp->query_name());
        gift->move(tp);
        Recipients += ({tp->query_name()});

        text = text + "\n\nThere's a " + gift->short() +
            " that has your name on it! You take it from the pile.\n\n";

        say(QCTNAME(tp) + " takes a " + gift->short() +
            " from the pile.\n");

    }

    else

    {

        text = text + "You've already taken your package from this" +
            " pile. All of these are for other people, but" +
            " who knows - maybe there will be another one" +
            " for you here tomorrow!\n";

    }

    return text;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    /*
     *  Every time a player comes by, this routine compares the current 
     *  day-of-month with the day that the pile was last replenished.  If the
     *  day has changed, the pile is replenished by clearing the list of
     *  players who have collected toys.    
     */

    string *datetime = explode(ctime(time()), " ");

    /*
     *  Contents of array "datetime": 
     *  [0] day-name
     *  [1] month
     *  [2] day-num
     *  [3] time
     *  [4] year
     *  The elements are in the same format as displayed by the "date"
     *  command.    
     */

    ::init();

    if (Pile_Date != datetime[2])

    {

        Recipients = ({});
        Pile_Date = datetime[2];

        /*
         *  And of course, the function must have entertainment value!    
         */

        tell_room(environment(),
            "A tiny green frog arrives dragging a big sack of gifts." +
            " He " +
            ({"pauses to wipe the sweat off his brow,",
            "takes a swig from a little bottle of brandy",
            "stretches his limbs after setting down his load"})[random(3)] +
            ", " +
            ({"kicks the gifts out of the bag onto the ",
            "whisks the sack out from under the gifts, which tumble" +
            " into the ",
            "lifts the sack high over his head and" +
            " heaves its contents onto the "})[random(3)] +
            short() +
            ", then dashes out of the room with the empty sack " +
            ({"thrown over his shoulders like a cape and" +
            " shouting, 'the Yule Frog strikes again!'",
            "pulled over his head to conceal his identity as" +
            " the Secret Yule Frog of Calia!",
            "spread out beneath him, carrying him away" +
            " like a flying carpet!"})[random(3)]);

    }

}

// OBJECT DEFINITION

void
create_object()

{

    set_short("pile of wrapped packages");
    set_long("@@look_at_gifts@@");
    set_name("pile");
    add_name("packages");
    add_name("wrapped packages");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 75000);
    add_prop(OBJ_I_VALUE, 1000000000);
    add_prop(OBJ_M_NO_GET, "You can't take the whole pile.\n");

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

}
