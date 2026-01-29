/*
 *  /d/Emerald/torque/unique_torque/raeldu_torque.c
 *
 *  This is the torque bound to Raeldu, who lies dead in the Crystal
 *  Tower under Del Rimmon. Torque location:
 *
 *      /d/Emerald/blackwall/delrimmon/lakeside/caves/tower_entry.c
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
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
    add_name( ({ "_raeldu_torque" }) );
    set_adj(({ "luminous", "fair-stoned", "crystal" }));
    set_short("luminous fair-stoned crystal torque");
} /* create_placed_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
