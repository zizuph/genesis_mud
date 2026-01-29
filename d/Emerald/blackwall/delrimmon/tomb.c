/*
 *  /d/Emerald/blackwall/delrimmon/tomb.c
 *
 *  This is the burial chamber of the torque wearers who were
 *  slain at the Battle of the Eastern Plains.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <stdproperties.h>

#define TORQUE_DIR      ( "/d/Emerald/torque/unique_torques/" )
#define TORQUES         ({ ("selvic_torque"),\
                           ("vidmin_torque"),\
                           ("locrael_torque"),\
                           ("randil_torque"),\
                           ("islin_torque"),\
                           ("formandil_torque"),\
                        })


/* prototypes */
public void        create_emerald_room();
public void        reset_room();


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("a small stone chamber filled with images of death");
    set_em_long("Here, within the confines of a very small stone"
      + " chamber, you are struck with images of death. Five"
      + " skeletal figures line the walls, each standing dressed"
      + " in full battle armour. Though their faces have decayed"
      + " to mere skulls, each has a dazzlingly beautiful crystal"
      + " torque set upon their brow.\n");
    
    add_prop(ROOM_I_INSIDE, 1); /* it is definitely indoors */
    reset_room();
} /* create_emerald_room */


/*
 * Function name:        reset_room
 * Description  :        add the torques to the chamber
 */
public void
reset_room()
{
    int     i;
    object  torque;

    if (present("torque", this_object()))
    {
        return;
    }

    for (i = 0; i < sizeof(TORQUES); i++)
    {
        if (!present(TORQUES[i], this_object()))
        {
            torque = clone_object(TORQUE_DIR + TORQUES[i]);
            torque->move(this_object());
        }
    }
}
