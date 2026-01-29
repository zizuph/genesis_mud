// OBJECT:  dispenser

    /* Calia Domain

    HISTORY

    [99/10/24] Created by Uhclem from [D:\CALIA\WEENWARE\MOUSE_HO.DOC].

    PURPOSE

    A home for the long-tusked boar mouse in the domain office in the Tower of
    Realms. This object is only used on Halloween.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

// GLOBAL VARIABLES

object Mouse;               /*  the currently foraging mouse  */
object This_Room;           /*  location of this mouse hole  */
int Mouse_Sequence;         /*  controls foraging sequence  */

// FUNCTIONS

// Function:  clean_up_fuzzies()

/*

Purpose:  removes excess cheese fuzzies from the room.

Arguments:  none

Returns:  nothing

*/

void
clean_up_fuzzies()

{

    object fuzzie = present("fuzzie", This_Room);
    string f;;

    if (!fuzzie) return;

    if (fuzzie->num_heap() > 1)

    {

        f = "fuzzies";

    }

    else

    {

        f = "fuzzie";

    }

    tell_room(This_Room,
        "\n" +
        ({
        "The gaunt, faceless figure of Death glides silently" +
        " into the room, reaches down to the floor with a bony" +
        " hand, scoops up the unwanted " + f + ", and rasps: Ah," +
        " just the thing for a midnight snack! Now to find" +
        " some fresh warm blood to go with it...\nDeath fades" +
        " away before your eyes, leaving only a chill in the air" +
        " as evidence of his visit.",
        "A raven flies into the room, alights briefly on the floor" +
        " to gobble up the superfluous " + f + ", then ascends" +
        " with a powerful flap of his wings and disappears" +
        " out the door.",
        "A huge, warty old toad appears at the door. He" +
        " flicks his stupendously long tongue into the middle" +
        " of the room, slurping up the extra " + f + ", then" +
        " leaps out of sight.",
        "A black bat swoops into the room and snatches" +
        " the extraneous "  + f + " off the floor in a" +
        " smooth, continuous arc that carries him back" +
        " out the door."
        })[random(4)] +
        "\n\n");

    fuzzie->remove_object();

}

// Function:  mouse_control()

/*

Purpose:  provide messages for the mouse throughout the foraging sequence,
which is interrupted if the mouse if taken by a player or otherwise removed
from the room.

Arguments:  none.

Returns:  nothing.

*/

void
mouse_control()

