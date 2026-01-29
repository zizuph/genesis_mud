inherit "/std/object";
inherit "/d/Emerald/blackwall/delrimmon/visions.c";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("medalion");
    add_name("_vamp_trance_medalion");
    add_adj( ({ "bloody", "blood", "soaked", "blood-soaked" }) );

    set_short("blood-soaked medalion");
    set_long("Staring at this medalion, you are struck by confusion."
      + " Tracing its blood-soaked lines with your fingertips, a"
      + " knowledge you cannot fathom streams into your emotions."
      + " Your Vampire flesh remembers things you have never"
      + " known or experienced. Sire upon Grandsire, the feelings"
      + " from your unknown legacy continue to mount until you are"
      + " filled with a clear understanding of purpose. You must"
      + " immediately find a place ... a hidden place ... a place"
      + " where no one will find you. Then, alone and safe, you"
      + " must <incant valshemai>.\n");

    add_prop(OBJ_M_NO_DROP,
        "Deep within you, you know you cannot drop this precious"
      + " link to your soul.\n");
    add_prop(OBJ_M_NO_GIVE,
        "You know that you must never part with this precious"
      + "object.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_SELL,
        "You sense such a connection with the Medalion. You could"
      + " never bring yourself to sell it.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 10);
} /* create_object */


/*
 * Function name:        do_incant
 * Description  :        allow players to incant the spell
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - otherwise
 */
public int
do_incant(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Incant what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "'valshemai' / 'valshemai!'"))
    {
        write("You incant: " + arg + "\n");
        return 1;
    }

    write("You incant: " + capitalize(arg) + "!\n");

    enter_trance(this_player(), VAMP_VISION,
        "blood-soaked medalion");

    return 1;
} /* do_incant */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_incant, "incant");
} /* init */  
