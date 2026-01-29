/*
 *  /d/Gondor/guilds/rangers/ithilien/entrance.c
 *
 * Modifications:
 * 20-Jul-2001,Alto: more tidy up, change inheritance for new
 *                   rangers.
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_ITH_DIR + "ith_funcs.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "exit.c"

#define RANGER_WAS_STEALTHY "_ranger_was_stealthy"
#define RANGER_WAS_MASKED   "_ranger_was_masked"

object ranger;

/* Prototypes */
public int   start_stealth();
public int   stop_stealth();

public void
create_gondor()
{
    set_short("under the bushes");
    set_long("You are standing at the top of a steep set of steps, "
        + "your head just bowed under a green roof of leaves. A little "
        + "light gets through from the outside, but enough for you to "
        + "see the stairs descending into a gloomy passage with stone "
        + "walls. You can step out of the bushes here. The sound of a "
        + "rushing stream comes from the north of here.\n"); 
    add_item("bushes", "The bushes growing here are covering this "
        + "hidden stair from unwanted visitors. You may step out "
        + "from them to the riverbank.\n");
    add_item("roof","The green leaf-roof is made of the bushes growing "
        + "here.\n");
    add_item(({"stairs", "steps"}), "The stone steps are carved into the "
        + "hill, leading down to a hidden path. The steps themselves "
        + "are smooth, but hidden from view by the bushes all around.\n");
    add_item("passage", "The passage leads west into darkness.\n");
    add_exit(RANGERS_ITH_DIR + "passage6", "down", &stop_stealth());
    add_exit(ITH_DIR + "nforest/fpath/bushes5", "out", &start_stealth());
    add_prop(ROOM_M_NO_SCRY, 1);
    restore_allowed();
}

public int
start_stealth()
{

    int result = 0;
    object tp = this_player();
    object mcloak = present("_mottled_cloak_", tp);


    if (tp->query_prop("_ranger_i_wearing_cloak") && 
        !tp->query_prop("_rangers_incognito"))
        tp->command("$hood myself");
    if (objectp(mcloak) && objectp(mcloak->query_worn()) 
       && tp->query_prop(RANGER_WAS_MASKED))
    {
        tp->remove_prop(RANGER_WAS_MASKED);
        tp->command("$mask myself");
        tp->command("$pin cloak");
    }

    if (tp->query_prop(RANGER_WAS_STEALTHY))
    {
        tp->remove_prop(RANGER_WAS_STEALTHY);

        if (tp->query_autosneak() || sizeof(TP->query_team()))
            return result;

        tp->set_autosneak(1);
        write("You prepare to move stealthily again as you were "
            + "when you entered Henneth Annun.\n");
    }
    return 0;
    //if people find there way here, allow them to leave
}

public int
stop_stealth()
{
    int result = check_ranger();
    object tp = this_player();
    if (tp->query_prop("_rangers_mask_closed"))
    {
        tp->add_prop(RANGER_WAS_MASKED, 1);
        tp->command("$unpin cloak");
        tp->command("$unmask me");
    }


    if (tp->query_autosneak())
    {
        tp->set_autosneak(0);
        write("You stop being stealthy as you enter the passage "
            + "to Henneth Annun.\n");
        tp->add_prop(RANGER_WAS_STEALTHY, 1);
    }

    return result;
}

