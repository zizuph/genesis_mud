/*
 *  /d/Cirath/tyr/citizen/std_citizen_district_room.c
 *
 *  Standard room for the Citizens District in which to keep all standard code.
 *
 *  Created by Ardent, 12/01/2005
 */

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_citizen_room()
{
}

// Creating the room.
create_room()
{
   set_short("Standard short room description in Citizens District");
   set_long("Standard long room description in Citizens District.\n");

   add_item(({"sun", "dark sun"}),
       "The scorching Dark Sun burns down on Athas, its glaring radiance "    +
       "dispelling any notion of shadows or darkness. \n");

// Very bright rooms due the very bright Athasian Dark Sun.
   add_prop(ROOM_I_LIGHT, 3);
// It is almost impossible to hide due to the bleakness in which nothing
// can hide, and because of the strong light. Also, Kalak hates sneakers
// and has placed a divination enchantment on the lands that makes it
// impossible to hide anything from his scrying eyes.
// His ban on magic is also in part due to the fact that he fears that
// someone will dispel his enchantments.
   add_prop(ROOM_I_HIDE, -1);

   reset_room();

   create_citizen_room();
}


