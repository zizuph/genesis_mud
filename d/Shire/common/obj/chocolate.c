#pragma strict_types

inherit "/std/object.c";

#include <cmdparse.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* prototypes */
public void    create_object();
public void    init();
public int     do_dip(string arg);


/* definitions */
#define    CHOCOLATE_PROP        "_shire_i_chocolate_coated"

/*
 * Function name:
 * Description  :    set up the object
 */
public void
create_object()
{
    set_name("pot");
    add_name("pot of chocolate");
    add_adj( ({ "large", "steaming", "chocolate" }) );

    set_short("large steaming pot of melted chocolate");
    set_long(BSN(
        "The smell which rises from this steaming pot of melted"
      + " chocolate is absolutely heavenly. If you have food,"
      + " you can 'dip' it in the pot to add a coating of"
      + " chocolate."));

    add_item( ({ "chocolate", "melted chocolate" }), BSN(
        "There is a great deal of melted chocolate in the pot."
      + " It is useful for dipping other foods in, to make them"
      + " taste even better."));

    add_prop(OBJ_I_WEIGHT, 2000);
} /* create_object */


/*
 * Function name:    init
 * Description  :    add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(do_dip, "dip");
} /* init */


/*
 * Function name:    do_dip
 * Description  :    allow the player to 'dip' food in the pot, and
 *                   have it become chocolate-coated
 * Arguments    :    string arg - what the player typed
 * Returns      :    1 - success, 0 - failure
 */
public int
do_dip(string arg)
{
    object   target;
    string   original_name;

    if (!strlen(arg))
    {
        NFN0("What do you wish to dip?");
    }

    if (!parse_command(arg, all_inventory(TP),
        "[the] %o [in] [the] [pot] [of] [chocolate]", target))
    {
        return 0;
    }

    if (IS_FOOD_OBJECT(target) || IS_HERB_OBJECT(target))
    {
        if (target->query_prop(CHOCOLATE_PROP))
        {
            NFN0("That has already been dipped in chocolate,"
              + " and does not need another coat.");
        }

        WRITE("You dip the " + target->short() + " in the pot,"
          + " coating it with delicious chocolate!");

        original_name = target->short();
        target->set_short(target->short() + " coated in chocolate");
        target->set_long(target->long() + "It is coated with"
          + " delicious chocolate!\n");
        target->set_adj("chocolate-coated");

        target->add_item( ({ "chocolate", "delicious chocolate" }), BSN(
            "A delicious chocolate coating has been added to this "
          + original_name + ", almost certainly making it yummier!"));

        target->add_prop(CHOCOLATE_PROP, 1);

        return 1;
    }

    NFN0("You decide that dipping anything inedible would "+
         "be a terrible waste of chocolate!");
} /* do_dip */
