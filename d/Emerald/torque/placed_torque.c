/*
 *  /d/Emerald/blackwall/delrimmon/obj/torque/placed_torque.c
 *
 *  This is the base for torques which will be placed
 *  throughout Emerald, either on corpses, or in places where
 *  they were set up by Formandil.
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/torque/torque_base";

#include <stdproperties.h>
#include "/d/Emerald/torque/torque.h"

/* prototypes */
public void        create_placed_torque();
public void        create_torque();
public int         query_torque_active(object requesting_torque);


/*
 * Function name:        create_placed_torque
 * Description  :        dummy function for inheriting files
 */
public void
create_placed_torque()
{
} /* create_placed_torque */


/*
 * Function name:        create_torque
 * Description  :        set up the torque
 */
public void
create_torque()
{
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET,
        "The torque is fused in place, and cannot be remove.\n");

    create_placed_torque();
} /* create_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
