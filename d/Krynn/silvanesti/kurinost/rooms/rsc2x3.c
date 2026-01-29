/*
 * rsc2x3.c
 *
 * Rocky shore climb -  02 x 03
 * Above or below the path on the rocky shore.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit CLIMBBASE;

// G L O B A L   V A R S
object gNest;
int gMaxseagulls = random(2) + 2;
status gNest_here = NESTCHANCE;

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Check for a nest here. If here, then populate with some seagulls
 *  to defend it.
 *
 */
public void
reset_kurinost_room()
{
    int index, ct;

    if (gNest_here && !objectp(gNest))
    {
        gNest = clone_object(RSOBJS + "nest");
        gNest->set_no_show_composite(1);
        gNest->move(TO, 1);
    }

    if (gNest_here)
    {
        ct = sizeof(filter(all_inventory(TO), &->id(GULLNAME)));

        if (ct < gMaxseagulls)
        {
            for (index = ct; index < gMaxseagulls; index++)
            {
                clone_object(RSLIVING + "seagull")->move(TO, 1);
            }
        }

        gNest->reset_nest();
    }
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    set_height_above_ocean("sixtyfive");

    add_vegetation(gNest_here);
    generate_path("up");
    generate_cliffs();
    
    set_short("Steep cliffside");
    set_long(show_me_long_desc);
    
    // Other possible exits:
    set_climb_dirs(({ 0, 1 }),
        ({ "Almost vertical cliffs obscures most of your vision " +
           "straight up, making it impossible to climb that " +
           "direction.\n",
           "rs2x3" }));

    setup_tells();

    reset_room();
}

