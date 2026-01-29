/*
 *  /d/Genesis/imbuement/obj/lapidarium.c
 *
 *  Stores stones
 *  This is the part the players carry, most of the functionality is in master
 *  object /d/Genesis/imbuement/lapidiarium_master.c
 *
 *  2010/10/25 Lavellan
 *
*/
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <std.h>
#include "../imbuement.h"
//#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */

/* Global Variables */

/* Prototypes */
public void                 create_object();
public void                 init();
public static int           check(string arg);
public static int           store(string arg);
public static int           extract(string arg);
public string               query_auto_load();
public int                  report(string arg);

/*
 * Function name:        create_object
 * Description  :        set up object basics
 */
public void
create_object()
{
    set_name("lapidarium");
    add_name(LAPID_NAME);
    set_long("This is your lapidarium. It looks rather like a briefcase," +
        " and has many small compartments inside for storing imbuement" +
        " stones.\n" +
        "You could <check> the contents, <store> a stone, or" +
        " <extract> a stone.\n");

    add_prop(OBJ_I_NO_SELL, "You need to keep your lapidarium!\n");
    add_prop(OBJ_I_NO_DROP, "You need to keep your lapidarium!\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(check, "check");
    add_action(store, "store");
    add_action(extract, "extract");
    add_action(report, "imbuement");
    
} /* init */


/*
 * Function name:        check
 * Description  :        let player check contents of lapidarium
 */
public static int
check(string arg)
{
    object tp = this_player();
    string junk;
    //object junk2;
    string player;
    int wiz = member_array(this_interactive()->query_real_name(),
        ALLOWED_WIZARDS) + 1;

    notify_fail("Perhaps you want to <check lapidarium>?\n");

    if (wiz)
        notify_fail("Perhaps you want to <check lapidarium> (<player>)?\n");

    if (!arg)
        return 0;

    if (!parse_command(arg, this_object(),
        "[the] [contents] [of] [my] [the] 'lapidarium' [contents] %s",
        player))
        return 0;

    if (wiz && (player != ""))
    {
        write("Checking lapidarium of player " + player + "\n");
        write(LAPID_MASTER->check(player));
    }
    else
    {
        write("You open your lapidarium to inspect the contents.\n");
        write(LAPID_MASTER->check(tp->query_real_name()));
        tell_room(environment(tp), QCTNAME(tp) + " checks the contents of " +
            tp->query_possessive() + " lapidarium.\n", tp);
    }
    return 1;
} /* check */

/*
 * Function name:        store
 * Description  :        let player store a stone in the lapidarium
 */
public static int
store(string arg)
{
    object *obs, ob, tp = this_player();
    
    notify_fail("What did you want to store?\n");
    if (!arg)
        return 0;
    
    if (!(obs = PARSE_COMMAND(arg, this_player(), 
        "[the] %i [in] [the] [my] [lapidarium]")))
        return 0;

    notify_fail("No, you can't store that in the lapidarium. It is only for" +
        " stones that are used in the enchanting arts.\n");

    obs = filter(obs, &call_other( , "id", STONE_NAME));
    if (!sizeof(obs))
        return 0;

    write("You store " + COMPOSITE_DEAD(obs) + " in your lapidarium.\n");
    tell_room(environment(tp), QCTNAME(tp) + " stores " + COMPOSITE_DEAD(obs) +
        " in " + tp->query_possessive() + " lapidarium.\n", tp);

    foreach(object ob: obs)
    {
        if (LAPID_MASTER->store(this_player(), ob))
        {
            ob->remove_object();
        }
        else
        {
            write("There is something wrong with your lapidarium. The " +
                ob-short() + " fell out again!\n");
        }
    }

    return 1;
} /* store */


/*
 * Function name:        extract
 * Description  :        let player retrieve a stone from the lapidarium
 */
public static int
extract(string arg)
{
    notify_fail("What did you want to extract?\n");
    if (!arg)
        return 0;

    write(LAPID_MASTER->extract(this_player(), arg) + "\n");

    return 1;
} /* extract */


/*
 * Function name:        query_auto_load
 * Description  :        Players shouldn't lose this
 */
public string
query_auto_load()
{
    /* Replace with the one in the AoD dir. */
    return "/d/Genesis/ateam/aod/imbuement/obj/lapidarium";
} /* query_auto_load */

/*
 * Function name: report
 * Description:   Allow players to report bugs etc.
 */
public int
report(string arg)
{
    IMBUE_LOGGER->report(arg);
    return 1;
} /* report */
