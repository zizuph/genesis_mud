// FOOD:  ham_cooked

    /* Calia Domain

    HISTORY

    [02-09-23] Created by Uhclem from
    [C:\CALIA\CENTRAL\BOG\OBJECTS\HAM_COOK.DOC].

    PURPOSE

    A large glazed ham ready for eating, anywhere from 5 to 10 kilos, whole if
    you have a truly monstrous appetite or sliced if you don't.  Slicing
    requires a good sharp knife and a bit of skill. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>
#include "defs.h"

// OBJECT DEFINITION

void
create_food()

{

    int weight = random(5000) + 5000;

    /*
     *  DESCRIPTION    
     */

    set_short("large glazed ham");
    set_name("ham");
    add_name("glazed ham");
    add_name("large glazed ham");
    add_name("large ham");

    set_long("The ham glistens with sweet, glistening" +
        " glaze studded with cloves. It's large enough to provide" +
        " a feast for one truly titanic appetite, or it can" +
        " be sliced for sharing with a large number of diners.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, weight + 500 + random(500));
    add_prop(OBJ_I_VALUE, (weight / 7));
    set_amount(weight);
    set_heap_size(1);

    add_prop(OBJ_M_NO_SELL, "No merchant would buy a fully-cooked" +
        " ham that may sit on his shelf for days - it" +
        " should be eaten immediately!\n");

    /*
     *  ITEMS    
     */

    add_item(({"glaze", "glistening glaze", "cloves", "clove"}),
        "The glaze covers the outside of the ham and is" +
        " studded liberally with cloves.\n");

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

}

// FUNCTIONS

// Function:  special_effect(num)

/*

Purpose:  add taste characteristics to this object.

Arguments:  int num, number of items eaten.

Returns:  nothing.

*/

void
special_effect(int num)

{

    /*
     *  The flavors are inspired by a maple and bourbon glazed ham prepared in 
     *  a Washington area shop, Sutton Place Gourmet.  Those of you on the
     *  other side of the pond can find worthy competitors in the Selfridge
     *  food hall, London.    
     */

    write(({"The promise of the fragrance is fulfilled in the" +
        " taste! The meat is tender and marbled," +
        " and its delicate natural flavor is enhanced by" +
        " the contrasting maple and whiskey flavors" +
        " in the glaze.\n",
        "First the startling flavor of the glaze hits" +
        " your tongue, an unexpected pairing of sweet maple" +
        " sugar and well-aged whiskey, but it complements" +
        " the natural delicate taste of the meat and" +
        " leaves a lingering, agreeable aftertaste.\n",
        "Tastes of delicate salt-cured ham, sweet maple" +
        " sugar, and robust oak-aged whiskey fill your mouth all" +
        " at once, a tumult of flavors that quickly merge" +
        " into a mellow, satisfying union that lingers after" +
        " the ham is consumed.\n"})[random(3)]);

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The aroma of the ham is tantalizing indeed," +
        " mixing the distinctive fragrances of sweet maple" +
        " sugar and spicy clove with traces of" +
        " mustard and whiskey.\n");

}

// Function:  slice_me(with_what)

/*

Purpose:  slice the ham; this is an all-or-nothing deal; either you turn the
whole ham into nice uniform slices or you don't slice it at all.

Arguments:  string containing "ham with" and the weapon used.

Returns:  1/0.

*/

int
slice_me(string with_what)

{

    object tp = this_player();
    object ham;
    object weapon;
    object slices;
    int num_slices;
    int new_weight;

    /*
     *  The combination of functions to generate the inventory is redundant, 
     *  but it ensures that any wielded weapon will be chosen before any
     *  unwielded one.    
     */

    if (parse_command(with_what,
        tp->query_weapon(-1) +
        all_inventory(tp) +
        all_inventory(environment(this_object())),
        " %o 'with' %o ", ham, weapon))

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
                 *  Then check to see if the weapon is a knife.    
                 */

                if (weapon->query_wt() != W_KNIFE)

                {

                    say(QCTNAME(tp) + " takes a whack at the " + short() +
                        " with " + LANG_ADDART(weapon->short()) +
                        " but can't manage to slice it with" +
                        " such a clumsy tool.\n");

                    write("The " + weapon->short() + " is too clumsy" +
                        " a tool for slicing fine ham.\n");

                }

                else

                {

                    /*
                     *  Then we check whether the weapon is sharp enough, both 
                     *  in original design and current condition, to slice the
                     *  ham.    
                     */

                    if (weapon->query_pen() > 10 && weapon->query_dull() < 10)

                    {

                        /*
                         *  Finally, we check to see if the player has 
                         *  sufficient stats and skills to slice a ham.    
                         */

                        if ((tp->query_stat(SS_DEX) / 10) +
                            tp->query_skill(W_KNIFE) > 20)

                        {

                            say(QCTNAME(tp) + " slices the " + short() +
                                " into many thin, uniform slices with " +
                                LANG_ADDART(weapon->short()) + ".\n");

                            write("You slice the ham into many" +
                                " thin, uniform slices with" +
                                " your " + weapon->short() + ".\n");

                            num_slices =
                                query_prop(OBJ_I_WEIGHT) / (random(50) + 175);

                            new_weight =
                                query_prop(OBJ_I_WEIGHT) / num_slices;

                            slices = clone_object(BOG_OBJECTS + "ham_sliced");

                            slices->add_prop(OBJ_I_WEIGHT, new_weight);
                            slices->add_prop(OBJ_I_VALUE, (new_weight / 7));
                            slices->add_prop(OBJ_I_VOLUME, new_weight - 10);
                            slices->set_amount(new_weight);
                            slices->set_heap_size(num_slices);

                            slices->move(environment(this_object()));

                            remove_object();

                        }

                        else

                        {

                            say(QCTNAME(tp) + " tries vainly to slice" +
                                " the " + short() + " with " +
                                LANG_ADDART(weapon->short()) +
                                " but doesn't even manage to make" +
                                " a scratch on its surface.\n");

                            write("You fumble with" +
                                " the " + weapon->short() +
                                " and attempt to slice the " + short() +
                                ", but your meager skill with a" +
                                " knife is simply inadequate" +
                                " for the task.\n");

                        }

                    }

                    else

                    {

                        say(QCTNAME(tp) +
                            " tries to slice the " + short() +
                            " with " + LANG_ADDART(weapon->short()) +
                            ", but it's too dull to cut a proper slice.\n");

                        write("You try to slice the " + short() +
                            " with the " + weapon->short() +
                            ", but it's too dull to cut a proper slice.\n");

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
                " an unsuitable tool for slicing. Perhaps" +
                " something with a sharp blade would" +
                " do the trick.\n");

        }

        return 1;

    }

    else

    {

        notify_fail("Slice what with what?\n");
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
    add_action(slice_me, "slice");

}
