/*
 *  /d/Emerald/common/guild/aod/obj/boulder_fragment.c
 *
 *  These are the debris that can be generated when a boulder is busted
 *  by an Ogre.
 *
 *  Created June 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>

/* Definitions */
#define        FRAGMENT_SHORTS  ({ "chipped stone shard",     \
                                   "broken stone fragment",   \
                                   "broken piece of rock",    \
                                   "shattered boulder chunk", \
                                   "piece of broken rock"  })

/* Prototypes */
public void        create_object();


/*
 * Function name:        create_object
 * Description  :        set up the item
 */
public void
create_object()
{
    set_short(one_of_list(FRAGMENT_SHORTS));

    switch (short())
    {
        case "chipped stone shard":
            set_name("shard");
            add_adj( ({ "chipped", "stone" }) );
            set_long("This shard is a long chipped piece of stone"
              + " that looks to have shattered off of some larger"
              + " rock.\n");
            break;
        case "broken stone fragment":
            set_name("fragment");
            add_adj( ({ "broken", "stone" }) );
            set_long("This fragment has clearly been broken from"
              + " a larger piece of rock recently.\n");
            break;
        case "broken piece of rock":
            set_name("piece");
            add_name("rock");
            add_adj( ({ "broken", "piece", "of" }) );
            set_long("This rock is jagged and rough, looking to have"
              + " recently broken away from a larger mass of stone.\n");
            break;
        case "shattered boulder chunk":
            set_name("chunk");
            add_adj( ({ "shattered", "boulder" }) );
            set_long("It looks as if someone has taken a boulder and"
              + " cracked it into pieces, this being one of them!\n");
            break;
        case "piece of broken rock":
            set_name("piece");
            add_name("rock");
            add_adj( ({ "broken", "of" }) );
            set_long("Some incredible force must have shattered this"
              + " piece off of a large boulder recently.\n");
            break;
    }

    add_prop(OBJ_I_WEIGHT, 100 + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
} /* create_object */