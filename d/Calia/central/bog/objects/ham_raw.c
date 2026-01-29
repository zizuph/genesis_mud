// OBJECT:  ham_raw

    /* Calia Domain

    HISTORY

    [99-07-03] Created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OBJECTS\HAM_RAW.DOC].

    PURPOSE

    A large whole smoked salt-and-sugar-cured ham [author drools slightly then
    continues writing] found in the Sanctimonian fortress.  It begins its
    existence hanging in the smokehouse room and is not edible.  If it is
    removed from the smokehouse and cooked, it turns into the ham_cooked object
    which can be eaten. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>

// GLOBAL VARIABLES

int Fully_Cured = random(2);

// OBJECT DEFINITION

void
create_object()

{

    int weight = random(5000) + 5000;

    /*
     *  DESCRIPTION    
     */

    set_short("large smoked ham hanging from the ceiling");
    set_pshort("large smoked hams hanging from the ceiling");
    set_name("ham");
    add_name("smoked ham");
    add_name("large smoked ham");
    add_name("large ham");

    set_long("The ham looks to be well coated with salt" +
        " that sparkles even under the " +
        ({"pale", "deep"})[Fully_Cured] +
        " brown patina bestowed by fragrant smoke upon the outer" +
        " layer of fat. It hangs from the ceiling suspended by" +
        " a heavy wire loop.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, weight + 500 + random(500));
    add_prop(OBJ_I_VALUE, (weight / 10) + (Fully_Cured * 50));

    add_prop(OBJ_M_NO_GET, "The ham is firmly attached to the ceiling" +
        " by a wire loop.\n");

    add_prop(OBJ_M_NO_SELL, "The merchant derides your attempt to" +
        " sell the ham: 'who knows where it's been and what you've" +
        " been doing with it?'\n");

    /*
     *  ITEMS    
     */

    add_item(({"patina", "brown patina", "fat", "layer of fat"}),
        ({"The ham seems well on its way to becoming thoroughly" +
        " cured, but it's not quite ready for eating yet.\n",
        "The dry, crumbly texture with just a hint of mold tells" +
        " you that this is a fully cured and smoked ham, ready to" +
        " be cooked and served.\n"})[Fully_Cured]);

    add_item(({"loop", "wire", "wire loop", "heavy wire loop"}),
        "The wire loops through the ham and around the" +
        " ceiling, and you don't see any way to unfasten" +
        " the wire or remove the ham. It looks as if the ham" +
        " is intended to hang here undisturbed until someone" +
        " thinks it's ready to be cut down.\n");

    add_item(({"salt", "surface"}),
        "Coarse salt covers the surface of the ham, adhering to" +
        " the outer layer of fat and browned to a deep amber" +
        " tone from being smoked.\n");

}

// FUNCTIONS

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("Mmmmmm... not only does the ham have an" +
        " appealing smoky aroma, but you detect that it" +
        " is cured with sugar - perhaps even maple sugar -" +
        " as well as salt.\n");

}

// Function:  eat_me(ham)

/*

Purpose:  supply a message if someone tries to eat this ham. It's not a
standard food item, so there's no default function for this.

Arguments:  string indicating this ham

Returns:  0/1

*/

int
eat_me(string ham)

