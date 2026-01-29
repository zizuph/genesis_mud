/*
 *  /d/Emerald/torque/unique_torques/plains_torque.c
 *
 *  This is the torque bound to an area atop the cliffs
 *  which overlook the Western Plains of Emerald, where
 *  the Torque wearers perished in the great battle
 *  there. Clone to:
 *
 *    /d/Emerald/blackwall/delrimmon/western_plains_lookout.c
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
    add_name( ({ "_plains_torque" }) );
    set_adj(({ "pulsing", "murky-stoned", "silver" }));
    set_short("pulsing murky-stoned silver torque");
} /* create_placed_torque */


public int
query_torque_active(object requesting_torque)
{
    return 1;
} /* query_torque_active */
