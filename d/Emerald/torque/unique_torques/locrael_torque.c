/*
 *  /d/Emerald/torque/unique_torque/locrael_torque.c
 *
 *  This is the torque bound to Locrael, who lies buried in the
 *  hills of Del Rimmon in Emerald.
 *
 *      /d/Emerald/blackwall/delrimmon/tomb.c
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Emerald/torque/placed_torque";


/* prototypes */
public void        create_placed_torque();
public int         query_torque_active(object requesting_torque);


/*
 * Function name:        create_placed_torque
 * Description  :        set up the torque
 */
public void
create_placed_torque()
{
    set_name("torque");
    set_adj(({ "shimmering", "multi-stoned", "crystal" }));
    set_short("shimmering multi-stoned crystal torque");
} /* create_placed_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
