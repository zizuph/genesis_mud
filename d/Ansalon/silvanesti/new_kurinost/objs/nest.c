/*
 * nest.c
 *
 * A seagull's nest.
 *
 * Copyright (C): Kellon, november 2010
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit "/std/container";

// D E F I N I T I O N S

// G L O B A L   V A R S
int gMaxeggs = random(3) + 1;
status gRetaliate = 1;

// P R O T O T Y P E S

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_container
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the container with basic descriptions and properties.
 *
 */
public void
create_container()
{
    set_name(({ "nest", NESTNAME }));
    set_long("Nestled securely on a tiny ledge, sheltered from " +
        "the worst of winds from the ocean is a nest made from " +
        "entertwined twigs and small branches. Insulated with " +
        "small pieces of bark from a tree and several feathers, " +
        "it seems crude but effective enough for seagulls.\n");

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 1500);
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 1500);
    add_prop(OBJ_M_NO_GET, "Nestled securely amongst the rocks on " +
        "a tiny ledge, the nest would surely break apart if you " +
        "picked it up.\n");
    add_prop(CONT_M_NO_INS, "Appearing quite crudely made, the " +
        "nest will probably not last long if things are dropped " +
        "down into it.\n");

    // We need to be able to clone some eggs from here.
    setuid();
    seteuid(getuid());
}


/*
 *  FUNCTION : leave_inv
 *  Arguments: objects, the item taken and the destination.
 *  Returns  : void
 * 
 *  Called when someone takes something from this container.
 *
 */
public void
leave_inv(object item, object dest_ob)
{
    object *gull;
    int index;

    if (item->id(EGGNAME) && interactive(dest_ob) && gRetaliate)
    {
        // Someone took the egg from a nest!
        gull = filter(all_inventory(E(TO)), &->id(GULLNAME));
        if (sizeof(gull))
        {
            gRetaliate = 0;

            for (index = 0; index < sizeof(gull); index++)
            {
                // Let any gulls attack on 1-2 out of 3.
                if (random(3))
                {
                    gull[index]->retaliate(dest_ob);
                }
            }
        }
    }
}


/*
 *  FUNCTION : reset_nest
 *  Arguments: none
 *  Returns  : void
 * 
 *  Updates the number of eggs inside the nest.
 *
 */
public void
reset_nest()
{
    // The egg is a heap_object. If it is here, there will only be
    // one of it. :)
    object *the_egg = filter(all_inventory(TO), &->id(EGGNAME));
    object new_egg;

    if (sizeof(the_egg))
    {
        the_egg[0]->set_heap_size(gMaxeggs);
    }
    else
    {
        new_egg = clone_object(RSOBJS + "speckled_egg");
        new_egg->set_heap_size(gMaxeggs);
        new_egg->move(TO, 1);
    }

    // Allow gulls to retaliate if someone takes the egg(s).
    gRetaliate = 1;
}

