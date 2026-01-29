// ARMOUR:  dancing_shoes

    /* Calia Domain

    HISTORY

    [96-03-05] Created by Uhclem from [C:\CALIA\GELAN\ARMOURS\DANCING_.DOC]
    based on Maniac's example.

    PURPOSE

    These shoes provide a variety of dancing emotes to the wearer.  To use
    them, the player uses a command in the form "<dance> <partner>" where
    <dance> is one of the dances available and <partner> is any living object
    in the same environment.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "armours.h"

#define DANCING_CMDSOUL "/d/Calia/gelan/specials/dancing_cmdsoul.c"

// FUNCTIONS

// Function:  wear

/*

Purpose:  Adds cmdsoul to player when shoes are worn.

Arguments:  object (these shoes).

Returns:  0 so that standard wear routine will be subsequently invoked.

*/

mixed
wear(object what)

    {

    object tp = this_player();
    tp->add_cmdsoul(DANCING_CMDSOUL);
    tp->update_hooks();
    return 0;

    }

// Function:  remove

/*

Purpose:  Removes cmdsoul from player when shoes are removed.

Arguments:  object (these shoes).

Returns:  0 so that standard remove routine will be subsequently invoked.

*/

mixed
remove(object what)

    {

    object tp = environment(this_object());

    if(living(tp))

        {

        tp->remove_cmdsoul(DANCING_CMDSOUL);
        tp->update_hooks();

        }

    return 0;

    }

// ARMOUR DEFINITION

void
create_armour()

    {

    /*  DESCRIPTION  */

    set_name("shoes");
    add_name("gelan_dancing_shoes");
    set_adj(("dancing"));
    set_short("pair of dancing shoes");
    set_pshort("pairs of dancing shoes");

    set_long("These shoes are polished shiny black and" +
        " have smooth leather soles.  If you've ever felt" +
        " you needed 'help dancing', you've got it when" +
        " you wear these!\n");

    /*  PROPERTIES  */

    set_ac(1);
    set_at(A_FEET);
    set_af(this_object());
    set_am(({ 0, 0, 0 }));
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    seteuid(getuid());

    add_prop(OBJ_S_WIZINFO, "These dancing shoes are sold in Gelan.  " +
        "When worn they give the player a variety of dancing emotes.\n");

    /*  ITEMS  */

    add_item(({"sole", "soles", "leather soles", "smooth leather soles",
        "leather sole", "smooth leather sole"}),
        "On the bottom of each" +
        " shoe is stamped:  Caution -" +
        " repeated use of these shoes may make you a" +
        " very passionate dancer.  Use them only with partners" +
        " with whom you are romantically involved" +
        " (or would like to be)!\n");

    }