{

    object where_is_mouse = environment(Mouse);
    object fuzzie;
    string mouse_pronoun = Mouse->query_pronoun();
    string mouse_possessive = Mouse->query_possessive();
    int n;

    /*
     *  First, check to see if the mouse has moved to a player's inventory or 
     *  to another room.  Cease controlling the mouse if this happens.    
     */

    if (where_is_mouse && where_is_mouse != This_Room)

    {

        Mouse = 0;  /*  Discontinue control of mouse when player takes it  */
        clean_up_fuzzies();
        return;

    }

    /*
     *  Second, make sure that a cheese fuzzie (which lures the mouse out of 
     *  the hole) is still either in the room or in the mouse's inventory.  If
     *  not, the mouse heads back into the hole.    
     */

    if (!present("fuzzie", This_Room) &&
        !present("fuzzie", Mouse))

    {

        tell_room(This_Room,
            "The " + Mouse->short() + " scurries back into" +
            " " + mouse_possessive + " hole!\n");

        Mouse->remove_object();
        return;

    }

    Mouse_Sequence += (random(2) + 1);

    switch (Mouse_Sequence)

    {

        case 0..1:

        tell_room(This_Room,
            ({
            QCNAME(Mouse) + " sticks " + mouse_possessive +
            " head out of " + mouse_possessive + " hole, takes" +
            " a look at you, and immediately ducks back" +
            " inside the hole.\n",
            "A faint noise comes out of the hole in the wall.\n",
            "Something moves inside the hole in the wall.\n"
            })[random(3)]);

        break;

        case 2..3:

        /*
         *  If the mouse has not yet entered the room, move him in now.    
         */

        if (!where_is_mouse)

        {

            Mouse->move(This_Room);

            tell_room(This_Room,
                QCNAME(Mouse) + " sticks " + mouse_possessive +
                " head out of " + mouse_possessive + " mouse" +
                " hole, sniffs around a bit, and then" +
                " timidly ventures out toward the cheese fuzzie.\n");

        }

        break;

        case 4..5:

        tell_room(This_Room,
            QCTNAME(Mouse) + " " +
            ({
            "circles around the cheese fuzzie, constantly glancing" +
            " up at you and then back at the food.\n",
            "approaches the cheese fuzzie, takes a quick sniff" +
            " up close, then backs away again.\n",
            "runs around the room haphazardly, weaving between" +
            " your feet and circling the cheese fuzzie.\n",
            "sits in the middle of the floor and" +
            " scratches behind " + mouse_possessive +
            " ear with " + mouse_possessive + " hind foot," +
            " all the while keeping an eye on the cheese fuzzie.\n",
            "twitches " + mouse_possessive +
            " whiskers as " + mouse_pronoun + " stealthily" +
            " approaches the cheese fuzzie.\n",
            "scampers across the floor, leaps over the cheese fuzzie," +
            " skids to a halt, and then reverses direction" +
            " back toward the food.\n",
            "creeps up toward the cheese fuzzie, pokes it" +
            " gingerly with " + mouse_possessive + " tusks," +
            " then backs away again.\n"
            })[random(7)]);

        break;

        case 6..7:

        if (present("fuzzie", Mouse))

        {

            tell_room(This_Room,
                QCTNAME(Mouse) + " " +
                ({
                "clutches the cheese fuzzie to " + mouse_possessive +
                " nose, closes " + mouse_possessive +
                " eyes, and inhales deeply.\n",
                "taps the cheese fuzzie with " + mouse_possessive +
                " tusks a few times, perhaps to see" +
                " if it's genuine.\n",
                "nibbles on a few crumbs that have fallen" +
                " from the cheese fuzzie.\n"
                })[random(3)]);

        }

        else

        {

            fuzzie = present("fuzzie", This_Room);
            n = fuzzie->num_heap();

            if (n > 1)

            {

                fuzzie->set_heap_size(n - 1);
                fuzzie = clone_object("/d/Calia/weenware/fuzzie");

            }

            fuzzie->move(Mouse);

            tell_room(This_Room,
                QCTNAME(Mouse) + " " +
                ({
                "snatches the cheese fuzzie in " + mouse_possessive +
                " little front paws, sits up on " + mouse_possessive +
                " haunches, and inspects " + mouse_possessive +
                " prize.\n",
                "dashes to the cheese fuzzie, grabs it, and begins" +
                " to move back toward " + mouse_possessive +
                " hole.\n",
                "races toward the cheese fuzzie and tackles it!\n",
                "pounces on the cheese fuzzie!\n",
                "picks up the cheese fuzzie with " + mouse_possessive +
                " paws and then looks around to see if anyone" +
                " is trying to steal " + mouse_possessive +
                " treasure.\n"
                })[random(5)]);

        }

        break;

        default:

        tell_room(This_Room,
            QCTNAME(Mouse) +
            " scurries back into " + mouse_possessive +
            " hole clutching the cheese fuzzie!\n");

        Mouse->remove_object();

        if (present("fuzzie", This_Room))

        {

            clean_up_fuzzies();

        }

        return;

    }

    /*
     *  This timer should allow the player anywhere from 10-20 seconds to get 
     *  the mouse.    
     */

    set_alarm(5.0, 0.0, mouse_control);

}

// Function:  deploy_mouse()

/*

Purpose:  send a mouse out to look for food.

Arguments:  none

Returns:  nothing

*/

void
deploy_mouse()

{

    /*
     *  Don't deploy more than one mouse at a time.    
     */

    if (objectp(Mouse)) return;

    Mouse = clone_object("/d/Calia/weenware/mouse");
    Mouse_Sequence = 0;
    set_alarm(2.5, 0.0, mouse_control);

}

// Function:  enter_env(inv, from)

/*

Purpose:  used here to set the value of This_Room; called when this object
enters an environment.

Arguments:  none

Returns:  nothing

*/

void
enter_env(object env, object from)

{

    ::enter_env(env, from);
    This_Room = env;

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("hole");
    add_name("mouse hole");
    add_name("small hole");
    set_short("small hole in the wall near the floor");

    set_long("The hole looks as if it has been chewed by a" +
        " small animal rather than cut with a tool.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_M_NO_GET, "If you need a hole, perhaps you could" +
        " ask a Calian Warrior to tear you a new one?\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);

    /*
     *  "uid" settings required for cloning the mouse.    
     */

    setuid();
    seteuid(getuid());

}
