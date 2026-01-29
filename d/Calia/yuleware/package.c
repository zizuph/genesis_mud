// OBJECT:  package

    /* Calia Domain

    HISTORY

    [1998-12-07] Created by Uhclem from [C:\CALIA\YULEWARE\PACKAGE.DOC].
    [1999-12-09] Toy list updated by Uhclem.
    [2000-12-20] Toy list, shapes list, selection formula updated by Uhclem.
    [2001-12-22] Message to holiday room added by Uhclem.

    PURPOSE

    This wrapped package contains a toy selected at random and is found under
    the Christmas tree in the domain office in the Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include "defs.h"

// GLOBAL VARIABLES

string Name_on_tag;
string Toy;

// FUNCTIONS

// Function:  write_tag(player_name)

/*

Purpose:  identify the recipient of this package so that nobody else can open
it. Called by the object which dispenses packages.

Arguments:  string with name of player

Returns:  nothing

*/

void
write_tag(string player_name)

{

    Name_on_tag = player_name;

    add_item(({"tag", "small tag"}),
        "It reads 'to " + player_name + "'.\n");

}

// Function:  check_tag()

/*

Purpose:  check to see if a player is the one to whom this package is
addressed.

Arguments:  none

Returns:  0 for the correct player, a string for anyone else.

*/

mixed
check_tag()

{

    if (this_player()->query_name() == Name_on_tag) return 0;
    else return "This package is not for you.\n";

}

// Function:  unwrap_package()

/*

Purpose:  take the toy out of the package (if it's yours), which is discarded.

Arguments:  none

Returns:  1.

*/

int
unwrap_package()

{

    object gift;
    object tp = this_player();

    if (check_tag())

    {

        write("Not even you are so depraved or callous as" +
            " to unwrap somebody else's present!\n");

    }

    else

    {

        gift = clone_object("/d/Calia/yuleware/toys/" + Toy);
        gift->move(tp);

        write("You unwrap the " + query_short() +
            " and discover a " + gift->short() + " inside!\n");

        say(QCTNAME(tp) + " unwraps a " + short() +
            " and discovers a " + gift->short() + " inside!\n");

        tell_room(HOLIDAY_ROOM,
            QCTNAME(tp) + " finds " + LANG_ADDART(gift->short()) +
            " under the tree.\n");

        remove_object();

    }

    return 1;

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

    ::init();
    add_action(unwrap_package, "unwrap");

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  VARIABLES    
     */

    string *darks = ({"red", "green", "blue", "purple", "orange"});
    string *brights = ({"gold", "silver", "white", "yellow"});
    string *tints = ({"bright", "dark", "pastel", "shiny", "metallic"});

    string *shapes = ({"cylindrical", "square", "soft", "round", "long",
        "small", "triangular", "flat", "spherical"});

    /*
     *  The "marionette" appears twice on purpose.  As of Christmas 2000, there 
     *  are 16 toys, and - assuming no crashes - each player will only have a
     *  chance to get 7 of them.  With over 30Kb of functions, the marionette
     *  is the most advanced toy, so I figure that a player will appreciate an
     *  extra chance to get one.  Keeping the two entries far apart minimizes
     *  the risk that a player will get it twice.    
     */

    string *toys = ({"marionette", "cymbals", "mage", "monkey", "pinwheel",
        "spinboing", "dogcow", "frisbee", "kroug", "marionette", "tiger",
        "handpuppet", "kender", "pipe", "bongos", "frog", "jumprope"});

    string dark = darks[random(sizeof(darks))];
    string bright = brights[random(sizeof(brights))];
    string tint = tints[random(sizeof(tints))];
    string shape;
    object tp = this_player();

    /*
     *  DESCRIPTION    
     */

    /*
     *  The following formula adds the day of the month to the player's average 
     *  stats to select a toy so that (a) different players get different toys
     *  to the degree possible and (b) a player returning the next day will
     *  most likely find a different toy waiting for him.    
     */

    Toy =
        toys[(tp->query_average() + atoi(explode(ctime(time()), " ")[2]))
        % sizeof(toys)];

    shape = shapes[member_array(Toy, toys) % sizeof(shapes)];
    set_name("package");
    add_name(shape + " package");

    set_long("This package must contain something special," +
        " but it's so pretty it seems a shame to unwrap it!\n");

    if (random(4))

    {

        add_name(shape + " " + bright + " package");
        add_name(bright + " package");
        add_adj(shape);
        add_adj(bright);

        set_short(shape + " " + bright + " package with a " + tint +
            " " + dark + " ribbon");

        add_item(({"ribbon", dark + " ribbon", tint + " " + dark + " ribbon"}),
            "The ribbon is made of satin and attached loosely so" +
            " that the package is easy to unwrap. A small" +
            " tag hangs from it.\n");

    }

    else

    {

        add_name(shape + " " + tint + " " + dark + " package");
        add_name(dark + " package");
        add_name(tint + " " + dark + " package");
        add_adj(shape);
        add_adj(dark);

        set_short(shape + " " + tint + " " + dark +
            " package with a " + bright + " ribbon");

        add_item(({"ribbon", bright + " ribbon"}),
            "The ribbon is made of satin and attached loosely so" +
            " that the package is easy to unwrap. A small" +
            " tag hangs from it.\n");

    }

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_VALUE, 0);

    add_prop(OBJ_M_NO_SELL, "Sell a gift even before you've" +
        " opened it? You've been downing too much eggnog!\n");

    add_prop(OBJ_M_NO_GIVE, "This package is for you alone!\n");
    add_prop(OBJ_M_NO_GET, "@@check_tag@@");

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

}