{

    object tp = this_player();
    object target;

    if (!stringp(ham)) /* Player did not specify what to eat. */

    {

        notify_fail("Eat what?\n");
        return 0;

    }

    if (parse_command(ham, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        write(({"This ham isn't ready to eat, and it won't be" +
            " for a long time!\n",
            "This ham is fully cured but it still must be cooked" +
            " before you can eat it.\n"})[Fully_Cured]);

        return 1;

    }

    return 0;

}

// Function:  cut_me_down(with_what)

/*

Purpose:  cut the ham down from the ceiling.  You need a pretty good bladed
weapon to do this (W_SLASH damage type).

Arguments:  string containing "ham [down] with" (or "[down] ham with") and the
weapon used.

Returns:  1/0.

*/

int
cut_me_down(string with_what)

{

    object tp = this_player();
    object ham;
    object weapon;

    /*
     *  Once the ham is cut down from where it is hanging, OBJ_M_NO_GET is 
     *  removed and this function no longer has any use.    
     */

    if (!query_prop(OBJ_M_NO_GET)) return 0;

    /*
     *  The combination of functions to generate the inventory is redundant, 
     *  but it ensures that any wielded weapon will be chosen before any
     *  unwielded one.    
     */

    if (parse_command(with_what,
        tp->query_weapon(-1) +
        all_inventory(tp) +
        all_inventory(environment(this_object())),
        " [down] %o [down] 'with' %o ", ham, weapon))

    {

        /*
         *  First, the weapon has to have a cutting edge.    
         */

        if (weapon->query_dt() & W_SLASH)

        {

            /*
             *  Next, the player must be wielding it in order to use it.    
             */

            if (weapon->query_wielded())

            {

                /*
                 *  Then we check the player's height and the size of his 
                 *  weapon, which unfortunately is available only in terms of
                 *  volume, to see if he can reach the ham.    
                 */

                if (((tp->query_prop(CONT_I_HEIGHT) * 10) +
                    weapon->query_prop(OBJ_I_VOLUME)) < 4000)

                {

                    say(QCTNAME(tp) + " tries to cut a ham down from" +
                        " the ceiling with " +
                        LANG_ADDART(weapon->short()) +
                        " but can't quite reach high enough.\n");

                    write("The ham is too far over your head for" +
                        " you to reach it with the " + weapon->short() +
                        ".\n");

                }

                else

                {

                    /*
                     *  Finally, we check whether the weapon is sharp enough, 
                     *  both in original design and current condition, to cut
                     *  through the wire.    
                     */

                    if (weapon->query_pen() > 15 && weapon->query_dull() < 15)

                    {

                        say(QCTNAME(tp) + " cuts a ham down from" +
                            " the ceiling with " +
                            LANG_ADDART(weapon->short()) + ".\n");

                        write("You cut a ham down from the ceiling with" +
                            " the " + weapon->short() + ".\n");

                        set_long("The ham looks to be well coated" +
                            " with salt that sparkles even under the " +
                            ({"pale", "deep"})[Fully_Cured] +
                            " brown patina bestowed by fragrant" +
                            " smoke upon the outer layer of fat.\n");

                        set_short("large smoked ham");
                        set_pshort("large smoked hams");
                        remove_prop(OBJ_M_NO_GET);
                        remove_item("loop");
                        remove_item(""wire");
                        remove_item("wire loop");
                        remove_item("heavy wire loop");

                        /*
                         *  Zero return code from move indicates success; 
                         *  nonzero indicates failure due to excessive weight,
                         *  volume, etc. for player.    
                         */

                        if (!move(tp))

                        {

                            write("You catch the ham as it falls" +
                                " from the ceiling.\n");

                            tell_room(environment(tp),
                                QCTNAME(tp) + "catches the ham" +
                                " as it falls from the ceiling.\n",
                                ({tp}));

                        }

                        else

                        {

                            /*
                             * Player can't hold ham and thus gains new insight 
                             *  into the meaning of life.   
                             */

                            tell_room(environment(),
                                "The " + short() + " falls to the" +
                                " ground with a resounding 'thud,'" +
                                " like the sound of " +
                                ({"a tree falling alone in the forest",
                                "one giant hand clapping"})[Fully_Cured] +
                                ".\n");

                        }

                    }

                    else

                    {

                        say(QCTNAME(tp) + " tries to cut a ham" +
                            " down from the ceiling with" +
                            " " + LANG_ADDART(weapon) + ", but it" +
                            " fails to cut through the wire.\n");

                        write("You try to cut a ham down from the" +
                            " ceiling with the " + weapon->short() +
                            ", but it fails to cut through the wire.\n");

                    }

                }

            }

            else

            {

                write("You must be wielding it to cut with it.\n");

            }

        }

        else

        {

            write("The " + weapon->short() + " is" +
                " an unsuitable tool for cutting. Perhaps" +
                " something with a sharp blade would" +
                " do the trick.\n");

        }

        return 1;

    }

    else

    {

        notify_fail("Cut what down with what?\n");
        return 0;

    }

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
    add_action(eat_me, "eat");

    /*
     *  This function is only relevant when the ham is still hanging from the 
     *  ceiling.    
     */

    if (query_prop(OBJ_M_NO_GET))

    {

        add_action(cut_me_down, "cut");

    }

}
