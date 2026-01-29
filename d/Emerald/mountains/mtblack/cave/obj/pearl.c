/* A fake pearl - Coded 30/04/96 by Tulix III.       */
/* This object may be obsolete when Immortal opens. */

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Emerald/tulix/t_defs.h"
#include "/d/Emerald/mountains/mtblack/cave/pearl_defs.h"

#pragma strict_types

/* Prototype functions */
public void check_immortal_status();


public void
create_object()
{
    set_name("pearl");
    set_pname("pearls");
    set_adj("fake");

    set_short("fake pearl");
    set_pshort("fake pearls");
    set_long("A careful look at the pearl reveals that it is in fact " +
        "a fake!\nDespite this, you get the feeling that one day it might " +
        "prove useful.\nThat day is probably not today, however...\n");

    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_M_NO_DROP, "You decide it may be useful one day...\n");
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_M_NO_SELL, "But surely the pearl is a worthless fake...\n");

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The pearl is a fake.\n", 0,
        "The pearl is a fake at the moment.\n", 20,
        "The pearl will one day transform into something else.\n", 40,
        "The pearl will one day transform into a real pearl!\n", 80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This pearl will one day turn into a real "
        + "pearl, needed for a quest.\n"
        + "Ask Tulix for more details.\n");

    set_alarm( 60.0, 0.0, check_immortal_status );
}

/*
 * Function name:   check_immortal_status
 * Description:     Replace the pearl when the immortal domain opens
 */
public void
check_immortal_status()
{
    object real_pearl, player;
    
    player = ENV(TO);

    if (!interactive(player))
    {
        /* This shouldn't happen, but what the hell. */
        TO->remove_object();
        return;
    }

    /* Here we check to see if the immortal domain has opened yet. */
    if (IMMORTAL_OPEN)
    {
        setuid();
        seteuid(getuid());

        real_pearl = clone_object(REAL_PEARL);
        if (objectp(real_pearl))
        {
            player->catch_msg("Your fake pearl suddenly explodes with " +
                "a loud BANG!!\n");
            tell_room(ENV(player), "Something carried by " + QTNAME(player) +
                " suddenly explodes with a loud BANG!!\n", player);

            player->catch_msg("When the smoke clears, you notice that the " +
                "outer layer of the pearl has broken away, revealing " +
                "a genuine pearl!\n");

            real_pearl->move(player);
            TO->remove_object();
        }
        else
        {
            player->catch_msg("Your fake pearl sudders slightly, but " +
                "nothing really happens.\n");
        }
    }
}

/*
 * Function name:   query_auto_load
 * Description:     make this object auto-loading
 * Returns:         string: the filepath of this object
 */
public string
query_auto_load()
{
    return MASTER;
}

