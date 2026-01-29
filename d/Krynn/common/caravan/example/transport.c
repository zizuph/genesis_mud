/* 
 *      /d/Gondor/minas/rooms/transport.c
 *
 *      The transport-office of Minas Tirith, where the 
 *      carriage is cloned and loaded into the game. 
 *
 *      By Elessar for Genesis, March '92.
 *
 *      Modification log:
 *      28-Jan-1997, Olorin:    Recoded.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

private void   wagon_reset();

static object  Wagon;

public void
create_gondor()
{
    set_short("the transport stable of Minas Tirith");
    set_long(BSN("This is the stable from where the horse "
      + "carriages are prepared for their tours. The "
      + "carriages accept passengers for a modest fee."));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(MINAS_DIR + "e3crc1", "east", 0, 0);
    wagon_reset(); 
}

public void
start_wagon()
{
    if (!objectp(Wagon) || !objectp(present(Wagon, TO)))
        return;

    tell_room(TO, "The driver attaches two horses to the carriage.\n"
              +   "Then he drives the wagon out into the street.\n");
    Wagon->set_horses(2);
    Wagon->move(MINAS_DIR + "e3crc1");
    Wagon->start(20.0);
}

private void
wagon_reset()
{
    Wagon = clone_object(MINAS_DIR + "obj/mtwagon");
    Wagon->move(TO);
    Wagon->set_leavable(1);

    set_alarm(10.0, 0.0, start_wagon);
}

public void
reset_room()
{
    if (!objectp(Wagon)) 
        wagon_reset();
}
EOF
