/*
 * /d/Gondor/pelargir/rooms/beacon06.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"


public void	create_pelargir_room();


/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_NORTH);
    set_street_name(STREET_BEACON);
    set_room_type(TYPE_STREET);

    set_extra_desc(
        "The street comes to an end here at the base of the Lighthouse"
      + " of Pelargir, which looms forbodingly against the cloudy"
      + " sky. Far below, the feet of this peninsula are constantly"
      + " jarred by the currents of the River Anduin, which"
      + " stretches as far as the eye can see to the north and"
      + " south.");

    add_item( ({ "lighthouse", "lighthouse of pelargir" }), BSN(
        "Dwarfing everything nearby, the lighthouse of pelargir"
      + " rises majestically from the crown of the peninsula here."
      + " From this close vantage point, the toll that hundreds of"
      + " years weathering the elements has taken on this mighty"
      + " structure is quite evident. Regardless of this, the"
      + " mighty building looks as if it could withstand another"
      + " ten centuries of wind and rain. A doorway leads"
      + " inside the lighthouse."));
    add_item( ({ "doorway", "door", "hinged door", "wooden door",
                 "hinged wooden door" }), BSN(
        "A hinged wooden door opens onto " + STREET_BEACON + " at"
      + " the base of the lighthouse."));
    add_item( ({ "base", "base of the lighthouse" }), BSN(
        "The base of the lighthouse is sunk deeply into the rock"
      + " of the peninsula."));
    add_item( ({ "rock", "rock of the peninsula", "peninsula",
                 "crown", "crown of the peninsula" }), BSN(
        "The street winds to a end here at the easternmost point"
      + " of the peninsula, where the lighthouse of pelargir stands"
      + " tall and silent."));
    add_item( ({ "anduin", "river", "anduin river", "river anduin",
                 "the mighty anduin", "anduin the great",
                 "mighty anduin", "water", "waters" }), BSN(
        "The waters of the mighty River Anduin flow majestically"
      + " around the expanse of the peninsula, far below, where"
      + " the currents jar against the rock with violent force."
      + " Were it not for the beacon of the lighthouse, ships would"
      + " almost certainly meet their end there."));


    add_exit((PELAR_DIR + "test/beacon05"), "west", 0);
    add_exit((PELAR_DIR + "docks/light1"), "in", 0);

} /* create_pelargir_room */
