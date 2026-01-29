/*
 *  /d/Emerald/torque/unique_torques/rath_torque.c
 *
 *  This is the torque bound to the top of Melan Rath.
 *
 *      /d/Emerald/blackwall/delrimmon/lakeside/cliffs/rath_summit.c
 *
 *  Copyright (c) May 2002, by Cooper Sherry (Gorboth)
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
    add_name( ({ "_rath_torque" }) );
    set_adj(({ "glittering", "red-stoned", "crystal" }));
    set_short("glittering red-stoned crystal torque");
} /* create_placed_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
