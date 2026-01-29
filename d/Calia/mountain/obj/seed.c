// OBJECT:  seed

    /* Calia Domain

    HISTORY

    [96-02-17] Created by Uhclem from [C:\CALIA\MOUNTAIN\OBJ\SEED.DOC].

    PURPOSE

    This seed is a quest item found in the Calia palace gardens.  It appears on
    the ground whenever someone feeds the fish in the pond.  Planting it is a
    key element of the quest.  The player who takes it may not drop it or give
    it to anyone else, but it is only useful (for quest purposes) to the player
    who fed the fish.  Acquiring this seed is not a difficult task, so no
    provision is made for recovery.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "obj.h"
#include GARDEN_QUEST

// OBJECT DEFINITION

void
create_object()

    {

    /*  DESCRIPTION  */

    set_name("seed");
    set_short("shiny seed");
    set_adj("shiny");

    set_long("This seed looks rare and valuable.  " +
        "You feel that it deserves special care.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_M_NO_DROP, "You feel a personal sense of " +
        "responsibility for the welfare of the seed " +
        "and decide to keep it.\n");

    add_prop(GARDEN_QUEST_SEED, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 2);

    }
