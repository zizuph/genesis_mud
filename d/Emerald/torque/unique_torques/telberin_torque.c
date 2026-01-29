/*
 *  /d/Emerald/torque/unique_torques/telberin_torque.c
 *
 *  This is the torque bound to the top of the Royal Palace in
 *  Telberin.
 *
 *      /d/Emerald/telberin/telberin_lookout.c
 *
 *  Copyright (c) June 2003, by Cooper Sherry (Gorboth)
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
    add_name( ({ "_telberin_torque" }) );
    set_adj(({ "glittering", "light-catching", "diamond" }));
    set_short("glittering light-catching diamond torque");
} /* create_placed_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
