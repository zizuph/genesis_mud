/*
 *  /d/Emerald/north_shore/outpost/outpost06.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;


/*
 * Function name:    create_outpost_inside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_inside_room()
{
    set_short("in an armoury in the central complex of the outpost");
    set_em_long("This room appears to serve the dual purpose of being"
      + " both an armoury and a repair station. Racks line the walls,"
      + " fitted for holding weapons and armours of all kinds. A"
      + " sturdy workbench rests in the center of the room where it"
      + " appears that much work has recently gone into the mending"
      + " of armaments. A corridor leads out of the room to the"
      + " northeast.\n");

    add_item( ({ "armoury", "repair station", "station" }), long);
    add_item( ({ "rack", "racks", "weapon rack", "weapon racks",
                 "armour rack", "armour racks", "wall", "walls",
                 "weapon and armour racks" }),
        "Weapon and armour racks line the walls here, presumably"
      + " having once held a great assortment of arms. Now, there is"
      + " nothing left, and the armoury has been emptied of its"
      + " stock.\n");
    add_item( ({ "workbench", "sturdy workbench", "bench" }),
        "The workbench has seen much use lately. Scattered all over"
      + " its surface are bits of leather and metal links which"
      + " have been put to use repairing armour.\n");
    add_item( ({ "leather", "bits", "bits of leather", "leather bits",
                 "link", "links", "metal", "metal links" }),
        "From the evidence on the workbench, it would seem as if there"
      + " has been a great need to repair a large quantity of armour"
      + " recently.\n");

    add_indoor_items();

    add_exit("outpost02" , "northeast");
} /* create_outpost_inside_room */
